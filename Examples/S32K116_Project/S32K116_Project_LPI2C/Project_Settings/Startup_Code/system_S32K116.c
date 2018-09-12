/*
** ###################################################################
**     Processor:           S32K116_16
**
**     Reference manual:    S32K14XRM Rev. 2 Draft B, 11/2016
**
**     Abstract:
**         Provides a system configuration function and a global variable that
**         contains the system frequency. It configures the device and initializes
**         the oscillator (PLL) that is part of the microcontroller device.
**
**     Copyright (c) 2015 Freescale Semiconductor, Inc.
**     Copyright 2016-2017 NXP
**     All rights reserved.
**
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
** ###################################################################
*/

/*!
 * @file S32K116
 * @version 1.0
 * @date 2017-09-13
 * @brief Device specific configuration file for S32K116 (implementation file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#include <stdint.h>
#include "system_S32K116.h"
#include "S32K116.h"




/* ----------------------------------------------------------------------------
   -- Core clock
   ---------------------------------------------------------------------------- */

uint32_t SystemCoreClock = DEFAULT_SYSTEM_CLOCK;

/* ----------------------------------------------------------------------------
   -- SystemInit()
   ---------------------------------------------------------------------------- */

void SystemInit (void) {

#if (DISABLE_WDOG)
  uint32_t cs = WDOG->CS;
  WDOG->CS = (uint32_t) (cs & ~WDOG_CS_EN_MASK);
  WDOG->TOVAL = 0x4;
#endif /* (DISABLE_WDOG) */

#ifdef CLOCK_SETUP
  if(PMC->REGSC &  PMC_REGSC_ACKISO_MASK) {
    PMC->REGSC |= PMC_REGSC_ACKISO_MASK; /* VLLSx recovery */
  }

  /* Power mode protection initialization */
#ifdef SYSTEM_SMC_PMPROT_VALUE
  SMC->PMPROT = SYSTEM_SMC_PMPROT_VALUE;
#endif

  /* System clock initialization */
  SCG->RCCR=SCG_RCCR_VALUE;
  SCG->VCCR=SCG_VCCR_VALUE;
  SCG->HCCR=SCG_HCCR_VALUE;

#ifdef SCG_MODE_FIRC_48M
  SCG->FIRCDIV=SCG_FIRCDIV_VALUE;
  SCG->FIRCCFG=SCG_FIRCCFG_VALUE;
  SCG->FIRCTCFG=SCG_FIRCTCFG_VALUE;
  SCG->FIRCCSR=SCG_FIRCCSR_VALUE;
  while(!SCG->FIRCCSR & SCG_FIRCCSR_FIRCVLD_MASK);
#elif defined SCG_MODE_SIRC_8M || defined SCG_MODE_SIRC_2M
  SCG->SIRCTDIV=SCG_SIRCDIV_VALUE;
  SCG->SIRCCFG=SCG_SIRCCFG_VALUE;
  SCG->SIRCTCFG=SCG_SIRCTCFG_VALUE;
  SCG->SIRCCSR=SCG_SIRCCSR_VALUE;
  while(!SCG->SIRCCSR & SCG_SIRCCSR_SIRCVLD_MASK);
#elif defined SCG_MODE_SPLL
  SCG->FIRCDIV=SCG_FIRCDIV_VALUE;
  SCG->FIRCCFG=SCG_FIRCCFG_VALUE;
  SCG->FIRCTCFG=SCG_FIRCTCFG_VALUE;
  SCG->FIRCCSR=SCG_FIRCCSR_VALUE;

  SCG->SPLLDIV=SCG_SPLLDIV_VALUE;
  SCG->SPLLCFG=SCG_SPLLCFG_VALUE;
  SCG->SPLLCSR=SCG_SPLLCSR_VALUE;
  while(!SCG->SPLLCSR & SCG_SPLLCSR_SPLLVLD_MASK);
#endif

  if (((SMC_PMCTRL_VALUE) & SMC_PMCTRL_RUNM_MASK) == SMC_PMCTRL_RUNM(0x02U)) {
    SMC->PMCTRL = (uint8_t)((SMC_PMCTRL_VALUE) & (SMC_PMCTRL_RUNM_MASK)); /* Enable VLPR mode */
    while(SMC->PMSTAT != 0x04U) {      /* Wait until the system is in VLPR mode */
    }
  }
#endif

}
