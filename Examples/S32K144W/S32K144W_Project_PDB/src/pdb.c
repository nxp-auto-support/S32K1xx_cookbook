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

#include "device_registers.h"	/* include peripheral declarations */
#include "pdb.h"

/*!
	PDB is a timer used to trigger other peripherals, in this case the ADC\n
	For this example, the PDB will be used in continuous mode and triggered by software\n
	When the counter overflows, it will start to count again, and it will trigger the ADC when it reaches the CH0_DLY(1000)\n
	The period is of 9ms\n
*/
void PDB0_init(void)
{
	/* ----- PDB configuration ----- */
	    PCC->PCCn[PCC_PDB0_INDEX] |= PCC_PCCn_CGC_MASK;     /* Enable PDB clock */

	    PDB0->MOD = PDB_MOD_MOD(30000);      /* Period is set to 9 ms */
	    PDB0->IDLY = 10000;                  

	    PDB0->SC = PDB_SC_PDBEIE_MASK |     /* Enable Sequence error interrupt */
	    			PDB_SC_PRESCALER_MASK |   /* PDB frequency is: PDB clock (System Clock) / ((2^PRESCALER) * MULT) */
	                PDB_SC_MULT(0b11) |      /* Selects PDB0_TRG_IN0 input */
	                PDB_SC_LDMOD(0)| /* Load mode 0: The internal registers are loaded with the values from their buffers  immediately after 1 is written to SC[LDOK]. */
					PDB_SC_TRGSEL(0b1111)|/*Software trigger*/
					PDB_SC_CONT(1);       /*Continuous mode*/
	    PDB0->CH[0].C1|=1|PDB_C1_TOS_MASK;
	    PDB0->CH[0].DLY[0] = 1000;

	    PDB0->SC |= PDB_SC_PDBEN_MASK |     /* Enable PDB */
	            PDB_SC_LDOK_MASK;           /* Load values for MOD, IDLY, CHnDLYm, and POyDLY registers */
	    PDB0->SC |= PDB_SC_SWTRIG_MASK
	    		|PDB_SC_LDOK_MASK;

}

/*!	PDB0 configuration for a period of 1s
 * 		PDB0 Period = (Sys. Clock / (Prescaler * Mult factor)) / Counts
 * 		PDB0 Period = 1s
 * 		Delay = 500ms
 * 	Channel 4 is triggered at delay complete, and channel 5, 6, 7 are in
 * 	Back-to-Back mode (wait for n+1 channel to be completed to start n
 * 	channel)
 */
void PDB_Config(void){
	PCC->PCCn[PCC_PDB0_INDEX] &=~ PCC_PCCn_CGC_MASK;	/* Enable clock for PDB */
	PCC->PCCn[PCC_PDB0_INDEX] |= PCC_PCCn_PCS(0b001);	/* Enable clock for PDB */
	PCC->PCCn[PCC_PDB0_INDEX] |= PCC_PCCn_CGC_MASK;		/* Enable clock for PDB */


	PDB0->SC = PDB_SC_PRESCALER(0b111)| /* Prescaler = 128 */
			   PDB_SC_TRGSEL(15)|		/* Software trigger selected */
			   PDB_SC_MULT(0b10)|		/* Mult factor = 20 */
			   PDB_SC_CONT_MASK;		/* Continuous mode Enable */
	PDB0->MOD = 18750;					/* Counts */

	PDB0->CH[0].C1 = (PDB_C1_BB(0xE0)| 	/* Back-to-back for pre-triggers 5/6/7 (wait for channel 4 to be finish)*/
					  PDB_C1_TOS(0x10)| /* Trigger channel 4 when delay is complete */
					  PDB_C1_EN(0xF0));	/* Triggers 4/5/6/7 enabled */
	PDB0->CH[0].DLY[4] = 9375;			/* Delay set to half of the period */

	PDB0->SC |= PDB_SC_PDBEN_MASK|	/* Enable PDB */
				PDB_SC_LDOK_MASK;	/* Load MOD and DLY */

	PDB0->SC |= PDB_SC_SWTRIG_MASK; /* Software Initial PDB trigger */
}

/*!	PDB0 configuration for a period of 1s
 * 		PDB0 Period = (Sys. Clock / (Prescaler * Mult factor)) / Counts
 * 		PDB0 Period = 2s
 * 		Delay = 1s
 * 	Channel 0 is triggered at delay complete.
 */
void PDB_FlexScan_Config(void){
	PCC->PCCn[PCC_PDB0_INDEX] &=~ PCC_PCCn_CGC_MASK;	/* Enable clock for PDB */
	PCC->PCCn[PCC_PDB0_INDEX] |= PCC_PCCn_PCS(0b001);	/* Enable clock for PDB */
	PCC->PCCn[PCC_PDB0_INDEX] |= PCC_PCCn_CGC_MASK;		/* Enable clock for PDB */


	PDB0->SC = PDB_SC_PRESCALER(0b111)| /* Prescaler = 128 */
			   PDB_SC_TRGSEL(15)|		/* Software trigger selected */
			   PDB_SC_MULT(0b10)|		/* Mult factor = 20 */
			   PDB_SC_CONT_MASK;		/* Continuous mode Enable */
	PDB0->MOD = 31250;					/* Counts */

	PDB0->CH[0].C1 =  PDB_C1_TOS(1)| /* Trigger channel 0 when delay is complete */
					  PDB_C1_EN(0x01);	/* Trigger 0 enabled */
	PDB0->CH[0].DLY[0] = 15625;			/* Delay set to half of the period */

	PDB0->SC |= PDB_SC_PDBEN_MASK|	/* Enable PDB */
				PDB_SC_LDOK_MASK;	/* Load MOD and DLY */

	PDB0->SC |= PDB_SC_SWTRIG_MASK; /* Software Initial PDB trigger */
}

