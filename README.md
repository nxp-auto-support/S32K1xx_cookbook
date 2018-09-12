# S32K1xx Series Cookbook
> Software examples and startup code to exercise microcontroller features.\
> In general, this code should be considered as a starting point. Users should review the initializations to see if any are missing or if changes are desired.\
> This is an extension of S32K14x Series Cookbook Application Note available on nxp.com

## Software Examples
> The table bellow lists all available software examples.
| Num.	| Name												|
| ----- |:-------------------------------------------------:| 
| 1 	| Hello World										|
| 2 	| Hello World + Clocks								|
| 3 	| Hello World + Clocks + Interrupts					|
| 4 	| Comparator (CMP)									|
| 5 	| Analog-to-Digital Converter (ADC)					|
| 6 	| Low Power Serial Peripheral Interface (LPSPI)		|
| 7 	| Low Power Inter-Integrated Circuit (LPI2C)		|
| 8 	| Low Power Universal Asynchronous Rx/Tx (LPUART)	|
| 9 	| Flexible I/O (FlexIO)								|
| 10 	| FlexCAN											|
| 11 	| CAN Flexible Data-Rate							|
| 12 	| Programmable delay block (PDB)					|
| 13 	| FlexTimer Module (FTM)							|
| 14 	| Low Power Timer (LPTMR)							|
| 15 	| Real Time Clock (RTC)								|
| 16 	| Direct Memory Access (DMA)						|
| 17 	| External Watchdog Monitor (EWM)					|
| 18 	| Cyclic Redundancy Check (CRC)						|
| 19	| Synchronous Audio Interface (SAI)					|

## License
> The 3-Clause BSD License.

# Importing projects
> See the following steps to import available projects into your S32DS workspace.

| Step	| Description  																								|
| ----- |:---------------------------------------------------------------------------------------------------------:| 
| 1 	| Prerequisites: Install and configure Git. 																|
| 2 	| Start S32 Design Studio for ARM with desired workspace. 													|
| 3 	| Go to File → Import... 																					|
| 4		| Select: Git → Projects from Git, and click Next. 															|
| 5		| Select: Clone URL, and click Next. 																		|
| 6		| Paste the repository http in the URL field.																|
| 7		| Check master branch, and click Next.																		|
| 8		| In Destination → Directory, enter the local path where you want to clone the repository and click Next.	|
| 9		| Select: Working Tree - directory, and click Next. 														|
| 10	| Check the projects you want to import, and click Finish. 													|
| 11	| Build and Debug. 																							|
| 12 	| Open "doc" folder, and double click the shortcut called "start_here". 									|

# Adding projects
> A simple way to create your own project is to start with an existing one. Example steps are listed in the following table.

| Step	| Description  																								|
| ----- |:---------------------------------------------------------------------------------------------------------:| 
| 1 	| Start S32 Design Studio with desired workspace. 															|
| 2 	| Add blank project, File → New → New S32DS Application Project.											|
| 3 	| Copy an existing source file from a different project in the new project "src" folder.					|
| 4 	| Make any file name adjustments.																			|
| 5 	| Build project, edit main.c as needed and rebuild by clicking on the hammer icon.							|
| 6 	| Tip: Close unrelated projects.																			|
