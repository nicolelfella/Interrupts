/*
 * Interrupt.c
 *
 *  Created on: Sep 16, 2016
 *      Author: nicole.fella
 *
 *  Interrupt Service Routine
 *  Starts or stops counter whenever KEY1 is pressed
 *  Resets count to zero when KEY2 is pressed
 *
 *  This will contain our MAIN function
 */


#include "system.h"
#include "alt_types.h"
#include "io.h"
#include "timerISR.h"
#include "buttonISR.h"
#include "HexDisplay.h"
#include "lcd.h"

#define DISPLAY_AS_BCD "Display as BCD"
#define DISPLAY_AS_HEX "Display as Hex"


int main(void)
{
	static volatile alt_u32 count = 0;
	static volatile t_flags my_flags;
	my_flags.do_reset = 0;
	my_flags.toggle_pause = 0;
	my_flags.toggle_bcd = 1;
	char * msg = DISPLAY_AS_BCD;
	timerSetup(&count);
	buttonSetup(&my_flags);

	LCD_clear();
	LCD_cursor(0,0);
	LCD_text("Welcome!");

	while(1)
	{
		if (my_flags.toggle_pause) {
			alt_u8 status = IORD(INTERVAL_TIMER_BASE, 1);
			if (status == 0x7) {
				IOWR(INTERVAL_TIMER_BASE, 1, 0x8); //STOP=1, START=0, CONT=0, ITO=0 = 1000b = 0x8
				LCD_clear();
				LCD_text("PAUSED!");

			} else
			{
				IOWR(INTERVAL_TIMER_BASE, 1, 0x7); //RUN
				LCD_clear();
				LCD_text("Counting :)");
			}
			my_flags.toggle_pause = 0;
		}

		if (my_flags.do_reset){
			count = 0;
			my_flags.do_reset = 0;
		}
		msg = (my_flags.toggle_bcd)?DISPLAY_AS_BCD:DISPLAY_AS_HEX;
		LCD_cursor(0,1);
		LCD_text(msg);

		HexDisplay(HEX3_HEX0_BASE, count, my_flags.toggle_bcd, 0);

		IOWR(RED_LEDS_BASE, 0, 0x3FFFF&(count));
	}

	return 0;


}
