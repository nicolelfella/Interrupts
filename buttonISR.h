/*
 * buttonISR.h
 *
 *  Created on: Sep 16, 2016
 *      Author: nicole.fella
 */

#ifndef BUTTONISR_H_
#define BUTTONISR_H_

typedef struct flags {
	alt_u8 toggle_pause;
	alt_u8 do_reset;
	alt_u8 toggle_bcd;
}t_flags;

void buttonSetup(t_flags * pFlags);
void buttonISR(void * pContext, alt_u32 id);


#endif /* BUTTONISR_H_ */
