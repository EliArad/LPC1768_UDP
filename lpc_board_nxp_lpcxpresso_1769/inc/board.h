/*
 * @brief NXP LPC1769 XPresso board file
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

#ifndef __BOARD_H_
#define __BOARD_H_

#include "chip.h"
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup BOARD_NXP_LPCXPRESSO_1769 NXP LPC1769 LPCXpresso board software API functions
 * @ingroup LPCOPEN_17XX_BOARD_LPCXPRESSO_1769
 * The board support software API functions provide some simple abstracted
 * functions used across multiple LPCOpen board examples. See @ref BOARD_COMMON_API
 * for the functions defined by this board support layer.<br>
 * @{
 */

/** @defgroup BOARD_NXP_LPCXPRESSO_1769_OPTIONS BOARD: NXP LPC1769 LPCXpresso board build options
 * This board has options that configure its operation at build-time.<br>
 * @{
 */

/** Define DEBUG_ENABLE to enable IO via the DEBUGSTR, DEBUGOUT, and
    DEBUGIN macros. If not defined, DEBUG* functions will be optimized
    out of the code at build time.
 */
#define DEBUG_ENABLE

/** Define DEBUG_SEMIHOSTING along with DEBUG_ENABLE to enable IO support
    via semihosting. You may need to use a C library that supports
    semihosting with this option.
 */
// #define DEBUG_SEMIHOSTING

/** Board UART used for debug output and input using the DEBUG* macros. This
    is also the port used for Board_UARTPutChar, Board_UARTGetChar, and
    Board_UARTPutSTR functions.
 */

#define FAST_GPIO 								1

#define DEBUG_UART LPC_UART2

#define RS422_CH1 LPC_UART0
#define RS422_CH2 LPC_UART3
#define RS422_CH2_TXD2EN_PORT                   4
#define RS422_CH2_TXD2EN_BIT                    29

#define RS422_CH2_RXD2DIS_PORT                  4
#define RS422_CH2_RXD2DIS_BIT                   28

#define RES_MINUS_PORT_NUM                      1
#define RES_MINUS_BIT_NUM                       19

#define LED1_GPIO_PORT_NUM                      1
#define LED1_GPIO_BIT_NUM                       28

#define LED2_GPIO_PORT_NUM                      1
#define LED2_GPIO_BIT_NUM                       29

#define LED3_GPIO_PORT_NUM                      0
#define LED3_GPIO_BIT_NUM                       16



#define DISPLAY_DATA_PORT					    2
#define DISPLAY_DATA0_BIT						0
#define DISPLAY_DATA1_BIT						1
#define DISPLAY_DATA2_BIT						2
#define DISPLAY_DATA3_BIT						3
#define DISPLAY_DATA4_BIT						4
#define DISPLAY_DATA5_BIT						5
#define DISPLAY_DATA6_BIT						6
#define DISPLAY_DATA7_BIT						7


#define DISPLAY_RS_BIT							1
#define DISPLAY_RESET_BIT						2
#define DISPLAY_CS0_BIT							3
#define DISPLAY_CS1_BIT							4
#define DISPLAY_CS2_BIT						 	5



#define DISPLAY_COL_LE_PORT 					2
#define DISPLAY_COL_LE_BIT  					8

#define DISPLAY_SH_LD0_PORT 					2
#define DISPLAY_SH_LD0_BIT  					9

#define DISPLAY_SH_LD1_PORT 					2
#define DISPLAY_SH_LD1_BIT  					11

#define DISPLAY_SH_LD2_PORT 					2
#define DISPLAY_SH_LD2_BIT  					12


#define KEYBOARD_RESET_PORT 					2
#define KEYBOARD_RESET_BIT  					13

#define DISCRETE_IN_PORT                        1
#define DISCRETE_IN_1_BIT                       22
#define DISCRETE_IN_2_BIT                       23

#define DISCRETE_OUT_PORT                       1
#define DISCRETE_OUT_1_BIT                      24
#define DISCRETE_OUT_2_BIT                      25

#define RCU_ID_PORT                             1
#define RCU_ID_1_BIT                            26
#define RCU_ID_2_BIT                            27


#define RDU_PORT                                0
#define DISP_CLK_BIT                            15
#define DISP_CONT_1_BIT                         17
#define DISP_DATA_BIT                           18
#define COLOMN_SELECT_1_BIT                     19
#define COLOMN_SELECT_2_BIT                     20
#define COLOMN_SELECT_3_BIT                     21
#define COLOMN_SELECT_4_BIT                     22
#define COLOMN_SELECT_5_BIT                     30


#define DIM_KNOB0F_PORT 						0
#define DIM_KNOB0F_BIT  						25

#define DISPLAY_COL_VOLTAGE_PORT 				0
#define DISPLAY_COL_VOLTAGE_BIT  				26


#define MDIO_MDC_PORT 1
#define MDIO_GPIO 	17
#define MDC_GPIO  	16



/**
 * @}
 */

/* Board name */
#define BOARD_NXP_LPCXPRESSO_1769

#define USE_RMII

/**
 * LED defines
 */
#define LEDS_LED1           0x01
#define LEDS_LED2           0x02
#define LEDS_LED3           0x04
#define LEDS_LED4           0x08
#define LEDS_NO_LEDS        0x00





/**
 * Dummy audio input selection values enum
 */
#define MCB_17XX_AUDIO_MIC_SELECT       0x00
#define MCB_17XX_AUDIO_LINE_IN_SELECT   0x00

/**
 * @brief	Initialize pin muxing for a UART
 * @param	pUART	: Pointer to UART register block for UART pins to init
 * @return	Nothing
 */
void Board_UART_Init(LPC_USART_T *pUART);

/**
 * @brief	Returns the MAC address assigned to this board
 * @param	mcaddr : Pointer to 6-byte character array to populate with MAC address
 * @return	Nothing
 * @note    Returns the MAC address used by Ethernet
 */
void Board_ENET_GetMacADDR(uint8_t *mcaddr, uint8_t rcuID);

/**
 * @brief	Sets up board specific I2S interface and UDA1380 CODEC
 * @param	pI2S	: I2S peripheral to use (Must be LPC_I2S)
 * @param	micIn	: If 1 MIC will be used as input device, if 0
 *          LINE_IN will be used as input to Audio Codec.
 * @return	Nothing
 */
void Board_Audio_Init(LPC_I2S_T *pI2S, int micIn);

/**
 * @brief	Initialize pin muxing for SSP interface
 * @param	pSSP	: Pointer to SSP interface to initialize
 * @return	Nothing
 */
void Board_SSP_Init(LPC_SSP_T *pSSP);

/**
 * @brief	Initialize pin muxing for SPI interface
 * @param	isMaster	: true for master mode, false for slave mode
 * @return	Nothing
 */
void Board_SPI_Init(bool isMaster);

/**
 * @brief	Assert SSEL pin
 * @return	Nothing
 */
void Board_SPI_AssertSSEL(void);

/**
 * @brief	De-assert SSEL pin
 * @return	Nothing
 */
void Board_SPI_DeassertSSEL(void);

/**
 * @brief	Sets up board specific I2C interface
 * @param	id	: ID of I2C peripheral
 * @return	Nothing
 */
void Board_I2C_Init(I2C_ID_T id);

/**
 * @brief	Sets up I2C Fast Plus mode
 * @param	id	: Must always be I2C0
 * @return	Nothing
 * @note	This function must be called before calling
 *          Chip_I2C_SetClockRate() to set clock rates above
 *          normal range 100KHz to 400KHz. Only I2C0 supports
 *          this mode.
 */
STATIC INLINE void Board_I2C_EnableFastPlus(I2C_ID_T id)
{
	Chip_IOCON_SetI2CPad(LPC_IOCON, I2CPADCFG_FAST_MODE_PLUS);
}

/**
 * @brief	Disables I2C Fast plus mode and enable normal mode
 * @param	id	: Must always be I2C0
 * @return	Nothing
 */
STATIC INLINE void Board_I2C_DisableFastPlus(I2C_ID_T id)
{
	Chip_IOCON_SetI2CPad(LPC_IOCON, I2CPADCFG_STD_MODE);
}

/**
 * @brief	Initialize buttons on the board
 * @return	Nothing
 */
void Board_Buttons_Init(void);

/**
 * @brief	Get button status
 * @return	status of button
 */
uint32_t Buttons_GetStatus(void);

/**
 * @brief	Initialize Joystick
 * @return	Nothing
 */
void Board_Joystick_Init(void);

/**
 * @brief	Get Joystick status
 * @return	status of Joystick
 */
uint8_t Joystick_GetStatus(void);

/**
 * @brief	Create Serial Stream
 * @param	Stream	: Pointer to stream
 * @return	Nothing
 */
void Serial_CreateStream(void *Stream);

/**
 * @brief	Initializes USB device mode pins per board design
 * @param	port	: USB port to be enabled 
 * @return	Nothing
 * @note	Only one of the USB port can be enabled at a given time.
 */
//void Board_USBD_Init(uint32_t port);


void msDelay(uint32_t ms);
/**
 * @}
 */

#include "board_api.h"
#include "lpc_phy.h"

#ifdef __cplusplus
}
#endif

#endif /* __BOARD_H_ */