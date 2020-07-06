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
 * ============================================================================================================
 * A FlexCAN module is initialized for 500 KHz (2 usec period) bit time based on an 8 MHz crystal.
 * Message buffer 0 transmits 8 byte messages and message buffer 4 can receive 8 byte messages.
 * To enable signals to the CAN bus, the SBC must be powered with external 12 V. EVBs with SBC
 * MC33903 require CAN transceiver configuration with SPI. EVBs with SBC UJA1169 do not require configuration.
 *
 * By default, the example configures for SBC MC33903 and “Node A” IDs. If a second EVB or CAN tool
 * is available, “Node B” IDs can be used for the tool or second EVB. FlexCAN.h file contains controls for
 * initializing Node A vs B and selecting SBC MC33903.
 * */

#include "device_registers.h" 								/* include peripheral declarations S32K144W */
#include "FlexCAN.h"
#include "clocks_and_modes_ht.h"

#define PTE4 (4)   											/* Port E4: FRDM EVB output to CAN0_RX */
#define PTE5 (5)											/* Port E5: FRDM EVB output to CAN0_TX */
#define PTE0 (0) 											/* Port E0: FRDM EVB output to green LED */

/*!
* @brief PORTn Initialization
*/
void PORT_init (void)
{
	/*!
	 *             Pins Definitions
	 * =======================================
	 *
	 *    Pin Number     |    Function
	 * ----------------- |------------------
	 * PTE4              | CAN0 [Rx]
	 * PTE5              | CAN0 [Tx]
	 * PTE0			     | GPIO [GREEN_LED]
	 */

	PCC -> PCCn[PCC_PORTE_INDEX] |= PCC_PCCn_CGC_MASK;		/* Enable clock for PORT E */

	PORTE -> PCR[PTE4] |= PORT_PCR_MUX(5);					/* Port E4: MUX = ALT5, CAN0_RX */
	PORTE -> PCR[PTE5] |= PORT_PCR_MUX(5); 					/* Port E5: MUX = ALT5, CAN0_TX */

	PORTE -> PCR[PTE0] = PORT_PCR_MUX(1);  					/* Port D16: MUX = GPIO */

	GPIOE -> PDDR |= 1<<PTE0;            	 				/* Port D16: Data direction = output */

	GPIOE -> PSOR |= 1<<PTE0;								/* Turn off green LED */
}

void WDOG_disable (void)
{
	WDOG -> CNT = 0xD928C520;     							/* Unlock watchdog */
	WDOG -> TOVAL = 0x0000FFFF;   							/* Maximum timeout value */
	WDOG -> CS = 0x00002100;    							/* Disable watchdog */
}

int main (void)
{
	uint32_t rx_msg_count = 0;								/* Receive message counter */

	/*!
	 * Initialization:
	 */
	WDOG_disable();		 									/* Disable WDOG */
	SOSC_init_8MHz();      									/* Initialize system oscillator for 8 MHz xtal */
	SPLL_init_160MHz();    									/* Initialize SPLL to 160 MHz with 8 MHz SOSC */
	NormalRUNmode_80MHz(); 									/* Init clocks: 80 MHz sysclk & core, 40 MHz bus, 20 MHz flash */

	PORT_init();             								/* Configure ports */
	FLEXCAN0_init();         								/* Initialize FlexCAN0 */

	#ifdef NODE_A              								/* Node A transmits first; Node B transmits after reception */
		FLEXCAN0_transmit_msg(); 							/* Transmit initial message from Node A to Node B */
	#endif

	/*!
	 * Infinite for:
	 */
	for (;;)												/* Loop: if a message is received, transmit a message */
	{
		if ((CAN0 -> IFLAG1 >> 4) & 1)  					/* If CAN 0 MB 4 flag is set (received message), read MB4 */
		{
			FLEXCAN0_receive_msg ();      					/* Read message */
			rx_msg_count++;               					/* Increment receive message counter */

			if (rx_msg_count == 1000)  						/* If 1000 messages have been received */
			{
				GPIOE -> PTOR |= 1<<PTE0;         			/* Toggle output port E0 (Green_LED) */
				rx_msg_count = 0;           				/* Reset message counter */
			}

			FLEXCAN0_transmit_msg ();     					/* Transmit message using MB0 */
		}
	}
}
