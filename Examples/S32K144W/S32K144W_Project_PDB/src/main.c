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
 * */

#include "device_registers.h" 							/* include peripheral declarations S32K144W */
#include "clocks_and_modes_ht.h"
#include "pdb.h"
#include "ADC.h"

#define PTE3 (3)   										/* Port E3: FRDM EVB output to blue LED */
#define PTE7 (7)										/* Port E7: FRDM EVB output to red LED */
#define PTE0 (0) 										/* Port E0: FRDM EVB output to green LED */

/*!
* @brief PORTn Initialization
*/
void PORT_init (void)
{
	/*!
	*            Pins Definitions
	* =======================================
	*
	*    Pin Number     |     Function
	* ----------------- |------------------
	* PTE3              | GPIO [BLUE_LED]
	* PTE7              | GPIO [RED_LED]
	* PTE0			    | GPIO [GREEN_LED]
	*/

	PCC -> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK;   /* Enable clock for PORT D */

	PORTE -> PCR[PTE3] = PORT_PCR_MUX(1);				/* Port E3: MUX = GPIO */
	PORTE -> PCR[PTE7] = PORT_PCR_MUX(1);  				/* Port E7: MUX = GPIO */
	PORTE -> PCR[PTE0] = PORT_PCR_MUX(1);  				/* Port E0: MUX = GPIO */

	GPIOE -> PDDR |= 1<<PTE3							/* Port E3: Data Direction = output */
				  |  1<<PTE7	        				/* Port E7: Data Direction = output */
				  |  1<<PTE0;         					/* Port E0: Data Direction = output */

	GPIOE -> PCOR |= 1<<PTE3							/* Turn-Off all LEDs */
				  |  1<<PTE7
				  |  1<<PTE0;
}

void WDOG_disable (void)
{
	WDOG -> CNT = 0xD928C520;     						/* Unlock watchdog */
	WDOG -> TOVAL = 0x0000FFFF;   						/* Maximum timeout value */
	WDOG -> CS = 0x00002100;    						/* Disable watchdog */
}

void Enable_Interrupt (uint8_t vector_number)
{
	S32_NVIC->ISER[(uint32_t)(vector_number) >> 5U] = (uint32_t)(1U << ((uint32_t)(vector_number) & (uint32_t)0x1FU));
	S32_NVIC->ICPR[(uint32_t)(vector_number) >> 5U] = (uint32_t)(1U << ((uint32_t)(vector_number) & (uint32_t)0x1FU));
}

int main (void)
{
	/*!
	* Initialization:
	*/
	WDOG_disable();		  								/* Disable WDOG */
	SOSC_init_8MHz();       							/* Initialize system oscilator for 8 MHz xtal */
	SPLL_init_160MHz();     							/* Initialize SPLL to 160 MHz with 8 MHz SOSC */
	NormalRUNmode_80MHz();  							/* Init clocks: 80 MHz sysclk & core, 40 MHz bus, 20 MHz flash */

	PORT_init();            							/* Configure ports */
	ADC_HW_trigger_init(9);								/* Configure ADC Channel */
	Enable_Interrupt(ADC0_IRQn);						/* Enable ADC0 interrupt */
	PDB0_init();										/* Configure PDB0 */

	/*!
	 * Infinite for:
	 */
	for (;;);
}

void ADC0_IRQHandler (void)
{
	volatile uint16_t adc_mv_result = 0;

	if (ADC0 -> SC1[0] & ADC_SC1_COCO_MASK)
	{
		adc_mv_result = ADC0 -> R[0];      				/* For SW trigger mode, R[0] is used */

		if (adc_mv_result > 3750) 						/* If result > 3.75V */
		{
			GPIOE -> PCOR |= 1<<PTE3 					/* Turn off blue LED */
					      |  1<<PTE0;    				/* Turn off green LED */
			GPIOE -> PSOR |= 1<<PTE7;              		/* Turn on red LED */
		}

		else if (adc_mv_result > 2500)  				/* If result > 2.50V */
		{
			GPIOE -> PCOR |= 1<<PTE3 					/* Turn off blue LED */
						  |  1<<PTE7;    				/* Turn off red LED */
			GPIOE -> PSOR |= 1<<PTE0;					/* Turn on green LED */
		}

		else if (adc_mv_result > 1250) 					/* If result > 1.25V */
		{
			GPIOE -> PCOR |= 1<<PTE7 					/* Turn off red LED */
						  |  1<<PTE0;   				/* Turn off green LED */
			GPIOE -> PSOR |= 1<<PTE3;     	      		/* Turn on blue LED */
		}

		else
		{
			GPIOE -> PCOR |= 1<<PTE3 | 1<<PTE7 | 1<<PTE0; /* Turn off all LEDs */
		}
	}
}
