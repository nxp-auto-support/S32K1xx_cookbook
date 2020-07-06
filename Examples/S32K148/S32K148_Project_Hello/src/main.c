/*
 * Copyright (c) 2014 - 2016, Freescale Semiconductor, Inc.
 * Copyright (c) 2016 - 2018, NXP.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY NXP "AS IS" AND ANY EXPRESSED OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL NXP OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

/*!
 * Description:
 * =====================================================================
 * This short project is a starting point to learn GPIO.
 * An input is polled to detect a high or low level. An output is set
 * depending on input state. If running code on the S32K14x evaluation
 * board, pressing button 0 lights up the blue LED.
 */

#include "device_registers.h"

#define PTE23 (23)
#define PTC12 (12)

void WDOG_disable (void)
{
  WDOG->CNT=0xD928C520;     /* Unlock watchdog 		*/
  WDOG->TOVAL=0x0000FFFF;   /* Maximum timeout value 	*/
  WDOG->CS = 0x00002100;    /* Disable watchdog 		*/
}

int main(void)
{
	int counter = 0;

	/*!
	 * Pins definitions
	 * ===================================================
	 *
	 * Pin number        | Function
	 * ----------------- |------------------
	 * PTE23             | GPIO [BLUE LED]
	 * PTC12             | GPIO [SW2]
	 */

	/*!
	 * Initialization
	 * ===================================================
	 */
	WDOG_disable();	/* Disable Watchdog in case it is not done in startup code */

	/* Enable clocks to peripherals (PORT modules) */
	PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK;	/* Enable clock to PORT C */
	PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK;	/* Enable clock to PORT E */


	/* Configure port C12 as GPIO input (BTN 0 [SW3] on EVB) */
	PTC->PDDR &= ~(1<<PTC12);   			/* Port C12: Data Direction= input (default) */
	PORTC->PCR[PTC12] = PORT_PCR_MUX(1)
					   |PORT_PCR_PFE_MASK; 	/* Port C12: MUX = GPIO, input filter enabled */

	/* Configure port E23 as GPIO output (LED on EVB) */
	PTE->PDDR |= 1<<PTE23;       			/* Port E23: Data Direction= output */
	PORTE->PCR[PTE23] = PORT_PCR_MUX(1); 	/* Port E23: MUX = GPIO */

	/*!
	 * Infinite for:
	 * ========================
	 */
		for(;;)
		{
			if (PTC->PDIR & (1<<PTC12)) {	 /* - If Pad Data Input = 1 (BTN0 [SW3] pushed)*/
				PTE-> PSOR |= 1<<PTE23;		 /*		Set Output on port E23 (LED on)*/
			}
			else {							 /* - If BTN0 was not pushed */
				PTE-> PCOR |= 1<<PTE23;      /*		Clear Output on port E23 (LED off) */
			}

		counter++;
		}
}
