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

#include "device_registers.h"	/* include peripheral declarations S32K144 */
#include "LPUART.h"

void LPUART1_init(void)  /* Init. summary: 115200 baud, 1 stop bit, 8 bit format, no parity */
{
	PCC->PCCn[PCC_LPUART1_INDEX] &= ~PCC_PCCn_CGC_MASK;    /* Ensure clk disabled for config */
	PCC->PCCn[PCC_LPUART1_INDEX] |= PCC_PCCn_PCS(0b010)    /* Clock Src = 2 (SIRCDIV2_CLK) */
                            	 |  PCC_PCCn_CGC_MASK;     /* Enable clock for LPUART1 regs */

	LPUART1->BAUD = LPUART_BAUD_SBR(0x4)  	/* Initialize for 115200 baud, 1 stop: */
                	|LPUART_BAUD_OSR(16);  	/* SBR=4 (0x4): baud divisor = 8M/115200/17 = ~4 */
											/* OSR=16: Over sampling ratio = 16+1=17 */
											/* SBNS=0: One stop bit */
											/* BOTHEDGE=0: receiver samples only on rising edge */
											/* M10=0: Rx and Tx use 7 to 9 bit data characters */
											/* RESYNCDIS=0: Resync during rec'd data word supported */
											/* LBKDIE, RXEDGIE=0: interrupts disable */
											/* TDMAE, RDMAE, TDMAE=0: DMA requests disabled */
											/* MAEN1, MAEN2,  MATCFG=0: Match disabled */

	LPUART1->CTRL =	LPUART_CTRL_RE_MASK
					|LPUART_CTRL_TE_MASK;   	/* Enable transmitter & receiver, no parity, 8 bit char: */
												/* RE=1: Receiver enabled */
												/* TE=1: Transmitter enabled */
												/* PE,PT=0: No hw parity generation or checking */
												/* M7,M,R8T9,R9T8=0: 8-bit data characters*/
												/* DOZEEN=0: LPUART enabled in Doze mode */
												/* ORIE,NEIE,FEIE,PEIE,TIE,TCIE,RIE,ILIE,MA1IE,MA2IE=0: no IRQ*/
												/* TxDIR=0: TxD pin is input if in single-wire mode */
												/* TXINV=0: TRansmit data not inverted */
												/* RWU,WAKE=0: normal operation; rcvr not in statndby */
												/* IDLCFG=0: one idle character */
												/* ILT=0: Idle char bit count starts after start bit */
												/* SBK=0: Normal transmitter operation - no break char */
												/* LOOPS,RSRC=0: no loop back */
}

void LPUART1_transmit_char(char send) {    /* Function to Transmit single Char */
	while((LPUART1->STAT & LPUART_STAT_TDRE_MASK)>>LPUART_STAT_TDRE_SHIFT==0);
	/* Wait for transmit buffer to be empty */
	LPUART1->DATA=send;              /* Send data */
}

void LPUART1_transmit_string(char data_string[])  {  /* Function to Transmit whole string */
	uint32_t i=0;
	while(data_string[i] != '\0')  {           /* Send chars one at a time */
		LPUART1_transmit_char(data_string[i]);
		i++;
	}
}

char LPUART1_receive_char(void) {    /* Function to Receive single Char */
	char receive;
	while((LPUART1->STAT & LPUART_STAT_RDRF_MASK)>>LPUART_STAT_RDRF_SHIFT==0);
	/* Wait for received buffer to be full */
	receive= LPUART1->DATA;            /* Read received data*/
	return receive;
}

void LPUART1_receive_and_echo_char(void)  {  /* Function to echo received char back */
	char send = LPUART1_receive_char();        /* Receive Char */
	LPUART1_transmit_char(send);               /* Transmit same char back to the sender */
	LPUART1_transmit_char('\n');               /* New line */
	LPUART1_transmit_char('\r');               /* Return */
}

/*!
* @brief Stores data from the LPUART1 Rx buffer until ENTER key is pressed.
*
* @return[uint16_t result] 16-bit Data Result from Rx buffer
*/
uint16_t LPUART1_receive_int (void)
{
	uint16_t data = 0;									/* Initialize data with zero every time when the ENTER key is pressed */
	uint16_t result;
	uint8_t data_temp;

	do													/* Ensure to perform the data reading at least once */
	{
		data_temp = LPUART1_receive_char();				/* Read received char from LPUART1 buffer */

		if (data_temp != 13)							/* Check if the received char is equal to CR or not */
														/* NOTE: 13 = CR (Carriage Return) in ASCII code. CR is the ENTER key on the keyboard */
		{
			data = (data * 10) + (data_temp - 48);		/* Store data from the LPUART1 buffer in a single variable */
														/* NOTE: 48 = 0 in ASCII code. Is used to cast between char and int. */
		}
	}
	while (data_temp != 13);							/* Do the data reading until CR (ENTER) is pressed */

	result = data;										/* Store final result after the ENTER key is pressed and before data becomes zero again */

	LPUART1_transmit_string("\n\n");					/* Print two new lines */

	return result;
}

/*!
* @brief Convert int data to char to be able to transmit it by UART.
* NOTE: This function can convert 5 digit values to char. If you want to convert larger values just modify the uart_data array size
*
* @param[uint16_t data] 16-bit Data to be transmitted by UART
*/
void LPUART1_int_to_char(uint16_t data)
{
	int i=0;											/* Counter */
	char uart[5]={0,0,0,0,0};							/* Value sent by UART. It stores the value digit by digit */

	char ascii[10]={48,49,50,51,52,53,54,55,56,57};		/* ASCII array code from 0 to 9. Ex. 50 = 2 in ASCII code*/


	while(data != 0){									/* While data is different from zero */
		uint16_t data_temp = data;
		data_temp = data_temp % 10;						/* Get the less significant digit */
		uart[i++] = ascii[data_temp];					/* Change int value to char */
		data = (data - data_temp) / 10;					/* Update data */
	}
	while(i >= 0)  {           							/* Send chars one at a time */
			LPUART1_transmit_char(uart[i--]);
	}
}
