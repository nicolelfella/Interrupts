/*
 * timerISR.c
 *
 *  Created on: Sep 16, 2016
 *      Author: nicole.fella
 *
 *  Timer to check every second if a button is pressed
 *  ISR evaluates after each instruction (1 second)
 */

#include "system.h"
#include "alt_types.h"
#include "timerISR.h"
#include "io.h"
#include "sys/alt_irq.h"


void timerSetup(alt_u32 * pCount)
{
	//initialize counter
	void* context = (void *)pCount;

	//configure count value to expire once per second
	IOWR(INTERVAL_TIMER_BASE, 2, 0x0000ffff&INTERVAL_TIMER_FREQ); // Set the low counter start value
	IOWR(INTERVAL_TIMER_BASE, 3, 0x0000ffff&(INTERVAL_TIMER_FREQ >> 16)); // Set the hi counter start value

	// Register the ISR with the interrupt handling system
	alt_irq_register (INTERVAL_TIMER_IRQ, context, timerISR);

	IOWR(INTERVAL_TIMER_BASE, 0, 0x0); // clear any interrupts pending

	//control register Stop=0, Start=1, Cont=1, ITO=1 => 0111b = 0x07
	IOWR(INTERVAL_TIMER_BASE, 1, 0x07);

}


void timerISR(void * context, alt_u32 id)
{
	//printf("TIMER");

	volatile int * timer_ptr = (int *)INTERVAL_TIMER_BASE;

	* (timer_ptr) = 0; 	// clear the interrupt

	alt_u32 * pCount = (alt_u32*) context;

	*pCount = *pCount + 1;



}

