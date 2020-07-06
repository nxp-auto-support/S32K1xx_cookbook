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
 * */

#include "device_registers.h"								/* include peripheral declarations S32K144W */
#include "clocks_and_modes_ht.h"
#include "lptmr.h"

#define PTE3 (3)   											/* Port E3: FRDM EVB output to blue LED */

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

void WDOG_disable (void)
{
	WDOG -> CNT = 0xD928C520;     							/* Unlock watchdog */
	WDOG -> TOVAL = 0x0000FFFF;   							/* Maximum timeout value */
	WDOG -> CS = 0x00002100;    							/* Disable watchdog */
}

void Enable_Interrupt (uint8_t vector_number)
{
	S32_NVIC->ISER[(uint32_t)(vector_number) >> 5U] = (uint32_t)(1U << ((uint32_t)(vector_number) & (uint32_t)0x1FU));
	S32_NVIC->ICPR[(uint32_t)(vector_number) >> 5U] = (uint32_t)(1U << ((uint32_t)(vector_number) & (uint32_t)0x1FU));
}

int main(void)
{
	/*!
	* Initialization:
	*/
	WDOG_disable();											/* Disable WDOG */
	SOSC_init_8MHz();										/* Initialize system oscilator for 8 MHz xtal */
	SPLL_init_160MHz();										/* Initialize SPLL to 160 MHz with 8 MHz SOSC */
	NormalRUNmode_80MHz();									/* Init clocks: 80 MHz sysclk & core, 40 MHz bus, 20 MHz flash */

	PORT_init();											/* Configure ports */
	LPTMR_init();											/* Configure LPTMR */
	Enable_Interrupt(LPTMR0_IRQn);							/* Enable LPTMR interrupt */

	/*!
	* Infinite for:
	*/
	for (;;);
}

void LPTMR0_IRQHandler (void)
{
	if(0 != (LPTMR0 -> CSR & LPTMR_CSR_TCF_MASK))			/* Check if TCF flag is set */
	{
		LPTMR0 -> CSR |= LPTMR_CSR_TCF_MASK;				/* Clear TCF flag by writing a logic one */
		GPIOE -> PTOR |= 1<<PTE3;                			/* Toggle output on port E3 (blue LED) */
	}
}
