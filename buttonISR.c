/*
 * buttonISR.c
 *
 *  Created on: Sep 16, 2016
 *      Author: nicole.fella
 *
 *  Detect edge button press
 *  KEY1, KEY2, KEY3
 */

#include "system.h"
#include "alt_types.h"
#include "io.h"
#include "sys/alt_irq.h"
#include "buttonISR.h"


void buttonSetup(t_flags * pFlags)
{
	//initialize counter
	void* context = (void *)pFlags;

	//configure registers - interrupt mask register and edgecapture register

	IOWR(PUSHBUTTONS_BASE, 2, 0xE); //masking 3 bits 1110b where the bit position is 0 doesn't care 111x

	//Register the ISR with the interrupt handling system
	alt_irq_register (PUSHBUTTONS_IRQ, context, buttonISR);

}

void buttonISR(void * context, alt_u32 id)
{

	t_flags * pFlags = (t_flags*)context;

	alt_u8 buttons = IORD(PUSHBUTTONS_BASE, 3); //edge capture bits Determine which button was pressed (binary)
	IOWR(PUSHBUTTONS_BASE, 3, 0x0); // clears the pending interrupts

	volatile int* KEY_ptr = (int*)PUSHBUTTONS_BASE;		//pushbutton KEY address
	volatile int* green_LED_ptr = (int*)GREEN_LEDS_BASE;	//green LED address

	
	IOWR(GREEN_LEDS_BASE, 0, buttons);
	switch(buttons){
		case 0x02: //KEY1 start or stop counter
			pFlags->toggle_pause = 1;
			break;
		case 0x04: //KEY2 reset count if pressed
			pFlags->do_reset = 1;
			break;
		case 0x08: //KEY3 toggle between HEX and BCD
			pFlags->toggle_bcd = !pFlags->toggle_bcd;
			break;
		default: break;
	}

}
