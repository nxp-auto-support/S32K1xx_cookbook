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
 * =============================================================
 *
 */

#include "SAI.h"
#include "device_registers.h"
#include "clocks_and_modes.h"

void PORT_init (void)
{
	/*!
	 * Pins definitions
	 * =====================================
	 *
	 * Pin number        | Function
	 * ----------------- |------------------
	 * PTA12             | SAI0 [BCLK]
	 * PTA13			 | SAI0 [D0]
	 * PTE1				 | SAI0 [D1]
	 * PTE0				 | SAI0 [D2]
	 * PTA14			 | SAI0 [D3]
	 * PTD1				 | SAI0 [MCLK]
	 * PTA11			 | SAI0 [SYNC]
	 */
	PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK;	/* Enable clock for PORT A */
	PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK;	/* Enable clock for PORT E */
	PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK;	/* Enable clock for PORT D */

    PORTA->PCR[12]  |= PORT_PCR_MUX(7); 	/* Port A12: MUX = ALT7, SAI0_BCLK 	*/
    PORTA->PCR[13]  |= PORT_PCR_MUX(7); 	/* Port A12: MUX = ALT7, SAI0_D0 		*/
    PORTE->PCR[1]   |= PORT_PCR_MUX(7); 	/* Port A12: MUX = ALT7, SAI0_D1 		*/
    PORTE->PCR[0]   |= PORT_PCR_MUX(7); 	/* Port A12: MUX = ALT7, SAI0_D2 		*/
    PORTA->PCR[14]  |= PORT_PCR_MUX(7); 	/* Port A12: MUX = ALT7, SAI0_D3 		*/
    PORTD->PCR[1]   |= PORT_PCR_MUX(5); 	/* Port A12: MUX = ALT7, SAI0_MCLK 	*/
    PORTA->PCR[11]  |= PORT_PCR_MUX(6); 	/* Port A12: MUX = ALT7, SAI0_SYNC 	*/
}

void WDOG_disable (void)
{
  WDOG->CNT=0xD928C520;     /* Unlock watchdog 		*/
  WDOG->TOVAL=0x0000FFFF;   /* Maximum timeout value 	*/
  WDOG->CS = 0x00002100;    /* Disable watchdog 		*/
}

int main(void)
{
	/*!
	 * Initialization
	 * ========================
	 */
	WDOG_disable();			/* Disable WDOG */
	SOSC_init_8MHz();		/* Initialize system oscilator for 8 MHz xtal */
	SPLL_init_160MHz();		/* Initialize SPLL to 160 MHz with 8 MHz SOSC */
	NormalRUNmode_80MHz();	/* Init clocks: 80 MHz sysclk & core, 40 MHz bus, 20 MHz flash */

	PORT_init();	/* Configure ports */
    SAI_init();		/* Initialize SAI Module */
    SAI_transfer();	/* SAI transfer... */

	/*!
	 * Wait forever
	 * ========================
	 */
	for(;;)
	{

	}
}
