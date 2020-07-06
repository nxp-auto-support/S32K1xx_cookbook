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
 * Simple program to show a basic  configuration of LPTMR module
 * LPTMR0 IRQHandler is used to toggle Blue LED every 500ms.
 *
 */

#include "lptmr.h"
#include "device_registers.h" 	/* include peripheral declarations S32K116 */
#include "clocks_and_modes_S32K11x.h"

void PORT_init (void)
{
	/*!
	 * Pins definitions
	 * =====================================
	 *
	 * Pin number        | Function
	 * ----------------- |------------------
	 * PTE8              | GPIO [BLUE LED]
	 */
	PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; /* Enable clock for PORT E */
	PTE->PDDR |= 1 <<8;      /* Port E8: Data Direction= output */
	PORTE->PCR[8] = PORT_PCR_MUX(1); /* Port E8: MUX = GPIO */
}

void WDOG_disable (void)
{
  WDOG->CNT=0xD928C520;     /* Unlock watchdog 		*/
  WDOG->TOVAL=0x0000FFFF;   /* Maximum timeout value 	*/
  WDOG->CS = 0x00002100;    /* Disable watchdog 		*/
}

void NVIC_init_IRQs (void)
{
	S32_NVIC->ICPR[0] = 1 << LPTMR0_IRQn;		/* IRQ8-LPTMR0: clr any pending IRQ*/
	S32_NVIC->ISER[0] = 1 << LPTMR0_IRQn;		/* IRQ8-LPTMR0: enable IRQ */
}

int main(void)
{
	/*!
	 * Initialization
	 * ===================================================
	 */
	WDOG_disable();			/* Disable watchdog */
	SOSC_init_40MHz(); 		/* Initialize system oscillator for 40 MHz xtal */
	RUN_mode_48MHz();		/* Init clocks: 48 MHz sys, core and bus,
	  	  	  	  	  	  	  	  	  		24 MHz flash. */

	PORT_init();
	LPTMR_init();
	NVIC_init_IRQs();

	/*!
	 * Wait forever
	 * ========================
	 */
	for(;;)
	{

	}
}

void LPTMR0_IRQHandler (void)
{
	if(0!=(LPTMR0->CSR & LPTMR_CSR_TCF_MASK))
	{
		/* Check if TCF flag is set */
		LPTMR0->CSR |= LPTMR_CSR_TCF_MASK;	/*	Clear TCF flag by writting a logic one */
		PTE->PTOR |= 1 <<8;					/* Toggle Blue led */
	}
}

