/*
** ###################################################################
**     Processor:           S32K144W_M4
**     Reference manual:    Dummy manual version Rev. 1.1 12/2016
**     Version:             rev. 1.0, 2019-04-17
**     Build:               b191023
**
**     Abstract:
**         Provides a system configuration function and a global variable that
**         contains the system frequency. It configures the device and initializes
**         the oscillator (PLL) that is part of the microcontroller device.
**
**     Copyright 2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2019 NXP
**     All rights reserved.
**
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2019-04-17)
**         Initial version.
**
** ###################################################################
*/

/*!
 * @file S32K144W_M4
 * @version 1.0
 * @date 2019-04-17
 * @brief Device specific configuration file for S32K144W_M4 (implementation
 *        file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#include <stdint.h>
#include "stdbool.h"
#include "device_registers.h"


/* ----------------------------------------------------------------------------
   -- Core clock
   ---------------------------------------------------------------------------- */

uint32_t SystemCoreClock = DEFAULT_SYSTEM_CLOCK;

/*FUNCTION**********************************************************************
 *
 * Function Name : SystemInit
 * Description   : This function disables the watchdog, enables FPU
 * and the power mode protection if the corresponding feature macro
 * is enabled. SystemInit is called from startup_device file.
 *
 * Implements    : SystemInit_Activity
 *END**************************************************************************/
void SystemInit(void)
{
/**************************************************************************/
                      /* FPU ENABLE*/
/**************************************************************************/
#ifdef ENABLE_FPU
  /* Enable CP10 and CP11 coprocessors */
  S32_SCB->CPACR |= (S32_SCB_CPACR_CP10_MASK | S32_SCB_CPACR_CP11_MASK);
#ifdef  ERRATA_E6940
  /* Disable lazy context save of floating point state by clearing LSPEN bit
   * Workaround for errata e6940 */
  S32_SCB->FPCCR &= ~(S32_SCB_FPCCR_LSPEN_MASK);
#endif
#endif /* ENABLE_FPU */

/**************************************************************************/
                      /* WDOG DISABLE*/
/**************************************************************************/

#if (DISABLE_WDOG)
  /* Write of the WDOG unlock key to CNT register, must be done in order to allow any modifications*/
  WDOG->CNT = (uint32_t ) FEATURE_WDOG_UNLOCK_VALUE;
  /* The dummy read is used in order to make sure that the WDOG registers will be configured only
   * after the write of the unlock value was completed. */
  (void)WDOG->CNT;

  /* Initial write of WDOG configuration register:
   * enables support for 32-bit refresh/unlock command write words,
   * clock select from LPO, update enable, watchdog disabled */
  WDOG->CS  = (uint32_t ) ( (1UL << WDOG_CS_CMD32EN_SHIFT)                       |
                            (FEATURE_WDOG_CLK_FROM_LPO << WDOG_CS_CLK_SHIFT) |
                            (0U << WDOG_CS_EN_SHIFT)                             |
                            (1U << WDOG_CS_UPDATE_SHIFT)                         );

  /* Configure timeout */
  WDOG->TOVAL = (uint32_t )0xFFFF;
#endif /* (DISABLE_WDOG) */

/**************************************************************************/
            /* ENABLE CACHE */
/**************************************************************************/
#if defined(I_CACHE) && (ICACHE_ENABLE == 1)
  /* Invalidate and enable code cache */
  LMEM->PCCCR = LMEM_PCCCR_INVW0(1) | LMEM_PCCCR_INVW1(1) | LMEM_PCCCR_GO(1) | LMEM_PCCCR_ENCACHE(1);
#endif /* defined(I_CACHE) && (ICACHE_ENABLE == 1) */
}


/*******************************************************************************
 * EOF
 ******************************************************************************/
