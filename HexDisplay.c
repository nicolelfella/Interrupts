/*
 * HexDisplay.c
 *
 *  Created on: Sep 16, 2016
 *      Author: nicole.fella
 *
 *      Taken from Dr. Horine
 */




#include "seven_seg_hex.h"
#include "seven_seg_bcd.h"



void HexDisplay(alt_u32 * base, alt_u16 num, alt_u8 display_as_bcd, alt_u8 leading_zeros) {
	if (display_as_bcd) {
		seven_seg_bcd(base, num, leading_zeros);
	} else {
		seven_seg_hex(base, num, leading_zeros);
	}
}

