/*
 * @brief NXP LPC1769 LPCXpresso Sysinit file
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2013
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "board.h"

/* The System initialization code is called prior to the application and
   initializes the board for run-time operation. Board initialization
   includes clock setup and default pin muxing configuration. */

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/* Pin muxing configuration */
    // PINGROUP , PINNUM ,
STATIC const PINMUX_GRP_T pinmuxing[] =
{

	// Serial communication of 422_2 channel 2
	{0,  0,   IOCON_MODE_INACT | IOCON_FUNC2},	/* TXD3 */
	{0,  1,   IOCON_MODE_INACT | IOCON_FUNC2},	/* RXD3 */
	{4, 28,   IOCON_MODE_INACT | IOCON_FUNC0},	/*  RXD2DIS  output  */
    {4, 29,   IOCON_MODE_INACT | IOCON_FUNC0},	/*  TXD2EN   output  */

	// Serial communication of 422_2 channel 1
	{0,  2,   IOCON_MODE_INACT | IOCON_FUNC1},	/* TXD0 */
	{0,  3,   IOCON_MODE_INACT | IOCON_FUNC1},	/* RXD0 */



	// UART DEBUG
	{0,  10,   IOCON_MODE_INACT | IOCON_FUNC1},	/* TXD2 */
	{0,  11,   IOCON_MODE_INACT | IOCON_FUNC1},	/* RXD2 */


	{0, 4, IOCON_MODE_INACT | IOCON_FUNC0},	/* RESET COMMAND  output*/
	{0, 5, IOCON_MODE_INACT | IOCON_FUNC0},	/* INTERNAL ISP output*/
	{0, 6, IOCON_MODE_INACT | IOCON_FUNC0},	/* DISPLAY OSC ENABLE TP3 output*/
	{0, 7, IOCON_MODE_INACT | IOCON_FUNC0},	/* TP4  output */
	{0, 8, IOCON_MODE_INACT | IOCON_FUNC0},	/* TP5  output */
	{0, 9, IOCON_MODE_INACT | IOCON_FUNC0},	/* TP6  output */

	{0, 15, IOCON_MODE_INACT | IOCON_FUNC0},	/*  DISP_CLK    output */
	{0, 17, IOCON_MODE_INACT | IOCON_FUNC0},	/*  DISP_CONT_1 output  */
	{0, 18, IOCON_MODE_INACT | IOCON_FUNC0},	/*  DISP_DATA   output  */
	{0, 19, IOCON_MODE_INACT | IOCON_FUNC0},	/*  COLOMN_SELECT_1  output  */
	{0, 20, IOCON_MODE_INACT | IOCON_FUNC0},	/*  COLOMN_SELECT_2  output  */
	{0, 21, IOCON_MODE_INACT | IOCON_FUNC0},	/*  COLOMN_SELECT_3  output  */
	{0, 22, IOCON_MODE_INACT | IOCON_FUNC0},	/*  COLOMN_SELECT_4  output  */
	{0, 30, IOCON_MODE_INACT | IOCON_FUNC0},	/*  COLOMN_SELECT_5  output  */



	/* ENET */
	{0x1, 0,  IOCON_MODE_INACT | IOCON_FUNC1},	/* ENET_TXD0 */
	{0x1, 1,  IOCON_MODE_INACT | IOCON_FUNC1},	/* ENET_TXD1 */
	{0x1, 4,  IOCON_MODE_INACT | IOCON_FUNC1},	/* ENET_TX_EN */
	{0x1, 8,  IOCON_MODE_INACT | IOCON_FUNC1},	/* ENET_CRS */
	{0x1, 9,  IOCON_MODE_INACT | IOCON_FUNC1},	/* ENET_RXD0 */
	{0x1, 10, IOCON_MODE_INACT | IOCON_FUNC1},	/* ENET_RXD1 */
	{0x1, 14, IOCON_MODE_INACT | IOCON_FUNC1},	/* ENET_RX_ER */
	{0x1, 15, IOCON_MODE_INACT | IOCON_FUNC1},	/* ENET_REF_CLK */
	{0x1, 16, IOCON_MODE_INACT | IOCON_FUNC1},	/* ENET_MDC */
	{0x1, 17, IOCON_MODE_INACT | IOCON_FUNC1},	/* ENET_MDIO */


	{1, 19, IOCON_MODE_INACT | IOCON_FUNC0},	/*  RES_MINUS  output  */
	{1, 22, IOCON_MODE_INACT | IOCON_FUNC0 | IOCON_MODE_PULLDOWN},	/*  DISCRETE_IN_1 input  */
	{1, 23, IOCON_MODE_INACT | IOCON_FUNC0 | IOCON_MODE_PULLDOWN},	/*  DISCRETE_IN_2 input  */
	{1, 24, IOCON_MODE_INACT | IOCON_FUNC0},	/*  DISCRETE_OUT_1 output  */
	{1, 25, IOCON_MODE_INACT | IOCON_FUNC0},	/*  DISCRETE_OUT_2 output  */
	{1, 26, IOCON_MODE_INACT | IOCON_FUNC0 | IOCON_MODE_PULLDOWN},	/*  RCU_ID1 input  */
	{1, 27, IOCON_MODE_INACT | IOCON_FUNC0 | IOCON_MODE_PULLDOWN},	/*  RCU_ID2 input  */

	//////// BIT ADC CHANNLES //////////
	// ADC INPUT - channel 4
	{1, 30, IOCON_MODE_INACT | IOCON_FUNC3},	/*  PLUS_5V_M   input   */
	// ADC INPUT - channel 5
	{1, 31, IOCON_MODE_INACT | IOCON_FUNC3},	/*  PLUS_3.3V_M  input  */
	// ADC INPUT - channel 0
	{0, 23, IOCON_MODE_INACT | IOCON_FUNC1},	/*  PLUS_12V_M  input  */
	// ADC INPUT - channel 1
	{0, 24, IOCON_MODE_INACT | IOCON_FUNC1},	/*  PLUS_V_LED_M  input  */
	// ADC INPUT - channel 2
	{0, 25, IOCON_MODE_INACT | IOCON_FUNC1},	/* DIM_KNOB0F */
	/////////////////////////////////////////////////////////


    // I20
	{0, 27, IOCON_MODE_INACT | IOCON_FUNC1},	/*  SDA  */
	{0, 28, IOCON_MODE_INACT | IOCON_FUNC1},	/*  SCL  */





	// RCU PIN MUXING
	////////////////  DISPLAY_DATA ///////////////////////////
	{2, 0, IOCON_MODE_INACT | IOCON_FUNC0},	/* DISPLAY_DATA0 output*/
	{2, 1, IOCON_MODE_INACT | IOCON_FUNC0},	/* DISPLAY_DATA1 output*/
	{2, 2, IOCON_MODE_INACT | IOCON_FUNC0},	/* DISPLAY_DATA2 output*/
	{2, 3, IOCON_MODE_INACT | IOCON_FUNC0},	/* DISPLAY_DATA3 output*/
	{2, 4, IOCON_MODE_INACT | IOCON_FUNC0},	/* DISPLAY_DATA4 output*/
	{2, 5, IOCON_MODE_INACT | IOCON_FUNC0},	/* DISPLAY_DATA5 output*/
	{2, 6, IOCON_MODE_INACT | IOCON_FUNC0},	/* DISPLAY_DATA6 output*/
	{2, 7, IOCON_MODE_INACT | IOCON_FUNC0},	/* DISPLAY_DATA7 output*/
	{2, 8, IOCON_MODE_INACT | IOCON_FUNC0},	/* DISPLAY_COL_LE output */
	{2, 9, IOCON_MODE_INACT | IOCON_FUNC0},	/* DISPLAY_SH_LD0 output */
	{2, 11, IOCON_MODE_INACT | IOCON_FUNC0}, /* DISPLAY_SH_LD1 */
	{2, 12, IOCON_MODE_INACT | IOCON_FUNC0}, /* DISPLAY_SH_LD2 */
	{2, 13, IOCON_MODE_INACT | IOCON_FUNC0}, /* KEYBOARD_RESET */
	{3, 25, IOCON_MODE_INACT | IOCON_FUNC0}, /* DISPLAY_CLOCK output */
	{0, 26, IOCON_MODE_INACT | IOCON_FUNC2}, /* DISPLAY_COL_VOLTAGE */
	{3, 26, IOCON_MODE_INACT | IOCON_FUNC0}, /* DISPLAY_CLOCK_DATA output */



	// PWM area
	{1, 18, IOCON_MODE_INACT | IOCON_FUNC2},	/*  INDCATORS_PWM  PWM.1  */
	{1, 20, IOCON_MODE_INACT | IOCON_FUNC2},	/*  DISPLAY_BL_PWM PWM.2  */

	//{1, 20, IOCON_MODE_INACT | IOCON_FUNC0},	/*  DISPLAY_BLANK_PWM PWM.2  */
	{1, 21, IOCON_MODE_INACT | IOCON_FUNC0},	/*  DISPLAY_OSC  PWM.3    */

	{1, 28, IOCON_MODE_INACT | IOCON_FUNC0},	/*  LED1  output  */
	{1, 29, IOCON_MODE_INACT | IOCON_FUNC0},	/*  LED2  output  */
	{0, 16, IOCON_MODE_INACT | IOCON_FUNC0},	/*  LED3  output  */






};

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Sets up system pin muxing */
void Board_SetupMuxing(void)
{
	Chip_IOCON_SetPinMuxing(LPC_IOCON, pinmuxing, sizeof(pinmuxing) / sizeof(PINMUX_GRP_T));
}

/* Setup system clocking */
void Board_SetupClocking(void)
{
	Chip_SetupXtalClocking();

	/* Setup FLASH access to 4 clocks (100MHz clock) */
	Chip_SYSCTL_SetFLASHAccess(FLASHTIM_100MHZ_CPU);
}

/* Set up and initialize hardware prior to call to main */
void Board_SystemInit(void)
{
	Board_SetupMuxing();
	Board_SetupClocking();
}
