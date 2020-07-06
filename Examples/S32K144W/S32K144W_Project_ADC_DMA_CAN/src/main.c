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
 * You will need 2 boards for this project to work properly as you have to set up one of them as Node 1
 * and the other as Node 2 to cover all the functionality of the project. Node 1 is configured so it sends
 * a CAN petition to Node 2 asking for the ADC value of the potentiometer or a PIN depending on which switch
 * is pressed down in Node 1. Meanwhile Node 2 is configured to constantly measure each ADC (Potentiometer
 * and Pin) and save the measurements in an array through DMA requests after the COCO flag of the ADC is
 * activated, when Node 2 receives a request from Node 1 it starts a transmission through CAN to send
 * the last measures to Node 1.
 *
 * The PIN is PTB0.
 * */

#include "device_registers.h"								/* include peripheral declarations S32K144W */
#include "clocks_and_modes_ht.h"
#include "dma.h"
#include "ADC.h"
#include "pdb.h"
#include "FlexCAN_FD.h"

#define PTE4 (4)   											/* Port E4: FRDM EVB output to CAN0_RX */
#define PTE5 (5)											/* Port E5: FRDM EVB output to CAN0_TX */
#define PTD2 (2)											/* Port D2: FRDM EVB input to SW2 */
#define PTD3 (3)											/* Port D3: FRDM EVB input to SW3 */

#define Condition1_Pin2 ((PORTD -> PCR[PTD2] & PORT_PCR_ISF_MASK) >> PORT_PCR_ISF_SHIFT)	/* Used to check if the interruption flag of PTD2 is activated */
#define Condition2_Pin2 ((PORTD -> PCR[PTD2] & PORT_PCR_IRQC_MASK) >> PORT_PCR_IRQC_SHIFT)	/* Used to check if the interruption config. has changed for PTD2 */
#define Condition1_Pin3 ((PORTD -> PCR[PTD3] & PORT_PCR_ISF_MASK) >> PORT_PCR_ISF_SHIFT)	/* Used to check if the interruption flag of PTD3 is activated */
#define Condition2_Pin3 ((PORTD -> PCR[PTD3] & PORT_PCR_IRQC_MASK) >> PORT_PCR_IRQC_SHIFT)	/* Used to Check if the interruption config. has changed for PTD3*/

uint32_t pot_value;											/* Variable to save the Value of the POT received by Node_1 from Node_2 */
uint32_t pin_value;											/* Variable to save the Value of the PIN received by Node_1 from Node_2	*/
uint32_t adc_nodo2[4];										/* TCD Destination Array of the DMA to deposit the ADC0 measurements in Node_2 */

void PORT_init (void)
{
	/*!
	*            Pins Definitions
	* ========================================
	*
	*    Pin Number     |    Function
	* ----------------- |------------------
	* PTE4              | CAN0 [Rx]
	* PTE5              | CAN0 [Tx]
	* PTD2              | GPIO [BUTTON_SW2]
	* PTD3				| GPIO [BUTTON_SW3]
	*/

	PCC -> PCCn[PCC_PORTE_INDEX] |= PCC_PCCn_CGC_MASK;		/* Enable the clock for PORT E */

	PORTE -> PCR[PTE4] |= PORT_PCR_MUX(5);					/* Selected PE4 as Rx CAN */
	PORTE -> PCR[PTE5] |= PORT_PCR_MUX(5);					/* Selected PE5 as Tx CAN */

	#ifdef Node_1

		PCC -> PCCn[PCC_PORTD_INDEX] |= PCC_PCCn_CGC_MASK;	/* Enable the clock for PORT D */

		PORTD -> PCR[PTD2] |= PORT_PCR_MUX(1)				/* Selected PD2 as GPIO */
						   |  PORT_PCR_IRQC(0b1001);		/* Enable interruption in rising edge */

		GPIOD -> PDDR &=~ 1<<PTD2;							/* Pin is configured as input */

		PORTD -> PCR[PTD3] |= PORT_PCR_MUX(1)				/* Selected PD3 as GPIO */
						   |  PORT_PCR_IRQC(0b1001);		/* Enable interruption in rising edge */

		GPIOD -> PDDR &=~ 1<<PTD3;							/* Pin is configured as input */

	#endif
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

int main (void)
{
	/*!
	* Initialization:
	*/
	WDOG_disable();        									/* Disable WDOG */
	SOSC_init_8MHz();      									/* Initialize system oscilator for 8 MHz xtal */
	SPLL_init_160MHz();    									/* Initialize SPLL to 160 MHz with 8 MHz SOSC */
	NormalRUNmode_80MHz(); 									/* Init clocks: 80 MHz sysclk & core, 40 MHz bus, 20 MHz flash */

	PORT_init();		  									/* Configure PINs to work for CANFD and set up the interruption if Node_1 is defined */
	Enable_Interrupt(PORTD_IRQn);							/* Enable Port C interrupt */
	S32_NVIC -> IP[PORTD_IRQn] = 1;							/* Level of priority (0 - 15) */

	FLEXCAN_FD_Config();									/* Initialize FLEXCAN FD if Node_1 is defined ID = 0x5111 else if Node_2 is define ID = 0x555 */

	#ifdef Node_2
		DMA_Config(adc_nodo2);								/* Set up DMAMUX CH3 with ADC0 COCO requests and set up the TCD Source and Destination */
		ADC_calibration_init(0,0);							/* Starts ADC calibration	*/
		ADC_Config(9);										/* Set up the ADC0 Channels to be used by HW Trigger of the PDB */
		PDB_Config();										/* Set up the PDB to trigger ADC */
	#endif

	/*!
	 * Infinite for:
	 */
	for (;;);
}

/*!
* Interruptions:
*/

#ifdef Node_1
/******************************************************************************
 * When one of the switch is pressed down an interrupt is enabled and a CAN
 * transmission is executed to request the value of the ADC on
 * node 2, depending on the switch the request could be the Pot
 * or a Pin (POT = SWITCH_2 and PIN = SWITCH_3)
 *****************************************************************************/
void PORTD_IRQHandler (void)
{
	if (Condition1_Pin2 && Condition2_Pin2)								/* POT Measure */
	{
		PORTD -> PCR[PTD2] |= PORT_PCR_ISF_MASK;						/* Turn off flag of interruption */
		CAN0 -> IFLAG1 = CAN_IFLAG1_BUF0I_MASK;							/* Clear MB0 Flag */

		CAN0 -> RAMn[0 * MsgBuffSize + 2] = 0xA;						/* Message word 1 */
		CAN0 -> RAMn[0 * MsgBuffSize + 3] = 0x87654321;					/* Message word 2 */
		CAN0 -> RAMn[0 * MsgBuffSize + 1] = 0x555<<18;					/* ID receiver */
		CAN0 -> RAMn[0 * MsgBuffSize + 0] = 1<<31						/* CAN FD format */
										  | 1<<30						/* Bit Rate switch */
										  | 0b1100<<24					/* Activate buffer to transmit */
										  | 1<<22						/* ??? */
										  | 0b1111<<16					/* 64 bytes */
										  | 8<<CAN_WMBn_CS_DLC_SHIFT;
	}

	if (Condition1_Pin3 && Condition2_Pin3)								/* Pin Measure */
	{
		PORTD -> PCR[PTD3] |= PORT_PCR_ISF_MASK;						/* Turn off flag of interruption */
		CAN0 -> IFLAG1 = CAN_IFLAG1_BUF0I_MASK;							/* Clear MB0 Flag */

		CAN0 -> RAMn[0 * MsgBuffSize + 2] = 0xB;						/* Message word 1 */
		CAN0 -> RAMn[0 * MsgBuffSize + 3] = 0x12345678;					/* Message word 2 */
		CAN0 -> RAMn[0 * MsgBuffSize + 1] = 0x555<<18;					/* ID receiver */
		CAN0 -> RAMn[0 * MsgBuffSize + 0] = 1<<31						/* CAN FD format */
										  | 1<<30						/* Bit Rate switch */
										  | 0b1100<<24					/* Activate buffer to transmit */
										  | 1<<22						/* ??? */
										  | 0b1111<<16					/* 64 bytes */
										  | 8<<CAN_WMBn_CS_DLC_SHIFT;
	}
}
#endif

/******************************************************************************
 * When the receptions ends the interruption is enable,
 * in this interruption the information from the bus is storaged, if
 * the information is coming from Node_1 to Node_2 then a transmission
 * begins from Node_2 to Node_1 with the corresponding value from the
 * ADC.
 *****************************************************************************/
void CAN0_ORed_0_15_MB_IRQHandler (void)
{
	/* Code field */
	RexCode = (CAN0 -> RAMn[4 * MsgBuffSize + 0] & 0x0F000000) >> 24;

	/* Message ID */
	RexID = (CAN0 -> RAMn[4 * MsgBuffSize + 1] & CAN_WMBn_ID_ID_MASK) >> CAN_WMBn_ID_ID_SHIFT;

	/* Message length (32 bits) */
	RexLength = (CAN0 -> RAMn[4 * MsgBuffSize + 0] & CAN_WMBn_CS_DLC_MASK) >> CAN_WMBn_CS_DLC_SHIFT;

	for(count = 0; count < 2; count++)
	{
		/* Extracting words from the message */
		RexData[count] = CAN0 -> RAMn[4 * MsgBuffSize + 2 + count];
	}

	RexTime = CAN0 -> TIMER;             								/* Read TIMER to unlock message buffers */
	CAN0 -> IFLAG1 = 0x00000010;      									/* Clear CAN0 MB4 flag */

	#ifdef Node_1

		if(RexData[0] == 0xA)											/* Pot Measure */
		{
			pot_value = RexData[1];
		}

		if(RexData[0] == 0xB)											/* Pin Measure */
		{
			pin_value = RexData[1];
		}
	#endif

	#ifdef Node_2

		CAN0 -> IFLAG1 = CAN_IFLAG1_BUF0I_MASK;							/* Clear MB0 Flag */

		if(RexData[0] == 0xA)											/* Pot Measure request */
		{
			CAN0 -> RAMn[0 * MsgBuffSize + 2] = 0xA;					/* Message word 1 */
			CAN0 -> RAMn[0 * MsgBuffSize + 3] = adc_nodo2[1];			/* Message word 2 */
			CAN0 -> RAMn[0 * MsgBuffSize + 1] = 0x511<<18;				/* ID receiver */
			CAN0 -> RAMn[0 * MsgBuffSize + 0] = 1<<31					/* CAB FD format */
											  | 1<<30					/* Bit Rate switch */
											  | 0b1100<<24				/* Activate buffer to transmit */
											  | 1<<22					/* ??? */
											  | 0b1111<<16				/* 64 bytes */
											  | 8<<CAN_WMBn_CS_DLC_SHIFT;
		}

		if(RexData[0] == 0xB)											/* Pin Measure request */
		{
			CAN0 -> RAMn[0 * MsgBuffSize + 2] = 0xB;					/* Message word 1 */
			CAN0 -> RAMn[0 * MsgBuffSize + 3] = adc_nodo2[2];			/* Message word 2 */
			CAN0 -> RAMn[0 * MsgBuffSize + 1] = 0x511<<18;				/* ID receiver */
			CAN0 -> RAMn[0 * MsgBuffSize + 0] = 1<<31					/* CAB FD format */
											  | 1<<30					/* Bit Rate switch */
											  | 0b1100<<24				/* Activate buffer to transmit */
											  | 1<<22					/* ??? */
											  | 0b1111<<16				/* 64 bytes */
											  | 8<<CAN_WMBn_CS_DLC_SHIFT;
		}
	#endif
}
