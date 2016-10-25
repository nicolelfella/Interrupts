/*
 * timerISR.h
 *
 *  Created on: Sep 16, 2016
 *      Author: nicole.fella
 */

#ifndef TIMERISR_H_
#define TIMERISR_H_

void timerSetup(alt_u32 * pCount);
void timerISR(void * pContext, alt_u32 id);



#endif /* TIMERISR_H_ */
