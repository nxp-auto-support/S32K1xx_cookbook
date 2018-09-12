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
 */


#include "device_registers.h" /* include peripheral declarations */
#include "pdb.h"
#include "ADC.h"
#include "clocks_and_modes_S32K11x.h"

#define PTE8 (8)   	/* Port D0: FRDM EVB output to blue LED 	*/
#define PTD15 (15)	/* Port D15: FRDM EVB output to red LED 	*/
#define PTD16 (16) 	/* Port D16: FRDM EVB output to green LED 	*/

void PORT_init (void)
{
	/*!
	 * Pins definitions
	 * ===================================================
	 *
	 * Pin number        | Function
	 * ----------------- |------------------
	 * PTD0              | GPIO [BLUE LED]
	 * PTD15             | GPIO [RED LED]
	 * PTD16			 | GPIO [GREEN LED]
	 */
  PCC->PCCn[PCC_PORTD_INDEX ]|=PCC_PCCn_CGC_MASK;   /* Enable clock for PORTD */
  PCC->PCCn[PCC_PORTE_INDEX ]|=PCC_PCCn_CGC_MASK;   /* Enable clock for PORTD */
  PORTE->PCR[PTE8]  = PORT_PCR_MUX(1);	/* Port D0: MUX = GPIO  */
  PORTD->PCR[PTD15] = PORT_PCR_MUX(1);  /* Port D15: MUX = GPIO */
  PORTD->PCR[PTD16] = PORT_PCR_MUX(1);  /* Port D16: MUX = GPIO */

  PTD->PDDR |= 1<<PTD16		/* Port D0:  Data Direction = output */
  	  	  	|1<<PTD15;	    /* Port D15: Data Direction = output */
  PTE->PDDR |= 1<<PTE8;
}

void WDOG_disable (void)
{
  WDOG->CNT=0xD928C520;     /* Unlock watchdog 		*/
  WDOG->TOVAL=0x0000FFFF;   /* Maximum timeout value 	*/
  WDOG->CS = 0x00002100;    /* Disable watchdog 		*/
}

int main(void)
{
	WDOG_disable();								/* Disable Watchdog */
	S32_NVIC->ICPR = 1 << ADC0_IRQn;		/* IRQ20-LPIT0 ch0: clr any pending IRQ*/
	S32_NVIC->ISER = 1 << ADC0_IRQn;		/* IRQ20-LPIT0 ch0: enable IRQ */

	SOSC_init_40MHz();      /* Initialize system oscillator for 8 MHz xtal 				*/
	RUN_mode_48MHz(); /* Init clocks: 80 MHz sysclk & core, 40 MHz bus, 20 MHz flash*/
	PORT_init();		     /* Init  port clocks and gpio outputs 						*/

	ADC_init_HWTrigger(3);
	PDB0_init();

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
		 if (ADC_result > 3750) {           /* If result > 3.75V */
			  PTD->PCOR |= 1<<PTD15;			  /* turn off blue, green LEDs */
			  PTE->PCOR |= 1<<PTE8;
			  PTD->PSOR |= 1<<PTD16;              /* turn on red LED 			*/
		    }
		    else if (ADC_result > 2500) {      		/* If result > 2.5V */
				  PTD->PCOR |= 1<<PTD16;    /* turn off blue, red LEDs 	\n*/
				  PTE->PCOR |= 1<<PTE8;
				  PTD->PSOR |= 1<<PTD15;     	      /* turn on green LED 		*/
		    }
		    else if (ADC_result >1250) {       /* If result > 1.25V */
				  PTD->PCOR |= 1<<PTD15 | 1<<PTD16;   /* turn off red, green LEDs  */
				  PTE->PSOR |= 1<<PTE8;     	      /* turn on blue LED 			*/
		    }
		    else {
				  PTD->PCOR |= 1<< PTD15 | 1<<PTD16; /* Turn off all LEDs */
				  PTE->PCOR |= 1<<PTE8;
		    }
	}
}
