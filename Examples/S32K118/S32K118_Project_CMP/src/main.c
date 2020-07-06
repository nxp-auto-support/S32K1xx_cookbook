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
 * ======================================================================
 * In this CMP initialization example, the LED will turn red if the input
 * voltage does not overcome the given threshold, and green if it does.
 */

#include "device_registers.h" 	/* include peripheral declarations S32K118 */
#include "clocks_and_modes_S32K11x.h"
#include "acmp.h"

void PORT_init (void)
{
	/*!
	 * Pins definitions
	 * =====================================
	 *
	 * Pin number        | Function
	 * ----------------- |------------------
	 * PTA4              | [CMP0_OUT]
	 * PTA0				 | [CMP0_IN0]
	 *
	 * PTD16             | GPIO [RED LED]
	 * PTD15			 | GPIO [GREEN LED]
	 */

  PCC->PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; 	/* Enable clock for PORT A  */
  PORTA->PCR[0] = PORT_PCR_MUX(0);		/* Port A0: default, Comparator Input Signal*/
//  PORTA->PCR[4] = PORT_PCR_MUX(1);		/* Port A4: MUX=4, CMP0_OUT */

  PCC->PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; 	/* Enable clock for PORT D  */
  PORTD->PCR[15] = PORT_PCR_MUX(1);  /* Port D15: MUX = GPIO */
  PORTD->PCR[16] = PORT_PCR_MUX(1);  /* Port D16: MUX = GPIO */

  PTD->PDDR |= 1 <<15	    /* Port D15: Data Direction = output */
  	  	  	  |1 <<16;    /* Port D16: Data Direction = output */
}


void WDOG_disable (void)
{
	WDOG->CNT=0xD928C520;     /* Unlock watchdog 		*/
	WDOG->TOVAL=0x0000FFFF;   /* Maximum timeout value 	*/
	WDOG->CS = 0x00002100;    /* Disable watchdog 		*/
}

void NVIC_init_IRQs (void)
{
	S32_NVIC->ICPR[0] = 1 << CMP0_IRQn;	/* IRQ20-CMP0: clr any pending IRQ*/
	S32_NVIC->ISER[0] = 1 << CMP0_IRQn;	/* IRQ20-CMP0: enable IRQ */
	S32_NVIC->IPR[0] = 0xA;		/* IRQ20-CMP0: priority 10 of 0-15*/
}

int main(void)
{
	/*!
	 * Initialization
	 * ===============================
	 */
  	WDOG_disable();		/* Disable WDOG */
  	PORT_init();       	/* Configure ports */
  	SOSC_init_40MHz(); 	/* Initialize system oscillator for 40 MHz xtal */
  	RUN_mode_48MHz();	/* Init clocks: 48 MHz sys, core and bus,
	  	  	  	  	  	  	  	  	  	24 MHz flash. */
	ACMP_Init(127);		/* Initialize CMP0 */
	NVIC_init_IRQs();	/* Enable CMP0 interrupt */

	/*!
	 * Wait forever
	 * */
	for(;;)
	{
	}
}

void CMP0_IRQHandler (void)
{
	if(CMP0->C0 & CMP_C0_CFR_MASK)
	{
		/* A rising edge on COUT has occurred */
		CMP0->C0 |= CMP_C0_CFR_MASK;	/* CFR is cleared by writing 1 to it. */
		PTD->PCOR |= 1 <<15;		/* Turn-Off RED led */
		PTD->PSOR |= 1 <<16;		/* Turn-On GREEN led */
	}
	else if(CMP0->C0 & CMP_C0_CFF_MASK)
	{
		/* A falling edge on COUT has occurred */
		CMP0->C0 |= CMP_C0_CFF_MASK;	/* CFF is cleared by writing 1 to it. */
		PTD->PCOR |= 1 <<16;		/* Turn-Off GREEN led */
		PTD->PSOR |= 1 <<15;		/* Turn-On RED led */
	}
}



