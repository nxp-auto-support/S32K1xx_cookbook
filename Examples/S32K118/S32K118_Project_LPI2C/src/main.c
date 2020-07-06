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
 * ===========================================
 * Initialize I2C Module as Master
 * and sends one single Address ignoring NACKS.
 */

#include "device_registers.h" 	/* include peripheral declarations S32K118 */
#include "lpi2c.h"
#include "clocks_and_modes_S32K11x.h"

void WDOG_disable (void)
{
  WDOG->CNT=0xD928C520;     /* Unlock watchdog 		*/
  WDOG->TOVAL=0x0000FFFF;   /* Maximum timeout value 	*/
  WDOG->CS = 0x00002100;    /* Disable watchdog 		*/
}

void PORT_init(void)
{
    /*!
     * Pins definitions
     * ====================================
     *
     * Pin number        | Function
     * ----------------- |-----------------
     * PTA2              | LPI2C0_SDA
     * PTA3              | LPI2C0_SCL
     */
	PCC->PCCn[PCC_PORTA_INDEX ]|=PCC_PCCn_CGC_MASK;	/* Enable PORTA*/
    PORTA->PCR[2]   |= PORT_PCR_MUX(3)      /* Port A2: MUX = ALT3, LPI2C_SDA */
                                               | PORT_PCR_PE_MASK   /* Pull resistor enable */
                                               | PORT_PCR_PS(1);    /* Pull up selected */
    PORTA->PCR[3]   |= PORT_PCR_MUX(3)      /* Port A3: MUX = ALT3, LPI2C_SCL */
                                                | PORT_PCR_PE_MASK  /* Pull resistor enable */
                                                | PORT_PCR_PS(1);   /* Pull up selected */
}

int main(void)
{
    /*! Initializations
     */
		WDOG_disable();			/* Disable watchdog */
		SOSC_init_40MHz(); 		/* Initialize system oscillator for 40 MHz xtal */
		RUN_mode_48MHz();		/* Init clocks: 48 MHz sys, core and bus,
												24 MHz flash. */
		PORT_init();           /* Init PORT clocks and GPIO outputs */
		LPI2C_init();          /* Initializes LPI2C ignoring NACK*/

    /*! Infinite for
     */
        for(;;)
        {
        	LPI2C_Transmit();	/* Transmit Address: 0x1E, Ignoring NACKs */
        }
}
