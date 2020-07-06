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
 * ================================================================================================================
 * This project is same as the prior one (Clocks), except an interrupt is implemented to handle the timer flag.
 * Instead of software polling the timer flag, the interrupt handler clears the flag and toggles the output.
 * The timeout is again one second using FIRCDIV2_CLK for the LPIT0 timer clock.
 */

#include "device_registers.h" 	/* include peripheral declarations S32K118 */
#include "clocks_and_modes_S32K11x.h"

int idle_counter = 0;           /*< main loop idle counter */
int lpit0_ch0_flag_counter = 0; /*< LPIT0 chan 0 timeout counter */

void NVIC_init_IRQs (void)
{
	S32_NVIC->ICPR[0] = 1 << LPIT0_IRQn;	/* IRQ20-LPIT0 ch0: clr any pending IRQ*/
	S32_NVIC->ISER[0] = 1 << LPIT0_IRQn;	/* IRQ20-LPIT0 ch0: enable IRQ */
	S32_NVIC->IPR[0] = 0xA;		/* IRQ20-LPIT0 ch0: priority 10 of 0-15*/
}

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

void LPIT0_init (void)
{
	/*!
	 * LPIT Clocking:
	 * ==============================
	 */
	PCC->PCCn[PCC_LPIT_INDEX] = PCC_PCCn_PCS(3);    /* Clock Src = 3 (FIRCDIV2_CLK)	*/
	PCC->PCCn[PCC_LPIT_INDEX] |= PCC_PCCn_CGC_MASK; /* Enable clk to LPIT0 regs 		*/

  /*!
   * LPIT Initialization:
   * =====================
   */
  LPIT0->MCR |= LPIT_MCR_M_CEN_MASK;  /* DBG_EN-0: Timer chans stop in Debug mode */
                              	  	  /* DOZE_EN=0: Timer chans are stopped in DOZE mode */
                              	  	  /* SW_RST=0: SW reset does not reset timer chans, regs */
                              	  	  /* M_CEN=1: enable module clk (allows writing other LPIT0 regs) */
  LPIT0->MIER = LPIT_MIER_TIE0_MASK;  /* TIE0=1: Timer Interrupt Enabled for chan0 */
  LPIT0->TMR[0].TVAL = 48000000;      /* Chan0 Timeout period: 48M clocks */

  LPIT0->TMR[0].TCTRL |= LPIT_TMR_TCTRL_T_EN_MASK;
  	  	  	  	  	  	  	  /* T_EN=1: Timer channel is enabled */
                              /* CHAIN=0: channel chaining is disabled */
                              /* MODE=0: 32 periodic counter mode */
                              /* TSOT=0: Timer decrements immediately based on restart */
                              /* TSOI=0: Timer does not stop after timeout */
                              /* TROT=0 Timer will not reload on trigger */
                              /* TRG_SRC=0: External trigger soruce */
                              /* TRG_SEL=0: Timer chan 0 trigger source is selected*/
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
	 * Initialization:
	 * =======================
	 */
	  WDOG_disable();	/* Disable WDOG */
	  PORT_init();      /* Configure ports */

	  SOSC_init_40MHz(); /* Initialize system oscillator for 40 MHz xtal */
	  RUN_mode_48MHz();	/* Init clocks: 48 MHz sys, core and bus,
	  	  	  	  	  	  	  	  	  	24 MHz flash. */
	  NVIC_init_IRQs();	/* Enable desired interrupts and priorities */
	  LPIT0_init();     /* Initialize PIT0 for 1 second timeout  */

	/*!
	 * Loop forever:
	 * ========================
	 */
	  for (;;)
	  {
		  idle_counter++;	/* Increment idle counter */
	  }
}

void LPIT0_IRQHandler (void)
{
	lpit0_ch0_flag_counter++;         	/* Increment LPIT0 timeout counter */
	PTE->PTOR |= 1 <<8;                	/* Toggle output on port D0 (blue LED) */
	LPIT0->MSR |= LPIT_MSR_TIF0_MASK; 	/* Clear LPIT0 timer flag 0 */
}

