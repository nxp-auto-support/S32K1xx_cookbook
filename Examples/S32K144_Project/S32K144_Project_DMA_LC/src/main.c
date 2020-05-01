/*
 * main implementation: use this 'C' sample to create your own application
 *
 */
#include "device_registers.h"
#include "clocks_and_modes.h"
#include "dma.h"

/*!
 * Description:
 * =============================================================================================
 * This project intends to show the Linking Channel Feature of the DMA where you can set up a link
 * so when a channel finishes a major or minor loop it activates another DMA channel and send
 * information from different sources or to different destinations or both. In this case we use it to link
 * CH0 to CH1 after CH0's major loop to copy the phrase "Hello World" from one string to another.
 *
 * */

void WDOG_disable (void)
{
	WDOG->CNT=0xD928C520;     /* Unlock watchdog 		*/
	WDOG->TOVAL=0x0000FFFF;   /* Maximum timeout value 	*/
	WDOG->CS = 0x00002100;    /* Disable watchdog 		*/
}

int main(void) {
	WDOG_disable();        /* Disable WDOG */
	SOSC_init_8MHz();      /* Initialize system oscillator for 8 MHz xtal */
	SPLL_init_160MHz();    /* Initialize SPLL to 160 MHz with 8 MHz SOSC */
	NormalRUNmode_80MHz(); /* Init clocks: 80 MHz sysclk & core, 40 MHz bus, 20 MHz flash */
	DMAMUX_LC_init();	   /* Initialize DMAMUX to always generate DMA requests for DMA CH0 and CH1	*/

	DMA_TCD_LC_Config();	/* Set up DMA TCD CH0 and CH1 to work with linking channel to completely 'save' "Hello World" */
	DMA->SERQ |= DMA_SERQ_SERQ(0);	/*	Enable DMA CH0 request	*/
	DMA->SERQ |= DMA_SERQ_SERQ(1);	/*	Enable DMA CH1 request	*/

	S32_NVIC->ICPR[1/32] |= 1 << (1 % 32);  /* DMA CH1: clr any pending IRQ	*/
	S32_NVIC->ISER[1/32] |= 1 << (1 % 32);  /* DMA CH1: enable IRQ 			*/
	for (;;) {
		/* Wait forever */
		/* Look for the TCD_LC_Dest array inside the dma driver */
    }
    return 0;
}

void DMA1_IRQHandler (void)
{
	 DMA->CDNE |= DMA_CDNE_CADN_MASK;	/* Clear Done status bit */
	 DMA->CINT |= DMA_CINT_CINT(1);					/* Clear Interrupt request */
}
