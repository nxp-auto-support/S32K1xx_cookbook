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
 * ==============================================================================
 * A simple LPSPI transfer is performed using FIFOs which can improve throughput.
 * After initialization, a 16 bit frame is transmitted at 1 Mbps. Software will
 * poll flags rather than using interrupts and/or DMA.
 * */

#include "device_registers.h"           		/* include peripheral declarations S32K144W */
#include "LPSPI.h"
#include "clocks_and_modes_ht.h"

#define PTD0 (0)   								/* Port D0: FRDM EVB output to LPSPI1_SCK */
#define PTD1 (1)								/* Port D1: FRDM EVB output to LPSPI1_SIN */
#define PTD2 (2)   								/* Port D2: FRDM EVB output to LPSPI1_SOUT */
#define PTD3 (3)								/* Port D3: FRDM EVB output to LPSPI1_PCS3 */

uint16_t tx_16bits = 0xFD00;
uint16_t LPSPI1_16bits_read;

/*!
* @brief PORTn Initialization
*/
void PORT_init (void)
{
	/*!
  	*             Pins Definitions
  	* =======================================
  	*
  	*    Pin Number     |     Function
  	* ----------------- |------------------
  	* PTD0              | LPSPI1 [SCK]
  	* PTD1              | LPSPI1 [SIN]
  	* PTD2			 	| LPSPI1 [SOUT]
  	* PTD3			 	| LPSPI1 [PCS3]
  	*/

    PCC -> PCCn[PCC_PORTD_INDEX] |= PCC_PCCn_CGC_MASK; 		/* Enable clock for PORT D */

    PORTD -> PCR[PTD0] |= PORT_PCR_MUX(3); 					/* Port D0: MUX = ALT3, LPSPI1_SCK */
    PORTD -> PCR[PTD1] |= PORT_PCR_MUX(3); 					/* Port D1: MUX = ALT3, LPSPI1_SIN */
    PORTD -> PCR[PTD2] |= PORT_PCR_MUX(3); 					/* Port D2: MUX = ALT3, LPSPI1_SOUT */
    PORTD -> PCR[PTD3] |= PORT_PCR_MUX(3); 					/* Port D3: MUX = ALT3, LPSPI1_PCS3 */
}

void WDOG_disable (void)
{
	WDOG -> CNT = 0xD928C520;     							/* Unlock watchdog */
    WDOG -> TOVAL = 0x0000FFFF;   							/* Maximum timeout value */
    WDOG -> CS = 0x00002100;    							/* Disable watchdog */
}

int main (void)
{
	uint32_t counter = 0;

	/*!
	 * Initialization:
	 */
	WDOG_disable();		   								/* Disable WDOG */
	SOSC_init_8MHz();        							/* Initialize system oscillator for 8 MHz xtal */
	SPLL_init_160MHz();      							/* Initialize SPLL to 160 MHz with 8 MHz SOSC */
	NormalRUNmode_80MHz();   							/* Init clocks: 80 MHz sysclk & core, 40 MHz bus, 20 MHz flash */

	PORT_init();             							/* Configure ports */
	LPSPI1_init_master();    							/* Initialize LPSPI1 as master */

	/*!
	 * Infinite for:
	 */
	for (;;)
	{
		LPSPI1_transmit_16bits(tx_16bits);       		/* Transmit half word (16 bits) on LPSPI1 */
		LPSPI1_16bits_read = LPSPI1_receive_16bits(); 	/* Receive half word on LSPI1 */
		counter++;
	}
}
