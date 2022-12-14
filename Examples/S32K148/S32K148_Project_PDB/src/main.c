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
 * The ADC is initialized for HW triggers, and the PDB will trigger it
 * with a small delay that can be noticed by the toggling LED's
 * 
 * 
 */

#include "device_registers.h" /* include peripheral declarations S32K144 */
#include "pdb.h"
#include "ADC.h"
#include "clocks_and_modes.h"

#define PTE21 (21)	/* Port E21: FRDM EVB output to red LED 	*/
#define PTE22 (22) 	/* Port E22: FRDM EVB output to green LED 	*/
#define PTE23 (23)	/* Port E23: FRDM EVB output to blue LED 	*/


void PORT_init (void) {

	/*!
	 * Pins definitions
	 * ===================================================
	 *
	 * Pin number        | Function
	 * ----------------- |------------------
	 * PTE21             | GPIO [RED LED]
	 * PTE22			 | GPIO [GREEN LED]
	 * PTE23             | GPIO [BLUE LED]
	 */

	PCC-> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; /* Enable clock for PORT D */

	PORTE->PCR[PTE21]  =  0x00000100;  /* Port D0: MUX = GPIO */
	PORTE->PCR[PTE22] =  0x00000100;  /* Port D15: MUX = GPIO */
	PORTE->PCR[PTE23] =  0x00000100;  /* Port D16: MUX = GPIO */

	PTE->PDDR |= 1<<PTE21;       	  /* Port D0:  Data Direction= output */
	PTE->PDDR |= 1<<PTE22;          /* Port D15: Data Direction= output */
	PTE->PDDR |= 1<<PTE23;          /* Port D16: Data Direction= output */
}
void WDOG_disable (void){
  WDOG->CNT=0xD928C520;     /* Unlock watchdog */
  WDOG->TOVAL=0x0000FFFF;   /* Maximum timeout value */
  WDOG->CS = 0x00002100;    /* Disable watchdog */
}


int main(void)
{
	/*!
	 *
	 *Initializations
	 *=========================================
	 */

	WDOG_disable();			/*Disable Watchdog*/
	S32_NVIC->ISER[1] = 1 << (ADC0_IRQn % 32);  /* IRQ48-LPIT0 ch0: enable IRQ */
	SOSC_init_8MHz();      /* Initialize system oscillator for 8 MHz xtal */
	SPLL_init_160MHz();    /* Initialize SPLL to 160 MHz with 8 MHz SOSC */
	NormalRUNmode_80MHz(); /* Init clocks: 80 MHz sysclk & core, 40 MHz bus, 20 MHz flash */
	PORT_init();			/* Initializates GPIO*/
	ADC_init_HWTrigger(44);/*Initialize the ADC in HW Trigger mode*/
	PDB0_init();	/*Initialize PDB0*/

	/*!
	 *
	 *Infinite for
	 *=========================================
	 */

	for(;;)
	{
	}
}


void ADC0_IRQHandler(void)
{
	volatile uint16_t ADC_result = 0;

	if(ADC0->SC1[0] & ADC_SC1_COCO_MASK)
	{
		ADC_result=ADC0->R[0];      /* For SW trigger mode, R[0] is used */
		 if (ADC_result > 3072) {           /* If result > 3.75V */
		      PTE->PCOR |= (1<<PTE22 | 1<<PTE23);    /* turn off blue, green LEDs */
		      PTE->PTOR |= (1<<PTE21);              /* turn on red LED */
		    }
		    else if (ADC_result > 2048) {      /* If result > 3.75V */
		      PTE->PCOR |= (1<<PTE21 | 1<<PTE23);    /* turn off blue, red LEDs */
		      PTE->PTOR |= (1<<PTE22);     	      /* turn on green LED */
		    }
		    else if (ADC_result >1024) {       /* If result > 3.75V */
		      PTE->PCOR |= (1<<PTE21 | 1<<PTE22);   /* turn off red, green LEDs */
		      PTE->PTOR |= (1<<PTE23);     	      /* turn on blue LED */
		    }
		    else {
		      PTE->PCOR |= (1<<PTE21 | 1<< PTE22 | 1<<PTE23); /* Turn off all LEDs */
		    }
	}
}
