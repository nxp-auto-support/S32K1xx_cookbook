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

#include "SAI.h"
#include "device_registers.h"

#define BIT_SIZE            (8)   	/* Bit size per word */
#define CHANNEL_MASK        (0xF) 	/* All channels */
#define WATERMARK           (6)   	/* FIFO size is 8, then watermark is set to FIFO_SIZE/2 */

void SAI_init (void)
{
    uint8_t SAI_index;

    PCC->PCCn[PCC_SAI0_INDEX] |= PCC_PCCn_CGC_MASK;  	/* Enable clock for SAI */
    SAI0->TCR2 = SAI_TCR2_BCP_MASK;     				/*! Bit clock is active low with drive outputs on
    									 	 	 	 	 *  falling edge and sample inputs on rising edge. 		*/
    SAI0->TCR3 &= ~SAI_TCR3_WDFL_MASK;  				/* Configures which word sets the start of word flag. 	*/

    SAI0->TCR4 = SAI_TCR4_FCONT_MASK 			/*! On FIFO error, the SAI will continue from
    											 *  the same word that caused the FIFO error	*/
    		    |SAI_TCR4_MF(1U) 				/* MSB is transmitted first. 					*/
				|SAI_TCR4_SYWD(BIT_SIZE - 1)	/* Length of the frame sync in number of bit clocks.*/
                |SAI_TCR4_FSE(0U) 				/* Frame sync asserts with the first bit of the frame. */
				|SAI_TCR4_FSP(0U) 				/* Frame sync is active high.*/
				|SAI_TCR4_FRSZ(1U);				/* One word in each frame */

    /* Set as master */
    SAI0->TCR2 |= SAI_TCR2_BCD_MASK;
    SAI0->TCR4 |= SAI_TCR4_FSD_MASK;

    SAI0->TCR2 &= ~SAI_TCR2_MSEL_MASK;	/* Bit clock source setting: 		*/
    SAI0->TCR2 |= SAI_TCR2_MSEL(0); 	/* Select bus clock as SAI clock 	*/

    /* Asyncrhonous mode */
    SAI0->TCR2 &= ~SAI_TCR2_SYNC_MASK;

    /* Set BCLK if needed */
    if (SAI0->TCR2 & SAI_TCR2_BCD_MASK)
    {
    	SAI0->TCR2 &= ~SAI_TCR2_DIV_MASK;
    	SAI0->TCR2 |= SAI_TCR2_DIV(1);
    }

    /* Left justified protocol */
    /* Bit clock per frame (32) ? */
    SAI0->TCR5 = SAI_TCR5_WNW(BIT_SIZE - 1) | SAI_TCR5_W0W(BIT_SIZE - 1) | SAI_TCR5_FBT(BIT_SIZE - 1);

    /* Disable data channels */
    SAI0->TCR3 &= ~SAI_TCR3_TCE_MASK;

    /* Unmask channel 0 and 1 */
    SAI0->TMR &= ~(0x0F);

    /* Set watermark to FIFO/2 */
    SAI0->TCR1 = SAI_TCR1_TFW(WATERMARK);

    /* Transmitter is enabled in debug mode */
    SAI0->TCSR |= SAI_TCSR_DBGE_MASK;

    /* If synchoronous mode is enabled, then RE bit should also be enabled */
    if (((SAI0->TCR2 & SAI_TCR2_SYNC_MASK) >> SAI_TCR2_SYNC_SHIFT) == 0x01)
    {
    	SAI0->RCSR |= SAI_RCSR_RE_MASK;
    }
    SAI0->TCSR |= SAI_TCSR_TE_MASK;

    /* fill FIFO buffers for all channels */
        for(SAI_index = 0; SAI_index < 8; SAI_index++)
        {
        	SAI0 -> TDR[0] = 0x55555555;
        	SAI0 -> TDR[1] = 0xAAAAAAAA;
        	SAI0 -> TDR[2] = 0xFFFFFFFF;
        	SAI0 -> TDR[3] = 0x01010101;
        }
        SAI0->TCR3 |= SAI_TCR3_TCE(CHANNEL_MASK);
    /* Enable channels on SAI module */
}

void SAI_transfer (void)
{
    uint8_t SAI_index;
    SAI0 -> TCSR &= ~SAI_TCSR_FEF_MASK;

    /* - if Transmit FIFO watermark has been reached: */
        if(((SAI0 -> TCSR & SAI_TCSR_FRF_MASK)>>SAI_TCSR_FRF_SHIFT) == 1)
        {
            for(SAI_index = 0; SAI_index < 4; SAI_index++)
            {
            	/* push the data (0x55555555) into the transmit data FIFO */
            	SAI0 -> TDR[0] = 0x55555555;
            	SAI0 -> TDR[1] = 0x55555555;
            	SAI0 -> TDR[2] = 0x55555555;
            	SAI0 -> TDR[3] = 0x55555555;
            }
        }
}
