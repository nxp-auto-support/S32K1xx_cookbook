/*
 * main implementation: use this 'C' sample to create your own application
 *
 */


#include "device_registers.h"
#include "dma.h"
#include "clocks_and_modes.h"
#include "pdb.h"
#include "ADC.h"

void WDOG_disable (void)
{
	WDOG->CNT=0xD928C520;     /* Unlock watchdog 		*/
	WDOG->TOVAL=0x0000FFFF;   /* Maximum timeout value 	*/
	WDOG->CS = 0x00002100;    /* Disable watchdog 		*/
}

int main(void)
{
	WDOG_disable();        			/* Disable WDOG */
	SOSC_init_8MHz();      			/* Initialize system oscillator for 8 MHz xtal */
	SPLL_init_160MHz();    			/* Initialize SPLL to 160 MHz with 8 MHz SOSC */
	NormalRUNmode_80MHz();			/* Init clocks: 80 MHz sysclk & core, 40 MHz bus, 20 MHz flash */
	ADC_FlexScan_Config();			/* Initialize ADC0 CH0 with HW Trigger and DMA Request */
	DMAMUX_FlexScan_init();			/* Initialize DMA to take requests from ADC0	*/
	DMA_TCD_FlexScan_Config();		/* Set up TCD CH0 to save measurements from ADC0 and link to CH1 to change ADC0 channel to measure */
	DMA->SERQ = DMA_SERQ_SERQ(0);	/* Enable Requests for DMA Channel 0 */

	PDB_FlexScan_Config();			/* Configure PDB to trigger ADC0 every second */

	S32_NVIC->ISER[0/32] |= 1<<(0%32);	/*	Enable interruption for DMA CH0	*/

        for(;;) {       

        }

	return 0;
}

void DMA0_IRQHandler (void) {
	DMA->CDNE = DMA_CDNE_CDNE(0);	/* Clear Done Status Flag of DMA Channel 0 */
	DMA->CINT = DMA_CINT_CINT(0);	/* Clear Interruption request flag of DMA Channel 0 */
	PDB0->SC &=~ PDB_SC_PDBEN_MASK;	/* Turn off PDB to stop getting samples after DMA CH0 major loop */
}
