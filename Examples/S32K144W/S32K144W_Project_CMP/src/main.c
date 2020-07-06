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
 * =================================================================
 * Initialization example, the LED will turn red if the input
 * voltage does not overcome the given threshold, and green if it does.
 * */

#include "device_registers.h"						/* include peripheral declarations S32K144W */
#include "clocks_and_modes_ht.h"
#include "acmp.h"

#define PTE7 (7)									/* Port E7: FRDM EVB output to red LED */
#define PTE0 (0) 									/* Port E0: FRDM EVB output to green LED */
#define PTE3 (3)   									/* Port E3: FRDM EVB output to CMP0_OUT */
#define PTA0 (0)									/* Port A0: FRDM EVB input to CMP0_IN0 */

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
	* PTE3              | CMP0 [OUT]
	* PTA0				| CMP0 [IN0]
	* PTE7              | GPIO [RED_LED]
	* PTE0			    | GPIO [GREEN_LED]
	*/

	PCC -> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; 	/* Enable clock for PORT A */

	PORTA -> PCR[PTA0] = PORT_PCR_MUX(0);				/* Port A0: default, Comparator Input Signal */

	PCC -> PCCn[PCC_PORTE_INDEX] = PCC_PCCn_CGC_MASK; 	/* Enable clock for PORT E */

	PORTE -> PCR[PTE7] = PORT_PCR_MUX(1);  				/* Port E7: MUX = GPIO */
	PORTE -> PCR[PTE0] = PORT_PCR_MUX(1);  				/* Port E0: MUX = GPIO */
	PORTE -> PCR[PTE3] = PORT_PCR_MUX(7);				/* Port E7: MUX = ALT7, Comparator Output trigger */

	GPIOE -> PDDR |= 1<<PTE7	    					/* Port E7: Data Direction = output */
				  |  1<<PTE0;         					/* Port E0: Data Direction = output */

	GPIOE -> PCOR |= 1<<PTE7							/* Turn-Off all LEDs */
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
	ACMP_Init(127);										/* Initialize CMP0 */
	Enable_Interrupt(CMP0_IRQn);						/* Enable CMP0 interrupt */

	/*!
	 * Infinite for:
	 */
	for (;;);
}

void CMP0_IRQHandler (void)
{
	if (CMP0 -> C0 & CMP_C0_CFR_MASK)					/* A rising edge on COUT has occurred */
	{
		CMP0 -> C0 |= CMP_C0_CFR_MASK;					/* CFR is cleared by writing 1 to it */
		GPIOE -> PCOR |= 1<<PTE7;						/* Turn off red LED */
		GPIOE -> PSOR |= 1<<PTE0;						/* Turn on green LED */
	}

	else if (CMP0 -> C0 & CMP_C0_CFF_MASK)				/* A falling edge on COUT has occurred */
	{
		CMP0 -> C0 |= CMP_C0_CFF_MASK;					/* CFF is cleared by writing 1 to it */
		GPIOE -> PCOR |= 1<<PTE0;						/* Turn off green LED */
		GPIOE -> PSOR |= 1<<PTE7;						/* Turn on red LED */
	}
}
