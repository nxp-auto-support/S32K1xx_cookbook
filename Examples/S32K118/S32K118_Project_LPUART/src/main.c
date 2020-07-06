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
 * ==========================================================================================
 * This example performs a simple UART transfer to a COM port on a PC. FIFOs, interrupts and
 * DMA are not implemented. The Open SDA interface can be used on the evaluation board, where 
 * the UART signals are transferred to a USB interface, which can connect to a PC which has a 
 * terminal emulation program such as PUTTY, TeraTerm or other software.
 * */

#include "device_registers.h" 	/* include peripheral declarations S32K118 */
#include "clocks_and_modes_S32K11x.h"
#include "LPUART_S32K11x.h"

char data=0;
void PORT_init (void)
{
	/*!
	 * Pins definitions
	 * ===================================================
	 *
	 * Pin number        | Function
	 * ----------------- |------------------
	 * PTB0              | LPUART0 RX
	 * PTB1              | LPUART0 TX
	 */
	  PCC->PCCn[PCC_PORTB_INDEX]|=PCC_PCCn_CGC_MASK;	/* Enable clock for PORT B */
	  PORTB->PCR[0]|=PORT_PCR_MUX(2);	/* Port B, bit 0, ALT=2: UART RX. */
	  PORTB->PCR[1]|=PORT_PCR_MUX(2);	/* Port B, bit 1: ALT=2: UART TX. */
}

void WDOG_disable (void)
{
  WDOG->CNT=0xD928C520;     /* Unlock watchdog 		*/
  WDOG->TOVAL=0x0000FFFF;   /* Maximum timeout value 	*/
  WDOG->CS = 0x00002100;    /* Disable watchdog 		*/
}

int main(void)
{
	/*!
	 * Initialization:
	 * =======================
	 */
  WDOG_disable();        /* Disable WDOG */
  PORT_init();           /* Configure ports */
  SOSC_init_40MHz(); 	/* Initialize system oscillator for 40 MHz xtal */
  RUN_mode_48MHz();		/* Init clocks: 48 MHz sys, core and bus,
	  	  	  	  	  	  	  	  	  	24 MHz flash. */

  LPUART0_init();        /* Initialize LPUART @ 9600*/
  LPUART0_transmit_string("Running LPUART example\n\r");     /* Transmit char string */
  LPUART0_transmit_string("Input character to echo...\n\r"); /* Transmit char string */

	/*!
	 * Infinite for:
	 * ========================
	 */
	  for(;;)
	  {
		  LPUART0_transmit_char('>');  		/* Transmit prompt character*/
		  LPUART0_receive_and_echo_char();	/* Wait for input char, receive & echo it*/
	  }
}


