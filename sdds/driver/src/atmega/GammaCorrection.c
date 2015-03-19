/*
 * GammaCorrection.c
 *
 *  Created on: 05.03.2013
 *      Author: kai
 */


#include "GammaCorrection.h"

#ifdef DRIVER_LED_DIMMING_GAMMACORRECTION

#ifdef DRIVER_LED_DIMMING_GAMMACORRECTION_8BIT
const uint8_t pwmtable_8to8[256] PROGMEM =
{
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
		0x02, 0x02, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x05, 0x05,
		0x05, 0x06, 0x06, 0x06, 0x07, 0x07, 0x07, 0x08, 0x08, 0x08, 0x09, 0x09, 0x0A, 0x0A, 0x0B, 0x0B,
		0x0C, 0x0C, 0x0D, 0x0D, 0x0E, 0x0F, 0x0F, 0x10, 0x11, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
		0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1F, 0x20, 0x21, 0x23, 0x24, 0x26, 0x27, 0x29, 0x2B, 0x2C,
		0x2E, 0x30, 0x32, 0x34, 0x36, 0x38, 0x3A, 0x3C, 0x3E, 0x40, 0x43, 0x45, 0x47, 0x4A, 0x4C, 0x4F,
		0x51, 0x54, 0x57, 0x59, 0x5C, 0x5F, 0x62, 0x64, 0x67, 0x6A, 0x6D, 0x70, 0x73, 0x76, 0x79, 0x7C,
		0x7F, 0x82, 0x85, 0x88, 0x8B, 0x8E, 0x91, 0x94, 0x97, 0x9A, 0x9C, 0x9F, 0xA2, 0xA5, 0xA7, 0xAA,
		0xAD, 0xAF, 0xB2, 0xB4, 0xB7, 0xB9, 0xBB, 0xBE, 0xC0, 0xC2, 0xC4, 0xC6, 0xC8, 0xCA, 0xCC, 0xCE,
		0xD0, 0xD2, 0xD3, 0xD5, 0xD7, 0xD8, 0xDA, 0xDB, 0xDD, 0xDE, 0xDF, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5,
		0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xED, 0xEE, 0xEF, 0xEF, 0xF0, 0xF1, 0xF1, 0xF2,
		0xF2, 0xF3, 0xF3, 0xF4, 0xF4, 0xF5, 0xF5, 0xF6, 0xF6, 0xF6, 0xF7, 0xF7, 0xF7, 0xF8, 0xF8, 0xF8,
		0xF9, 0xF9, 0xF9, 0xF9, 0xFA, 0xFA, 0xFA, 0xFA, 0xFA, 0xFB, 0xFB, 0xFB, 0xFB, 0xFB, 0xFB, 0xFC,
		0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD,
		0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF
};
#endif /* DRIVER_LED_DIMMING_GAMMACORRECTION_8BIT*/

#ifdef DRIVER_LED_DIMMING_GAMMACORRECTION_16BIT
const uint16_t pwmtable_8to16[256] PROGMEM =
{
    0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3,
    3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 7,
    7, 7, 8, 8, 8, 9, 9, 10, 10, 10, 11, 11, 12, 12, 13, 13, 14, 15,
    15, 16, 17, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
    31, 32, 33, 35, 36, 38, 40, 41, 43, 45, 47, 49, 52, 54, 56, 59,
    61, 64, 67, 70, 73, 76, 79, 83, 87, 91, 95, 99, 103, 108, 112,
    117, 123, 128, 134, 140, 146, 152, 159, 166, 173, 181, 189, 197,
    206, 215, 225, 235, 245, 256, 267, 279, 292, 304, 318, 332, 347,
    362, 378, 395, 412, 431, 450, 470, 490, 512, 535, 558, 583, 609,
    636, 664, 693, 724, 756, 790, 825, 861, 899, 939, 981, 1024, 1069,
    1117, 1166, 1218, 1272, 1328, 1387, 1448, 1512, 1579, 1649, 1722,
    1798, 1878, 1961, 2048, 2139, 2233, 2332, 2435, 2543, 2656, 2773,
    2896, 3025, 3158, 3298, 3444, 3597, 3756, 3922, 4096, 4277, 4467,
    4664, 4871, 5087, 5312, 5547, 5793, 6049, 6317, 6596, 6889, 7194,
    7512, 7845, 8192, 8555, 8933, 9329, 9742, 10173, 10624, 11094,
    11585, 12098, 12634, 13193, 13777, 14387, 15024, 15689, 16384,
    17109, 17867, 18658, 19484, 20346, 21247, 22188, 23170, 24196,
    25267, 26386, 27554, 28774, 30048, 31378, 32768, 34218, 35733,
    37315, 38967, 40693, 42494, 44376, 46340, 48392, 50534, 52772,
    55108, 57548, 60096, 62757, 65535
};
#endif /*DRIVER_LED_DIMMING_GAMMACORRECTION_16BIT*/


#ifdef DRIVER_LED_DIMMING_GAMMACORRECTION_10BIT
const uint16_t pwmtable_8to10[256] PROGMEM =
{
	0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
	0,    0,    0,    0,    0,    0,    1,    1,    1,    1,
	1,    1,    2,    2,    2,    3,    3,    3,    4,    4,
	4,    5,    5,    6,    6,    7,    7,    8,    8,    9,
	9,   10,   11,   11,   12,   13,   14,   14,   15,   16,
	17,   18,   19,   20,   21,   22,   23,   24,   25,   26,
	27,   28,   29,   31,   32,   33,   34,   36,   37,   38,
	40,   41,   43,   44,   46,   47,   49,   51,   52,   54,
	56,   58,   59,   61,   63,   65,   67,   69,   71,   73,
	75,   77,   79,   82,   84,   86,   88,   91,   93,   96,
	98,  101,  103,  106,  108,  111,  113,  116,  119,  122,
	125,  127,  130,  133,  136,  139,  142,  145,  149,  152,
	155,  158,  161,  165,  168,  172,  175,  179,  182,  186,
	189,  193,  197,  200,  204,  208,  212,  216,  220,  224,
	228,  232,  236,  240,  245,  249,  253,  258,  262,  266,
	271,  276,  280,  285,  289,  294,  299,  304,  309,  314,
	319,  324,  329,  334,  339,  344,  349,  355,  360,  365,
	371,  376,  382,  387,  393,  399,  404,  410,  416,  422,
	428,  434,  440,  446,  452,  458,  464,  471,  477,  483,
	490,  496,  503,  509,  516,  523,  529,  536,  543,  550,
	557,  564,  571,  578,  585,  592,  600,  607,  614,  622,
	629,  637,  644,  652,  660,  667,  675,  683,  691,  699,
	707,  715,  723,  731,  739,  748,  756,  764,  773,  781,
	790,  799,  807,  816,  825,  834,  842,  851,  860,  870,
	879,  888,  897,  906,  916,  925,  935,  944,  954,  963,
	973,  983,  993, 1003, 1013, 1023
};
#endif /*DRIVER_LED_DIMMING_GAMMACORRECTION_10BIT*/

#ifdef DRIVER_LED_DIMMING_GAMMACORRECTION_8BIT
rc_t GammaCorrection_getValue8to8(uint8_t in, uint8_t* out) {

	*out = pgm_read_byte(& pwmtable_8to8[in]);
	return SDDS_RT_OK;
}
#endif /*DRIVER_LED_DIMMING_GAMMACORRECTION_8BIT*/


#ifdef DRIVER_LED_DIMMING_GAMMACORRECTION_16BIT
rc_t GammaCorrection_getValue8to16(uint8_t in, uint16_t* out) {

	*out = pgm_read_word(&pwmtable_8to16[in]);
	return SDDS_RT_OK;
}
#endif /* DRIVER_LED_DIMMING_GAMMACORRECTION_16BIT */

#ifdef DRIVER_LED_DIMMING_GAMMACORRECTION_10BIT
rc_t GammaCorrection_getValue8to10(uint8_t in, uint16_t* out) {

	*out = pgm_read_word(&pwmtable_8to10[in]);
	return SDDS_RT_OK;
}
#endif /* DRIVER_LED_DIMMING_GAMMACORRECTION_10BIT */

#endif /* DRIVER_LED_DIMMING_GAMMACORRECTION*/
