/*
 * driver.h
 *
 *  Created on: 2 Jul 2012
 *      Author: k_beckma \& d_mierswa
 */

#ifndef DRIVER_H_
#define DRIVER_H_

#define INTERNAL_CONCAT2(x, y) x ## y
#define INTERNAL_CONCAT(x, y) INTERNAL_CONCAT2(x, y)
#define INTERNAL_MAX(x, y) ((x) > (y) ? (x) : (y))
#define INTERNAL_MIN(x, y) ((x) < (y) ? (x) : (y))

#if defined(__OPTIMIZE__) && defined(F_CPU)
#include <util/delay.h>
#endif

#ifndef __OPTIMIZE__
#ifndef F_CPU
#error "Please set F_CPU to the frequency of the target system in Hz."
#endif

// 8 cycles on 8MHz == 1µs
#define custom_delay_8cyc(x) \
	do \
	{ \
		asm volatile( \
			"nop\n"                    /* [1 cycle] */ \
			"nop\n"                    /* [1 cycle] */ \
			"cp  %A0, __zero_reg__ \n" /* count & 0xFF == 0     [1 cycle] */ \
			"cpc %B0, __zero_reg__ \n" /* (count & 0xFF00 >> 8) [1 cycle] */ \
			"breq 2f\n"                /* jump to end [1 cycle] */ \
			"1:\n" \
			"sbiw %0, 1\n"             /* count-- [count * 2 cycles] */ \
			"brne 1b\n"                /* loop if != 0 [(count - 1) * 2 cycles + 1 cycle] */ \
			"2:" \
			                           /* 4 * (count + 1) if count > 0, else 6 */ \
		::"w"((x)) \
		); \
	} while(0);

#define _delay_ms(x) custom_delay_8cyc(((x) * F_CPU) / 1000 / 8)
#define _delay_us(x) custom_delay_8cyc(((x) * F_CPU) / 1000 / 1000 / 8)

#endif

#endif /* DRIVER_H_ */
