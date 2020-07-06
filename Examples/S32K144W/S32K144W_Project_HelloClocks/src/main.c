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
 * ==================================================================================================
 * This project provides common initialization for clocks and an LPIT channel counter function.
 * Core clock is set to 80 MHz. LPIT0 channel 0 is configured to count one second of SPLL clocks.
 * Software polls the channel’s timeout flag and toggles the GPIO output to the LED when the flag sets.
 * */

#include "device_registers.h"           					/* include peripheral declarations S32K144W */
#include "clocks_and_modes_ht.h"

#define PTE3 (3)   											/* Port E3: FRDM EVB output to blue LED */

int lpit0_ch0_flag_counter = 0; 							/* LPIT0 timeout counter */

/*!
* @brief PORTn Initialization
*/
void PORT_init (void)
{
	/*!
	 *            Pins Definitions
	 * =========================================
	 *
	 *    Pin Number     |     Function
	 * ----------------- |------------------
	 * PTE3              | GPIO [BLUE_LED]
	 */

	PCC -> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; 		/* Enable clock for PORT E */

	PORTE -> PCR[PTE3] |=  PORT_PCR_MUX(1);  				/* Port D0: MUX = ALT1, GPIO (to blue LED on EVB) */

	GPIOE -> PDDR |= 1<<PTE3;            					/* Port D0: Data Direction = output */
}

/*!
* @brief LPIT0 Initialization
*/
void LPIT0_init (void)
{
	/*!
	* LPIT Clocking:
	*/
	PCC -> PCCn[PCC_LPIT_INDEX] = PCC_PCCn_PCS(6);    		/* Clock Source = 6 (SPLL2_DIV2_CLK) */
	PCC -> PCCn[PCC_LPIT_INDEX] |= PCC_PCCn_CGC_MASK; 		/* Enable CLK to LPIT0 register */

	/*!
	* LPIT Initialization:
	*/
	LPIT0 -> MCR |= LPIT_MCR_M_CEN_MASK;  					/* M_CEN = 1: enable module CLK (allows writing other LPIT0 register) */
															/* DBG_EN = 0: Timer channels stop in Debug mode */
                              	  	  	  	  	  	  	  	/* DOZE_EN = 0: Timer channels are stopped in DOZE mode */
                              	  	  	  	  	  	  	  	/* SW_RST = 0: SW reset does not reset timer channels, registers */

	LPIT0 -> TMR[0].TVAL = 40000000;      					/* Channel 0 Timeout period: 40M clocks */

	LPIT0 -> TMR[0].TCTRL |= LPIT_TMR_TCTRL_T_EN_MASK;		/* T_EN = 1: Timer channel is enabled */
                              	  	  	  	  	  	  	  	/* CHAIN = 0: channel chaining is disabled */
															/* MODE = 0: 32 periodic counter mode */
															/* TSOT = 0: Timer decrements immediately based on restart */
															/* TSOI = 0: Timer does not stop after timeout */
															/* TROT = 0 Timer will not reload on trigger */
															/* TRG_SRC = 0: External trigger source */
															/* TRG_SEL = 0: Timer channel 0 trigger source is selected*/
}

void WDOG_disable (void)
{
	WDOG -> CNT = 0xD928C520;     							/* Unlock watchdog */
	WDOG -> TOVAL = 0x0000FFFF;   							/* Maximum timeout value */
	WDOG -> CS = 0x00002100;    							/* Disable watchdog */
}

int main (void)
{
	/*!
	* Initialization:
	*/
	WDOG_disable();											/* Disable WDOG */
	SOSC_init_8MHz();										/* Initialize system oscilator for 8 MHz xtal */
	SPLL_init_160MHz();										/* Initialize SPLL to 160 MHz with 8 MHz SOSC */
	NormalRUNmode_80MHz();									/* Init clocks: 80 MHz sysclk & core, 40 MHz bus, 20 MHz flash */

	PORT_init();            								/* Configure ports */
	LPIT0_init();           								/* Initialize PIT0 for 1 second timeout  */

	/*!
	* Infinite for:
	*/
	for (;;)
	{
		/* Toggle output to LED every LPIT0 timeout */
		while (0 == (LPIT0 -> MSR & LPIT_MSR_TIF0_MASK)) {} /* Wait for LPIT0 CH0 Flag */

		lpit0_ch0_flag_counter++;         					/* Increment LPIT0 timeout counter */

		GPIOE -> PTOR |= 1<<PTE3;                			/* Toggle output on port E3 (blue LED) */
		LPIT0 -> MSR |= LPIT_MSR_TIF0_MASK; 				/* Clear LPIT0 timer flag 0 */
	}
}
