/*
 * https://www.arc.id.au/FilterDesign.html
 */

#ifndef DSP_H
#define DSP_H

//#define CW_LEVEL (int16_t)15 // (100mv / 3.3) * 1024 / 2 (200mW)
//#define CW_LEVEL (int16_t)60 // (400mv / 3.3) * 1024 / 2 (2.4W)
#define CW_LEVEL   (int16_t)120 // (800mv / 3.3) * 1024 / 2 (8.0W)
#define SAMPLERATE 31250
#define FIR_LENGTH 256
#define __mac_tap(_h) acc += (_h)*x[i++]

static const int16_t sin2700[] =
{
  32767,
  28056,
  15278,
  -1893,
  -18520,
  -29821,
  -32548,
  -25916,
  -11832,
  5654,
  21514,
  31189,
  31895,
  23430,
  8229,
  -9339,
  -24222,
  -32139,
  -30816,
  -20632,
  -4515,
  12900,
  26606,
  32661,
  29325,
  17557,
  741,
  -16288,
  -28634,
  -32747,
  -27443,
  -14249,
  3043,
  19459,
  30281,
  32395,
  25195,
  10750,
  -6786,
  -22370,
  -31523,
  -31611,
  -22610,
  -7108,
  10438,
  24983,
  32344,
  30405,
  19723,
  3370,
  -13952,
  -27262,
  -32733,
  -28793,
  -16573,
  412,
  17278,
  29177,
  32686,
  26796,
  13202,
  -4188,
  -20375,
  -30702,
  -32202,
  -24442,
  -9654,
  7909,
  23199,
  31818,
  31288,
  21762,
  5978,
  -11525,
  -25713,
  -32509,
  -29956,
  -18791,
  -2222,
  14986,
  27885,
  32765,
  28225,
  15569,
  -1564,
  -18247,
  -29683,
  -32585,
  -26116,
  -12139,
  5329,
  21265,
  31086,
  31969,
  23659,
  8547,
  -9023,
  -23999,
  -32074,
  -30926,
  -20886,
  -4841,
  12596,
  26412,
  32633,
  29471,
  17835,
  1070,
  -16002,
  -28473,
  -32757,
  -27622,
  -14545,
  2715,
  19193,
  30153,
  32443,
  25404,
  11061,
  -6463,
  -22129,
  -31431,
  -31696,
  -22847,
  -7429,
  10126,
  24769,
  32290,
  30526,
  19985,
  3698,
  -13653,
  -27078,
  -32717,
  -28949,
  -16857,
  82,
  16998,
  29026,
  32707,
  26985,
  13503,
  -3862,
  -20116,
  -30586,
  -32261,
  -24660,
  -9969,
  7589,
  22965,
  31738,
  31384,
  22007,
  6302,
  -11216,
  -25508,
  -32466,
  -30088,
  -19060,
  -2550,
  14692,
  27710,
  32760,
  28391,
  15858,
  -1235,
  -17973,
  -29542,
  -32618,
  -26314,
  -12444,
  5004,
  21013,
  30980,
  32040,
  23886,
  8865,
  -8706,
  -23773,
  -32005,
  -31034,
  -21139,
  -5167,
  12292,
  26216,
  32602,
  29613,
  18110,
  1400,
  -15713,
  -28308,
  -32763,
  -27798,
  -14839,
  2386,
  18925,
  30023,
  32488,
  25611,
  11370,
  -6140,
  -21885,
  -31337,
  -31778,
  -23082,
  -7749,
  9812,
  24552,
  32232,
  30644,
  20245,
  4025,
  -13353,
  -26891,
  -32697,
  -29102,
  -17138,
  -247,
  16715,
  28871,
  32726,
  27170,
  13802,
  -3534,
  -19855,
  -30466,
  -32317,
  -24876,
  -10282,
  7268,
  22729,
  31654,
  31477,
  22250,
  6625,
  -10905,
  -25300,
  -32419,
  -30217,
  -19327,
  -2879,
  14397,
  27533,
  32752,
  28554,
  16145,
  -906,
  -17696,
  -29398,
  -32647,
  -26509,
  -12748,
  4678,
  20759,
  30871,
  32107,
  24110,
  9181,
  -8388,
  -23545,
  -31932,
  -31138,
  -21390,
  -5492,
  11986,
  26017,
  32567,
  29753,
  18384,
  1729,
  -15424,
  -28141,
  -32767,
  -27971,
  -15132,
  2057,
  18655,
  29889,
  32529,
  25815,
  11679,
  -5816,
  -21638,
  -31239,
  -31857,
  -23315,
  -8069,
  9497,
  24332,
  32171,
  30759,
  20503,
  4352,
  -13051,
  -26701,
  -32674,
  -29251,
  -17418,
  -576,
  16431,
  28714,
  32741,
  27353,
  14100,
  -3207,
  -19592,
  -30343,
  -32370,
  -25089,
  -10594,
  6947,
  22491,
  31567,
  31567,
  22491,
  6947,
  -10594,
  -25089,
  -32370,
  -30343,
  -19592,
  -3207,
  14100,
  27353,
  32741,
  28714,
  16431,
  -576,
  -17418,
  -29251,
  -32674,
  -26701,
  -13051,
  4352,
  20503,
  30759,
  32171,
  24332,
  9497,
  -8069,
  -23315,
  -31857,
  -31239,
  -21638,
  -5816,
  11679,
  25815,
  32529,
  29889,
  18655,
  2057,
  -15132,
  -27971,
  -32767,
  -28141,
  -15424,
  1729,
  18384,
  29753,
  32567,
  26017,
  11986,
  -5492,
  -21390,
  -31138,
  -31932,
  -23545,
  -8388,
  9181,
  24110,
  32107,
  30871,
  20759,
  4678,
  -12748,
  -26509,
  -32647,
  -29398,
  -17696,
  -906,
  16145,
  28554,
  32752,
  27533,
  14397,
  -2879,
  -19327,
  -30217,
  -32419,
  -25300,
  -10905,
  6625,
  22250,
  31477,
  31654,
  22729,
  7268,
  -10282,
  -24876,
  -32317,
  -30466,
  -19855,
  -3534,
  13802,
  27170,
  32726,
  28871,
  16715,
  -247,
  -17138,
  -29102,
  -32697,
  -26891,
  -13353,
  4025,
  20245,
  30644,
  32232,
  24552,
  9812,
  -7749,
  -23082,
  -31778,
  -31337,
  -21885,
  -6140,
  11370,
  25611,
  32488,
  30023,
  18925,
  2386,
  -14839,
  -27798,
  -32763,
  -28308,
  -15713,
  1400,
  18110,
  29613,
  32602,
  26216,
  12292,
  -5167,
  -21139,
  -31034,
  -32005,
  -23773,
  -8706,
  8865,
  23886,
  32040,
  30980,
  21013,
  5004,
  -12444,
  -26314,
  -32618,
  -29542,
  -17973,
  -1235,
  15858,
  28391,
  32760,
  27710,
  14692,
  -2550,
  -19060,
  -30088,
  -32466,
  -25508,
  -11216,
  6302,
  22007,
  31384,
  31738,
  22965,
  7589,
  -9969,
  -24660,
  -32261,
  -30586,
  -20116,
  -3862,
  13503,
  26985,
  32707,
  29026,
  16998,
  82,
  -16857,
  -28949,
  -32717,
  -27078,
  -13653,
  3698,
  19985,
  30526,
  32290,
  24769,
  10126,
  -7429,
  -22847,
  -31696,
  -31431,
  -22129,
  -6463,
  11061,
  25404,
  32443,
  30153,
  19193,
  2715,
  -14545,
  -27622,
  -32757,
  -28473,
  -16002,
  1070,
  17835,
  29471,
  32633,
  26412,
  12596,
  -4841,
  -20886,
  -30926,
  -32074,
  -23999,
  -9023,
  8547,
  23659,
  31969,
  31086,
  21265,
  5329,
  -12139,
  -26116,
  -32585,
  -29683,
  -18247,
  -1564,
  15569,
  28225,
  32765,
  27885,
  14986,
  -2222,
  -18791,
  -29956,
  -32509,
  -25713,
  -11525,
  5978,
  21762,
  31288,
  31818,
  23199,
  7909,
  -9654,
  -24442,
  -32202,
  -30702,
  -20375,
  -4188,
  13202,
  26796,
  32686,
  29177,
  17278,
  412,
  -16573,
  -28793,
  -32733,
  -27262,
  -13952,
  3370,
  19723,
  30405,
  32344,
  24983,
  10438,
  -7108,
  -22610,
  -31611,
  -31523,
  -22370,
  -6786,
  10750,
  25195,
  32395,
  30281,
  19459,
  3043,
  -14249,
  -27443,
  -32747,
  -28634,
  -16288,
  741,
  17557,
  29325,
  32661,
  26606,
  12900,
  -4515,
  -20632,
  -30816,
  -32139,
  -24222,
  -9339,
  8229,
  23430,
  31895,
  31189,
  21514,
  5654,
  -11832,
  -25916,
  -32548,
  -29821,
  -18520,
  -1893,
  15278,
  28056
};
static const int32_t sin2700_size = sizeof(sin2700) / sizeof(int16_t);

static const int16_t __not_in_flash_func(lpf_2400)(const int16_t sample)
{
   // 31250 sample rate
   // 127 taps
   // 60dB
   static int32_t x[FIR_LENGTH] = { 0 };
   static uint8_t sample_index = 0;
   uint8_t i = sample_index;
   x[sample_index--] = sample;
   int32_t acc = 0;
   __mac_tap(-3);
   __mac_tap(-5);
   __mac_tap(-6);
   __mac_tap(-5);
   __mac_tap(-2);
   __mac_tap(2);
   __mac_tap(7);
   __mac_tap(12);
   __mac_tap(15);
   __mac_tap(14);
   __mac_tap(8);
   __mac_tap(-1);
   __mac_tap(-14);
   __mac_tap(-26);
   __mac_tap(-34);
   __mac_tap(-35);
   __mac_tap(-27);
   __mac_tap(-10);
   __mac_tap(14);
   __mac_tap(39);
   __mac_tap(59);
   __mac_tap(68);
   __mac_tap(60);
   __mac_tap(36);
   __mac_tap(-3);
   __mac_tap(-49);
   __mac_tap(-91);
   __mac_tap(-117);
   __mac_tap(-118);
   __mac_tap(-89);
   __mac_tap(-32);
   __mac_tap(42);
   __mac_tap(118);
   __mac_tap(177);
   __mac_tap(201);
   __mac_tap(177);
   __mac_tap(105);
   __mac_tap(-6);
   __mac_tap(-133);
   __mac_tap(-247);
   __mac_tap(-318);
   __mac_tap(-320);
   __mac_tap(-242);
   __mac_tap(-90);
   __mac_tap(109);
   __mac_tap(315);
   __mac_tap(476);
   __mac_tap(546);
   __mac_tap(489);
   __mac_tap(298);
   __mac_tap(-8);
   __mac_tap(-375);
   __mac_tap(-726);
   __mac_tap(-972);
   __mac_tap(-1026);
   __mac_tap(-824);
   __mac_tap(-338);
   __mac_tap(414);
   __mac_tap(1367);
   __mac_tap(2415);
   __mac_tap(3430);
   __mac_tap(4276);
   __mac_tap(4836);
   __mac_tap(5033);
   __mac_tap(4836);
   __mac_tap(4276);
   __mac_tap(3430);
   __mac_tap(2415);
   __mac_tap(1367);
   __mac_tap(414);
   __mac_tap(-338);
   __mac_tap(-824);
   __mac_tap(-1026);
   __mac_tap(-972);
   __mac_tap(-726);
   __mac_tap(-375);
   __mac_tap(-8);
   __mac_tap(298);
   __mac_tap(489);
   __mac_tap(546);
   __mac_tap(476);
   __mac_tap(315);
   __mac_tap(109);
   __mac_tap(-90);
   __mac_tap(-242);
   __mac_tap(-320);
   __mac_tap(-318);
   __mac_tap(-247);
   __mac_tap(-133);
   __mac_tap(-6);
   __mac_tap(105);
   __mac_tap(177);
   __mac_tap(201);
   __mac_tap(177);
   __mac_tap(118);
   __mac_tap(42);
   __mac_tap(-32);
   __mac_tap(-89);
   __mac_tap(-118);
   __mac_tap(-117);
   __mac_tap(-91);
   __mac_tap(-49);
   __mac_tap(-3);
   __mac_tap(36);
   __mac_tap(60);
   __mac_tap(68);
   __mac_tap(59);
   __mac_tap(39);
   __mac_tap(14);
   __mac_tap(-10);
   __mac_tap(-27);
   __mac_tap(-35);
   __mac_tap(-34);
   __mac_tap(-26);
   __mac_tap(-14);
   __mac_tap(-1);
   __mac_tap(8);
   __mac_tap(14);
   __mac_tap(15);
   __mac_tap(12);
   __mac_tap(7);
   __mac_tap(2);
   __mac_tap(-2);
   __mac_tap(-5);
   __mac_tap(-6);
   __mac_tap(-5);
   __mac_tap(-3);
   return (int16_t)(acc >> 15);
}

static const int16_t __not_in_flash_func(lpf_2700)(const int16_t sample)
{
   // 31250 sample rate
   // 127 taps
   // 50dB
   static int32_t x[FIR_LENGTH] = { 0 };
   static uint8_t sample_index = 0;
   uint8_t i = sample_index;
   x[sample_index--] = sample;
   int32_t acc = 0;
  __mac_tap(3);
  __mac_tap(8);
  __mac_tap(12);
  __mac_tap(13);
  __mac_tap(9);
  __mac_tap(1);
  __mac_tap(-11);
  __mac_tap(-22);
  __mac_tap(-28);
  __mac_tap(-27);
  __mac_tap(-17);
  __mac_tap(1);
  __mac_tap(23);
  __mac_tap(42);
  __mac_tap(50);
  __mac_tap(44);
  __mac_tap(22);
  __mac_tap(-11);
  __mac_tap(-47);
  __mac_tap(-75);
  __mac_tap(-84);
  __mac_tap(-67);
  __mac_tap(-27);
  __mac_tap(29);
  __mac_tap(84);
  __mac_tap(121);
  __mac_tap(125);
  __mac_tap(91);
  __mac_tap(23);
  __mac_tap(-63);
  __mac_tap(-142);
  __mac_tap(-188);
  __mac_tap(-182);
  __mac_tap(-118);
  __mac_tap(-9);
  __mac_tap(119);
  __mac_tap(228);
  __mac_tap(281);
  __mac_tap(254);
  __mac_tap(143);
  __mac_tap(-28);
  __mac_tap(-216);
  __mac_tap(-364);
  __mac_tap(-421);
  __mac_tap(-355);
  __mac_tap(-167);
  __mac_tap(103);
  __mac_tap(385);
  __mac_tap(594);
  __mac_tap(652);
  __mac_tap(514);
  __mac_tap(185);
  __mac_tap(-274);
  __mac_tap(-748);
  __mac_tap(-1096);
  __mac_tap(-1178);
  __mac_tap(-890);
  __mac_tap(-197);
  __mac_tap(853);
  __mac_tap(2133);
  __mac_tap(3455);
  __mac_tap(4604);
  __mac_tap(5385);
  __mac_tap(5662);
  __mac_tap(5385);
  __mac_tap(4604);
  __mac_tap(3455);
  __mac_tap(2133);
  __mac_tap(853);
  __mac_tap(-197);
  __mac_tap(-890);
  __mac_tap(-1178);
  __mac_tap(-1096);
  __mac_tap(-748);
  __mac_tap(-274);
  __mac_tap(185);
  __mac_tap(514);
  __mac_tap(652);
  __mac_tap(594);
  __mac_tap(385);
  __mac_tap(103);
  __mac_tap(-167);
  __mac_tap(-355);
  __mac_tap(-421);
  __mac_tap(-364);
  __mac_tap(-216);
  __mac_tap(-28);
  __mac_tap(143);
  __mac_tap(254);
  __mac_tap(281);
  __mac_tap(228);
  __mac_tap(119);
  __mac_tap(-9);
  __mac_tap(-118);
  __mac_tap(-182);
  __mac_tap(-188);
  __mac_tap(-142);
  __mac_tap(-63);
  __mac_tap(23);
  __mac_tap(91);
  __mac_tap(125);
  __mac_tap(121);
  __mac_tap(84);
  __mac_tap(29);
  __mac_tap(-27);
  __mac_tap(-67);
  __mac_tap(-84);
  __mac_tap(-75);
  __mac_tap(-47);
  __mac_tap(-11);
  __mac_tap(22);
  __mac_tap(44);
  __mac_tap(50);
  __mac_tap(42);
  __mac_tap(23);
  __mac_tap(1);
  __mac_tap(-17);
  __mac_tap(-27);
  __mac_tap(-28);
  __mac_tap(-22);
  __mac_tap(-11);
  __mac_tap(1);
  __mac_tap(9);
  __mac_tap(13);
  __mac_tap(12);
  __mac_tap(8);
  __mac_tap(3);
   return (int16_t)(acc >> 15);
}

static const int16_t __not_in_flash_func(lpf_2500)(const int16_t sample)
{
   // 31250 sample rate
   // 201 taps
   // 60dB
   static int32_t x[FIR_LENGTH] = { 0 };
   static uint8_t sample_index = 0;
   uint8_t i = sample_index;
   x[sample_index--] = sample;
   int32_t acc = 0;
  __mac_tap(0);
  __mac_tap(-2);
  __mac_tap(-3);
  __mac_tap(-4);
  __mac_tap(-4);
  __mac_tap(-3);
  __mac_tap(-1);
  __mac_tap(2);
  __mac_tap(4);
  __mac_tap(6);
  __mac_tap(7);
  __mac_tap(5);
  __mac_tap(2);
  __mac_tap(-3);
  __mac_tap(-8);
  __mac_tap(-12);
  __mac_tap(-13);
  __mac_tap(-11);
  __mac_tap(-6);
  __mac_tap(2);
  __mac_tap(10);
  __mac_tap(17);
  __mac_tap(20);
  __mac_tap(18);
  __mac_tap(11);
  __mac_tap(0);
  __mac_tap(-14);
  __mac_tap(-25);
  __mac_tap(-32);
  __mac_tap(-31);
  __mac_tap(-21);
  __mac_tap(-5);
  __mac_tap(14);
  __mac_tap(32);
  __mac_tap(44);
  __mac_tap(45);
  __mac_tap(34);
  __mac_tap(13);
  __mac_tap(-15);
  __mac_tap(-41);
  __mac_tap(-61);
  __mac_tap(-66);
  __mac_tap(-55);
  __mac_tap(-28);
  __mac_tap(9);
  __mac_tap(48);
  __mac_tap(78);
  __mac_tap(90);
  __mac_tap(80);
  __mac_tap(48);
  __mac_tap(0);
  __mac_tap(-54);
  __mac_tap(-99);
  __mac_tap(-122);
  __mac_tap(-116);
  __mac_tap(-80);
  __mac_tap(-18);
  __mac_tap(54);
  __mac_tap(119);
  __mac_tap(159);
  __mac_tap(162);
  __mac_tap(122);
  __mac_tap(46);
  __mac_tap(-49);
  __mac_tap(-141);
  __mac_tap(-206);
  __mac_tap(-223);
  __mac_tap(-183);
  __mac_tap(-92);
  __mac_tap(32);
  __mac_tap(161);
  __mac_tap(261);
  __mac_tap(303);
  __mac_tap(269);
  __mac_tap(162);
  __mac_tap(0);
  __mac_tap(-181);
  __mac_tap(-334);
  __mac_tap(-418);
  __mac_tap(-401);
  __mac_tap(-277);
  __mac_tap(-63);
  __mac_tap(196);
  __mac_tap(438);
  __mac_tap(599);
  __mac_tap(624);
  __mac_tap(484);
  __mac_tap(191);
  __mac_tap(-209);
  __mac_tap(-630);
  __mac_tap(-967);
  __mac_tap(-1115);
  __mac_tap(-989);
  __mac_tap(-542);
  __mac_tap(215);
  __mac_tap(1218);
  __mac_tap(2349);
  __mac_tap(3461);
  __mac_tap(4398);
  __mac_tap(5023);
  __mac_tap(5242);
  __mac_tap(5023);
  __mac_tap(4398);
  __mac_tap(3461);
  __mac_tap(2349);
  __mac_tap(1218);
  __mac_tap(215);
  __mac_tap(-542);
  __mac_tap(-989);
  __mac_tap(-1115);
  __mac_tap(-967);
  __mac_tap(-630);
  __mac_tap(-209);
  __mac_tap(191);
  __mac_tap(484);
  __mac_tap(624);
  __mac_tap(599);
  __mac_tap(438);
  __mac_tap(196);
  __mac_tap(-63);
  __mac_tap(-277);
  __mac_tap(-401);
  __mac_tap(-418);
  __mac_tap(-334);
  __mac_tap(-181);
  __mac_tap(0);
  __mac_tap(162);
  __mac_tap(269);
  __mac_tap(303);
  __mac_tap(261);
  __mac_tap(161);
  __mac_tap(32);
  __mac_tap(-92);
  __mac_tap(-183);
  __mac_tap(-223);
  __mac_tap(-206);
  __mac_tap(-141);
  __mac_tap(-49);
  __mac_tap(46);
  __mac_tap(122);
  __mac_tap(162);
  __mac_tap(159);
  __mac_tap(119);
  __mac_tap(54);
  __mac_tap(-18);
  __mac_tap(-80);
  __mac_tap(-116);
  __mac_tap(-122);
  __mac_tap(-99);
  __mac_tap(-54);
  __mac_tap(0);
  __mac_tap(48);
  __mac_tap(80);
  __mac_tap(90);
  __mac_tap(78);
  __mac_tap(48);
  __mac_tap(9);
  __mac_tap(-28);
  __mac_tap(-55);
  __mac_tap(-66);
  __mac_tap(-61);
  __mac_tap(-41);
  __mac_tap(-15);
  __mac_tap(13);
  __mac_tap(34);
  __mac_tap(45);
  __mac_tap(44);
  __mac_tap(32);
  __mac_tap(14);
  __mac_tap(-5);
  __mac_tap(-21);
  __mac_tap(-31);
  __mac_tap(-32);
  __mac_tap(-25);
  __mac_tap(-14);
  __mac_tap(0);
  __mac_tap(11);
  __mac_tap(18);
  __mac_tap(20);
  __mac_tap(17);
  __mac_tap(10);
  __mac_tap(2);
  __mac_tap(-6);
  __mac_tap(-11);
  __mac_tap(-13);
  __mac_tap(-12);
  __mac_tap(-8);
  __mac_tap(-3);
  __mac_tap(2);
  __mac_tap(5);
  __mac_tap(7);
  __mac_tap(6);
  __mac_tap(4);
  __mac_tap(2);
  __mac_tap(-1);
  __mac_tap(-3);
  __mac_tap(-4);
  __mac_tap(-4);
  __mac_tap(-3);
  __mac_tap(-2);
  __mac_tap(0);
   return (int16_t)(acc >> 15);
}

static const int16_t __not_in_flash_func(hpf_300)(const int16_t sample)
{
   // 31250 sample rate
   // 201 taps
   // 40dB
   static int32_t x[FIR_LENGTH] = { 0 };
   static uint8_t sample_index = 0;
   uint8_t i = sample_index;
   x[sample_index--] = sample;
   int32_t acc = 0;
  __mac_tap(3);
  __mac_tap(5);
  __mac_tap(6);
  __mac_tap(7);
  __mac_tap(9);
  __mac_tap(11);
  __mac_tap(12);
  __mac_tap(14);
  __mac_tap(16);
  __mac_tap(18);
  __mac_tap(21);
  __mac_tap(23);
  __mac_tap(25);
  __mac_tap(27);
  __mac_tap(30);
  __mac_tap(32);
  __mac_tap(35);
  __mac_tap(37);
  __mac_tap(40);
  __mac_tap(42);
  __mac_tap(44);
  __mac_tap(47);
  __mac_tap(49);
  __mac_tap(51);
  __mac_tap(53);
  __mac_tap(54);
  __mac_tap(56);
  __mac_tap(57);
  __mac_tap(58);
  __mac_tap(59);
  __mac_tap(60);
  __mac_tap(60);
  __mac_tap(60);
  __mac_tap(60);
  __mac_tap(59);
  __mac_tap(58);
  __mac_tap(56);
  __mac_tap(54);
  __mac_tap(52);
  __mac_tap(49);
  __mac_tap(46);
  __mac_tap(42);
  __mac_tap(37);
  __mac_tap(32);
  __mac_tap(27);
  __mac_tap(21);
  __mac_tap(14);
  __mac_tap(7);
  __mac_tap(-1);
  __mac_tap(-10);
  __mac_tap(-18);
  __mac_tap(-28);
  __mac_tap(-38);
  __mac_tap(-49);
  __mac_tap(-60);
  __mac_tap(-72);
  __mac_tap(-84);
  __mac_tap(-97);
  __mac_tap(-110);
  __mac_tap(-124);
  __mac_tap(-138);
  __mac_tap(-152);
  __mac_tap(-167);
  __mac_tap(-183);
  __mac_tap(-198);
  __mac_tap(-214);
  __mac_tap(-231);
  __mac_tap(-247);
  __mac_tap(-264);
  __mac_tap(-280);
  __mac_tap(-297);
  __mac_tap(-314);
  __mac_tap(-331);
  __mac_tap(-348);
  __mac_tap(-365);
  __mac_tap(-381);
  __mac_tap(-398);
  __mac_tap(-414);
  __mac_tap(-430);
  __mac_tap(-445);
  __mac_tap(-461);
  __mac_tap(-476);
  __mac_tap(-490);
  __mac_tap(-504);
  __mac_tap(-517);
  __mac_tap(-530);
  __mac_tap(-542);
  __mac_tap(-554);
  __mac_tap(-564);
  __mac_tap(-575);
  __mac_tap(-584);
  __mac_tap(-592);
  __mac_tap(-600);
  __mac_tap(-607);
  __mac_tap(-613);
  __mac_tap(-618);
  __mac_tap(-622);
  __mac_tap(-625);
  __mac_tap(-628);
  __mac_tap(-629);
  __mac_tap(32138);
  __mac_tap(-629);
  __mac_tap(-628);
  __mac_tap(-625);
  __mac_tap(-622);
  __mac_tap(-618);
  __mac_tap(-613);
  __mac_tap(-607);
  __mac_tap(-600);
  __mac_tap(-592);
  __mac_tap(-584);
  __mac_tap(-575);
  __mac_tap(-564);
  __mac_tap(-554);
  __mac_tap(-542);
  __mac_tap(-530);
  __mac_tap(-517);
  __mac_tap(-504);
  __mac_tap(-490);
  __mac_tap(-476);
  __mac_tap(-461);
  __mac_tap(-445);
  __mac_tap(-430);
  __mac_tap(-414);
  __mac_tap(-398);
  __mac_tap(-381);
  __mac_tap(-365);
  __mac_tap(-348);
  __mac_tap(-331);
  __mac_tap(-314);
  __mac_tap(-297);
  __mac_tap(-280);
  __mac_tap(-264);
  __mac_tap(-247);
  __mac_tap(-231);
  __mac_tap(-214);
  __mac_tap(-198);
  __mac_tap(-183);
  __mac_tap(-167);
  __mac_tap(-152);
  __mac_tap(-138);
  __mac_tap(-124);
  __mac_tap(-110);
  __mac_tap(-97);
  __mac_tap(-84);
  __mac_tap(-72);
  __mac_tap(-60);
  __mac_tap(-49);
  __mac_tap(-38);
  __mac_tap(-28);
  __mac_tap(-18);
  __mac_tap(-10);
  __mac_tap(-1);
  __mac_tap(7);
  __mac_tap(14);
  __mac_tap(21);
  __mac_tap(27);
  __mac_tap(32);
  __mac_tap(37);
  __mac_tap(42);
  __mac_tap(46);
  __mac_tap(49);
  __mac_tap(52);
  __mac_tap(54);
  __mac_tap(56);
  __mac_tap(58);
  __mac_tap(59);
  __mac_tap(60);
  __mac_tap(60);
  __mac_tap(60);
  __mac_tap(60);
  __mac_tap(59);
  __mac_tap(58);
  __mac_tap(57);
  __mac_tap(56);
  __mac_tap(54);
  __mac_tap(53);
  __mac_tap(51);
  __mac_tap(49);
  __mac_tap(47);
  __mac_tap(44);
  __mac_tap(42);
  __mac_tap(40);
  __mac_tap(37);
  __mac_tap(35);
  __mac_tap(32);
  __mac_tap(30);
  __mac_tap(27);
  __mac_tap(25);
  __mac_tap(23);
  __mac_tap(21);
  __mac_tap(18);
  __mac_tap(16);
  __mac_tap(14);
  __mac_tap(12);
  __mac_tap(11);
  __mac_tap(9);
  __mac_tap(7);
  __mac_tap(6);
  __mac_tap(5);
  __mac_tap(3);
   return (int16_t)(acc >> 15);
}

static const int16_t __not_in_flash_func(lpf_SSB_2400)(const int16_t sample)
{
  // 31250
  // Taps: 51
  // Att: 50
  static int32_t x[FIR_LENGTH] = { 0 };
  static uint8_t sample_index = 0;
  uint8_t i = sample_index;
  x[sample_index--] = sample;
  int32_t acc = 0;
  __mac_tap(-12);
  __mac_tap(-30);
  __mac_tap(-50);
  __mac_tap(-63);
  __mac_tap(-58);
  __mac_tap(-26);
  __mac_tap(36);
  __mac_tap(119);
  __mac_tap(203);
  __mac_tap(261);
  __mac_tap(258);
  __mac_tap(172);
  __mac_tap(-5);
  __mac_tap(-253);
  __mac_tap(-524);
  __mac_tap(-745);
  __mac_tap(-828);
  __mac_tap(-697);
  __mac_tap(-298);
  __mac_tap(377);
  __mac_tap(1281);
  __mac_tap(2318);
  __mac_tap(3352);
  __mac_tap(4232);
  __mac_tap(4824);
  __mac_tap(5033);
  __mac_tap(4824);
  __mac_tap(4232);
  __mac_tap(3352);
  __mac_tap(2318);
  __mac_tap(1281);
  __mac_tap(377);
  __mac_tap(-298);
  __mac_tap(-697);
  __mac_tap(-828);
  __mac_tap(-745);
  __mac_tap(-524);
  __mac_tap(-253);
  __mac_tap(-5);
  __mac_tap(172);
  __mac_tap(258);
  __mac_tap(261);
  __mac_tap(203);
  __mac_tap(119);
  __mac_tap(36);
  __mac_tap(-26);
  __mac_tap(-58);
  __mac_tap(-63);
  __mac_tap(-50);
  __mac_tap(-30);
  __mac_tap(-12);
   return (int16_t)(acc >> 15);
}

static const int16_t __not_in_flash_func(lpf_fs4)(const int16_t sample)
{
  // 31250
  // Taps: 199
  // Att: 45
  static int32_t x[FIR_LENGTH] = { 0 };
  static uint8_t sample_index = 0;
  uint8_t i = sample_index;
  x[sample_index--] = sample;
  int32_t acc = 0;
  __mac_tap(-10);
  __mac_tap(0);
  __mac_tap(11);
  __mac_tap(0);
  __mac_tap(-14);
  __mac_tap(0);
  __mac_tap(15);
  __mac_tap(0);
  __mac_tap(-18);
  __mac_tap(0);
  __mac_tap(20);
  __mac_tap(0);
  __mac_tap(-24);
  __mac_tap(0);
  __mac_tap(25);
  __mac_tap(0);
  __mac_tap(-30);
  __mac_tap(0);
  __mac_tap(32);
  __mac_tap(0);
  __mac_tap(-37);
  __mac_tap(0);
  __mac_tap(40);
  __mac_tap(0);
  __mac_tap(-45);
  __mac_tap(0);
  __mac_tap(49);
  __mac_tap(0);
  __mac_tap(-54);
  __mac_tap(0);
  __mac_tap(59);
  __mac_tap(0);
  __mac_tap(-65);
  __mac_tap(0);
  __mac_tap(70);
  __mac_tap(0);
  __mac_tap(-78);
  __mac_tap(0);
  __mac_tap(83);
  __mac_tap(0);
  __mac_tap(-92);
  __mac_tap(0);
  __mac_tap(99);
  __mac_tap(0);
  __mac_tap(-108);
  __mac_tap(0);
  __mac_tap(116);
  __mac_tap(0);
  __mac_tap(-127);
  __mac_tap(0);
  __mac_tap(136);
  __mac_tap(0);
  __mac_tap(-148);
  __mac_tap(0);
  __mac_tap(160);
  __mac_tap(0);
  __mac_tap(-174);
  __mac_tap(0);
  __mac_tap(187);
  __mac_tap(0);
  __mac_tap(-204);
  __mac_tap(0);
  __mac_tap(220);
  __mac_tap(0);
  __mac_tap(-240);
  __mac_tap(0);
  __mac_tap(260);
  __mac_tap(0);
  __mac_tap(-284);
  __mac_tap(0);
  __mac_tap(309);
  __mac_tap(0);
  __mac_tap(-340);
  __mac_tap(0);
  __mac_tap(373);
  __mac_tap(0);
  __mac_tap(-413);
  __mac_tap(0);
  __mac_tap(459);
  __mac_tap(0);
  __mac_tap(-516);
  __mac_tap(0);
  __mac_tap(583);
  __mac_tap(0);
  __mac_tap(-669);
  __mac_tap(0);
  __mac_tap(778);
  __mac_tap(0);
  __mac_tap(-929);
  __mac_tap(0);
  __mac_tap(1142);
  __mac_tap(0);
  __mac_tap(-1478);
  __mac_tap(0);
  __mac_tap(2076);
  __mac_tap(0);
  __mac_tap(-3472);
  __mac_tap(0);
  __mac_tap(10428);
  __mac_tap(16384);
  __mac_tap(10428);
  __mac_tap(0);
  __mac_tap(-3472);
  __mac_tap(0);
  __mac_tap(2076);
  __mac_tap(0);
  __mac_tap(-1478);
  __mac_tap(0);
  __mac_tap(1142);
  __mac_tap(0);
  __mac_tap(-929);
  __mac_tap(0);
  __mac_tap(778);
  __mac_tap(0);
  __mac_tap(-669);
  __mac_tap(0);
  __mac_tap(583);
  __mac_tap(0);
  __mac_tap(-516);
  __mac_tap(0);
  __mac_tap(459);
  __mac_tap(0);
  __mac_tap(-413);
  __mac_tap(0);
  __mac_tap(373);
  __mac_tap(0);
  __mac_tap(-340);
  __mac_tap(0);
  __mac_tap(309);
  __mac_tap(0);
  __mac_tap(-284);
  __mac_tap(0);
  __mac_tap(260);
  __mac_tap(0);
  __mac_tap(-240);
  __mac_tap(0);
  __mac_tap(220);
  __mac_tap(0);
  __mac_tap(-204);
  __mac_tap(0);
  __mac_tap(187);
  __mac_tap(0);
  __mac_tap(-174);
  __mac_tap(0);
  __mac_tap(160);
  __mac_tap(0);
  __mac_tap(-148);
  __mac_tap(0);
  __mac_tap(136);
  __mac_tap(0);
  __mac_tap(-127);
  __mac_tap(0);
  __mac_tap(116);
  __mac_tap(0);
  __mac_tap(-108);
  __mac_tap(0);
  __mac_tap(99);
  __mac_tap(0);
  __mac_tap(-92);
  __mac_tap(0);
  __mac_tap(83);
  __mac_tap(0);
  __mac_tap(-78);
  __mac_tap(0);
  __mac_tap(70);
  __mac_tap(0);
  __mac_tap(-65);
  __mac_tap(0);
  __mac_tap(59);
  __mac_tap(0);
  __mac_tap(-54);
  __mac_tap(0);
  __mac_tap(49);
  __mac_tap(0);
  __mac_tap(-45);
  __mac_tap(0);
  __mac_tap(40);
  __mac_tap(0);
  __mac_tap(-37);
  __mac_tap(0);
  __mac_tap(32);
  __mac_tap(0);
  __mac_tap(-30);
  __mac_tap(0);
  __mac_tap(25);
  __mac_tap(0);
  __mac_tap(-24);
  __mac_tap(0);
  __mac_tap(20);
  __mac_tap(0);
  __mac_tap(-18);
  __mac_tap(0);
  __mac_tap(15);
  __mac_tap(0);
  __mac_tap(-14);
  __mac_tap(0);
  __mac_tap(11);
  __mac_tap(0);
  __mac_tap(-10);
  return (int16_t)(acc >> 15);
}

static const int16_t __not_in_flash_func(lpf_fs4_i)(const int16_t sample)
{
  // 31250
  // Taps: 15
  // Att: 60db
  static int32_t x[FIR_LENGTH] = { 0 };
  static uint8_t sample_index = 0;
  uint8_t i = sample_index;
  x[sample_index--] = sample;
  int32_t acc = 0;
  __mac_tap(-31);
  __mac_tap(0);
  __mac_tap(462);
  __mac_tap(0);
  __mac_tap(-2127);
  __mac_tap(0);
  __mac_tap(9896);
  __mac_tap(16384);
  __mac_tap(9896);
  __mac_tap(0);
  __mac_tap(-2127);
  __mac_tap(0);
  __mac_tap(462);
  __mac_tap(0);
  __mac_tap(-31);
  return (int16_t)(acc >> 15);
}

static const int16_t __not_in_flash_func(lpf_fs4_q)(const int16_t sample)
{
  // 31250
  // Taps: 15
  // Att: 60db
  static int32_t x[FIR_LENGTH] = { 0 };
  static uint8_t sample_index = 0;
  uint8_t i = sample_index;
  x[sample_index--] = sample;
  int32_t acc = 0;
  __mac_tap(-31);
  __mac_tap(0);
  __mac_tap(462);
  __mac_tap(0);
  __mac_tap(-2127);
  __mac_tap(0);
  __mac_tap(9896);
  __mac_tap(16384);
  __mac_tap(9896);
  __mac_tap(0);
  __mac_tap(-2127);
  __mac_tap(0);
  __mac_tap(462);
  __mac_tap(0);
  __mac_tap(-31);
  return (int16_t)(acc >> 15);
}

static const uint16_t __not_in_flash_func(atanj_fixed_31250)(uint16_t y, uint16_t x)
{

   // for sample rate of 31250

   static const uint16_t A_fixed[65] = {
      0,
      0,
      0,
      1,
      1,
      2,
      3,
      5,
      8,
      11,
      14,
      19,
      24,
      30,
      36,
      44,
      53,
      62,
      73,
      84,
      97,
      111,
      125,
      141,
      158,
      176,
      194,
      214,
      235,
      257,
      280,
      304,
      329,
      355,
      382,
      409,
      437,
      467,
      497,
      527,
      559,
      591,
      623,
      657,
      691,
      725,
      760,
      795,
      831,
      867,
      904,
      941,
      978,
      1016,
      1053,
      1091,
      1129,
      1168,
      1206,
      1245,
      1284,
      1322,
      1361,
      1400,
      1439
   };

   static const uint16_t B_fixed[65] = {
      4973,
      4971,
      4966,
      4959,
      4949,
      4937,
      4923,
      4906,
      4887,
      4866,
      4843,
      4818,
      4791,
      4762,
      4731,
      4698,
      4664,
      4628,
      4590,
      4551,
      4511,
      4469,
      4426,
      4383,
      4338,
      4292,
      4246,
      4198,
      4151,
      4102,
      4053,
      4004,
      3954,
      3904,
      3854,
      3803,
      3753,
      3702,
      3652,
      3602,
      3551,
      3501,
      3452,
      3402,
      3353,
      3304,
      3255,
      3207,
      3159,
      3112,
      3065,
      3019,
      2973,
      2928,
      2883,
      2839,
      2795,
      2752,
      2710,
      2668,
      2627,
      2586,
      2546,
      2506,
      2467
   };

   if (x == 0) return 0;
   const uint32_t value = (y << 16) / x;
   const uint8_t index = (uint8_t)(value >> 10);
   return A_fixed[index] + ((B_fixed[index] * value) >> 16);
}

#define PI__OVER_TWO (SAMPLERATE/4)
#define ONE__PI (SAMPLERATE/2)
#define TWO__PI (SAMPLERATE)

const int16_t __not_in_flash_func(atan2j)(int16_t y, int16_t x)
{
   int16_t z = 0; // returned value
   bool x_is_negative = false;
   bool y_is_negative = false;
   if (x < 0)
   {
      x_is_negative = true;
      x = -x;
   }
   if (y < 0)
   {
      y_is_negative = true;
      y = -y;
   }

   if (y < x)
      z = atanj_fixed_31250(y, x);
   else
   {
      z = atanj_fixed_31250(x, y);
      z = PI__OVER_TWO - z;
   }
   if (x_is_negative) z = ONE__PI - z;
   if (y_is_negative) z = TWO__PI - z;
   /***********************
    * the above statement ensures that the returned value is between 0 and 2*pi
    * If one wants the returned value to be between -pi and +pi, replace that
    * statement with;
    *
    * 		z = -z;
    *
    * *************************/

   return z;
}

#define iter1(N) \
   partial = root + (1 << (N)); \
   if (n >= partial << (N)) \
   { \
      n -= partial << (N); \
      root |= 2 << (N); \
   }

static const uint32_t __not_in_flash_func(isqrt)(uint32_t n)
{
   uint32_t root = 0;
   uint32_t partial = 0;
   iter1(15);
   iter1(14);
   iter1(13);
   iter1(12);
   iter1(11);
   iter1(10);
   iter1(9);
   iter1(8);
   iter1(7);
   iter1(6);
   iter1(5);
   iter1(4);
   iter1(3);
   iter1(2);
   iter1(1);
   iter1(0);
   return root >> 1;
}

static const int16_t __not_in_flash_func(dc)(const int16_t in)
{
  static int32_t s = 0;
  static int32_t x1 = 0;
  static int16_t y1 = 0;
  s -= x1;
  x1 = (int32_t)in << 16;
  s += x1 - ((int32_t)y1 << 8);
  return (y1 = s >> 16);
}

const int16_t __not_in_flash_func(process_iDSB)(const int16_t s)
{
  // for iDSB, LPF, Mix, LPF, ALC
  // used to keep maximum level to 10 bits
  // so that PWM does not overflow
  volatile static int32_t alc = 256L;

  // remove DC and band limit mic signal
  const int32_t mic = lpf_2400(dc(s));

  static uint32_t lo = 0;
  const int32_t bfo = sin2700[lo];
  lo++;
  if (lo>=sin2700_size)
  {
    lo = 0;
  }

  // note extra divide by 2 to bring
  // value close to 10 bit range for PWM
  const int16_t mixer_out = (int16_t)((bfo * mic) >> 16);

  // remove the image
  const int32_t mic_out = ((int32_t)lpf_2500(mixer_out) * alc) >> 8;

  // ALC
  if (abs(mic_out)>511L) alc--;
  return mic_out;
}

const int16_t __not_in_flash_func(process_DSB)(const int16_t s)
{
  // used to keep maximum level to 10 bits
  // so that PWM does not overflow
  volatile static int32_t alc = 256L;

  // remove DC and band limit mic signal
  const int32_t mic_in = lpf_2400(hpf_300(dc(s)));
  const int32_t mic_out = ((mic_in >> 2)  * alc) >> 8;;

  // ALC
  if (abs(mic_out)>511L) alc--;
  return mic_out;
}

const int16_t __not_in_flash_func(process_AM)(const int16_t s)
{
  // remove DC and band limit mic signal
  const int32_t mic_in = lpf_2400(dc(s));

  // reduce mic input to 7 bits (+/-64)
  // so that adding 64 gives max 100% modulation
  const int16_t mic_out = (mic_in>>5) + 64;
  return mic_out;
}

const int16_t __not_in_flash_func(process_CW)(const bool keydown)
{
  // DC value generates CW
  return keydown?CW_LEVEL:0;
}

const int16_t __not_in_flash_func(process_SSB)(const int16_t s,uint16_t &frequency)
{
  volatile static int16_t prev_phase = 0;
  volatile static uint8_t lo = 0;
  const uint8_t bfo = lo & 0x03;

  // bfo oscillators
  lo++;

  // remove DC and band limit mic signal
  const int16_t mic_in = lpf_SSB_2400(dc(s));

  // up convert to FS/4
  int16_t v = 0;
  switch (bfo)
  {
    case 0: v = +mic_in; break;
    case 2: v = -mic_in; break;
  }

  // remove the upper image
  v = lpf_fs4(v);

  // down convert into quadrature
  int16_t sig_i = 0;
  int16_t sig_q = 0;
  switch (bfo)
  {
    case 0: sig_i = +v; break;
    case 1: sig_q = +v; break;
    case 2: sig_i = -v; break;
    case 3: sig_q = -v; break;
  }

  // remove the upper image with another FS/4 LPF
  sig_i = lpf_fs4_i(sig_i);
  sig_q = lpf_fs4_q(sig_q);

  // get the phase
  const int16_t phase = atan2j(sig_q, sig_i);

  // get the frequency
  int16_t freq = phase - prev_phase;
  prev_phase = phase;
  if (freq < 0) freq += SAMPLERATE;
  frequency = freq;
/*
  if (freq<300)
  {
    frequency = 300;
    return 0;
  }
  if (freq>2500)
  {
    frequency = 2500;
    return 0;
  }
*/
  if (freq<300 || freq>2500)
  {
    return 0;
  }

  // magnitude
  return isqrt(sig_i*sig_i + sig_q*sig_q);
}

#endif