This version supports double sideband (DSB), inverse DSB, AM, CW and LSB. Pleae note, the SSB mode is experimental and uses the so called Envelope Elimination and Restoration method. This is not however class E and the quality of audio is not perfect. Also, LSB applies to the transmitted signal only and the receiver remains direct conversion.

## To build in Arduino IDE

### Under Tools, set:
* Board: Raspberry Pi Pico
* CPU speed to 240MHz
* Optimize More (-O2)
* USB Stack: No USB
