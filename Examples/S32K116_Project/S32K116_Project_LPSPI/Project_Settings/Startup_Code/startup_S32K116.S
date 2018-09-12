/* ---------------------------------------------------------------------------------------*/
/*  @file:    startup_S32K116.s                                                           */
/*  @purpose: GNU Compiler Collection Startup File                                        */
/*            S32K116                                                                     */
/*  @version: 1.0                                                                         */
/*  @date:    2017-1-10                                                                   */
/*  @build:   b170107                                                                     */
/* ---------------------------------------------------------------------------------------*/
/*                                                                                        */
/* Copyright (c) 1997 - 2016 , Freescale Semiconductor, Inc.                              */
/* Copyright 2016 NXP                                                                     */
/* All rights reserved.                                                                   */
/*                                                                                        */
/* Redistribution and use in source and binary forms, with or without modification,       */
/* are permitted provided that the following conditions are met:                          */
/*                                                                                        */
/* o Redistributions of source code must retain the above copyright notice, this list     */
/*   of conditions and the following disclaimer.                                          */
/*                                                                                        */
/* o Redistributions in binary form must reproduce the above copyright notice, this       */
/*   list of conditions and the following disclaimer in the documentation and/or          */
/*   other materials provided with the distribution.                                      */
/*                                                                                        */
/* o Neither the name of Freescale Semiconductor, Inc. nor the names of its               */
/*   contributors may be used to endorse or promote products derived from this            */
/*   software without specific prior written permission.                                  */
/*                                                                                        */
/* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND        */
/* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED          */
/* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE                 */
/* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR       */
/* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES         */
/* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;           */
/* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON         */
/* ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT                */
/* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS          */
/* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                           */
/*****************************************************************************/
/* Version: GNU Compiler Collection                                          */
/*****************************************************************************/
    .syntax unified
    .arch armv6-m

    .section .isr_vector, "a"
    .align 2
    .globl __isr_vector
__isr_vector:
    .long   __StackTop                                      /* Top of Stack */
    .long   Reset_Handler                                   /* Reset Handler */
    .long   NMI_Handler                                     /* NMI Handler*/
    .long   HardFault_Handler                               /* Hard Fault Handler*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   SVC_Handler                                     /* SVCall Handler*/
    .long   0                                               /* Reserved*/
    .long   0                                               /* Reserved*/
    .long   PendSV_Handler                                  /* PendSV Handler*/
    .long   SysTick_Handler                                 /* SysTick Handler*/

                                                            /* External Interrupts*/
    .long   DMA0_IRQHandler                                 /* DMA channel 0 transfer complete*/
    .long   DMA1_IRQHandler                                 /* DMA channel 1 transfer complete*/
    .long   DMA2_IRQHandler                                 /* DMA channel 2 transfer complete*/
    .long   DMA3_IRQHandler                                 /* DMA channel 3 transfer complete*/
    .long   DMA_Error_IRQHandler                            /* DMA error interrupt channels 0-3*/
    .long   ERM_fault_IRQHandler                            /* ERM single and double bit error correction*/
    .long   RTC_IRQHandler                                  /* RTC alarm interrupt*/
    .long   RTC_Seconds_IRQHandler                          /* RTC seconds interrupt*/
    .long   LPTMR0_IRQHandler                               /* LPTIMER interrupt request*/
    .long   PORT_IRQHandler                                 /* Port A, B, C, D and E pin detect interrupt*/
    .long   CAN0_ORed_Err_Wakeup_IRQHandler                 /* OR'ed [Bus Off OR Bus Off Done OR Transmit Warning OR Receive Warning], Interrupt indicating that errors were detected on the CAN bus, Interrupt asserted when Pretended Networking operation is enabled, and a valid message matches the selected filter criteria during Low Power mode*/
    .long   CAN0_ORed_0_31_MB_IRQHandler                    /* OR'ed Message buffer (0-15, 16-31)*/
    .long   FTM0_Ch0_7_IRQHandler                           /* FTM0 Channel 0 to 7 interrupt*/
    .long   FTM0_Fault_IRQHandler                           /* FTM0 Fault interrupt*/
    .long   FTM0_Ovf_Reload_IRQHandler                      /* FTM0 Counter overflow and Reload interrupt*/
    .long   FTM1_Ch0_7_IRQHandler                           /* FTM1 Channel 0 to 7 interrupt*/
    .long   FTM1_Fault_IRQHandler                           /* FTM1 Fault interrupt*/
    .long   FTM1_Ovf_Reload_IRQHandler                      /* FTM1 Counter overflow and Reload interrupt*/
    .long   FTFC_IRQHandler                                 /* FTFC Command complete, Read collision and Double bit fault detect*/
    .long   PDB0_IRQHandler                                 /* PDB0 interrupt*/
    .long   LPIT0_IRQHandler                                /* LPIT interrupt*/
    .long   SCG_CMU_LVD_LVWSCG_IRQHandler                   /* PMC Low voltage detect interrupt, SCG bus interrupt request and CMU loss of range interrupt*/
    .long   WDOG_IRQHandler                                 /* WDOG interrupt request out before wdg reset out*/
    .long   RCM_IRQHandler                                  /* RCM Asynchronous Interrupt*/
    .long   LPI2C0_Master_Slave_IRQHandler                  /* LPI2C0 Master Interrupt and Slave Interrupt*/
    .long   FLEXIO_IRQHandler                               /* FlexIO Interrupt*/
    .long   LPSPI0_IRQHandler                               /* LPSPI0 Interrupt*/
    .long   Reserved43_IRQHandler                           /* Reserved Interrupt 43*/
    .long   ADC0_IRQHandler                                 /* ADC0 interrupt request.*/
    .long   CMP0_IRQHandler                                 /* CMP0 interrupt request*/
    .long   LPUART1_RxTx_IRQHandler                         /* LPUART1 Transmit / Receive  Interrupt*/
    .long   LPUART0_RxTx_IRQHandler                         /* LPUART0 Transmit / Receive Interrupt*/

    .size    __isr_vector, . - __isr_vector

/* Flash Configuration */
    .section .FlashConfig, "a"
    .long 0xFFFFFFFF   /* 8 bytes backdoor comparison key */
    .long 0xFFFFFFFF   
    .long 0xFFFFFFFF   /* 4 bytes program flash protection bytes */
    .long 0xFFFEFFFE   /* FDPROT:FEPROT:FOPT:FSEC(0xFE = unsecured) */

    .text
    .thumb

/* Reset Handler */

    .thumb_func
    .align 2
    .globl   Reset_Handler
    .weak    Reset_Handler
    .type    Reset_Handler, %function
Reset_Handler:
    cpsid   i               /* Mask interrupts */

    /* Init VTOR */    
    .equ    VTOR, 0xE000ED08
    ldr     r0, =VTOR
    ldr     r1, =__isr_vector
    str     r1, [r0]
    
    /* Init the rest of the registers */
    ldr     r1,=0
    ldr     r2,=0
    ldr     r3,=0
    ldr     r4,=0
    ldr     r5,=0
    ldr     r6,=0
    ldr     r7,=0
    mov     r8,r7
    mov     r9,r7
    mov     r10,r7
    mov     r11,r7
    mov     r12,r7

    /* Initialize the stack pointer */
    ldr     r0,=__StackTop
    mov     r13,r0
    
    cpsie   i               /* Unmask interrupts */
    
#ifndef __NO_SYSTEM_INIT
    /* Call the CMSIS system init routine */
    ldr     r0,=SystemInit
    blx     r0
#endif

#ifdef START_FROM_FLASH

    /* Init ECC RAM */

    ldr r1, =__DATA_RAM
    ldr r2, =__DATA_RAM_END

    subs    r2, r1
    ble .LC5

    movs    r0, 0
    movs    r3, #4
.LC4:
    str r0, [r1]
    add	r1, r1, r3
    subs r2, 4
    bgt .LC4
.LC5:
#endif

/*     Loop to copy data from read only memory to RAM. The ranges
 *      of copy from/to are specified by following symbols evaluated in
 *      linker script.
 *      __etext: End of code section, i.e., begin of data sections to copy from.
 *      __data_start__/__data_end__: RAM address range that data should be
 *      copied to. Both must be aligned to 4 bytes boundary.  */

    ldr    r1, =__etext
    ldr    r2, =__data_start__
    ldr    r3, =__data_end__

    subs    r3, r2
    ble     .LC0

.LC1:
    subs    r3, 4
    ldr    r0, [r1,r3]
    str    r0, [r2,r3]
    bgt    .LC1
.LC0:

    /* Init .data and .bss sections */
    ldr r1, =__bss_start__
    ldr r2, =__bss_end__

    subs    r2, r1
    ble .LC3

    movs    r0, 0
.LC2:
    str r0, [r1, r2]
    subs    r2, 4
    bge .LC2
.LC3:

    bl    main
    .pool
    .size Reset_Handler, . - Reset_Handler

    .align	1
    .thumb_func
    .weak DefaultISR
    .type DefaultISR, %function
DefaultISR:
    ldr	r0, =DefaultISR
    bx r0
    .size DefaultISR, . - DefaultISR

/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
    .macro def_irq_handler	handler_name
    .weak \handler_name
    .set  \handler_name, DefaultISR
    .endm

/* Exception Handlers */
    def_irq_handler    NMI_Handler
    def_irq_handler    HardFault_Handler
    def_irq_handler    SVC_Handler
    def_irq_handler    PendSV_Handler
    def_irq_handler    SysTick_Handler
    def_irq_handler    DMA0_IRQHandler
    def_irq_handler    DMA1_IRQHandler
    def_irq_handler    DMA2_IRQHandler
    def_irq_handler    DMA3_IRQHandler
    def_irq_handler    DMA_Error_IRQHandler
    def_irq_handler    ERM_fault_IRQHandler
    def_irq_handler    RTC_IRQHandler
    def_irq_handler    RTC_Seconds_IRQHandler
    def_irq_handler    LPTMR0_IRQHandler
    def_irq_handler    PORT_IRQHandler
    def_irq_handler    CAN0_ORed_Err_Wakeup_IRQHandler
    def_irq_handler    CAN0_ORed_0_31_MB_IRQHandler
    def_irq_handler    FTM0_Ch0_7_IRQHandler
    def_irq_handler    FTM0_Fault_IRQHandler
    def_irq_handler    FTM0_Ovf_Reload_IRQHandler
    def_irq_handler    FTM1_Ch0_7_IRQHandler
    def_irq_handler    FTM1_Fault_IRQHandler
    def_irq_handler    FTM1_Ovf_Reload_IRQHandler
    def_irq_handler    FTFC_IRQHandler
    def_irq_handler    PDB0_IRQHandler
    def_irq_handler    LPIT0_IRQHandler
    def_irq_handler    SCG_CMU_LVD_LVWSCG_IRQHandler
    def_irq_handler    WDOG_IRQHandler
    def_irq_handler    RCM_IRQHandler
    def_irq_handler    LPI2C0_Master_Slave_IRQHandler
    def_irq_handler    FLEXIO_IRQHandler
    def_irq_handler    LPSPI0_IRQHandler
    def_irq_handler    Reserved43_IRQHandler
    def_irq_handler    ADC0_IRQHandler
    def_irq_handler    CMP0_IRQHandler
    def_irq_handler    LPUART1_RxTx_IRQHandler
    def_irq_handler    LPUART0_RxTx_IRQHandler

    .end
