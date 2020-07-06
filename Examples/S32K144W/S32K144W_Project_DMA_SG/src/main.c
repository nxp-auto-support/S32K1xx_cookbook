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
 * =============================================================================================
 * This examples shows the function of the Scatter Gather of the eDMA that lets you change the
 * TCD configuration. We use this feature to combine the characters contained in 2 different
 * strings and mix them together in a single array to get the phrase "Hello World".
 * */

#include "device_registers.h"								/* include peripheral declarations S32K144W */
#include "clocks_and_modes_ht.h"
#include "dma.h"

#define SOFF 1												/* Define the source byte offset of the TCD after transfer */
#define DOFF 1												/* Define the destination byte offset of the TCD after transfer */
#define SIZE1 6												/* Define the first amount of minor loops for the TCD according to the amount of bytes to be send */
#define SIZE2 5												/* Define the second amount of minor loops for the TCD according to the amount of bytes to be send */

uint8_t volatile TCD0_Source_1[SIZE1] = {"Hello "}; 		/* SIZE1 bits long source for the DMA */
uint8_t volatile TCD0_Source_2[SIZE2] = {"World"};			/* SIZE2 bits long source for the DMA */
uint8_t volatile TCD0_Destination[SIZE1 + SIZE2];			/* (SIZE1 + SIZE2) bytes length destination of the sources */

TCD_t TCDm[2] __attribute__ ((aligned(32)));				/* Define an array of 2 TCD_t variables aligned to 32 bits to maintain structure */

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

int main (void)
{

	/*!
	* Initialization:
	*/
	WDOG_disable();											/* Disable watchdog */
	SOSC_init_8MHz();      									/* Initialize system oscilator for 8 MHz xtal */
	SPLL_init_160MHz();    									/* Initialize SPLL to 160 MHz with 8 MHz SOSC */
	NormalRUNmode_80MHz(); 									/* Init clocks: 80 MHz sysclk & core, 40 MHz bus, 20 MHz flash */

	DMA_SG_init();		   									/* Initialize DMAMUX to always generate DMA requests */

	Enable_Interrupt(DMA0_IRQn);							/* Enable DMA CH0 interrupt */

	/*Start saving in the TCDm array the different TCDs to be used by the DMA*/
	/*Save information in each TCDm with the source you would like */

	/* Saving TCD configuration in RAM */
	DMA_TCDm_config((uint32_t *)&TCD0_Source_1[0], SOFF, (uint32_t *)&TCD0_Destination[0], DOFF, SIZE1, &TCDm[0]);

	TCDm[0].CSR &= ~(DMA_TCD_CSR_DREQ(1));					/* DREQ = 0: Keep DMA CH active after major loop */
	TCDm[0].CSR |= DMA_TCD_CSR_ESG(1);						/* ESG = 1: Enable Scatter Gather feature	*/
	TCDm[0].DLASTSGA = DMA_TCD_DLASTSGA_DLASTSGA(&TCDm[1]);	/* Indicate where in the memory is the TCD configuration to be used next */

	/* Saving TCD configuration in RAM */
	DMA_TCDm_config((uint32_t *)&TCD0_Source_2[0], SOFF, (uint32_t *)&TCD0_Destination[6], DOFF, SIZE2, &TCDm[1]);

	DMA_TCD_Push(0,&TCDm[0]);								/* "Push" TCD with index 0 to DMA channel 0 */
	DMA -> SERQ = DMA_SERQ_SERQ(0);							/* Enable DMA CH0 request */

	/*!
	* Infinite for:
	*/
    for (;;);
}

void DMA0_IRQHandler (void)
{
	 DMA -> CDNE |= DMA_CDNE_CADN(0x0);						/* Clear all Done status bit */
	 DMA -> CINT |= 0;										/* Clear Interrupt request */
	 /* Set a breakpoint here and keep an eye on the TCD_LC_Dest Array inside the DMA driver */
}
