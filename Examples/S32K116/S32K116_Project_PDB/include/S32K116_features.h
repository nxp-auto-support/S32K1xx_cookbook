/*
 * Copyright (c) 2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
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
 * @file S32K116_features.h
 * @brief Chip specific module features
 *
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 2.3, Global typedef not referenced.
 * Type used only in some modules of the SDK.
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 2.4, tag unused outside of typedefs
 * Tag defined specifically for typedef
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 2.5, Global macro not referenced.
 * The macros defined are used to define features for each driver, so this might be reported
 * when the analysis is made only on one driver.
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Directive 4.9, Function-like macro
 * These are very simple macros used for abstracting hw implementation.
 * They help make the code easy to understand.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 5.1, identifier clash
 * The supported compilers use more than 31 significant characters for identifiers.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 5.2, identifier clash
 * The supported compilers use more than 31 significant characters for identifiers.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 5.4, identifier clash
 * The supported compilers use more than 31 significant characters for identifiers.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 5.5, identifier clash
 * The supported compilers use more than 31 significant characters for identifiers.
 *
 */

#if !defined(S32K116_FEATURES_H)
#define S32K116_FEATURES_H

/* ERRATA sections*/

/* @brief E10655: When using LPSPI in master mode and the SR[MBF] bit is read as a one, then, the
 * flag is set. If it is read as a zero, it must be read second time and this second read will be
 * the correct state of the bit.​ */
#define ERRATA_E10655

/* @brief E10792: LPI2C: Slave Transmit Data Flag may incorrectly read as one when TXCFG is zero.
 * Interrupts for transfer data should be enabled after the address valid event is detected and
 * disabled at the end of the transfer. */
#define ERRATA_E10792

/* @brief Errata workaround: System clock status register may be a erroneous status during the system clock switch.
 * Read system clock source twice. */
#define ERRATA_E10777

/* @brief Number of cores. */
#define NUMBER_OF_CORES (1u)

/* SOC module features */

/* @brief PORT availability on the SoC. */
#define FEATURE_SOC_PORT_COUNT (5)

#define FEATURE_SOC_SCG_COUNT (1)

/* @brief Slow IRC high range clock frequency. */
#define FEATURE_SCG_SIRC_HIGH_RANGE_FREQ (8000000U)

/* @brief Fast IRC trimmed clock frequency(48MHz). */
#define FEATURE_SCG_FIRC_FREQ0  (48000000U)

/* FLASH module features */

/* @brief Is of type FTFA. */
#define FEATURE_FLS_IS_FTFA (0u)
/* @brief Is of type FTFC. */
#define FEATURE_FLS_IS_FTFC (1u)
/* @brief Is of type FTFE. */
#define FEATURE_FLS_IS_FTFE (0u)
/* @brief Is of type FTFL. */
#define FEATURE_FLS_IS_FTFL (0u)
/* @brief Has flags indicating the status of the FlexRAM (register bits FCNFG[EEERDY], FCNFG[RAMRDY] and FCNFG[PFLSH]). */
#define FEATURE_FLS_HAS_FLEX_RAM_FLAGS (1u)
/* @brief Has program flash swapping status flag (register bit FCNFG[SWAP]). */
#define FEATURE_FLS_HAS_PF_SWAPPING_STATUS_FLAG (0u)
/* @brief Has EEPROM region protection (register FEPROT). */
#define FEATURE_FLS_HAS_EEROM_REGION_PROTECTION (1u)
/* @brief Has data flash region protection (register FDPROT). */
#define FEATURE_FLS_HAS_DATA_FLS_REGION_PROTECTION (1u)
/* @brief P-Flash block count. */
#define FEATURE_FLS_PF_BLOCK_COUNT (1u)
/* @brief P-Flash block size. */
#define FEATURE_FLS_PF_BLOCK_SIZE (0x20000U)
/* @brief P-Flash sector size. */
#define FEATURE_FLS_PF_BLOCK_SECTOR_SIZE (2048u)
/* @brief P-Flash write unit size. */
#define FEATURE_FLS_PF_BLOCK_WRITE_UNIT_SIZE (8u)
/* @brief P-Flash block swap feature. */
#define FEATURE_FLS_HAS_PF_BLOCK_SWAP (0u)
/* @brief Has FlexNVM memory. */
#define FEATURE_FLS_HAS_FLEX_NVM (1u)
/* @brief FlexNVM block count. */
#define FEATURE_FLS_DF_BLOCK_COUNT (1u)
/* @brief FlexNVM block size. */
#define FEATURE_FLS_DF_BLOCK_SIZE (32768u)
/* @brief FlexNVM sector size. */
#define FEATURE_FLS_DF_BLOCK_SECTOR_SIZE (2048u)
/* @brief FlexNVM write unit size. */
#define FEATURE_FLS_DF_BLOCK_WRITE_UNIT_SIZE (8u)
/* @brief FlexNVM start address. (Valid only if FlexNVM is available.) */
#define FEATURE_FLS_DF_START_ADDRESS (0x10000000u)
/* @brief Has FlexRAM memory. */
#define FEATURE_FLS_HAS_FLEX_RAM (1u)
/* @brief FlexRAM size. */
#define FEATURE_FLS_FLEX_RAM_SIZE (2048u)
/* @brief FlexRAM start address. (Valid only if FlexRAM is available.) */
#define FEATURE_FLS_FLEX_RAM_START_ADDRESS (0x14000000u)
/* @brief Has 0x00 Read 1s Block command. */
#define FEATURE_FLS_HAS_READ_1S_BLOCK_CMD (1u)
/* @brief Has 0x01 Read 1s Section command. */
#define FEATURE_FLS_HAS_READ_1S_SECTION_CMD (1u)
/* @brief Has 0x02 Program Check command. */
#define FEATURE_FLS_HAS_PROGRAM_CHECK_CMD (1u)
/* @brief Has 0x03 Read Resource command. */
#define FEATURE_FLS_HAS_READ_RESOURCE_CMD (0u)
/* @brief Has 0x06 Program Longword command. */
#define FEATURE_FLS_HAS_PROGRAM_LONGWORD_CMD (0u)
/* @brief Has 0x07 Program Phrase command. */
#define FEATURE_FLS_HAS_PROGRAM_PHRASE_CMD (1u)
/* @brief Has 0x08 Erase Flash Block command. */
#define FEATURE_FLS_HAS_ERASE_BLOCK_CMD (1u)
/* @brief Has 0x09 Erase Flash Sector command. */
#define FEATURE_FLS_HAS_ERASE_SECTOR_CMD (1u)
/* @brief Has 0x0B Program Section command. */
#define FEATURE_FLS_HAS_PROGRAM_SECTION_CMD (1u)
/* @brief Has 0x40 Read 1s All Blocks command. */
#define FEATURE_FLS_HAS_READ_1S_ALL_BLOCKS_CMD (1u)
/* @brief Has 0x41 Read Once command. */
#define FEATURE_FLS_HAS_READ_ONCE_CMD (1u)
/* @brief Has 0x43 Program Once command. */
#define FEATURE_FLS_HAS_PROGRAM_ONCE_CMD (1u)
/* @brief Has 0x44 Erase All Blocks command. */
#define FEATURE_FLS_HAS_ERASE_ALL_CMD (1u)
/* @brief Has 0x45 Verify Backdoor Access Key command. */
#define FEATURE_FLS_HAS_VERIFY_BACKDOOR_ACCESS_KEY_CMD (1u)
/* @brief Has 0x46 Swap Control command. */
#define FEATURE_FLS_HAS_SWAP_CONTROL_CMD (0u)
/* @brief Has 0x49 Erase All Blocks unsecure command. */
#define FEATURE_FLS_HAS_ERASE_ALL_BLOCKS_UNSECURE_CMD (1u)
/* @brief Has 0x80 Program Partition command. */
#define FEATURE_FLS_HAS_PROGRAM_PARTITION_CMD (1u)
/* @brief Has 0x81 Set FlexRAM Function command. */
#define FEATURE_FLS_HAS_SET_FLEXRAM_FUNCTION_CMD (1u)
/* @brief P-Flash Erase/Read 1st all block command address alignment. */
#define FEATURE_FLS_PF_BLOCK_CMD_ADDRESS_ALIGMENT (8u)
/* @brief P-Flash Erase sector command address alignment. */
#define FEATURE_FLS_PF_SECTOR_CMD_ADDRESS_ALIGMENT (8u)
/* @brief P-Flash Program/Verify section command address alignment. */
#define FEATURE_FLS_PF_SECTION_CMD_ADDRESS_ALIGMENT (8u)
/* @brief P-Flash Read resource command address alignment. */
#define FEATURE_FLS_PF_RESOURCE_CMD_ADDRESS_ALIGMENT (8u)
/* @brief P-Flash Program check command address alignment. */
#define FEATURE_FLS_PF_CHECK_CMD_ADDRESS_ALIGMENT (4u)
/* @brief P-Flash Program check command address alignment. */
#define FEATURE_FLS_PF_SWAP_CONTROL_CMD_ADDRESS_ALIGMENT (0u)
/* @brief FlexNVM Erase/Read 1st all block command address alignment. */
#define FEATURE_FLS_DF_BLOCK_CMD_ADDRESS_ALIGMENT (8u)
/* @brief FlexNVM Erase sector command address alignment. */
#define FEATURE_FLS_DF_SECTOR_CMD_ADDRESS_ALIGMENT (8u)
/* @brief FlexNVM Program/Verify section command address alignment. */
#define FEATURE_FLS_DF_SECTION_CMD_ADDRESS_ALIGMENT (8u)
/* @brief FlexNVM Read resource command address alignment. */
#define FEATURE_FLS_DF_RESOURCE_CMD_ADDRESS_ALIGMENT (8u)
/* @brief FlexNVM Program check command address alignment. */
#define FEATURE_FLS_DF_CHECK_CMD_ADDRESS_ALIGMENT (4u)
/* @brief FlexNVM partition code 0000 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FEATURE_FLS_DF_SIZE_0000 (0x00008000u)
/* @brief FlexNVM partition code 0001 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FEATURE_FLS_DF_SIZE_0001 (0xFFFFFFFFu)
/* @brief FlexNVM partition code 0010 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FEATURE_FLS_DF_SIZE_0010 (0xFFFFFFFFu)
/* @brief FlexNVM partition code 0011 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FEATURE_FLS_DF_SIZE_0011 (0x00000000u)
/* @brief FlexNVM partition code 0100 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FEATURE_FLS_DF_SIZE_0100 (0xFFFFFFFFu)
/* @brief FlexNVM partition code 0101 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FEATURE_FLS_DF_SIZE_0101 (0xFFFFFFFFu)
/* @brief FlexNVM partition code 0110 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FEATURE_FLS_DF_SIZE_0110 (0xFFFFFFFFu)
/* @brief FlexNVM partition code 0111 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FEATURE_FLS_DF_SIZE_0111 (0xFFFFFFFFu)
/* @brief FlexNVM partition code 1000 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FEATURE_FLS_DF_SIZE_1000 (0x00000000u)
/* @brief FlexNVM partition code 1001 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FEATURE_FLS_DF_SIZE_1001 (0x00002000u)
/* @brief FlexNVM partition code 1010 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FEATURE_FLS_DF_SIZE_1010 (0xFFFFFFFFu)
/* @brief FlexNVM partition code 1011 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FEATURE_FLS_DF_SIZE_1011 (0x00008000u)
/* @brief FlexNVM partition code 1100 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FEATURE_FLS_DF_SIZE_1100 (0xFFFFFFFFu)
/* @brief FlexNVM partition code 1101 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FEATURE_FLS_DF_SIZE_1101 (0xFFFFFFFFu)
/* @brief FlexNVM partition code 1110 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FEATURE_FLS_DF_SIZE_1110 (0xFFFFFFFFu)
/* @brief FlexNVM partition code 1111 mapping to data flash size in bytes (0xFFFFFFFF = reserved). */
#define FEATURE_FLS_DF_SIZE_1111 (0x00008000u)
/* @brief Emulated EEPROM size code 0000 mapping to emulated EEPROM size in bytes (0xFFFF = reserved). */
#define FEATURE_FLS_EE_SIZE_0000 (0xFFFFu)
/* @brief Emulated EEPROM size code 0001 mapping to emulated EEPROM size in bytes (0xFFFF = reserved). */
#define FEATURE_FLS_EE_SIZE_0001 (0xFFFFu)
/* @brief Emulated EEPROM size code 0010 mapping to emulated EEPROM size in bytes (0xFFFF = reserved). */
#define FEATURE_FLS_EE_SIZE_0010 (0xFFFFu)
/* @brief Emulated EEPROM size code 0011 mapping to emulated EEPROM size in bytes (0xFFFF = reserved). */
#define FEATURE_FLS_EE_SIZE_0011 (0x0800u)
/* @brief Emulated EEPROM size code 0100 mapping to emulated EEPROM size in bytes (0xFFFF = reserved). */
#define FEATURE_FLS_EE_SIZE_0100 (0xFFFFu)
/* @brief Emulated EEPROM size code 0101 mapping to emulated EEPROM size in bytes (0xFFFF = reserved). */
#define FEATURE_FLS_EE_SIZE_0101 (0xFFFFu)
/* @brief Emulated EEPROM size code 0110 mapping to emulated EEPROM size in bytes (0xFFFF = reserved). */
#define FEATURE_FLS_EE_SIZE_0110 (0xFFFFu)
/* @brief Emulated EEPROM size code 0111 mapping to emulated EEPROM size in bytes (0xFFFF = reserved). */
#define FEATURE_FLS_EE_SIZE_0111 (0xFFFFu)
/* @brief Emulated EEPROM size code 1000 mapping to emulated EEPROM size in bytes (0xFFFF = reserved). */
#define FEATURE_FLS_EE_SIZE_1000 (0xFFFFu)
/* @brief Emulated EEPROM size code 1001 mapping to emulated EEPROM size in bytes (0xFFFF = reserved). */
#define FEATURE_FLS_EE_SIZE_1001 (0xFFFFu)
/* @brief Emulated EEPROM size code 1010 mapping to emulated EEPROM size in bytes (0xFFFF = reserved). */
#define FEATURE_FLS_EE_SIZE_1010 (0xFFFFu)
/* @brief Emulated EEPROM size code 1011 mapping to emulated EEPROM size in bytes (0xFFFF = reserved). */
#define FEATURE_FLS_EE_SIZE_1011 (0xFFFFu)
/* @brief Emulated EEPROM size code 1100 mapping to emulated EEPROM size in bytes (0xFFFF = reserved). */
#define FEATURE_FLS_EE_SIZE_1100 (0xFFFFu)
/* @brief Emulated EEPROM size code 1101 mapping to emulated EEPROM size in bytes (0xFFFF = reserved). */
#define FEATURE_FLS_EE_SIZE_1101 (0xFFFFu)
/* @brief Emulated EEPROM size code 1110 mapping to emulated EEPROM size in bytes (0xFFFF = reserved). */
#define FEATURE_FLS_EE_SIZE_1110 (0xFFFFu)
/* @brief Emulated EEPROM size code 1111 mapping to emulated EEPROM size in bytes (0xFFFF = reserved). */
#define FEATURE_FLS_EE_SIZE_1111 (0x0000u)
/* @brief Has the detection of uncorrected ECC errors. */
#define FEATURE_FLS_HAS_DETECT_ECC_ERROR (1)
/* @brief Has the interrupt double bit fault detect. */
#define FEATURE_FLS_HAS_INTERRUPT_DOUBLE_BIT_FAULT_IRQ (0)

/* @brief VECTKEY value so that AIRCR register write is not ignored. */
#define FEATURE_SCB_VECTKEY               (0x05FAU)

/* SMC module features */

/* @brief Has stop option (register bit STOPCTRL[STOPO]). */
#define FEATURE_SMC_HAS_STOPO (1)
/* @brief Has partial stop option (register bit STOPCTRL[PSTOPO]). */
#define FEATURE_SMC_HAS_PSTOPO (0)
/* @brief Has WAIT and VLPW options. */
#define FEATURE_SMC_HAS_WAIT_VLPW (0)
/* @brief Has high speed run mode (register bit PMPROT[AHSRUN]). */
#define FEATURE_SMC_HAS_HIGH_SPEED_RUN_MODE (0)

/* RCM module feature */

/* @brief Has existence of CMU loss of clock as reset source */
#define FEATURE_RCM_HAS_EXISTENCE_CMU_LOSS_OF_CLOCK (1)
/* @brief Has CMU loss of clock as reset source */
#define FEATURE_RCM_HAS_CMU_LOSS_OF_CLOCK (1)
/* @brief Has sticky CMU loss of clock as reset source */
#define FEATURE_RCM_HAS_STICKY_CMU_LOSS_OF_CLOCK (1)

/* WDOG module features */

/* @brief The 32-bit value used for unlocking the WDOG. */
#define FEATURE_WDOG_UNLOCK_VALUE                       (0xD928C520U)
/* @brief The 32-bit value used for resetting the WDOG counter. */
#define FEATURE_WDOG_TRIGGER_VALUE                      (0xB480A602U)
/* @brief The reset value of the timeout register. */
#define FEATURE_WDOG_TO_RESET_VALUE                     (0x400U)
/* @brief The value minimum of the timeout register. */
#define FEATURE_WDOG_MINIMUM_TIMEOUT_VALUE              (0x0U)
/* @brief The reset value of the window register. */
#define FEATURE_WDOG_WIN_RESET_VALUE                    (0x0U)
/* @brief The mask of the reserved bit in the CS register. */
#define FEATURE_WDOG_CS_RESERVED_MASK                   (0x2000U)
/* @brief The value used to set WDOG source clock from LPO. */
#define FEATURE_WDOG_CLK_FROM_LPO                       (0x1UL)
/* @brief The first 16-bit value used for unlocking the WDOG. */
#define FEATURE_WDOG_UNLOCK16_FIRST_VALUE               (0xC520U)
/* @brief The second 16-bit value used for unlocking the WDOG. */
#define FEATURE_WDOG_UNLOCK16_SECOND_VALUE              (0xD928U)
/* @brief The first 16-bit value used for resetting the WDOG counter. */
#define FEATURE_WDOG_TRIGGER16_FIRST_VALUE              (0xA602U)
/* @brief The second 16-bit value used for resetting the WDOG counter. */
#define FEATURE_WDOG_TRIGGER16_SECOND_VALUE             (0xB480U)
/* @brief Default reset value of the CS register. */
#define FEATURE_WDOG_CS_RESET_VALUE                     (0x2520U)

/* Interrupt module features */

/* @brief Lowest interrupt request number. */
#define FEATURE_INTERRUPT_IRQ_MIN         (NonMaskableInt_IRQn)
/* @brief Highest interrupt request number. */
#define FEATURE_INTERRUPT_IRQ_MAX         (LPUART0_RxTx_IRQn)
/**< Number of priority bits implemented in the NVIC */
#define FEATURE_NVIC_PRIO_BITS            (2U)
/* @brief Has software interrupt. */
#define FEATURE_INTERRUPT_HAS_SOFTWARE_IRQ  (0u)
/* @brief Has pending interrupt state. */
#define FEATURE_INTERRUPT_HAS_PENDING_STATE (1u)
/* @brief Has active interrupt state. */
#define FEATURE_INTERRUPT_HAS_ACTIVE_STATE  (0u)
/* @brief Multicore support for interrupts */
#define FEATURE_INTERRUPT_MULTICORE_SUPPORT  (0u)
/* @brief Registers in which the start of interrupt vector table needs to be configured */
#define FEATURE_INTERRUPT_INT_VECTORS {&S32_SCB->VTOR}

/* FTM module features */

/* @brief Number of PWM channels */
#define FEATURE_FTM_CHANNEL_COUNT               (8U)
/* @brief Number of fault channels */
#define FTM_FEATURE_FAULT_CHANNELS              (4U)
/* @brief Width of control channel */
#define FTM_FEATURE_COMBINE_CHAN_CTRL_WIDTH     (8U)
/* @brief Output channel offset */
#define FTM_FEATURE_OUTPUT_CHANNEL_OFFSET       (16U)
/* @brief Max counter value */
#define FTM_FEATURE_CNT_MAX_VALUE_U32           (0x0000FFFFU)
/* @brief Input capture for single shot */
#define FTM_FEATURE_INPUT_CAPTURE_SINGLE_SHOT   (2U)
/* @brief Dithering has supported on the generated PWM signals */
#define FEATURE_FTM_HAS_SUPPORTED_DITHERING     (1U)
/*! @brief Number of interrupt vector for channels of the FTM module. */
#define FEATURE_FTM_HAS_NUM_IRQS_CHANS          (1U)

/* CSEc module features */

/*! @brief CSE_PRAM offset of the page length parameter used by the following
commands: CMD_ENC_ECB, CMD_ENC_CBC, CMD_DEC_ECB, CMD_DEC_CBC, CMD_MP_COMPRESS */
#define FEATURE_CSEC_PAGE_LENGTH_OFFSET                   (0xEU)
/*! @brief CSE_PRAM offset of the message length parameter used by the following
commands: CMD_GENERATE_MAC, CMD_VERIFY_MAC (both copy and pointer methods) */
#define FEATURE_CSEC_MESSAGE_LENGTH_OFFSET                (0xCU)
/*! @brief CSE_PRAM offset of the MAC length parameter used by the following
commands: CMD_VERIFY_MAC (both copy and pointer methods) */
#define FEATURE_CSEC_MAC_LENGTH_OFFSET                    (0x8U)
/*! @brief CSE_PRAM offset of the boot size parameter used by the following
commands: CMD_BOOT_DEFINE */
#define FEATURE_CSEC_BOOT_SIZE_OFFSET                     (0x1CU)
/*! @brief CSE_PRAM offset of the boot flavor parameter used by the following
commands: CMD_BOOT_DEFINE */
#define FEATURE_CSEC_BOOT_FLAVOR_OFFSET                   (0x1BU)
/*! @brief CSE_PRAM offset of the Flash start address parameter used by the
following commands: CMD_GENERATE_MAC, CMD_VERIFY_MAC (pointer method) */
#define FEATURE_CSEC_FLASH_START_ADDRESS_OFFSET           (0x10U)
/*! @brief CSE_PRAM offset of the verification status parameter used by the
following commands: CMD_VERIFY_MAC (both copy and pointer methods) */
#define FEATURE_CSEC_VERIFICATION_STATUS_OFFSET           (0x14U)
/*! @brief CSE_PRAM offset of the error bits field contained by all commands */
#define FEATURE_CSEC_ERROR_BITS_OFFSET                    (0x4U)
/*! @brief CSE_PRAM offset of the SREG parameter used by the following commands:
CMD_GET_ID */
#define FEATURE_CSEC_SREG_OFFSET                          (0x2FU)

/*! @brief CSE_PRAM offset of page 0 */
#define FEATURE_CSEC_PAGE_0_OFFSET                        (0x0U)
/*! @brief CSE_PRAM offset of page 1 */
#define FEATURE_CSEC_PAGE_1_OFFSET                        (0x10U)
/*! @brief CSE_PRAM offset of page 2 */
#define FEATURE_CSEC_PAGE_2_OFFSET                        (0x20U)
/*! @brief CSE_PRAM offset of page 3 */
#define FEATURE_CSEC_PAGE_3_OFFSET                        (0x30U)
/*! @brief CSE_PRAM offset of page 4 */
#define FEATURE_CSEC_PAGE_4_OFFSET                        (0x40U)
/*! @brief CSE_PRAM offset of page 5 */
#define FEATURE_CSEC_PAGE_5_OFFSET                        (0x50U)
/*! @brief CSE_PRAM offset of page 6 */
#define FEATURE_CSEC_PAGE_6_OFFSET                        (0x60U)
/*! @brief CSE_PRAM offset of page 7 */
#define FEATURE_CSEC_PAGE_7_OFFSET                        (0x70U)

/* CRC module features */

/* @brief CRC module use for S32K. */
#define FEATURE_CRC_DRIVER_SOFT_POLYNOMIAL
/* @brief Default CRC bit width */
#define FEATURE_CRC_DEFAULT_WIDTH               CRC_BITS_16
/* @brief Default CRC read transpose */
#define FEATURE_CRC_DEFAULT_READ_TRANSPOSE      CRC_TRANSPOSE_NONE
/* @brief Default CRC write transpose */
#define FEATURE_CRC_DEFAULT_WRITE_TRANSPOSE     CRC_TRANSPOSE_NONE
/* @brief Default polynomial 0x1021U */
#define FEATURE_CRC_DEFAULT_POLYNOMIAL          (0x1021U)
/* @brief Default seed value is 0xFFFFU */
#define FEATURE_CRC_DEFAULT_SEED                (0xFFFFU)

/* CMP module features */

/* @brief Comparator hard block offset control */
#define FEATURE_CMP_HAS_HARD_BLOCK_OFFSET   (1U)
/* @brief Comparator fix DAC input to mux side */
#define FEATURE_CMP_DAC_FIX_SELECTION       (0U)
/* @brief Comparator initialization delay */
#define FEATURE_CMP_HAS_INIT_DELAY          (1U)

#define C0_RESET_VALUE (CMP_C0_DMAEN(0U) | CMP_C0_IER(0U) | CMP_C0_IEF(0U) | CMP_C0_CFR(1U) |                     \
                        CMP_C0_CFF(1U) | CMP_C0_FPR(0U) | CMP_C0_SE(0U) | CMP_C0_WE(0U) |                         \
                        CMP_C0_PMODE(0U) | CMP_C0_INVT(0U) | CMP_C0_COS(0U) | CMP_C0_OPE(0U) |                    \
                        CMP_C0_EN(0U) | CMP_C0_FILTER_CNT(0U) | CMP_C0_OFFSET(0U) | CMP_C0_HYSTCTR(0U))

#define C1_RESET_VALUE (CMP_C1_INPSEL(0U) | CMP_C1_INNSEL(0U) | CMP_C1_CHN7(0U) | CMP_C1_CHN6(0U) |               \
                        CMP_C1_CHN5(0U) | CMP_C1_CHN4(0U) | CMP_C1_CHN3(0U) | CMP_C1_CHN2(0U) |                   \
                        CMP_C1_CHN1(0U) | CMP_C1_CHN0(0U) | CMP_C1_DACEN(0U) | CMP_C1_VRSEL(0U) |                 \
                        CMP_C1_PSEL(0U) | CMP_C1_MSEL(0U) |  CMP_C1_VOSEL(0U))

#define C2_RESET_VALUE (CMP_C2_RRE(0U) | CMP_C2_RRIE(0U) | CMP_C2_FXMP(0U) | CMP_C2_FXMXCH(0U) | CMP_C2_CH7F(1U) |    \
                        CMP_C2_CH6F(1U) | CMP_C2_CH5F(1U) | CMP_C2_CH4F(1U) | CMP_C2_CH3F(1U) | CMP_C2_CH2F(1U) |     \
                        CMP_C2_CH1F(1U) | CMP_C2_CH0F(1U) | CMP_C2_NSAM(0U) | CMP_C2_NSAM(0U) | CMP_C2_INITMOD(0U) |  \
                        CMP_C2_ACOn(0U))

#define CMP_DAC_SOURCE          0U
#define CMP_MUX_SOURCE          1U
#define CMP_DAC_RESOLUTION      255U

/* ISELED Pins */

#define ISELED_PIN_0     0    /*PTA10*/
#define ISELED_PIN_1     1    /*PTD0*/
#define ISELED_PIN_2     2    /*PTD9*/
#define ISELED_PIN_3     3    /*PTA11*/
#define ISELED_PIN_4     4    /*PTD1*/
#define ISELED_PIN_5     5    /*PTD8*/
#define ISELED_PIN_6     6    /*PTA0*/
#define ISELED_PIN_7     7    /*PTE15*/
#define ISELED_PIN_8     8    /*PTA1*/
#define ISELED_PIN_9     9    /*PTE16*/
#define ISELED_PIN_10    10    /*PTA2*/
#define ISELED_PIN_11    11    /*PTD2*/
#define ISELED_PIN_12    12    /*PTE10*/
#define ISELED_PIN_13    13    /*PTA3*/
#define ISELED_PIN_14    14    /*PTE11*/
#define ISELED_PIN_15    15    /*PTD3*/
#define ISELED_PIN_16    16    /*PTA8*/
#define ISELED_PIN_17    17    /*PTE3*/
#define ISELED_PIN_18    18    /*PTA9*/
#define ISELED_PIN_19    19    /*PTE3*/

#define ISELED_PIN_20    20    /*PTB2*/
#define ISELED_PIN_21    21    /*PTB1*/
#define ISELED_PIN_22    22    /*PTD15*/
#define ISELED_PIN_23    23    /*PTB4*/
#define ISELED_PIN_24    24    /*PTE0*/
#define ISELED_PIN_25    25    /*PTE2*/
#define ISELED_PIN_26    26    /*PTD0*/
#define ISELED_PIN_27    27    /*PTD2*/
#define ISELED_PIN_28    28    /*PTB14*/
#define ISELED_PIN_29    29    /*PTB16*/
#define ISELED_PIN_30    30    /*PTE15*/
#define ISELED_PIN_31    31    /*PTA8*/
#define ISELED_PIN_32    32    /*PTC15*/
#define ISELED_PIN_33    33    /*PTC1*/

#define ISELED_PIN_34    34    /*PTE1*/
#define ISELED_PIN_35    35    /*PTB3*/
#define ISELED_PIN_36    36    /*PTD16*/
#define ISELED_PIN_37    37    /*PTB15*/
#define ISELED_PIN_38    38    /*PTD1*/
#define ISELED_PIN_39    39    /*PTC0*/

#define MAX_NR_OF_STRIPS 13U

/* ADC module features */

/*! @brief ADC feature flag for extended number of SC1 and R registers,
 * generically named 'alias registers' */
#define FEATURE_ADC_HAS_EXTRA_NUM_REGS                    (0)

#define NUMBER_OF_ALT_CLOCKS  ADC_CLK_ALT_1
/*! @brief ADC feature flag for defining number of external ADC channels.
 * If each ADC instance has different number of external channels, then
 * this define is set with the maximum value. */
#define FEATURE_ADC_MAX_NUM_EXT_CHANS                     (14)
#define FEATURE_ADC_HAS_CHANNEL_2                         (0)
#define FEATURE_ADC_HAS_CHANNEL_8                         (0)
#define ADC_CLOCKS                                        {ADC0_CLK}
/*! @brief ADC number of control channels */
#if FEATURE_ADC_HAS_EXTRA_NUM_REGS
#define ADC_CTRL_CHANS_COUNT                              ADC_aSC1_COUNT
#else
#define ADC_CTRL_CHANS_COUNT                              ADC_SC1_COUNT
#endif /* FEATURE_ADC_HAS_EXTRA_NUM_REGS */

/*! @brief ADC default Sample Time from RM */
#define ADC_DEFAULT_SAMPLE_TIME                           (0x0CU)
/*! @brief ADC default User Gain from RM */
#define ADC_DEFAULT_USER_GAIN                             (0x04U)
/* @brief Max of adc clock frequency */
#define ADC_CLOCK_FREQ_MAX_RUNTIME     (50000000u)
/* @brief Min of adc clock frequency */
#define ADC_CLOCK_FREQ_MIN_RUNTIME     (2000000u)

/* LPUART module features */

/* @brief Has extended data register ED. */
#define FEATURE_LPUART_HAS_EXTENDED_DATA_REGISTER_FLAGS (1)
/* @brief Hardware flow control (RTS, CTS) is supported. */
#define FEATURE_LPUART_HAS_MODEM_SUPPORT (1)
/* @brief Baud rate oversampling is available. */
#define FEATURE_LPUART_HAS_BAUD_RATE_OVER_SAMPLING_SUPPORT (1)
/* @brief Baud rate oversampling is available. */
#define FEATURE_LPUART_HAS_BOTH_EDGE_SAMPLING_SUPPORT (1)
/* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
#define FEATURE_LPUART_FIFO_SIZE (4U)
/* @brief Supports two match addresses to filter incoming frames. */
#define FEATURE_LPUART_HAS_ADDRESS_MATCHING (1)
/* @brief Has transmitter/receiver DMA enable bits. */
#define FEATURE_LPUART_HAS_DMA_ENABLE (1)
/* @brief Flag clearance mask for STAT register. */
#define FEATURE_LPUART_STAT_REG_FLAGS_MASK (0xC01FC000U)
/* @brief Flag clearance mask for FIFO register. */
#define FEATURE_LPUART_FIFO_REG_FLAGS_MASK (0x00030000U)
/* @brief Reset mask for FIFO register. */
#define FEATURE_LPUART_FIFO_RESET_MASK (0x0003C000U)
/* @brief Default oversampling ratio. */
#define FEATURE_LPUART_DEFAULT_OSR (0x0FUL)
/* @brief Default baud rate modulo divisor. */
#define FEATURE_LPUART_DEFAULT_SBR (0x04UL)
/* @brief Clock names for LPUART. */
#define LPUART_CLOCK_NAMES {LPUART0_CLK, LPUART1_CLK}

/* FlexIO module features */

/* @brief Define the maximum number of shifters for any FlexIO instance. */
#define FEATURE_FLEXIO_MAX_SHIFTER_COUNT  (4U)
/* @brief Define DMA request names for Flexio. */
#define FEATURE_FLEXIO_DMA_REQ_0    EDMA_REQ_FLEXIO_SHIFTER0
#define FEATURE_FLEXIO_DMA_REQ_1    EDMA_REQ_FLEXIO_SHIFTER1
#define FEATURE_FLEXIO_DMA_REQ_2    EDMA_REQ_FLEXIO_SHIFTER2
#define FEATURE_FLEXIO_DMA_REQ_3    EDMA_REQ_FLEXIO_SHIFTER3

/* LPIT module features */

/*! @brief Number of interrupt vector for channels of the LPIT module. */
#define FEATURE_LPIT_HAS_NUM_IRQS_CHANS                  (1U)
/*! @brief Clock names for LPIT. */
#define LPIT_CLOCK_NAMES    {LPIT0_CLK}

/* MSCM module features */

/* @brief Has interrupt router control registers (IRSPRCn). */
#define FEATURE_MSCM_HAS_INTERRUPT_ROUTER                (0)
/* @brief Has directed CPU interrupt routerregisters (IRCPxxx). */
#define FEATURE_MSCM_HAS_CPU_INTERRUPT_ROUTER            (0)

/* TRGMUX module features */
/*!
 * @brief Enumeration for trigger source module of TRGMUX
 *
 * Describes all possible inputs (trigger sources) of the TRGMUX IP
 * This enumeration depends on the supported instances in device
 */
enum trgmux_trigger_source_e
{
    TRGMUX_TRIG_SOURCE_DISABLED             = 0U,
    TRGMUX_TRIG_SOURCE_VDD                  = 1U,
    TRGMUX_TRIG_SOURCE_TRGMUX_IN0           = 2U,
    TRGMUX_TRIG_SOURCE_TRGMUX_IN1           = 3U,
    TRGMUX_TRIG_SOURCE_TRGMUX_IN2           = 4U,
    TRGMUX_TRIG_SOURCE_TRGMUX_IN3           = 5U,
    TRGMUX_TRIG_SOURCE_TRGMUX_IN4           = 6U,
    TRGMUX_TRIG_SOURCE_TRGMUX_IN5           = 7U,
    TRGMUX_TRIG_SOURCE_TRGMUX_IN7           = 9U,
    TRGMUX_TRIG_SOURCE_TRGMUX_IN8           = 10U,
    TRGMUX_TRIG_SOURCE_TRGMUX_IN9           = 11U,
    TRGMUX_TRIG_SOURCE_CMP0_OUT             = 14U,
    TRGMUX_TRIG_SOURCE_LPIT_CH0             = 17U,
    TRGMUX_TRIG_SOURCE_LPIT_CH1             = 18U,
    TRGMUX_TRIG_SOURCE_LPIT_CH2             = 19U,
    TRGMUX_TRIG_SOURCE_LPIT_CH3             = 20U,
    TRGMUX_TRIG_SOURCE_LPTMR0               = 21U,
    TRGMUX_TRIG_SOURCE_FTM0_INIT_TRIG       = 22U,
    TRGMUX_TRIG_SOURCE_FTM0_EXT_TRIG        = 23U,
    TRGMUX_TRIG_SOURCE_FTM1_INIT_TRIG       = 24U,
    TRGMUX_TRIG_SOURCE_FTM1_EXT_TRIG        = 25U,
    TRGMUX_TRIG_SOURCE_ADC0_SC1A_COCO       = 30U,
    TRGMUX_TRIG_SOURCE_ADC0_SC1B_COCO       = 31U,
    TRGMUX_TRIG_SOURCE_PDB0_CH0_TRIG        = 34U,
    TRGMUX_TRIG_SOURCE_PDB0_PULSE_OUT       = 36U,
    TRGMUX_TRIG_SOURCE_RTC_ALARM            = 43U,
    TRGMUX_TRIG_SOURCE_RTC_SECOND           = 44U,
    TRGMUX_TRIG_SOURCE_FLEXIO_TRIG0         = 45U,
    TRGMUX_TRIG_SOURCE_FLEXIO_TRIG1         = 46U,
    TRGMUX_TRIG_SOURCE_FLEXIO_TRIG2         = 47U,
    TRGMUX_TRIG_SOURCE_FLEXIO_TRIG3         = 48U,
    TRGMUX_TRIG_SOURCE_LPUART0_RX_DATA      = 49U,
    TRGMUX_TRIG_SOURCE_LPUART0_TX_DATA      = 50U,
    TRGMUX_TRIG_SOURCE_LPUART0_RX_IDLE      = 51U,
    TRGMUX_TRIG_SOURCE_LPUART1_RX_DATA      = 52U,
    TRGMUX_TRIG_SOURCE_LPUART1_TX_DATA      = 53U,
    TRGMUX_TRIG_SOURCE_LPUART1_RX_IDLE      = 54U,
    TRGMUX_TRIG_SOURCE_LPI2C0_MASTER_TRIG   = 55U,
    TRGMUX_TRIG_SOURCE_LPI2C0_SLAVE_TRIG    = 56U,
    TRGMUX_TRIG_SOURCE_LPSPI0_FRAME         = 59U,
    TRGMUX_TRIG_SOURCE_LPSPI0_RX_DATA       = 60U,
    TRGMUX_TRIG_SOURCE_SIM_SW_TRIG          = 63U,
};

/*!
 * @brief Enumeration for target module of TRGMUX
 *
 * Describes all possible outputs (target modules) of the TRGMUX IP
 * This enumeration depends on the supported instances in device
 */
enum trgmux_target_module_e
{
    TRGMUX_TARGET_MODULE_DMA_CH0            = 0U,
    TRGMUX_TARGET_MODULE_DMA_CH1            = 1U,
    TRGMUX_TARGET_MODULE_DMA_CH2            = 2U,
    TRGMUX_TARGET_MODULE_DMA_CH3            = 3U,
    TRGMUX_TARGET_MODULE_TRGMUX_OUT0        = 4U,
    TRGMUX_TARGET_MODULE_TRGMUX_OUT1        = 5U,
    TRGMUX_TARGET_MODULE_TRGMUX_OUT2        = 6U,
    TRGMUX_TARGET_MODULE_TRGMUX_OUT3        = 7U,
    TRGMUX_TARGET_MODULE_ADC0_ADHWT_TLA0    = 12U,
    TRGMUX_TARGET_MODULE_ADC0_ADHWT_TLA1    = 13U,
    TRGMUX_TARGET_MODULE_ADC0_ADHWT_TLA2    = 14U,
    TRGMUX_TARGET_MODULE_ADC0_ADHWT_TLA3    = 15U,
    TRGMUX_TARGET_MODULE_CMP0_SAMPLE        = 28U,
    TRGMUX_TARGET_MODULE_FTM0_HWTRIG0       = 40U,
    TRGMUX_TARGET_MODULE_FTM0_FAULT0        = 41U,
    TRGMUX_TARGET_MODULE_FTM0_FAULT1        = 42U,
    TRGMUX_TARGET_MODULE_FTM0_FAULT2        = 43U,
    TRGMUX_TARGET_MODULE_FTM1_HWTRIG0       = 44U,
    TRGMUX_TARGET_MODULE_FTM1_FAULT0        = 45U,
    TRGMUX_TARGET_MODULE_FTM1_FAULT1        = 46U,
    TRGMUX_TARGET_MODULE_FTM1_FAULT2        = 47U,
    TRGMUX_TARGET_MODULE_PDB0_TRG_IN        = 56U,
    TRGMUX_TARGET_MODULE_FLEXIO_TRG_TIM0    = 68U,
    TRGMUX_TARGET_MODULE_FLEXIO_TRG_TIM1    = 69U,
    TRGMUX_TARGET_MODULE_FLEXIO_TRG_TIM2    = 70U,
    TRGMUX_TARGET_MODULE_FLEXIO_TRG_TIM3    = 71U,
    TRGMUX_TARGET_MODULE_LPIT_TRG_CH0       = 72U,
    TRGMUX_TARGET_MODULE_LPIT_TRG_CH1       = 73U,
    TRGMUX_TARGET_MODULE_LPIT_TRG_CH2       = 74U,
    TRGMUX_TARGET_MODULE_LPIT_TRG_CH3       = 75U,
    TRGMUX_TARGET_MODULE_LPUART0_TRG        = 76U,
    TRGMUX_TARGET_MODULE_LPUART1_TRG        = 80U,
    TRGMUX_TARGET_MODULE_LPI2C0_TRG         = 84U,
    TRGMUX_TARGET_MODULE_LPSPI0_TRG         = 92U,
    TRGMUX_TARGET_MODULE_LPTMR0_ALT0        = 100U,
};

/* @brief Constant array storing the value of all TRGMUX output(target module) identifiers */
#define FEATURE_TRGMUX_TARGET_MODULE          \
{                                             \
    TRGMUX_TARGET_MODULE_DMA_CH0,             \
    TRGMUX_TARGET_MODULE_DMA_CH1,             \
    TRGMUX_TARGET_MODULE_DMA_CH2,             \
    TRGMUX_TARGET_MODULE_DMA_CH3,             \
    TRGMUX_TARGET_MODULE_TRGMUX_OUT0,         \
    TRGMUX_TARGET_MODULE_TRGMUX_OUT1,         \
    TRGMUX_TARGET_MODULE_TRGMUX_OUT2,         \
    TRGMUX_TARGET_MODULE_TRGMUX_OUT3,         \
    TRGMUX_TARGET_MODULE_ADC0_ADHWT_TLA0,     \
    TRGMUX_TARGET_MODULE_ADC0_ADHWT_TLA1,     \
    TRGMUX_TARGET_MODULE_ADC0_ADHWT_TLA2,     \
    TRGMUX_TARGET_MODULE_ADC0_ADHWT_TLA3,     \
    TRGMUX_TARGET_MODULE_CMP0_SAMPLE,         \
    TRGMUX_TARGET_MODULE_FTM0_HWTRIG0,        \
    TRGMUX_TARGET_MODULE_FTM0_FAULT0,         \
    TRGMUX_TARGET_MODULE_FTM0_FAULT1,         \
    TRGMUX_TARGET_MODULE_FTM0_FAULT2,         \
    TRGMUX_TARGET_MODULE_FTM1_HWTRIG0,        \
    TRGMUX_TARGET_MODULE_FTM1_FAULT0,         \
    TRGMUX_TARGET_MODULE_FTM1_FAULT1,         \
    TRGMUX_TARGET_MODULE_FTM1_FAULT2,         \
    TRGMUX_TARGET_MODULE_PDB0_TRG_IN,         \
    TRGMUX_TARGET_MODULE_FLEXIO_TRG_TIM0,     \
    TRGMUX_TARGET_MODULE_FLEXIO_TRG_TIM1,     \
    TRGMUX_TARGET_MODULE_FLEXIO_TRG_TIM2,     \
    TRGMUX_TARGET_MODULE_FLEXIO_TRG_TIM3,     \
    TRGMUX_TARGET_MODULE_LPIT_TRG_CH0,        \
    TRGMUX_TARGET_MODULE_LPIT_TRG_CH1,        \
    TRGMUX_TARGET_MODULE_LPIT_TRG_CH2,        \
    TRGMUX_TARGET_MODULE_LPIT_TRG_CH3,        \
    TRGMUX_TARGET_MODULE_LPUART0_TRG,         \
    TRGMUX_TARGET_MODULE_LPUART1_TRG,         \
    TRGMUX_TARGET_MODULE_LPI2C0_TRG,          \
    TRGMUX_TARGET_MODULE_LPSPI0_TRG,          \
    TRGMUX_TARGET_MODULE_LPTMR0_ALT0          \
}

/* MPU module features */

/* @brief Specifies hardware revision level. */
#define FEATURE_MPU_HARDWARE_REVISION_LEVEL   (1U)
/* @brief Has process identifier support. */
#define FEATURE_MPU_HAS_PROCESS_IDENTIFIER    (1U)
/* @brief Specifies total number of bus masters. */
#define FEATURE_MPU_MASTER_COUNT              (3U)
/* @brief Specifies maximum number of masters which have separated
privilege rights for user and supervisor mode accesses (e.g. master0~3 in S32K1xx).
*/
#define FEATURE_MPU_MAX_LOW_MASTER_NUMBER     (3U)
/* @brief Specifies maximum number of masters which have only
read and write permissions (e.g. master4~7 in S32K1xx).
*/
#define FEATURE_MPU_MAX_HIGH_MASTER_NUMBER    (7U)

/* @brief Specifies number of set access control right bits for
   masters which have separated privilege rights for user and
   supervisor mode accesses (e.g. master0~3 in S32K1xx).
*/
#define FEATURE_MPU_LOW_MASTER_CONTROL_WIDTH  (6U)
/* @brief Specifies number of set access control right bits for
   masters which have only read and write permissions(e.g. master4~7 in S32K1xx).
*/
#define FEATURE_MPU_HIGH_MASTER_CONTROL_WIDTH (2U)

/* @brief The MPU Logical Bus Master Number for core bus master. */
#define FEATURE_MPU_MASTER_CORE               (0U)
/* @brief The MPU Logical Bus Master Number for Debugger master. */
#define FEATURE_MPU_MASTER_DEBUGGER           (1U)
/* @brief The MPU Logical Bus Master Number for DMA master. */
#define FEATURE_MPU_MASTER_DMA                (2U)
/* @brief Specifies master number. */
#define FEATURE_MPU_MASTER                        \
{                                                 \
    FEATURE_MPU_MASTER_CORE,     /*!< CORE */     \
    FEATURE_MPU_MASTER_DEBUGGER, /*!< DEBUGGER */ \
    FEATURE_MPU_MASTER_DMA,      /*!< DMA */      \
}

/* @brief Specifies total number of slave ports. */
#define FEATURE_MPU_SLAVE_COUNT               (2U)
/* @brief The MPU Slave Port Assignment for Flash Controller and boot ROM. */
#define FEATURE_MPU_SLAVE_FLASH_BOOTROM       (0U)
/* @brief The MPU Slave Port Assignment for SRAM, MTB, DWT and MCM. */
#define FEATURE_MPU_SLAVE_SRAM_MTB_DWT_MCM    (1U)
/* @brief The MPU Slave Port mask. */
#define FEATURE_MPU_SLAVE_MASK                (0xC0000000U)
#define FEATURE_MPU_SLAVE_SHIFT               (30u)
#define FEATURE_MPU_SLAVE_WIDTH               (2u)
#define FEATURE_MPU_SLAVE(x)                  (((uint32_t)(((uint32_t)(x))<<FEATURE_MPU_SLAVE_SHIFT))&FEATURE_MPU_SLAVE_MASK)


/* CAN module features */

/* @brief Frames available in Rx FIFO flag shift */
#define FEATURE_CAN_RXFIFO_FRAME_AVAILABLE  (5U)
/* @brief Rx FIFO warning flag shift */
#define FEATURE_CAN_RXFIFO_WARNING          (6U)
/* @brief Rx FIFO overflow flag shift */
#define FEATURE_CAN_RXFIFO_OVERFLOW         (7U)
/* @brief Has Flexible Data Rate for CAN0 */
#define FEATURE_CAN0_HAS_FD                 (1)
/* @brief Maximum number of Message Buffers supported for payload size 8 for CAN0 */
#define FEATURE_CAN0_MAX_MB_NUM             (32U)
/* @brief Has PE clock source select (bit field CAN_CTRL1[CLKSRC]). */
#define FEATURE_CAN_HAS_PE_CLKSRC_SELECT    (1)
/* @brief Has DMA enable (bit field MCR[DMA]). */
#define FEATURE_CAN_HAS_DMA_ENABLE          (1)
/* @brief Maximum number of Message Buffers supported for payload size 8 for any of the CAN instances */
#define FEATURE_CAN_MAX_MB_NUM              (32U)
/* @brief Maximum number of Message Buffers supported for payload size 8 for any of the CAN instances */
#define FEATURE_CAN_MAX_MB_NUM_ARRAY        { FEATURE_CAN0_MAX_MB_NUM }
/* @brief Has Pretending Networking mode */
#define FEATURE_CAN_HAS_PRETENDED_NETWORKING    (1)
/* @brief Has Stuff Bit Count Enable Bit */
#define FEATURE_CAN_HAS_STFCNTEN_ENABLE         (0)
/* @brief Has ISO CAN FD Enable Bit */
#define FEATURE_CAN_HAS_ISOCANFDEN_ENABLE       (1)
/* @brief Has Message Buffer Data Size Region 1 */
#define FEATURE_CAN_HAS_MBDSR1                  (0)
/* @brief Has Message Buffer Data Size Region 2 */
#define FEATURE_CAN_HAS_MBDSR2                  (0)
/* @brief DMA hardware requests for all FlexCAN instances */
#define FEATURE_CAN_EDMA_REQUESTS              { EDMA_REQ_FLEXCAN0 }


/* @brief Maximum number of Message Buffers IRQs */
#define FEATURE_CAN_MB_IRQS_MAX_COUNT       (2U)
/* @brief Message Buffers IRQs */
#define FEATURE_CAN_MB_IRQS                 { CAN_ORed_0_15_MB_IRQS, \
                                              CAN_ORed_16_31_MB_IRQS }
/* @brief Has Wake Up Irq channels (CAN_Wake_Up_IRQS_CH_COUNT > 0u) */
#define FEATURE_CAN_HAS_WAKE_UP_IRQ         (1)
/* @brief Has Self Wake Up mode */
#define FEATURE_CAN_HAS_SELF_WAKE_UP        (0)
/* @brief Has Flexible Data Rate */
#define FEATURE_CAN_HAS_FD                  (1)

/* OSIF module features */

#define FEATURE_OSIF_USE_SYSTICK                         (1)
#define FEATURE_OSIF_USE_PIT                             (0)
#define FEATURE_OSIF_FREERTOS_ISR_CONTEXT_METHOD         (1) /* Cortex M device */

/* @brief Supports high speed run mode. */
#define FEATURE_HAS_HIGH_SPEED_RUN_MODE  (0U)
/* @brief Supports SPLL clock source. */
#define FEATURE_HAS_SPLL_CLK             (0U)
/* @brief Clock name for the PE oscillator clock source */
#define FEATURE_CAN_PE_OSC_CLK_NAME         SOSC_CLK
/* @bried FlexCAN has Detection And Correction of Memory Errors */
#define FEATURE_CAN_HAS_MEM_ERR_DET			(0)

/*! @brief Clock names. */
typedef enum {
    /* Main clocks */
    CORE_CLK                     = 0u,       /*!< Core clock                     */
    BUS_CLK                      = 1u,       /*!< Bus clock                      */
    SLOW_CLK                     = 2u,       /*!< Slow clock                     */
    CLKOUT_CLK                   = 3u,       /*!< CLKOUT clock                   */

    /* Other internal clocks used by peripherals. */
    SIRC_CLK                     = 4u,       /*!< SIRC clock                     */
    FIRC_CLK                     = 5u,       /*!< FIRC clock                     */
    SOSC_CLK                     = 6u,       /*!< SOSC clock                     */
    RTC_CLKIN_CLK                = 8u,       /*!< RTC_CLKIN clock                */
    SCG_CLKOUT_CLK               = 9u,       /*!< SCG CLK_OUT clock              */
    SIRCDIV1_CLK                 = 10u,      /*!< SIRCDIV1 functional clock      */
    SIRCDIV2_CLK                 = 11u,      /*!< SIRCDIV2 functional clock      */
    FIRCDIV1_CLK                 = 12u,      /*!< FIRCDIV1 functional clock      */
    FIRCDIV2_CLK                 = 13u,      /*!< FIRCDIV2 functional clock      */
    SOSCDIV1_CLK                 = 14u,      /*!< SOSCDIV1 functional clock      */
    SOSCDIV2_CLK                 = 15u,      /*!< SOSCDIV2 functional clock      */

    SCG_END_OF_CLOCKS            = 18u,      /*!< End of SCG clocks              */

    /* SIM clocks */
    SIM_FTM0_CLOCKSEL            = 21u,      /*!< FTM0 External Clock Pin Select */
    SIM_FTM1_CLOCKSEL            = 22u,      /*!< FTM1 External Clock Pin Select */
    SIM_CLKOUTSELL               = 23u,      /*!< CLKOUT Select                  */
    SIM_RTCCLK_CLK               = 24u,      /*!< RTCCLK clock                   */
    SIM_LPO_CLK                  = 25u,      /*!< LPO clock                      */
    SIM_LPO_1K_CLK               = 26u,      /*!< LPO 1KHz clock                 */
    SIM_LPO_32K_CLK              = 27u,      /*!< LPO 32KHz clock                */
    SIM_LPO_128K_CLK             = 28u,      /*!< LPO 128KHz clock               */
    SIM_EIM_CLK                  = 29u,      /*!< EIM clock source               */
    SIM_ERM_CLK                  = 30u,      /*!< ERM clock source               */
    SIM_DMA_CLK                  = 31u,      /*!< DMA clock source               */
    SIM_MPU_CLK                  = 32u,      /*!< MPU clock source               */
    SIM_MSCM_CLK                 = 33u,      /*!< MSCM clock source              */
    SIM_END_OF_CLOCKS            = 34u,      /*!< End of SIM clocks              */

    CMP0_CLK                     = 41u,      /*!< CMP0 clock source              */
    CRC0_CLK                     = 42u,      /*!< CRC0 clock source              */
    DMAMUX0_CLK                  = 43u,      /*!< DMAMUX0 clock source           */
    PORTA_CLK                    = 44u,      /*!< PORTA clock source             */
    PORTB_CLK                    = 45u,      /*!< PORTB clock source             */
    PORTC_CLK                    = 46u,      /*!< PORTC clock source             */
    PORTD_CLK                    = 47u,      /*!< PORTD clock source             */
    PORTE_CLK                    = 48u,      /*!< PORTE clock source             */
    RTC0_CLK                     = 49u,      /*!< RTC0 clock source              */
    PCC_END_OF_BUS_CLOCKS        = 50u,      /*!< End of BUS clocks              */
    FlexCAN0_CLK                 = 51u,      /*!< FlexCAN0 clock source          */
    PDB0_CLK                     = 52u,      /*!< PDB0 clock source              */
    PCC_END_OF_SYS_CLOCKS        = 53u,      /*!< End of SYS clocks              */
    FTFC0_CLK                    = 54u,      /*!< FTFC0 clock source             */
    PCC_END_OF_SLOW_CLOCKS       = 55u,      /*!< End of SLOW clocks             */
    FTM0_CLK                     = 56u,      /*!< FTM0 clock source              */
    FTM1_CLK                     = 57u,      /*!< FTM1 clock source              */
    PCC_END_OF_ASYNCH_DIV1_CLOCKS= 58u,      /*!< End of ASYNCH DIV1 clocks      */
    ADC0_CLK                     = 59u,      /*!< ADC0 clock source              */
    FLEXIO0_CLK                  = 60u,      /*!< FLEXIO0 clock source           */
    LPI2C0_CLK                   = 61u,      /*!< LPI2C0 clock source            */
    LPIT0_CLK                    = 62u,      /*!< LPIT0 clock source             */
    LPSPI0_CLK                   = 63u,      /*!< LPSPI0 clock source            */
    LPTMR0_CLK                   = 64u,      /*!< LPTMR0 clock source            */
    LPUART0_CLK                  = 65u,      /*!< LPUART0 clock source           */
    LPUART1_CLK                  = 66u,      /*!< LPUART1 clock source           */
    PCC_END_OF_ASYNCH_DIV2_CLOCKS= 67u,      /*!< End of ASYNCH DIV2 clocks      */
    PCC_END_OF_CLOCKS            = 68u,      /*!< End of PCC clocks              */
    CLOCK_NAME_COUNT             = 69u,      /*!< The total number of entries    */
} clock_names_t;

#define PCC_INVALID_INDEX  0

  /*! @brief PCC clock name mappings
   *  Mappings between clock names and peripheral clock control indexes.
   *  If there is no peripheral clock control index for a clock name,
   *  then the corresponding value is PCC_INVALID_INDEX.
   */
#define PCC_CLOCK_NAME_MAPPINGS \
{                                                                                \
PCC_INVALID_INDEX,                  /*!< Core clock                      0  */   \
PCC_INVALID_INDEX,                  /*!< Bus clock                       1  */   \
PCC_INVALID_INDEX,                  /*!< Slow clock                      2  */   \
PCC_INVALID_INDEX,                  /*!< CLKOUT clock                    3  */   \
PCC_INVALID_INDEX,                  /*!< SIRC clock                      4  */   \
PCC_INVALID_INDEX,                  /*!< FIRC clock                      5  */   \
PCC_INVALID_INDEX,                  /*!< SOSC clock                      6  */   \
PCC_INVALID_INDEX,                  /*!< No clock entry in clock_names_t 7  */   \
PCC_INVALID_INDEX,                  /*!< RTC_CLKIN clock                 8  */   \
PCC_INVALID_INDEX,                  /*!< SCG CLK_OUT clock               9  */   \
PCC_INVALID_INDEX,                  /*!< SIRCDIV1 functional clock       10 */   \
PCC_INVALID_INDEX,                  /*!< SIRCDIV2 functional clock       11 */   \
PCC_INVALID_INDEX,                  /*!< FIRCDIV1 functional clock       12 */   \
PCC_INVALID_INDEX,                  /*!< FIRCDIV2 functional clock       13 */   \
PCC_INVALID_INDEX,                  /*!< SOSCDIV1 functional clock       14 */   \
PCC_INVALID_INDEX,                  /*!< SOSCDIV2 functional clock       15 */   \
PCC_INVALID_INDEX,                  /*!< No clock entry in clock_names_t 16 */   \
PCC_INVALID_INDEX,                  /*!< No clock entry in clock_names_t 17 */   \
PCC_INVALID_INDEX,                  /*!< End of SCG clocks               18 */   \
PCC_INVALID_INDEX,                  /*!< No clock entry in clock_names_t 19 */   \
PCC_INVALID_INDEX,                  /*!< No clock entry in clock_names_t 20 */   \
PCC_INVALID_INDEX,                  /*!< FTM0 External Clock Pin Select  21 */   \
PCC_INVALID_INDEX,                  /*!< FTM1 External Clock Pin Select  22 */   \
PCC_INVALID_INDEX,                  /*!< CLKOUT Select                   23 */   \
PCC_INVALID_INDEX,                  /*!< CLK32K clock                    24 */   \
PCC_INVALID_INDEX,                  /*!< LPO clock                       25 */   \
PCC_INVALID_INDEX,                  /*!< LPO 1KHz clock                  26 */   \
PCC_INVALID_INDEX,                  /*!< LPO 32KHz clock                 27 */   \
PCC_INVALID_INDEX,                  /*!< LPO 128KHz clock                28 */   \
PCC_INVALID_INDEX,                  /*!< EIM clock source                29 */   \
PCC_INVALID_INDEX,                  /*!< ERM clock source                30 */   \
PCC_INVALID_INDEX,                  /*!< DMA clock source                31 */   \
PCC_INVALID_INDEX,                  /*!< MPU clock source                32 */   \
PCC_INVALID_INDEX,                  /*!< MSCM clock source               33 */   \
PCC_INVALID_INDEX,                  /*!< No clock entry in clock_names_t 34 */   \
PCC_INVALID_INDEX,                  /*!< No clock entry in clock_names_t 35 */   \
PCC_INVALID_INDEX,                  /*!< No clock entry in clock_names_t 36 */   \
PCC_INVALID_INDEX,                  /*!< No clock entry in clock_names_t 37 */   \
PCC_INVALID_INDEX,                  /*!< No clock entry in clock_names_t 38 */   \
PCC_INVALID_INDEX,                  /*!< No clock entry in clock_names_t 39 */   \
PCC_INVALID_INDEX,                  /*!< No clock entry in clock_names_t 40 */   \
PCC_CMP0_INDEX,                     /*!< CMP0 clock source               41 */   \
PCC_CRC_INDEX,                      /*!< CRC clock source                42 */   \
PCC_DMAMUX_INDEX,                   /*!< DMAMUX clock source             43 */   \
PCC_PORTA_INDEX,                    /*!< PORTA clock source              44 */   \
PCC_PORTB_INDEX,                    /*!< PORTB clock source              45 */   \
PCC_PORTC_INDEX,                    /*!< PORTC clock source              46 */   \
PCC_PORTD_INDEX,                    /*!< PORTD clock source              47 */   \
PCC_PORTE_INDEX,                    /*!< PORTE clock source              48 */   \
PCC_RTC_INDEX,                      /*!< RTC clock source                49 */   \
PCC_INVALID_INDEX,                  /*!< End of BUS clocks               50 */   \
PCC_FlexCAN0_INDEX,                 /*!< FlexCAN0 clock source           51 */   \
PCC_PDB0_INDEX,                     /*!< PDB0 clock source               52 */   \
PCC_INVALID_INDEX,                  /*!< End of SYS clocks               53 */   \
PCC_FTFC_INDEX,                     /*!< FTFC clock source               54 */   \
PCC_INVALID_INDEX,                  /*!< End of SLOW clocks              55 */   \
PCC_FTM0_INDEX,                     /*!< FTM0 clock source               56 */   \
PCC_FTM1_INDEX,                     /*!< FTM1 clock source               57 */   \
PCC_INVALID_INDEX,                  /*!< End of ASYNCH DIV1 clocks       58 */   \
PCC_ADC0_INDEX,                     /*!< ADC0 clock source               59 */   \
PCC_FlexIO_INDEX,                   /*!< FlexIO clock source             60 */   \
PCC_LPI2C0_INDEX,                   /*!< LPI2C0 clock source             61 */   \
PCC_LPIT_INDEX,                     /*!< LPIT clock source               62 */   \
PCC_LPSPI0_INDEX,                   /*!< LPSPI0 clock source             63 */   \
PCC_LPTMR0_INDEX,                   /*!< LPTMR0 clock source             64 */   \
PCC_LPUART0_INDEX,                  /*!< LPUART0 clock source            65 */   \
PCC_LPUART1_INDEX,                  /*!< LPUART1 clock source            66 */   \
PCC_INVALID_INDEX,                  /*!< End of ASYNCH DIV2 clocks       67 */   \
PCC_INVALID_INDEX,                  /*!< End of PCC clocks               68 */   \
}

/*! @brief Peripheral instance features
 *  List of features that are supported by a peripheral instance
 */
#define NO_PERIPHERAL_FEATURE                   (0U)         /* It's not a peripheral instance, there is no peripheral feature. */
#define HAS_CLOCK_GATING_IN_SIM                 (1U << 0U)   /* Clock gating is implemented in SIM (it's not in PCC) */
#define HAS_MULTIPLIER                          (1U << 1U)   /* Multiplier is implemented in PCC */
#define HAS_DIVIDER                             (1U << 2U)   /* Divider is implemented in PCC */
#define HAS_PROTOCOL_CLOCK_FROM_ASYNC1          (1U << 3U)   /* Functional clock source is provided by the first asynchronous clock. */
#define HAS_PROTOCOL_CLOCK_FROM_ASYNC2          (1U << 4U)   /* Functional clock source is provided by the second asynchronous clock. */
#define HAS_INT_CLOCK_FROM_BUS_CLOCK            (1U << 5U)   /* Interface clock is provided by the bus clock. */
#define HAS_INT_CLOCK_FROM_SYS_CLOCK            (1U << 6U)   /* Interface clock is provided by the sys clock. */
#define HAS_INT_CLOCK_FROM_SLOW_CLOCK           (1U << 7U)   /* Interface clock is provided by the slow clock. */

/*! @brief Peripheral features.
*  List of features for each clock name. If a clock name is not
*  a peripheral, no feature is supported.
*/
#define PERIPHERAL_FEATURES \
{                                                                                                                                                \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< Core clock                      0  */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< Bus clock                       1  */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< Slow clock                      2  */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< CLKOUT clock                    3  */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< SIRC clock                      4  */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< FIRC clock                      5  */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< SOSC clock                      6  */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< No clock entry in clock_names_t 7  */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< RTC_CLKIN clock                 8  */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< SCG CLK_OUT clock               9  */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< End of SCG clocks               10 */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< No clock entry in clock_names_t 11 */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< No clock entry in clock_names_t 12 */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< No clock entry in clock_names_t 13 */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< No clock entry in clock_names_t 14 */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< No clock entry in clock_names_t 15 */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< No clock entry in clock_names_t 16 */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< No clock entry in clock_names_t 17 */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< No clock entry in clock_names_t 18 */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< No clock entry in clock_names_t 19 */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< No clock entry in clock_names_t 20 */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< FTM0 External Clock Pin Select  21 */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< FTM1 External Clock Pin Select  22 */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< CLKOUT Select                   23 */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< CLK32K clock                    24 */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< LPO clock                       25 */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< LPO 1KHz clock                  26 */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< LPO 32KHz clock                 27 */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< LPO 128KHz clock                28 */   \
(HAS_CLOCK_GATING_IN_SIM | HAS_INT_CLOCK_FROM_SYS_CLOCK),                                           /*!< EIM clock source                29 */   \
(HAS_CLOCK_GATING_IN_SIM | HAS_INT_CLOCK_FROM_SYS_CLOCK),                                           /*!< ERM clock source                30 */   \
(HAS_CLOCK_GATING_IN_SIM | HAS_INT_CLOCK_FROM_SYS_CLOCK),                                           /*!< DMA clock source                31 */   \
(HAS_CLOCK_GATING_IN_SIM | HAS_INT_CLOCK_FROM_SYS_CLOCK),                                           /*!< MPU clock source                32 */   \
(HAS_CLOCK_GATING_IN_SIM | HAS_INT_CLOCK_FROM_SYS_CLOCK),                                           /*!< MSCM clock source               33 */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< No clock entry in clock_names_t 34 */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< No clock entry in clock_names_t 35 */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< No clock entry in clock_names_t 36 */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< No clock entry in clock_names_t 37 */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< No clock entry in clock_names_t 38 */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< No clock entry in clock_names_t 39 */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< No clock entry in clock_names_t 40 */   \
(HAS_INT_CLOCK_FROM_BUS_CLOCK),                                                                     /*!< CMP0 clock source               41 */   \
(HAS_INT_CLOCK_FROM_BUS_CLOCK),                                                                     /*!< CRC clock source                42 */   \
(HAS_INT_CLOCK_FROM_BUS_CLOCK),                                                                     /*!< DMAMUX clock source             43 */   \
(HAS_INT_CLOCK_FROM_BUS_CLOCK),                                                                     /*!< PORTA clock source              44 */   \
(HAS_INT_CLOCK_FROM_BUS_CLOCK),                                                                     /*!< PORTB clock source              45 */   \
(HAS_INT_CLOCK_FROM_BUS_CLOCK),                                                                     /*!< PORTC clock source              46 */   \
(HAS_INT_CLOCK_FROM_BUS_CLOCK),                                                                     /*!< PORTD clock source              47 */   \
(HAS_INT_CLOCK_FROM_BUS_CLOCK),                                                                     /*!< PORTE clock source              48 */   \
(HAS_INT_CLOCK_FROM_BUS_CLOCK),                                                                     /*!< RTC clock source                49 */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< End of BUS clocks               50 */   \
(HAS_INT_CLOCK_FROM_SYS_CLOCK),                                                                     /*!< FlexCAN0 clock source           51 */   \
(HAS_INT_CLOCK_FROM_SYS_CLOCK),                                                                     /*!< PDB0 clock source               52 */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< End of SYS clocks               53 */   \
(HAS_INT_CLOCK_FROM_SLOW_CLOCK),                                                                    /*!< FTFC clock source               54 */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< End of SLOW clocks              55 */   \
(HAS_PROTOCOL_CLOCK_FROM_ASYNC1 | HAS_INT_CLOCK_FROM_SYS_CLOCK),                                    /*!< FTM0 clock source               56 */   \
(HAS_PROTOCOL_CLOCK_FROM_ASYNC1 | HAS_INT_CLOCK_FROM_SYS_CLOCK),                                    /*!< FTM1 clock source               57 */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< End of ASYNCH DIV1 clocks       58 */   \
(HAS_PROTOCOL_CLOCK_FROM_ASYNC2 | HAS_INT_CLOCK_FROM_BUS_CLOCK),                                    /*!< ADC0 clock source               59 */   \
(HAS_PROTOCOL_CLOCK_FROM_ASYNC2 | HAS_INT_CLOCK_FROM_BUS_CLOCK),                                    /*!< FLEXIO clock source             60 */   \
(HAS_PROTOCOL_CLOCK_FROM_ASYNC2 | HAS_INT_CLOCK_FROM_BUS_CLOCK),                                    /*!< LPI2C0 clock source             61 */   \
(HAS_PROTOCOL_CLOCK_FROM_ASYNC2 | HAS_INT_CLOCK_FROM_BUS_CLOCK),                                    /*!< LPIT clock source               62 */   \
(HAS_PROTOCOL_CLOCK_FROM_ASYNC2 | HAS_INT_CLOCK_FROM_BUS_CLOCK),                                    /*!< LPSPI0 clock source             63 */   \
(HAS_MULTIPLIER | HAS_DIVIDER | HAS_PROTOCOL_CLOCK_FROM_ASYNC2 | HAS_INT_CLOCK_FROM_BUS_CLOCK),     /*!< LPTMR0 clock source             64 */   \
(HAS_PROTOCOL_CLOCK_FROM_ASYNC2 | HAS_INT_CLOCK_FROM_BUS_CLOCK),                                    /*!< LPUART0 clock source            65 */   \
(HAS_PROTOCOL_CLOCK_FROM_ASYNC2 | HAS_INT_CLOCK_FROM_BUS_CLOCK),                                    /*!< LPUART1 clock source            66 */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< End of ASYNCH DIV2 clocks       67 */   \
(NO_PERIPHERAL_FEATURE),                                                                            /*!< End of PCC clocks               68 */   \
}

/* Time to wait for SIRC to stabilize (number of
 * cycles when core runs at maximum speed - 112 MHz */
#define SIRC_STABILIZATION_TIMEOUT 100U

/* Time to wait for FIRC to stabilize (number of
 * cycles when core runs at maximum speed - 112 MHz */
#define FIRC_STABILIZATION_TIMEOUT 20U

/* Time to wait for SOSC to stabilize (number of
 * cycles when core runs at maximum speed - 112 MHz */
#define SOSC_STABILIZATION_TIMEOUT 3205000U;

/* Time to wait for SPLL to stabilize (number of
 * cycles when core runs at maximum speed - 112 MHz */
#define SPLL_STABILIZATION_TIMEOUT 1000U;


/*! @brief Temporary system clock source configurations.
 *         Each line represents the SYS(CORE), BUS and SLOW(FLASH) dividers
 *         for SIRC, FIRC, SOSC and SPLL clock sources.
  *
 *          SYS_CLK  BUS_CLK  SLOW_CLK
 *  SIRC       *        *         *
 *  FIRC       *        *         *
 *  SOSC       *        *         *
 *  SPLL       *        *         *
 */
#define TMP_SIRC_CLK   0U
#define TMP_FIRC_CLK   1U
#define TMP_SOSC_CLK   2U
#define TMP_SPLL_CLK   3U

#define TMP_SYS_DIV    0U
#define TMP_BUS_DIV    1U
#define TMP_SLOW_DIV   2U

#define TMP_SYS_CLK_NO 4U
#define TMP_SYS_DIV_NO 3U

#define TMP_SYSTEM_CLOCK_CONFIGS                                                                                \
{  /*       SYS_CLK                    BUS_CLK                  SLOW_CLK      */                                \
{  SCG_SYSTEM_CLOCK_DIV_BY_1, SCG_SYSTEM_CLOCK_DIV_BY_1, SCG_SYSTEM_CLOCK_DIV_BY_2},  /*!< Dividers for SIRC */ \
{  SCG_SYSTEM_CLOCK_DIV_BY_1, SCG_SYSTEM_CLOCK_DIV_BY_2, SCG_SYSTEM_CLOCK_DIV_BY_4},  /*!< Dividers for FIRC */ \
{  SCG_SYSTEM_CLOCK_DIV_BY_1, SCG_SYSTEM_CLOCK_DIV_BY_2, SCG_SYSTEM_CLOCK_DIV_BY_2},  /*!< Dividers for SOSC */ \
{  SCG_SYSTEM_CLOCK_DIV_BY_3, SCG_SYSTEM_CLOCK_DIV_BY_2, SCG_SYSTEM_CLOCK_DIV_BY_2},  /*!< Dividers for SPLL */ \
}

/* LPSPI module features */
/* @brief Initial value for state structure */
#define FEATURE_LPSPI_STATE_STRUCTURES_NULL {NULL}
/* @brief Clock indexes for LPSPI clock */
#define FEATURE_LPSPI_CLOCKS_NAMES {LPSPI0_CLK};

/* DMA module features */

/* @brief Number of DMA channels. */
#define FEATURE_DMA_CHANNELS (4U)
/* @brief Number of DMA virtual channels. */
#define FEATURE_DMA_VIRTUAL_CHANNELS (FEATURE_DMA_CHANNELS * DMA_INSTANCE_COUNT)
/* @brief Number of DMA interrupt lines. */
#define FEATURE_DMA_CHANNELS_INTERRUPT_LINES (4U)
/* @brief Number of DMA virtual interrupt lines. */
#define FEATURE_DMA_VIRTUAL_CHANNELS_INTERRUPT_LINES ((uint32_t)FEATURE_DMA_CHANNELS_INTERRUPT_LINES * (uint32_t)DMA_INSTANCE_COUNT)
/* @brief Number of DMA error interrupt lines. */
#define FEATURE_DMA_ERROR_INTERRUPT_LINES (1U)
/* @brief Number of DMA virtual error interrupt lines. */
#define FEATURE_DMA_VIRTUAL_ERROR_INTERRUPT_LINES ((uint32_t)FEATURE_DMA_ERROR_INTERRUPT_LINES * (uint32_t)DMA_INSTANCE_COUNT)
/* @brief DMA module has error interrupt. */
#define FEATURE_DMA_HAS_ERROR_IRQ
/* @brief DMA module separate interrupt lines for each channel. */
#define FEATURE_DMA_SEPARATE_IRQ_LINES_PER_CHN
/* @brief Conversion from channel index to DCHPRI index. */
#define FEATURE_DMA_CHN_TO_DCHPRI_INDEX(x) ((x) ^ 3U)
/* @brief DMA channel groups count. */
#define FEATURE_DMA_CHANNEL_GROUP_COUNT (1U)
/* @brief Clock name for DMA. */
#define FEATURE_DMA_CLOCK_NAMES {SIM_DMA_CLK}
/* @brief DMA channel width based on number of TCDs: 2^N, N=4,5,... */
#define FEATURE_DMA_CH_WIDTH (4U)
/* @brief DMA channel to instance. */
#define FEATURE_DMA_VCH_TO_INSTANCE(x) 	((x) >> (uint32_t)FEATURE_DMA_CH_WIDTH)
/* @brief DMA virtual channel to channel. */
#define FEATURE_DMA_VCH_TO_CH(x)        ((x) & ((uint32_t)FEATURE_DMA_CHANNELS - 1U))
/* @brief DMA supports the following particular channel priorities. */
#define FEATURE_DMA_4_CH_PRIORITIES
/* @brief DMA supports bus bandwidth control. */
#define FEATURE_DMA_ENGINE_STALL

/* DMAMUX module features */

/* @brief DMAMUX peripheral is available in silicon. */
#define FEATURE_DMAMUX_AVAILABLE
/* @brief Number of DMA channels. */
#define FEATURE_DMAMUX_CHANNELS (4U)
/* @brief Has the periodic trigger capability. */
#define FEATURE_DMAMUX_HAS_TRIG (1)
/* @brief Conversion from request source to the actual DMAMUX channel. */
#define FEATURE_DMAMUX_REQ_SRC_TO_CH(x) (x)
/* @brief Mapping between request source and DMAMUX instance. */
#define FEATURE_DMAMUX_REQ_SRC_TO_INSTANCE(x) (0U)
/* @brief Conversion from eDMA channel index to DMAMUX channel. */
#define FEATURE_DMAMUX_DMA_CH_TO_CH(x) (x)
/* @brief Conversion from DMAMUX channel DMAMUX register index. */
#define FEATURE_DMAMUX_CHN_REG_INDEX(x) (x)
/* @brief Clock names for DMAMUX. */
#define FEATURE_DMAMUX_CLOCK_NAMES {DMAMUX0_CLK}
/*!
 * @brief Structure for the DMA hardware request
 *
 * Defines the structure for the DMA hardware request collections. The user can configure the
 * hardware request into DMAMUX to trigger the DMA transfer accordingly. The index
 * of the hardware request varies according  to the to SoC.
 */

typedef enum {
    EDMA_REQ_DISABLED = 0U,
    EDMA_REQ_LPUART0_RX = 2U,
    EDMA_REQ_LPUART0_TX = 3U,
    EDMA_REQ_LPUART1_RX = 4U,
    EDMA_REQ_LPUART1_TX = 5U,
    EDMA_REQ_FLEXIO_SHIFTER0 = 10U,
    EDMA_REQ_FLEXIO_SHIFTER1 = 11U,
    EDMA_REQ_FLEXIO_SHIFTER2 = 12U,
    EDMA_REQ_FLEXIO_SHIFTER3 = 13U,
    EDMA_REQ_LPSPI0_RX = 14U,
    EDMA_REQ_LPSPI0_TX = 15U,
    EDMA_REQ_FTM1_CHANNEL_0 = 20U,
    EDMA_REQ_FTM1_CHANNEL_1 = 21U,
    EDMA_REQ_FTM1_CHANNEL_2 = 22U,
    EDMA_REQ_FTM1_CHANNEL_3 = 23U,
    EDMA_REQ_FTM1_CHANNEL_4 = 24U,
    EDMA_REQ_FTM1_CHANNEL_5 = 25U,
    EDMA_REQ_FTM1_CHANNEL_6 = 26U,
    EDMA_REQ_FTM1_CHANNEL_7 = 27U,
    EDMA_REQ_FTM0_OR_CH0_CH7 = 36U,
    EDMA_REQ_ADC0 = 42U,
    EDMA_REQ_LPI2C0_RX = 44U,
    EDMA_REQ_LPI2C0_TX = 45U,
    EDMA_REQ_PDB0 = 46U,
    EDMA_REQ_CMP0 = 48U,
    EDMA_REQ_PORTA = 49U,
    EDMA_REQ_PORTB = 50U,
    EDMA_REQ_PORTC = 51U,
    EDMA_REQ_PORTD = 52U,
    EDMA_REQ_PORTE = 53U,
    EDMA_REQ_FLEXCAN0 = 54U,
    EDMA_REQ_LPTMR0 = 59U,
    EDMA_REQ_DMAMUX_ALWAYS_ENABLED0 = 62U,
    EDMA_REQ_DMAMUX_ALWAYS_ENABLED1 = 63U
} dma_request_source_t;

/* PORT module features */
/*! @brief PORT Used for setting Pins */
#define FEATURE_PINS_DRIVER_USING_PORT          (1)
/* @brief Has control lock (register bit PCR[LK]). */
#define FEATURE_PORT_HAS_PIN_CONTROL_LOCK       (1)
/* @brief Has open drain control (register bit PCR[ODE]). */
#define FEATURE_PINS_HAS_OPEN_DRAIN             (0)
/* @brief Has digital filter (registers DFER, DFCR and DFWR). */
#define FEATURE_PORT_HAS_DIGITAL_FILTER         (1)
/* @brief Has trigger output to trigger other peripherals (register bit field PCR[IRQC] values). */
#define FEATURE_PORT_HAS_TRIGGER_OUT            (0)
/* @brief Has setting flag only (register bit field PCR[IRQC] values). */
#define FEATURE_PORT_HAS_FLAG_SET_ONLY          (0)
/* @brief Has over-current feature (register bit field PCR[OCIE] values). */
#define FEATURE_PINS_HAS_OVER_CURRENT           (0)
/* @brief Has pull resistor selection available. */
#define FEATURE_PINS_HAS_PULL_SELECTION         (1)
/* @brief Has slew rate control (register bit PCR[SRE]). */
#define FEATURE_PINS_HAS_SLEW_RATE              (0)
/* @brief Has passive filter (register bit field PCR[PFE]). */
#define FEATURE_PORT_HAS_PASSIVE_FILTER         (1)
/* @brief Has drive strength (register bit PCR[DSE]). */
#define FEATURE_PINS_HAS_DRIVE_STRENGTH         (1)
/* @brief Has drive strength control bits*/
#define FEATURE_PINS_HAS_DRIVE_STRENGTH_CONTROL (0)
/* @brief Has port input disable control bits*/
#define FEATURE_PORT_HAS_INPUT_DISABLE          (0)
/* @brief SIM_CHIPCTL_ADC_INTERLEAVE_EN bit is not available */
#define FEATURE_PINS_HAS_ADC_INTERLEAVE_EN      (0)

/* LPTMR module features */

/* @brief LPTMR pulse counter input options */
#define FEATURE_LPTMR_HAS_INPUT_ALT1_SELECTION (0U)

/* LPI2C module features */

/* @brief DMA instance used for LPI2C module */
#define LPI2C_DMA_INSTANCE 0U

/* @brief EDMA requests for LPI2C module. */
#define LPI2C_EDMA_REQ                           {{(uint8_t)EDMA_REQ_LPI2C0_TX, (uint8_t)EDMA_REQ_LPI2C0_RX}}
/* @brief PCC clocks for LPI2C module. */
#define LPI2C_PCC_CLOCKS                         {LPI2C0_CLK}

/* @brief Disable high-speed and ultra-fast operating modes for S32K14x. */
#define LPI2C_HAS_FAST_PLUS_MODE (0U)
#define LPI2C_HAS_HIGH_SPEED_MODE (0U)
#define LPI2C_HAS_ULTRA_FAST_MODE (0U)

/* LPI2C module features */

/* @brief DMA instance used for LPI2C module */
#define LPI2C_DMA_INSTANCE 0U

/* @brief EDMA requests for LPI2C module. */
#define LPI2C_EDMA_REQ                           {{(uint8_t)EDMA_REQ_LPI2C0_TX, (uint8_t)EDMA_REQ_LPI2C0_RX}}
/* @brief PCC clocks for LPI2C module. */
#define LPI2C_PCC_CLOCKS                         {LPI2C0_CLK}

/* PDB module features */

/* @brief PDB has back-to-back at instance level */
#define FEATURE_PDB_HAS_INSTANCE_BACKTOBACK  (0)

#endif /* S32K116_FEATURES_H */
/*******************************************************************************
 * EOF
 ******************************************************************************/
