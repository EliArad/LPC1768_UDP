/*
 * @brief NXP LPC1769 LPCXpresso board file
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
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
#include "string.h"

//#include "retarget.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/


/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/* System oscillator rate and RTC oscillator rate */
const uint32_t OscRateIn = 12000000;
const uint32_t RTCOscRateIn = 32768;

/*****************************************************************************
 * Private functions
 ****************************************************************************/

static void Board_SetGpioDirections();

/* Initializes board LED(s) */
static void Board_LED_Init(void)
{

	Chip_GPIO_WriteDirBit(LPC_GPIO, LED1_GPIO_PORT_NUM, LED1_GPIO_BIT_NUM, 0);
	Chip_GPIO_WriteDirBit(LPC_GPIO, LED2_GPIO_PORT_NUM, LED2_GPIO_BIT_NUM, 0);
	Chip_GPIO_WriteDirBit(LPC_GPIO, LED3_GPIO_PORT_NUM, LED3_GPIO_BIT_NUM, 0);
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Initialize UART pins */
void Board_UART_Init(LPC_USART_T *pUART)
{
	/* Pin Muxing has already been done during SystemInit */
}

/* Initialize debug output via UART for board */
void Board_Uarts_Init(void)
{
#if defined(DEBUG_ENABLE)
	Board_UART_Init(DEBUG_UART);

	Chip_UART_Init(DEBUG_UART);
	Chip_UART_SetBaud(DEBUG_UART, 115200);
	Chip_UART_ConfigData(DEBUG_UART, UART_LCR_WLEN8 | UART_LCR_SBS_1BIT | UART_LCR_PARITY_DIS);
	/* Enable UART Transmit */
	Chip_UART_TXEnable(DEBUG_UART);


	// Enable the 422 Serial comm for channel 1
	Board_UART_Init(RS422_CH1);

	Chip_UART_Init(RS422_CH1);
	Chip_UART_SetBaud(RS422_CH1, 115200);
	Chip_UART_ConfigData(RS422_CH1, UART_LCR_WLEN8 | UART_LCR_SBS_1BIT | UART_LCR_PARITY_DIS);
	/* Enable UART Transmit */
	Chip_UART_TXEnable(RS422_CH1);



	// Enable the 422 Serial comm for channel 1
	Board_UART_Init(RS422_CH2);

	Chip_UART_Init(RS422_CH2);
	Chip_UART_SetBaud(RS422_CH2, 115200);
	Chip_UART_ConfigData(RS422_CH2, UART_LCR_WLEN8 | UART_LCR_SBS_1BIT | UART_LCR_PARITY_DIS);
	/* Enable UART Transmit */
	Chip_UART_TXEnable(RS422_CH2);




#endif
}

/* Sends a character on the UART */
void Board_UARTPutChar(char ch)
{
#if defined(DEBUG_ENABLE)
	while ((Chip_UART_ReadLineStatus(DEBUG_UART) & UART_LSR_THRE) == 0) {}
	Chip_UART_SendByte(DEBUG_UART, (uint8_t) ch);
#endif
}

/* Gets a character from the UART, returns EOF if no character is ready */
int Board_UARTGetChar(void)
{
#if defined(DEBUG_ENABLE)
	if (Chip_UART_ReadLineStatus(DEBUG_UART) & UART_LSR_RDR) {
		return (int) Chip_UART_ReadByte(DEBUG_UART);
	}
#endif
	return EOF;
}

/* Outputs a string on the debug UART */
void Board_UARTPutSTR(char *str)
{
#if defined(DEBUG_ENABLE)
	while (*str != '\0') {
		Board_UARTPutChar(*str++);
	}
#endif
}

/* Sets the state of a board LED to on or off */
void Board_LED_Set(uint8_t LEDNumber, bool On)
{
	/*  one LED at a time */
	if (LEDNumber & 0x1)
	{
		Chip_GPIO_WritePortBit(LPC_GPIO, LED1_GPIO_PORT_NUM, LED1_GPIO_BIT_NUM, On);
	}
	if (LEDNumber & 0x2)
	{
		Chip_GPIO_WritePortBit(LPC_GPIO, LED2_GPIO_PORT_NUM, LED2_GPIO_BIT_NUM, On);
	}
	if (LEDNumber & 0x4)
	{
		Chip_GPIO_WritePortBit(LPC_GPIO, LED3_GPIO_PORT_NUM, LED3_GPIO_BIT_NUM, On);
	}
}

static uint8_t leds[3];
void Board_LED_Toogle(uint8_t LEDNumber)
{
	/*  one LED at a time */
	if (LEDNumber & 0x1)
	{
		leds[0] = !leds[0];
		Chip_GPIO_WritePortBit(LPC_GPIO, LED1_GPIO_PORT_NUM, LED1_GPIO_BIT_NUM, leds[0]);
	}
	if (LEDNumber & 0x2)
	{
		leds[1] = !leds[1];
		Chip_GPIO_WritePortBit(LPC_GPIO, LED2_GPIO_PORT_NUM, LED2_GPIO_BIT_NUM, leds[1]);
	}
	if (LEDNumber & 0x4)
	{
		leds[2] = !leds[2];
		Chip_GPIO_WritePortBit(LPC_GPIO, LED3_GPIO_PORT_NUM, LED3_GPIO_BIT_NUM, leds[2]);
	}
}

/* Returns the current state of a board LED */
bool Board_LED_Test(uint8_t LEDNumber)
{
	bool state = false;

	if (LEDNumber & 1)
	{
		state = Chip_GPIO_ReadPortBit(LPC_GPIO, LED1_GPIO_PORT_NUM, LED1_GPIO_BIT_NUM);
	}
	if (LEDNumber & 2)
	{
		state = Chip_GPIO_ReadPortBit(LPC_GPIO, LED1_GPIO_PORT_NUM, LED1_GPIO_BIT_NUM);
	}
	if (LEDNumber & 4)
	{
		state = Chip_GPIO_ReadPortBit(LPC_GPIO, LED1_GPIO_PORT_NUM, LED1_GPIO_BIT_NUM);
	}

	return state;
}

void Board_LED_Toggle(uint8_t LEDNumber)
{
	if (LEDNumber == 0) {
		Board_LED_Set(LEDNumber, !Board_LED_Test(LEDNumber));
	}
}

/* Set up and initialize all required blocks and functions related to the
   board hardware */
void Board_Init(void)
{
	/* Sets up DEBUG UART */
	DEBUGINIT();

	/* Initializes GPIO */
	Chip_GPIO_Init(LPC_GPIO);
	Chip_IOCON_Init(LPC_IOCON);

	/* Initialize LEDs */
	Board_LED_Init();

	Board_SetGpioDirections();
}

static void Board_SetGpioDirections()
{

	Chip_GPIO_SetPinDIROutput(LPC_GPIO,2, 0);	/* DISPLAY_DATA0 output*/
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,2, 1);	/* DISPLAY_DATA1 output*/
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,2, 2);	/* DISPLAY_DATA2 output*/
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,2, 3);	/* DISPLAY_DATA3 output*/
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,2, 4);	/* DISPLAY_DATA4 output*/
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,2, 5);	/* DISPLAY_DATA5 output*/
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,2, 6);	/* DISPLAY_DATA6 output*/
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,2, 7);	/* DISPLAY_DATA7 output*/
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,2, 8);	/* DISPLAY_COL_LE output */
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,2, 9);	/* DISPLAY_SH_LD0 output */
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,2, 11); /* DISPLAY_SH_LD1 */
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,2, 12); /* DISPLAY_SH_LD2 */
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,2, 13); /* KEYBOARD_RESET */
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,3, 25); /* DISPLAY_CLOCK output */
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,3, 26); /* DISPLAY_CLOCK_DATA output */

	Chip_GPIO_SetPinDIRInput(LPC_GPIO, 0, 4); /* RESET COMMAND  input*/
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, 0, 5); /* INTERNAL ISP input*/

	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 6); /* DISPLAY OSC ENABLE TP3 output*/

	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 7); /* TP4  output */


	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 8); /* TP5  output */


	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 9);	/* TP6  output */
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 15);	/*  Display clock  output */
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 17);	/*  DISP_CONT_1 output  */
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 18);	/*  DISP_DATA   output  */
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 19);	/*  COLOMN_SELECT_1  output  */
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 20);	/*  COLOMN_SELECT_2  output  */
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 21);	/*  COLOMN_SELECT_3  output  */
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 22);	/*  COLOMN_SELECT_4  output  */
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 30);	/*  COLOMN_SELECT_5  output  */

	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 19);	/*  RES_MINUS  output  */
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, 1, 22);	/*  DISCRETE_IN_1 input  */
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, 1, 23);	/*  DISCRETE_IN_2 input  */
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 24);	/*  DISCRETE_OUT_1 output  */
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 25);	/*  DISCRETE_OUT_2 output  */
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, 1, 26);	/*  RCU_ID1 input  */
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, 1, 27);	/*  RCU_ID2 input  */


	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 28);	/*  LED1  output  */
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 29);	/*  LED2  output  */
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 16);	/*  LED3  output  */


	//Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 20);	/*  DISPLAY BLANK  temporary has gpio output  */

	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 4, 28); /*  RXD2DIS  output  */
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 4, 29); /*  TXD2EN   output  */




}
/* Returns the MAC address assigned to this board */
void Board_ENET_GetMacADDR(uint8_t *mcaddr, uint8_t rcuID)
{
	if (rcuID == 0)
	{
		const uint8_t boardmac[] = {0x00, 0x60, 0x37, 0x12, 0x34, 0x56};
		memcpy(mcaddr, boardmac, 6);
	}
	else
	{
		const uint8_t boardmac[] = {0x00, 0x60, 0x37, 0x12, 0x34, 0x57};
		memcpy(mcaddr, boardmac, 6);
	}
}

/* Initialize pin muxing for SSP interface */
void Board_SSP_Init(LPC_SSP_T *pSSP)
{
	if (pSSP == LPC_SSP1) {
		/* Set up clock and muxing for SSP1 interface */
		/*
		 * Initialize SSP0 pins connect
		 * P0.7: SCK
		 * P0.6: SSEL
		 * P0.8: MISO
		 * P0.9: MOSI
		 */
		Chip_IOCON_PinMux(LPC_IOCON, 0, 7, IOCON_MODE_INACT, IOCON_FUNC2);
		Chip_IOCON_PinMux(LPC_IOCON, 0, 6, IOCON_MODE_INACT, IOCON_FUNC2);
		Chip_IOCON_PinMux(LPC_IOCON, 0, 8, IOCON_MODE_INACT, IOCON_FUNC2);
		Chip_IOCON_PinMux(LPC_IOCON, 0, 9, IOCON_MODE_INACT, IOCON_FUNC2);
	}
	else {
		/* Set up clock and muxing for SSP0 interface */
		/*
		 * Initialize SSP0 pins connect
		 * P0.15: SCK
		 * P0.16: SSEL
		 * P0.17: MISO
		 * P0.18: MOSI
		 */
		Chip_IOCON_PinMux(LPC_IOCON, 0, 15, IOCON_MODE_INACT, IOCON_FUNC2);
		Chip_IOCON_PinMux(LPC_IOCON, 0, 16, IOCON_MODE_INACT, IOCON_FUNC2);
		Chip_IOCON_PinMux(LPC_IOCON, 0, 17, IOCON_MODE_INACT, IOCON_FUNC2);
		Chip_IOCON_PinMux(LPC_IOCON, 0, 18, IOCON_MODE_INACT, IOCON_FUNC2);
	}
}

/* Initialize pin muxing for SPI interface */
void Board_SPI_Init(bool isMaster)
{
	/* Set up clock and muxing for SSP0 interface */
	/*
	 * Initialize SSP0 pins connect
	 * P0.15: SCK
	 * P0.16: SSEL
	 * P0.17: MISO
	 * P0.18: MOSI
	 */
	Chip_IOCON_PinMux(LPC_IOCON, 0, 15, IOCON_MODE_PULLDOWN, IOCON_FUNC3);
	if (isMaster) {
		Chip_IOCON_PinMux(LPC_IOCON, 0, 16, IOCON_MODE_PULLUP, IOCON_FUNC0);
		Chip_GPIO_WriteDirBit(LPC_GPIO, 0, 16, true);
		Board_SPI_DeassertSSEL();

	}
	else {
		Chip_IOCON_PinMux(LPC_IOCON, 0, 16, IOCON_MODE_PULLUP, IOCON_FUNC3);
	}
	Chip_IOCON_PinMux(LPC_IOCON, 0, 17, IOCON_MODE_INACT, IOCON_FUNC3);
	Chip_IOCON_PinMux(LPC_IOCON, 0, 18, IOCON_MODE_INACT, IOCON_FUNC3);
}

/* Assert SSEL pin */
void Board_SPI_AssertSSEL(void)
{
	Chip_GPIO_WritePortBit(LPC_GPIO, 0, 16, false);
}

/* De-Assert SSEL pin */
void Board_SPI_DeassertSSEL(void)
{
	Chip_GPIO_WritePortBit(LPC_GPIO, 0, 16, true);
}

void Board_Audio_Init(LPC_I2S_T *pI2S, int micIn)
{
	I2S_AUDIO_FORMAT_T I2S_Config;

	/* Chip_Clock_EnablePeripheralClock(SYSCTL_CLOCK_I2S); */

	I2S_Config.SampleRate = 48000;
	I2S_Config.ChannelNumber = 2;	/* 1 is mono, 2 is stereo */
	I2S_Config.WordWidth =  16;		/* 8, 16 or 32 bits */
	Chip_I2S_Init(pI2S);
	Chip_I2S_TxConfig(pI2S, &I2S_Config);
}

/* Sets up board specific I2C interface */
void Board_I2C_Init(I2C_ID_T id)
{
	switch (id)
	{
		case I2C0:
			Chip_IOCON_PinMux(LPC_IOCON, 0, 27, IOCON_MODE_INACT, IOCON_FUNC1);
			Chip_IOCON_PinMux(LPC_IOCON, 0, 28, IOCON_MODE_INACT, IOCON_FUNC1);
			Chip_IOCON_SetI2CPad(LPC_IOCON, I2CPADCFG_STD_MODE);
		break;

		case I2C1:
			Chip_IOCON_PinMux(LPC_IOCON, 0, 19, IOCON_MODE_INACT, IOCON_FUNC2);
			Chip_IOCON_PinMux(LPC_IOCON, 0, 20, IOCON_MODE_INACT, IOCON_FUNC2);
			Chip_IOCON_EnableOD(LPC_IOCON, 0, 19);
			Chip_IOCON_EnableOD(LPC_IOCON, 0, 20);
		break;

		case I2C2:
			Chip_IOCON_PinMux(LPC_IOCON, 0, 10, IOCON_MODE_INACT, IOCON_FUNC2);
			Chip_IOCON_PinMux(LPC_IOCON, 0, 11, IOCON_MODE_INACT, IOCON_FUNC2);
			Chip_IOCON_EnableOD(LPC_IOCON, 0, 10);
			Chip_IOCON_EnableOD(LPC_IOCON, 0, 11);
		break;
	}
}



#if 0
/* Initialize Joystick */
void Board_Joystick_Init(void)
{
	int ix;

	/* IOCON states already selected in SystemInit(), GPIO setup only. Pullups
	   are external, so IOCON with no states */
	for (ix = 0; ix < NUM_BUTTONS; ix++) {
		Chip_GPIO_SetPinDIRInput(LPC_GPIO, portButton[ix], pinButton[ix]);
	}
}

/* Get Joystick status */
uint8_t Joystick_GetStatus(void)
{
	uint8_t ix, ret = 0;

	for (ix = 0; ix < NUM_BUTTONS; ix++) {
		if ((Chip_GPIO_GetPinState(LPC_GPIO, portButton[ix], pinButton[ix])) == false) {
			ret |= stateButton[ix];
		}
	}

	return ret;
}
#endif

void Serial_CreateStream(void *Stream)
{}

void Board_USBD_Init(uint32_t port)
{
	/* VBUS is not connected on the NXP LPCXpresso LPC1769, so leave the pin at default setting. */
	/*Chip_IOCON_PinMux(LPC_IOCON, 1, 30, IOCON_MODE_INACT, IOCON_FUNC2);*/ /* USB VBUS */
	
	Chip_IOCON_PinMux(LPC_IOCON, 0, 29, IOCON_MODE_INACT, IOCON_FUNC1);	/* P0.29 D1+, P0.30 D1- */
	Chip_IOCON_PinMux(LPC_IOCON, 0, 30, IOCON_MODE_INACT, IOCON_FUNC1);

	LPC_USB->USBClkCtrl = 0x12;                /* Dev, AHB clock enable */
	while ((LPC_USB->USBClkSt & 0x12) != 0x12); 
}

