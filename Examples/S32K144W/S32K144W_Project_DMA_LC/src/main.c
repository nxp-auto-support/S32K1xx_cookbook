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
 * This project intends to show the Linking Channel Feature of the DMA where you can set up a link
 * so when a channel finishes a major or minor loop it activates another DMA channel and send
 * information from different sources or to different destinations or both. In this case we use it to link
 * CH0 to CH1 after CH0's major loop to copy the phrase "Hello World" from one string to another.
 * */

#include "device_registers.h"					/* include peripheral declarations S32K144W */
#include "clocks_and_modes_ht.h"
#include "dma.h"

void WDOG_disable (void)
{
	WDOG -> CNT = 0xD928C520;     				/* Unlock watchdog */
	WDOG -> TOVAL = 0x0000FFFF;   				/* Maximum timeout value	*/
	WDOG -> CS = 0x00002100;    				/* Disable watchdog */
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
	WDOG_disable();        						/* Disable WDOG */
	SOSC_init_8MHz();      						/* Initialize system oscilator for 8 MHz xtal */
	SPLL_init_160MHz();    						/* Initialize SPLL to 160 MHz with 8 MHz SOSC */
	NormalRUNmode_80MHz(); 						/* Init clocks: 80 MHz sysclk & core, 40 MHz bus, 20 MHz flash */

	DMAMUX_LC_init();	   						/* Initialize DMAMUX to always generate DMA requests for DMA CH0 and CH1	*/
	DMA_TCD_LC_Config();						/* Set up DMA TCD CH0 and CH1 to work with linking channel to completely 'save' "Hello World" */

	DMA -> SERQ |= DMA_SERQ_SERQ(0);			/* Enable DMA CH0 request */

	Enable_Interrupt(DMA1_IRQn);				/* Enable DMA CH1 interrupt */

	/*!
	 * Infinite for:
	 */
	for (;;)
	{
		/* Look for the TCD_LC_Dest array inside the dma driver */
    }
}

void DMA1_IRQHandler (void)
{
	 DMA -> CDNE |= DMA_CDNE_CADN_MASK;			/* Clear Done status bit */
	 DMA -> CINT |= DMA_CINT_CINT(1);			/* Clear Interrupt request */
	 /* Set a breakpoint here and keep an eye on the TCD_LC_Dest Array inside the DMA driver */
}
