/*
 * Copyright 2024 Ian Mitchell VK7IAN
 * Licenced under the GNU GPL Version 3
 *
 * libraries
 *
 * https://github.com/etherkit/Si5351Arduino
 * https://github.com/brianlow/Rotary
 * https://github.com/datacute/Tiny4kOLED
 *
 */
#include <si5351.h>
#include <Tiny4kOLED.h>
#include "Rotary.h"
#include "agc.h"
#include "mic.h"
#include "hardware/pwm.h"
#include "hardware/adc.h"
#include "hardware/vreg.h"

//#define YOUR_CALL "VK7IAN"

#define VERSION_STRING         " V1.1."
#define DEFAULT_FREQUENCY      7100000ul
#define FREQUENCY_MIN          7000000UL
#define FREQUENCY_MAX          7300000UL
#define DEFAULT_STEP           1000ul
#define BUTTON_LONG_PRESS_TIME 800ul
#define SHOW_STEP_TIMEOUT      8000ul
#define TCXO_FREQ              25000000ul
#define LM4875_MUTE            56u
#define LM4875_SHUTDOWN        0u

#define PIN_UNUSED_0   0
#define PIN_TXN        1 // Enable TX mixer (active low)
#define PIN_RXN        2 // Enable RX mixer (active low)
#define PIN_UNUSED_3   3
#define PIN_SDA        4 // I2C
#define PIN_SCL        5 // I2C
#define PIN_TX000H     6 // PWM
#define PIN_TX000L     7 // PWM
#define PIN_TX180H     8 // PWM
#define PIN_TX180L     9 // PWM
#define PIN_UNUSED_10 10
#define PIN_ENCBUT    11 // rotary
#define PIN_ENCB      12 // rotary
#define PIN_ENCA      13 // rotary
#define PIN_UNUSED_14 14
#define PIN_PTT       15 // Mic PTT (active low)
#define PIN_AGCOUT    16 // PWM
#define PIN_TXBIAS    17 // enable TX bias
#define PIN_UNUSED_18 18
#define PIN_UNUSED_19 19
#define PIN_UNUSED_20 20
#define PIN_UNUSED_21 21
#define PIN_UNUSED_22 22
#define PIN_REG       23 // Pico regulator
#define PIN_UNUSED_24 24
#define PIN_UNUSED_25 25
#define PIN_MIC       26 // analog MIC
#define PIN_UNUSED_27 27
#define PIN_AGCIN     28 // analog AGC

#if PIN_MIC == 26U
#define MIC_MUX 0U
#elif PIN_MIC == 27U
#define MIC_MUX 1U
#elif PIN_MIC == 28U
#define MIC_MUX 2U
#elif PIN_MIC == 29U
#define MIC_MUX 3U
#endif

#if PIN_AGCIN == 26U
#define AGC_MUX 0U
#elif PIN_AGCIN == 27U
#define AGC_MUX 1U
#elif PIN_AGCIN == 28U
#define AGC_MUX 2U
#elif PIN_AGCIN == 29U
#define AGC_MUX 3U
#endif

// the PWM simulates a 10 bit DAC using both channels
// resistors on the pin pairs have a ratio of 32:1 (eg 33k and 1k)
// assuming a pin resistance (on average) of 50 ohms (33050/1050 = 31.48)
// since the PWM operates in phase correct mode
// the PWM frequency will be processor clock / 32 / 2 (eg 225Mhz/32/2 = ~3.5MHz)
// v is signed, channel A is the high 5 bits, channel B is the low 5 bits
// need to convert to unsigned and extract the high and low 5 bits
// PWM A is Pin 2 (high bits - 1k resistor)
// PWM B is Pin 3 (low bits - 33k resistor)

#define DAC(pwm,v) pwm_set_both_levels(pwm,((((uint32_t)(v+512UL))>>5)&0x1f),(((uint32_t)(v+512UL))&0x1f))

auto_init_mutex(rotary_mutex);
volatile static uint32_t mic_p_pwm = 0;
volatile static uint32_t mic_n_pwm = 0;
volatile static bool setup_complete = false;

enum radio_mode_t
{
  MODE_iDSB,
  MODE_DSB
};

volatile static struct
{
  int32_t tune;
  uint32_t step;
  uint32_t frequency;
  radio_mode_t mode;
  bool tx_enable;
}
radio =
{
  0,
  DEFAULT_STEP,
  DEFAULT_FREQUENCY,
  MODE_iDSB,
  false
};

Si5351 si5351;
Rotary r = Rotary(PIN_ENCB,PIN_ENCA);

void init_adc(void)
{
  adc_init();
  adc_gpio_init(PIN_MIC);
  adc_gpio_init(PIN_AGCIN);
  adc_select_input(AGC_MUX);
  adc_fifo_setup(true, false, 4, false, false);
  adc_irq_set_enabled(true);
  irq_set_exclusive_handler(ADC_IRQ_FIFO, adc_interrupt_handler);
  irq_set_enabled(ADC_IRQ_FIFO, true);
  adc_run(true);
}

void setup(void)
{
  // run DSP on core 0
  vreg_set_voltage(VREG_VOLTAGE_1_30);
  const uint32_t clksys = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_SYS);

  // set pin modes
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(PIN_TXBIAS,OUTPUT);
  pinMode(PIN_TXN,OUTPUT);
  pinMode(PIN_RXN,OUTPUT);
  pinMode(PIN_PTT,INPUT_PULLUP);
  pinMode(PIN_ENCBUT,INPUT_PULLUP);
  pinMode(PIN_REG,OUTPUT);

  // pin defaults
  // set pico regulator to low noise
  digitalWrite(PIN_REG,HIGH);
  digitalWrite(PIN_TXBIAS,LOW);
  digitalWrite(PIN_TXN,HIGH);
  digitalWrite(PIN_RXN,LOW);
  delay(40);
  digitalWrite(LED_BUILTIN,LOW);

  // set pin function to PWM
  gpio_set_function(PIN_TX000H,GPIO_FUNC_PWM); //  6  PWM
  gpio_set_function(PIN_TX000L,GPIO_FUNC_PWM); //  7  PWM
  gpio_set_function(PIN_TX180H,GPIO_FUNC_PWM); //  8  PWM
  gpio_set_function(PIN_TX180L,GPIO_FUNC_PWM); //  9  PWM

  // get PWM slice connected to each pin pair
  mic_p_pwm = pwm_gpio_to_slice_num(PIN_TX000H);
  mic_n_pwm = pwm_gpio_to_slice_num(PIN_TX180H);

  // set period of 32 cycles
  pwm_set_wrap(mic_p_pwm,31);
  pwm_set_wrap(mic_n_pwm,31);

  // switch to phase correct
  pwm_set_phase_correct(mic_p_pwm,true);
  pwm_set_phase_correct(mic_n_pwm,true);

  // initialise to zero (low)
  DAC(mic_p_pwm,-512L);
  DAC(mic_n_pwm,-512L);

  // set each PWM running
  pwm_set_enabled(mic_p_pwm,true);
  pwm_set_enabled(mic_n_pwm,true);

  // init rotary
  r.begin();

  // init PLL and set default frequency
  radio.frequency = DEFAULT_FREQUENCY;

#ifdef DEBUG_LED
  pinMode(LED_BUILTIN,OUTPUT);
  for (int i=0;i<2;i++)
  {
    digitalWrite(LED_BUILTIN,HIGH);
    delay(10);
    digitalWrite(LED_BUILTIN,LOW);
    delay(250);
  }
#endif

  Wire.setSDA(PIN_SDA);
  Wire.setSCL(PIN_SCL);
  Wire.setClock(400000ul);
  const bool si5351_found = si5351.init(SI5351_CRYSTAL_LOAD_0PF,TCXO_FREQ,0);
  if (!si5351_found)
  {
    for (;;)
    {
      digitalWrite(LED_BUILTIN,HIGH);
      delay(50);
      digitalWrite(LED_BUILTIN,LOW);
      delay(500);
    }
  }
  si5351.drive_strength(SI5351_CLK0,SI5351_DRIVE_8MA);
  const uint64_t f = radio.frequency*SI5351_FREQ_MULT;
  si5351.set_freq(f,SI5351_CLK0);

#ifdef DEBUG_LED
  pinMode(LED_BUILTIN,OUTPUT);
  for (int i=0;i<2;i++)
  {
    digitalWrite(LED_BUILTIN,HIGH);
    delay(50);
    digitalWrite(LED_BUILTIN,LOW);
    delay(250);
  }
#endif

  init_adc();

  // disable Mic in RX mode
  pinMode(PIN_MIC,OUTPUT);
  digitalWrite(PIN_MIC,LOW);

  // OLED bright and rotated
  // note: include file declares the oled object
  oled.begin(64,32,sizeof(tiny4koled_init_64x32br),tiny4koled_init_64x32br);
  oled.enableChargePump();
  oled.setRotation(0);
  oled.setInternalIref(true);
  oled.clear();
  oled.on();
  oled.switchRenderFrame();

  // intro screen
  oled.clear();
  oled.setFont(FONT6X8);
  oled.setCursor(0,0);
  oled.print("iDSB40 TRX");
  char sz_clksys[16] = "";
  memset(sz_clksys,0,sizeof(sz_clksys));
  ultoa(clksys,sz_clksys,10);
  sz_clksys[3] = '\0';
  oled.print(VERSION_STRING);
  oled.print(sz_clksys);
  oled.setCursor(0,1);
#ifdef YOUR_CALL
  oled.setFont(FONT8X16);
  oled.setCursor(0,2);
  oled.print(" ");
  oled.print(YOUR_CALL);
#else
  oled.setFont(FONT8X16);
  oled.setCursor(0,2);
  oled.print(" VK7IAN");
#endif
  oled.switchFrame();
  delay(4000);

  setup_complete = true;
}

void setup1(void)
{
  // run UI on core 1
  // only go to loop1 when setup() has completed
  while (!setup_complete)
  {
    tight_loop_contents();
  }

#ifdef DEBUG_LED
  pinMode(LED_BUILTIN,OUTPUT);
  for (int i=0;i<5;i++)
  {
    digitalWrite(LED_BUILTIN,HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN,LOW);
    delay(250);
  }
#endif
}

void update_display(const uint32_t signal_level = 0u,const bool show_step = false)
{
    char sz_frequency[16] = "";
    memset(sz_frequency,0,sizeof(sz_frequency));
    ultoa(radio.frequency,sz_frequency,10);
    static const uint8_t freq_pos = 3u;
    // 7 digits
    // 7123450 -> 7.123.450
    // 0123456    012345678
    sz_frequency[8] = sz_frequency[6];
    sz_frequency[7] = sz_frequency[5];
    sz_frequency[6] = sz_frequency[4];
    sz_frequency[5] = '.';
    sz_frequency[4] = sz_frequency[3];
    sz_frequency[3] = sz_frequency[2];
    sz_frequency[2] = sz_frequency[1];
    sz_frequency[1] = '.';
    oled.clear();
    oled.setFont(FONT6X8);
    oled.setCursor(freq_pos,0);
    if (show_step)
    {
      oled.write(sz_frequency[0]); // 1 MHz
      oled.write(sz_frequency[1]); // Dot
      oled.write(sz_frequency[2]); // 100 KHz
      oled.write(sz_frequency[3]); // 10 Khz
      if (radio.step==1000) oled.invertOutput(true);
      oled.write(sz_frequency[4]); // 1 Khz
      if (radio.step==1000) oled.invertOutput(false);
      oled.write(sz_frequency[5]); // Dot
      if (radio.step==100) oled.invertOutput(true);
      oled.write(sz_frequency[6]); // 100 Hz
      if (radio.step==100) oled.invertOutput(false);
      if (radio.step==10) oled.invertOutput(true);
      oled.write(sz_frequency[7]); // 10 Hz
      if (radio.step==10) oled.invertOutput(false);
      oled.write(sz_frequency[8]); // 1 Hz
    }
    else
    {
      oled.print(sz_frequency);
    }
    oled.setCursor(0,1);
    oled.print("Mode:");
    switch (radio.mode)
    {
      case MODE_iDSB: oled.print(radio.tx_enable?"*iDSB":" iDSB"); break;
      case MODE_DSB:  oled.print(radio.tx_enable?" *DSB":"  DSB"); break;
    }
    oled.setCursor(0,2);
    oled.print(radio.tx_enable?"-25-50-75-":"-3-5-7-9-+");
    const uint8_t sig = min(signal_level,63);
    oled.bitmap(0, 3, sig, 4, AGC::meter);
    oled.switchFrame();
}

volatile static int16_t adc_value = 0;
volatile static int16_t agc_adc_value = 0;
volatile static int32_t dac_value_p = 0;
volatile static int32_t dac_value_n = 0;
volatile static bool adc_value_ready = false;
volatile static bool agc_value_ready = false;

void adc_interrupt_handler(void)
{
  volatile static uint32_t counter = 0;
  volatile static uint32_t adc_raw = 0;
  if (adc_fifo_get_level()<4u)
  {
    return;
  }
  adc_raw += adc_fifo_get();
  adc_raw += adc_fifo_get();
  adc_raw += adc_fifo_get();
  adc_raw += adc_fifo_get();
  if (counter==4)
  {
    DAC(mic_p_pwm,dac_value_p);
    DAC(mic_n_pwm,dac_value_n);
    adc_value = (int16_t)(adc_raw>>4)-2048;
    adc_value_ready = true;
    adc_raw = 0;
    counter = 0;
  }
  counter++;
}

void loop(void)
{
  // run DSP on core 0
  static bool tx = false;
  if (tx)
  {
    // TX, check if changed to RX
    if (radio.tx_enable)
    {
      if (adc_value_ready)
      {
        adc_value_ready = false;
        int16_t mic = process_mic(adc_value,radio.mode==MODE_iDSB);
        mic = constrain(mic,-512,+511);
        dac_value_p = +mic;
        dac_value_n = -mic;
        agc_adc_value = 0;
      }
    }
    else
    {
      // switched to RX
      pinMode(PIN_MIC,OUTPUT);
      digitalWrite(PIN_MIC,LOW);
      adc_select_input(AGC_MUX);
      tx = false;
    }
  }
  else
  {
    // RX, check if changed to TX
    if (radio.tx_enable)
    {
      // switch to TX
      adc_gpio_init(PIN_MIC);
      adc_select_input(MIC_MUX);
      tx = true;
    }
    else
    {
      if (adc_value_ready)
      {
        adc_value_ready = false;
        agc_adc_value = adc_value;
        agc_value_ready = true;
        // set TX output to zero in receive mode
        dac_value_p = -512;
        dac_value_n = -512;
      }
      // only process rotary in receive mode
      switch (r.process())
      {
        case DIR_CW:
        {
          mutex_enter_blocking(&rotary_mutex);
          radio.tune++;
          mutex_exit(&rotary_mutex);
          break;
        }
        case DIR_CCW:
        {
          mutex_enter_blocking(&rotary_mutex);
          radio.tune--;
          mutex_exit(&rotary_mutex);
          break;
        }
      }
    }
  }
}

void loop1(void)
{
  // run UI on core 1
  static uint32_t old_frequency = radio.frequency;
  static uint32_t agc_continue = 0;
  static uint8_t saved_agc_level = 0;
  static uint32_t show_step = 0;

  // process AGC
  if (agc_value_ready && millis()>agc_continue)
  {
    agc_value_ready = false;
    const uint8_t agc_level = AGC::agc_pwm(agc_adc_value);
    analogWrite(PIN_AGCOUT,agc_level);
    saved_agc_level = agc_level;
  }

  // process button press
  // short press: change step
  // long press: change mode
  enum button_state_t {BUTTON_IDLE,BUTTON_TEST_SHORT,BUTTON_WAIT_RELEASE};
  enum button_action_t {BUTTON_NO_PRESS,BUTTON_SHORT_PRESS,BUTTON_LONG_PRESS};
  static button_state_t button_state = BUTTON_IDLE;
  static uint32_t button_timer = 0;
  button_action_t button_action = BUTTON_NO_PRESS;
  if (!radio.tx_enable)
  {
    switch (button_state)
    {
      case BUTTON_IDLE:
      {
        if (digitalRead(PIN_ENCBUT)==LOW)
        {
          button_state = BUTTON_TEST_SHORT;
          button_timer = millis()+BUTTON_LONG_PRESS_TIME;
          delay(50);
        }
        break;
      }
      case BUTTON_TEST_SHORT:
      {
        const uint32_t now = millis();
        if (digitalRead(PIN_ENCBUT)==HIGH)
        {
          button_state = BUTTON_IDLE;
          if (now<button_timer)
          {
            button_action = BUTTON_SHORT_PRESS;
          }
          delay(50);
          break;
        }
        if (now>button_timer)
        {
          button_state = BUTTON_WAIT_RELEASE;
          button_action = BUTTON_LONG_PRESS;
        }
        break;
      }
      case BUTTON_WAIT_RELEASE:
      {
        if (digitalRead(PIN_ENCBUT)==HIGH)
        {
          button_state = BUTTON_IDLE;
          delay(50);
        }
        break;
      }
    }

    // process botton action
    switch (button_action)
    {
      case BUTTON_SHORT_PRESS:
      {
        show_step = millis() + SHOW_STEP_TIMEOUT;
        switch (radio.step)
        {
          case 1000: radio.step = 100;  break;
          case 100:  radio.step = 10;   break;
          case 10:   radio.step = 1000; break;
        }
        break;
      }
      case BUTTON_LONG_PRESS:
      {
        // toggle iDSB and DSB
        switch (radio.mode)
        {
          case MODE_iDSB: radio.mode = MODE_DSB;  break;
          case MODE_DSB:  radio.mode = MODE_iDSB; break;
        }
        break;
      }
    }

    // process main tuning
    mutex_enter_blocking(&rotary_mutex);
    const int32_t tuning_delta = radio.tune;
    radio.tune = 0;
    mutex_exit(&rotary_mutex);
    radio.frequency = radio.frequency+(tuning_delta * (int32_t)radio.step);
    radio.frequency = radio.frequency/radio.step;
    radio.frequency = radio.frequency*radio.step;
    radio.frequency = constrain(radio.frequency,FREQUENCY_MIN,FREQUENCY_MAX);
    if (radio.frequency!=old_frequency)
    {
      old_frequency = radio.frequency;
      const uint64_t f = radio.frequency*SI5351_FREQ_MULT;
      si5351.set_freq(f,SI5351_CLK0);
    }
  }
 
  // update the display every 50ms
  static uint32_t next_update = 0;
  const uint32_t now = millis();
  if (now>next_update)
  {
    next_update = now + 50ul;
    update_display(AGC::smeter(),now<show_step);
  }

  // check for PTT
  if (digitalRead(PIN_PTT)==LOW)
  {
    // 1. mute the receiver
    // 2. disable detector
    // 3. enable MIC (DSP)
    // 4. enable TX bias

    digitalWrite(LED_BUILTIN,HIGH);

    // mute the receiver
    analogWrite(PIN_AGCOUT,LM4875_SHUTDOWN);
    delay(50);

    // set TX frequency down by 2700 since
    // inverted audio is now at frequency + 1700
    if (radio.mode==MODE_iDSB)
    {
      const uint64_t txf = (radio.frequency-2700) * SI5351_FREQ_MULT;
      si5351.set_freq(txf,SI5351_CLK0);
    }

    // prevent TX/RX feedback
    // *Note, there is an issue with the RP2040 ADC switching circuitry
    pinMode(PIN_AGCIN,OUTPUT);
    digitalWrite(PIN_AGCIN,LOW);

    // disable detector
    digitalWrite(PIN_RXN,HIGH);

    // enable MIC processing
    radio.tx_enable = true;
    update_display();
    delay(10);

    // enable tx mixer and TX bias
    digitalWrite(PIN_TXN,LOW);
    digitalWrite(PIN_TXBIAS,HIGH);
    delay(50);

    // wait for PTT release
    uint32_t mic_peak_level = 0;
    uint32_t mic_level_update = 0;
    uint32_t tx_display_update = 0;
    uint32_t mic_hangtime_update = 0;
    uint32_t tx_debounce = 0;
    while (digitalRead(PIN_PTT)==LOW)
    {
      static const uint32_t MIC_LEVEL_DECAY_RATE = 50ul;
      static const uint32_t MIC_LEVEL_HANG_TIME = 1000ul;
      const uint32_t now = millis();
      const uint32_t mic_level = abs(adc_value)>>5;
      if (mic_level>mic_peak_level)
      {
        mic_peak_level = mic_level;
        mic_level_update = now + MIC_LEVEL_DECAY_RATE;
        mic_hangtime_update = now + MIC_LEVEL_HANG_TIME;
      }
      else
      {
        if (now>mic_hangtime_update)
        {
          if (now>mic_level_update)
          {
            if (mic_peak_level) mic_peak_level--;
            mic_level_update = now + MIC_LEVEL_DECAY_RATE;
          }
        }
      }
      if (now>tx_display_update)
      {
        update_display(mic_peak_level);
        tx_display_update = now + 50ul;
      }
      else
      {
        delayMicroseconds(32);
      }
    }

    // back to receive
    digitalWrite(PIN_TXBIAS,LOW);
    digitalWrite(PIN_TXN,HIGH);
    adc_gpio_init(PIN_AGCIN);
    radio.tx_enable = false;
    delay(20);
    if (radio.mode==MODE_iDSB)
    {
      si5351.set_freq(radio.frequency * SI5351_FREQ_MULT,SI5351_CLK0);
      delay(20);
    }
    digitalWrite(PIN_RXN,LOW);
    digitalWrite(LED_BUILTIN,LOW);
    update_display();
    for (uint32_t ramp=LM4875_MUTE;ramp<saved_agc_level;ramp++)
    {
      // ramp up to AGC level
      analogWrite(PIN_AGCOUT,ramp);
      delay(5);
    }
    agc_continue = millis()+200ul;
  }
}
