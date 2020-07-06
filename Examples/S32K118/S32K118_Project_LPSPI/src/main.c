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
 */

#include "device_registers.h" 	/* include peripheral declarations S32K118 */
#include "LPSPI_S32K11x.h"
#include "clocks_and_modes_S32K11x.h"

  uint16_t tx_16bits = 0x2580;
  uint16_t LPSPI0_16bits_read;

void WDOG_disable (void)
{
	WDOG->CNT=0xD928C520;     /* Unlock watchdog 		*/
    WDOG->TOVAL=0x0000FFFF;   /* Maximum timeout value */
    WDOG->CS = 0x00002100;    /* Disable watchdog 		*/
}

void PORT_init (void)
{
	/*!
	 * Pins definitions
	 * ===================================================
	 *
	 * Pin number        | Function
	 * ----------------- |------------------
	 * PTB2         	 | SBC SCK
	 * PTB3     	     | SBC MISO
	 * PTB4				 | SBC MOSI
	 * PTB5				 | SBC CS0
	 */
  PCC->PCCn[PCC_PORTB_INDEX] |= PCC_PCCn_CGC_MASK; /* Enable clock for PORTB */
  PORTB->PCR[2] |= PORT_PCR_MUX(3); /* Port B2: MUX = ALT3, LPSPI0 SCK */
  PORTB->PCR[3] |= PORT_PCR_MUX(3); /* Port B3: MUX = ALT3, LPSPI0 SIN */
  PORTB->PCR[4] |= PORT_PCR_MUX(3); /* Port B4: MUX = ALT3, LPSPI0 SOUT */
  PORTB->PCR[5] |= PORT_PCR_MUX(4); /* Port B5: MUX = ALT3, LPSPI0 PCS0 */
}

int main(void)
{
  uint32_t counter = 0;

	/*!
	 * Initialization:
	 * =======================
	 */
  	  WDOG_disable();		   /* Disable WDOG */
  	  SOSC_init_40MHz(); /* Initialize system oscillator for 40 MHz xtal */
  	  RUN_mode_48MHz();	/* Init clocks: 48 MHz sys, core and bus,
										24 MHz flash. */
	  LPSPI0_init_master();    /* Initialize LPSPI0 as master */
	  PORT_init();             /* Configure ports */

	/*!
	 * Infinite for:
	 * ========================
	 */
		  for(;;)
		  {
			LPSPI0_transmit_16bits(tx_16bits);       		/* Transmit half word (16 bits) on LPSPI0 */
//			LPSPI0_16bits_read = LPSPI0_receive_16bits(); 	/* Receive half word on LPSPI0 */
			counter++;
		  }
}


