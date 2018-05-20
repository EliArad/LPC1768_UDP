/*
 * @brief LPC17xx/40xx I2C driver
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2014
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

#ifndef __I2C_17XX_40XX_H_
#define __I2C_17XX_40XX_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup I2C_17XX_40XX CHIP: LPC17xx/40xx I2C driver
 * @ingroup CHIP_17XX_40XX_Drivers
 * @{
 */

/**
 * @brief I2C register block structure
 */
typedef struct {				/* I2C0 Structure         */
	__IO uint32_t CONSET;		/*!< I2C Control Set Register. When a one is written to a bit of this register, the corresponding bit in the I2C control register is set. Writing a zero has no effect on the corresponding bit in the I2C control register. */
	__I  uint32_t STAT;			/*!< I2C Status Register. During I2C operation, this register provides detailed status codes that allow software to determine the next action needed. */
	__IO uint32_t DAT;			/*!< I2C Data Register. During master or slave transmit mode, data to be transmitted is written to this register. During master or slave receive mode, data that has been received may be read from this register. */
	__IO uint32_t ADR0;			/*!< I2C Slave Address Register 0. Contains the 7-bit slave address for operation of the I2C interface in slave mode, and is not used in master mode. The least significant bit determines whether a slave responds to the General Call address. */
	__IO uint32_t SCLH;			/*!< SCH Duty Cycle Register High Half Word. Determines the high time of the I2C clock. */
	__IO uint32_t SCLL;			/*!< SCL Duty Cycle Register Low Half Word. Determines the low time of the I2C clock. SCLL and SCLH together determine the clock frequency generated by an I2C master and certain times used in slave mode. */
	__O  uint32_t CONCLR;		/*!< I2C Control Clear Register. When a one is written to a bit of this register, the corresponding bit in the I2C control register is cleared. Writing a zero has no effect on the corresponding bit in the I2C control register. */
	__IO uint32_t MMCTRL;		/*!< Monitor mode control register. */
	__IO uint32_t ADR1;			/*!< I2C Slave Address Register. Contains the 7-bit slave address for operation of the I2C interface in slave mode, and is not used in master mode. The least significant bit determines whether a slave responds to the General Call address. */
	__IO uint32_t ADR2;			/*!< I2C Slave Address Register. Contains the 7-bit slave address for operation of the I2C interface in slave mode, and is not used in master mode. The least significant bit determines whether a slave responds to the General Call address. */
	__IO uint32_t ADR3;			/*!< I2C Slave Address Register. Contains the 7-bit slave address for operation of the I2C interface in slave mode, and is not used in master mode. The least significant bit determines whether a slave responds to the General Call address. */
	__I  uint32_t DATA_BUFFER;	/*!< Data buffer register. The contents of the 8 MSBs of the DAT shift register will be transferred to the DATA_BUFFER automatically after every nine bits (8 bits of data plus ACK or NACK) has been received on the bus. */
	__IO uint32_t MASK[4];		/*!< I2C Slave address mask register */
} LPC_I2C_T;

/**
 * @brief	Return values for SLAVE handler
 * @note
 * Chip drivers will usally be designed to match their events with this value
 */
#define RET_SLAVE_TX    6	/**< Return value, when 1 byte TX'd successfully */
#define RET_SLAVE_RX    5	/**< Return value, when 1 byte RX'd successfully */
#define RET_SLAVE_IDLE  2	/**< Return value, when slave enter idle mode */
#define RET_SLAVE_BUSY  0	/**< Return value, when slave is busy */

/**
 * @brief I2C state handle return values
 */
#define I2C_STA_STO_RECV            0x20

/*
 * @brief I2C Control Set register description
 */
#define I2C_I2CONSET_AA             ((0x04))/*!< Assert acknowledge flag */
#define I2C_I2CONSET_SI             ((0x08))/*!< I2C interrupt flag */
#define I2C_I2CONSET_STO            ((0x10))/*!< STOP flag */
#define I2C_I2CONSET_STA            ((0x20))/*!< START flag */
#define I2C_I2CONSET_I2EN           ((0x40))/*!< I2C interface enable */

/*
 * @brief I2C Control Clear register description
 */
#define I2C_I2CONCLR_AAC            ((1 << 2))	/*!< Assert acknowledge Clear bit */
#define I2C_I2CONCLR_SIC            ((1 << 3))	/*!< I2C interrupt Clear bit */
#define I2C_I2CONCLR_STOC           ((1 << 4))	/*!< I2C STOP Clear bit */
#define I2C_I2CONCLR_STAC           ((1 << 5))	/*!< START flag Clear bit */
#define I2C_I2CONCLR_I2ENC          ((1 << 6))	/*!< I2C interface Disable bit */

/*
 * @brief	I2C Common Control register description
 */
#define I2C_CON_AA            (1UL << 2)	/*!< Assert acknowledge bit */
#define I2C_CON_SI            (1UL << 3)	/*!< I2C interrupt bit */
#define I2C_CON_STO           (1UL << 4)	/*!< I2C STOP bit */
#define I2C_CON_STA           (1UL << 5)	/*!< START flag bit */
#define I2C_CON_I2EN          (1UL << 6)	/*!< I2C interface bit */

/*
 * @brief I2C Status Code definition (I2C Status register)
 */
#define I2C_STAT_CODE_BITMASK       ((0xF8))/*!< Return Code mask in I2C status register */
#define I2C_STAT_CODE_ERROR         ((0xFF))/*!< Return Code error mask in I2C status register */

/*
 * @brief I2C return status code definitions
 */
#define I2C_I2STAT_NO_INF                       ((0xF8))/*!< No relevant information */
#define I2C_I2STAT_BUS_ERROR                    ((0x00))/*!< Bus Error */

/*
 * @brief I2C Master transmit mode
 */
#define I2C_I2STAT_M_TX_START                   ((0x08))/*!< A start condition has been transmitted */
#define I2C_I2STAT_M_TX_RESTART                 ((0x10))/*!< A repeat start condition has been transmitted */
#define I2C_I2STAT_M_TX_SLAW_ACK                ((0x18))/*!< SLA+W has been transmitted, ACK has been received */
#define I2C_I2STAT_M_TX_SLAW_NACK               ((0x20))/*!< SLA+W has been transmitted, NACK has been received */
#define I2C_I2STAT_M_TX_DAT_ACK                 ((0x28))/*!< Data has been transmitted, ACK has been received */
#define I2C_I2STAT_M_TX_DAT_NACK                ((0x30))/*!< Data has been transmitted, NACK has been received */
#define I2C_I2STAT_M_TX_ARB_LOST                ((0x38))/*!< Arbitration lost in SLA+R/W or Data bytes */

/*
 * @brief I2C Master receive mode
 */
#define I2C_I2STAT_M_RX_START                   ((0x08))/*!< A start condition has been transmitted */
#define I2C_I2STAT_M_RX_RESTART                 ((0x10))/*!< A repeat start condition has been transmitted */
#define I2C_I2STAT_M_RX_ARB_LOST                ((0x38))/*!< Arbitration lost */
#define I2C_I2STAT_M_RX_SLAR_ACK                ((0x40))/*!< SLA+R has been transmitted, ACK has been received */
#define I2C_I2STAT_M_RX_SLAR_NACK               ((0x48))/*!< SLA+R has been transmitted, NACK has been received */
#define I2C_I2STAT_M_RX_DAT_ACK                 ((0x50))/*!< Data has been received, ACK has been returned */
#define I2C_I2STAT_M_RX_DAT_NACK                ((0x58))/*!< Data has been received, NACK has been returned */

/*
 * @brief I2C Slave receive mode
 */
#define I2C_I2STAT_S_RX_SLAW_ACK                ((0x60))/*!< Own slave address has been received, ACK has been returned */
#define I2C_I2STAT_S_RX_ARB_LOST_M_SLA          ((0x68))/*!< Arbitration lost in SLA+R/W as master */
// #define I2C_I2STAT_S_RX_SLAW_ACK				((0x68)) /*!< Own SLA+W has been received, ACK returned */
#define I2C_I2STAT_S_RX_GENCALL_ACK             ((0x70))/*!< General call address has been received, ACK has been returned */
#define I2C_I2STAT_S_RX_ARB_LOST_M_GENCALL      ((0x78))/*!< Arbitration lost in SLA+R/W (GENERAL CALL) as master */
// #define I2C_I2STAT_S_RX_GENCALL_ACK				((0x78)) /*!< General call address has been received, ACK has been returned */
#define I2C_I2STAT_S_RX_PRE_SLA_DAT_ACK         ((0x80))/*!< Previously addressed with own SLA; Data has been received, ACK has been returned */
#define I2C_I2STAT_S_RX_PRE_SLA_DAT_NACK        ((0x88))/*!< Previously addressed with own SLA;Data has been received and NOT ACK has been returned */
#define I2C_I2STAT_S_RX_PRE_GENCALL_DAT_ACK     ((0x90))/*!< Previously addressed with General Call; Data has been received and ACK has been returned */
#define I2C_I2STAT_S_RX_PRE_GENCALL_DAT_NACK    ((0x98))/*!< Previously addressed with General Call; Data has been received and NOT ACK has been returned */
#define I2C_I2STAT_S_RX_STA_STO_SLVREC_SLVTRX   ((0xA0))/*!< A STOP condition or repeated START condition has been received while still addressed as SLV/REC (Slave Receive) or
														   SLV/TRX (Slave Transmit) */

/*
 * @brief I2C Slave transmit mode
 */
#define I2C_I2STAT_S_TX_SLAR_ACK                ((0xA8))/*!< Own SLA+R has been received, ACK has been returned */
#define I2C_I2STAT_S_TX_ARB_LOST_M_SLA          ((0xB0))/*!< Arbitration lost in SLA+R/W as master */
// #define I2C_I2STAT_S_TX_SLAR_ACK				((0xB0)) /*!< Own SLA+R has been received, ACK has been returned */
#define I2C_I2STAT_S_TX_DAT_ACK                 ((0xB8))/*!< Data has been transmitted, ACK has been received */
#define I2C_I2STAT_S_TX_DAT_NACK                ((0xC0))/*!< Data has been transmitted, NACK has been received */
#define I2C_I2STAT_S_TX_LAST_DAT_ACK            ((0xC8))/*!< Last data byte in I2DAT has been transmitted (AA = 0); ACK has been received */
#define I2C_SLAVE_TIME_OUT                      0x10000000UL/*!< Time out in case of using I2C slave mode */

/*
 * @brief I2C Data register definition
 */
#define I2C_I2DAT_BITMASK           ((0xFF))/*!< Mask for I2DAT register */
#define I2C_I2DAT_IDLE_CHAR         (0xFF)	/*!< Idle data value will be send out in slave mode in case of the actual expecting data requested from the master is greater than
											     its sending data length that can be supported */

/*
 * @brief I2C Monitor mode control register description
 */
#define I2C_I2MMCTRL_MM_ENA         ((1 << 0))			/**< Monitor mode enable */
#define I2C_I2MMCTRL_ENA_SCL        ((1 << 1))			/**< SCL output enable */
#define I2C_I2MMCTRL_MATCH_ALL      ((1 << 2))			/**< Select interrupt register match */
#define I2C_I2MMCTRL_BITMASK        ((0x07))		/**< Mask for I2MMCTRL register */

/*
 * @brief I2C Data buffer register description
 */
#define I2DATA_BUFFER_BITMASK       ((0xFF))/*!< I2C Data buffer register bit mask */

/*
 * @brief I2C Slave Address registers definition
 */
#define I2C_I2ADR_GC                ((1 << 0))	/*!< General Call enable bit */
#define I2C_I2ADR_BITMASK           ((0xFF))/*!< I2C Slave Address registers bit mask */

/*
 * @brief I2C Mask Register definition
 */
#define I2C_I2MASK_MASK(n)          ((n & 0xFE))/*!< I2C Mask Register mask field */

/*
 * @brief I2C SCL HIGH duty cycle Register definition
 */
#define I2C_I2SCLH_BITMASK          ((0xFFFF))	/*!< I2C SCL HIGH duty cycle Register bit mask */

/*
 * @brief I2C SCL LOW duty cycle Register definition
 */
#define I2C_I2SCLL_BITMASK          ((0xFFFF))	/*!< I2C SCL LOW duty cycle Register bit mask */

/*
 * @brief I2C status values
 */
#define I2C_SETUP_STATUS_ARBF   (1 << 8)	/**< Arbitration false */
#define I2C_SETUP_STATUS_NOACKF (1 << 9)	/**< No ACK returned */
#define I2C_SETUP_STATUS_DONE   (1 << 10)	/**< Status DONE */

/*
 * @brief I2C state handle return values
 */
#define I2C_OK                      0x00
#define I2C_BYTE_SENT               0x01
#define I2C_BYTE_RECV               0x02
#define I2C_LAST_BYTE_RECV          0x04
#define I2C_SEND_END                0x08
#define I2C_RECV_END                0x10
#define I2C_STA_STO_RECV            0x20

#define I2C_ERR                     (0x10000000)
#define I2C_NAK_RECV                (0x10000000 | 0x01)

#define I2C_CheckError(ErrorCode)   (ErrorCode & 0x10000000)

/*
 * @brief I2C monitor control configuration defines
 */
#define I2C_MONITOR_CFG_SCL_OUTPUT  I2C_I2MMCTRL_ENA_SCL		/**< SCL output enable */
#define I2C_MONITOR_CFG_MATCHALL    I2C_I2MMCTRL_MATCH_ALL		/**< Select interrupt register match */

/**
 * @brief	I2C Slave Identifiers
 */
typedef enum {
	I2C_SLAVE_GENERAL,	/**< Slave ID for general calls */
	I2C_SLAVE_0,		/**< Slave ID fo Slave Address 0 */
	I2C_SLAVE_1,		/**< Slave ID fo Slave Address 1 */
	I2C_SLAVE_2,		/**< Slave ID fo Slave Address 2 */
	I2C_SLAVE_3,		/**< Slave ID fo Slave Address 3 */
	I2C_SLAVE_NUM_INTERFACE	/**< Number of slave interfaces */
} I2C_SLAVE_ID;

/**
 * @brief	I2C transfer status
 */
typedef enum {
	I2C_STATUS_DONE,	/**< Transfer done successfully */
	I2C_STATUS_NAK,		/**< NAK received during transfer */
	I2C_STATUS_ARBLOST,	/**< Aribitration lost during transfer */
	I2C_STATUS_BUSERR,	/**< Bus error in I2C transfer */
	I2C_STATUS_BUSY,	/**< I2C is busy doing transfer */
} I2C_STATUS_T;

/**
 * @brief Master transfer data structure definitions
 */
typedef struct {
	uint8_t slaveAddr;		/**< 7-bit I2C Slave address */
	const uint8_t *txBuff;	/**< Pointer to array of bytes to be transmitted */
	int     txSz;			/**< Number of bytes in transmit array,
							   if 0 only receive transfer will be carried on */
	uint8_t *rxBuff;		/**< Pointer memory where bytes received from I2C be stored */
	int     rxSz;			/**< Number of bytes to received,
							   if 0 only transmission we be carried on */
	I2C_STATUS_T status;	/**< Status of the current I2C transfer */
} I2C_XFER_T;

/**
 * @brief	I2C interface IDs
 * @note
 * All Chip functions will take this as the first parameter,
 * I2C_NUM_INTERFACE must never be used for calling any Chip
 * functions, it is only used to find the number of interfaces
 * available in the Chip.
 */
typedef enum I2C_ID {
	I2C0,				/**< ID I2C0 */
	I2C1,				/**< ID I2C1 */
	I2C2,				/**< ID I2C2 */
	I2C_NUM_INTERFACE	/**< Number of I2C interfaces in the chip */
} I2C_ID_T;

/**
 * @brief	I2C master events
 */
typedef enum {
	I2C_EVENT_WAIT = 1,	/**< I2C Wait event */
	I2C_EVENT_DONE,		/**< Done event that wakes up Wait event */
	I2C_EVENT_LOCK,		/**< Re-entrency lock event for I2C transfer */
	I2C_EVENT_UNLOCK,	/**< Re-entrency unlock event for I2C transfer */
	I2C_EVENT_SLAVE_RX,	/**< Slave receive event */
	I2C_EVENT_SLAVE_TX,	/**< Slave transmit event */
} I2C_EVENT_T;

/**
 * @brief	Event handler function type
 */
typedef void (*I2C_EVENTHANDLER_T)(I2C_ID_T, I2C_EVENT_T);

/**
 * @brief	Initializes the LPC_I2C peripheral with specified parameter.
 * @param	id			: I2C peripheral ID (I2C0, I2C1 ... etc)
 * @return	Nothing
 */
void Chip_I2C_Init(I2C_ID_T id);

/**
 * @brief	De-initializes the I2C peripheral registers to their default reset values
 * @param	id			: I2C peripheral ID (I2C0, I2C1 ... etc)
 * @return	Nothing
 */
void Chip_I2C_DeInit(I2C_ID_T id);

/**
 * @brief	Set up clock rate for LPC_I2C peripheral.
 * @param	id			: I2C peripheral ID (I2C0, I2C1 ... etc)
 * @param	clockrate	: Target clock rate value to initialized I2C peripheral (Hz)
 * @return	Nothing
 * @note
 * Parameter @a clockrate for I2C0 should be from 1000 up to 1000000
 * (1 KHz to 1 MHz), as I2C0 support Fast Mode Plus. If the @a clockrate
 * is more than 400 KHz (Fast Plus Mode) Board_I2C_EnableFastPlus()
 * must be called prior to calling this function.
 */
void Chip_I2C_SetClockRate(I2C_ID_T id, uint32_t clockrate);

/**
 * @brief	Get current clock rate for LPC_I2C peripheral.
 * @param	id			: I2C peripheral ID (I2C0, I2C1 ... etc)
 * @return	The current I2C peripheral clock rate
 */
uint32_t Chip_I2C_GetClockRate(I2C_ID_T id);

/**
 * @brief	Transmit and Receive data in master mode
 * @param	id		: I2C peripheral selected (I2C0, I2C1 etc)
 * @param	xfer	: Pointer to a I2C_XFER_T structure see notes below
 * @return
 * Any of #I2C_STATUS_T values, xfer->txSz will have number of bytes
 * not sent due to error, xfer->rxSz will have the number of bytes yet
 * to be received.
 * @note
 * The parameter @a xfer should have its member @a slaveAddr initialized
 * to the 7-Bit slave address to which the master will do the xfer, Bit0
 * to bit6 should have the address and Bit8 is ignored. During the transfer
 * no code (like event handler) must change the content of the memory
 * pointed to by @a xfer. The member of @a xfer, @a txBuff and @a txSz be
 * initialized to the memory from which the I2C must pick the data to be
 * transfered to slave and the number of bytes to send respectively, similarly
 * @a rxBuff and @a rxSz must have pointer to memroy where data received
 * from slave be stored and the number of data to get from slave respectilvely.
 */
I2C_STATUS_T Chip_I2C_MasterTransfer(I2C_ID_T id, I2C_XFER_T *xfer);

/**
 * @brief	Transmit data to I2C slave using I2C Master mode
 * @param	id			: I2C peripheral ID (I2C0, I2C1 .. etc)
 * @param	slaveAddr	: Slave address to which the data be written
 * @param	buff		: Pointer to buffer having the array of data
 * @param	len			: Number of bytes to be transfered from @a buff
 * @return	Number of bytes successfully transfered
 */
I2C_STATUS_T Chip_I2C_MasterSend(I2C_ID_T id, uint8_t slaveAddr, const uint8_t *buff, uint8_t len);

/**
 * @brief	Transfer a command to slave and receive data from slave after a repeated start
 * @param	id			: I2C peripheral ID (I2C0, I2C1 ... etc)
 * @param	slaveAddr	: Slave address of the I2C device
 * @param	cmd			: Command (Address/Register) to be written
 * @param	buff		: Pointer to memory that will hold the data received
 * @param	len			: Number of bytes to receive
 * @return	Number of bytes successfully received
 */
int Chip_I2C_MasterCmdRead(I2C_ID_T id, uint8_t slaveAddr, uint8_t cmd, uint8_t *buff, int len);

/**
 * @brief	Get pointer to current function handling the events
 * @param	id			: I2C peripheral ID (I2C0, I2C1 ... etc)
 * @return	Pointer to function handing events of I2C
 */
I2C_EVENTHANDLER_T Chip_I2C_GetMasterEventHandler(I2C_ID_T id);

/**
 * @brief	Set function that must handle I2C events
 * @param	id			: I2C peripheral ID (I2C0, I2C1 ... etc)
 * @param	event		: Pointer to function that will handle the event (Should not be NULL)
 * @return	1 when successful, 0 when a transfer is on going with its own event handler
 */
int Chip_I2C_SetMasterEventHandler(I2C_ID_T id, I2C_EVENTHANDLER_T event);

/**
 * @brief	Set function that must handle I2C events
 * @param	id			: I2C peripheral ID (I2C0, I2C1 ... etc)
 * @param	slaveAddr	: Slave address from which data be read
 * @param	buff		: Pointer to memory where data read be stored
 * @param	len			: Number of bytes to read from slave
 * @return	Number of bytes read successfully
 */
int Chip_I2C_MasterRead(I2C_ID_T id, uint8_t slaveAddr, uint8_t *buff, int len);

/**
 * @brief	Default event handler for polling operation
 * @param	id		: I2C peripheral ID (I2C0, I2C1 ... etc)
 * @param	event	: Event ID of the event that called the function
 * @return	Nothing
 */
void Chip_I2C_EventHandlerPolling(I2C_ID_T id, I2C_EVENT_T event);

/**
 * @brief	Default event handler for interrupt base operation
 * @param	id		: I2C peripheral ID (I2C0, I2C1 ... etc)
 * @param	event	: Event ID of the event that called the function
 * @return	Nothing
 */
void Chip_I2C_EventHandler(I2C_ID_T id, I2C_EVENT_T event);

/**
 * @brief	I2C Master transfer state change handler
 * @param	id		: I2C peripheral ID (I2C0, I2C1 ... etc)
 * @return	Nothing
 * @note	Usually called from the appropriate Interrupt handler
 */
void Chip_I2C_MasterStateHandler(I2C_ID_T id);

/**
 * @brief	Disable I2C peripheral's operation
 * @param	id			: I2C peripheral ID (I2C0, I2C1 ... etc)
 * @return	Nothing
 */
void Chip_I2C_Disable(I2C_ID_T id);

/**
 * @brief	Checks if master xfer in progress
 * @param	id		: I2C peripheral ID (I2C0, I2C1 ... etc)
 * @return	1 if master xfer in progress 0 otherwise
 * @note
 * This API is generally used in interrupt handler
 * of the application to decide whether to call
 * master state handler or to call slave state handler
 */
int Chip_I2C_IsMasterActive(I2C_ID_T id);

/**
 * @brief	Setup a slave I2C device
 * @param	id			: I2C peripheral ID (I2C0, I2C1 ... etc)
 * @param	sid			: I2C Slave peripheral ID (I2C_SLAVE_0, I2C_SLAVE_1 etc)
 * @param	xfer		: Pointer to transfer structure (see note below for more info)
 * @param	event		: Event handler for slave transfers
 * @param	addrMask	: Address mask to use along with slave address (see notes below for more info)
 * @return	Nothing
 * @note
 * Parameter @a xfer should point to a valid I2C_XFER_T structure object
 * and must have @a slaveAddr initialized with 7bit Slave address (From Bit1 to Bit7),
 * Bit0 when set enables general call handling, @a slaveAddr along with @a addrMask will
 * be used to match the slave address. @a rxBuff and @a txBuff must point to valid buffers
 * where slave can receive or send the data from, size of which will be provided by
 * @a rxSz and @a txSz respectively. Function pointed to by @a event will be called
 * for the following events #I2C_EVENT_SLAVE_RX (One byte of data received successfully
 * from the master and stored inside memory pointed by xfer->rxBuff, incremented
 * the pointer and decremented the @a xfer->rxSz), #I2C_EVENT_SLAVE_TX (One byte of
 * data from xfer->txBuff was sent to master successfully, incremented the pointer
 * and decremented xfer->txSz), #I2C_EVENT_DONE (Master is done doing its transfers
 * with the slave).<br>
 * <br>Bit-0 of the parameter @a addrMask is reserved and should always be 0. Any bit (BIT1
 * to BIT7) set in @a addrMask will make the corresponding bit in *xfer->slaveAddr* as
 * don't care. Thit is, if *xfer->slaveAddr* is (0x10 << 1) and @a addrMask is (0x03 << 1) then
 * 0x10, 0x11, 0x12, 0x13 will all be considered as valid slave addresses for the registered
 * slave. Upon receving any event *xfer->slaveAddr* (BIT1 to BIT7) will hold the actual
 * address which was received from master.<br>
 * <br><b>General Call Handling</b><br>
 * Slave can receive data from master using general call address (0x00). General call
 * handling must be setup as given below
 *      - Call Chip_I2C_SlaveSetup() with argument @a sid as I2C_SLAVE_GENERAL
 *          - xfer->slaveAddr ignored, argument @a addrMask ignored
 *          - function provided by @a event will registered to be called when slave received data using addr 0x00
 *          - xfer->rxBuff and xfer->rxSz should be valid in argument @a xfer
 *      - To handle General Call only (No other slaves are configured)
 *          - Call Chip_I2C_SlaveSetup() with sid as I2C_SLAVE_X (X=0,1,2,3)
 *          - setup @a xfer with slaveAddr member set to 0, @a event is ignored hence can be NULL
 *          - provide @a addrMask (typically 0, if not you better be knowing what you are doing)
 *      - To handler General Call when other slave is active
 *          - Call Chip_I2C_SlaveSetup() with sid as I2C_SLAVE_X (X=0,1,2,3)
 *          - setup @a xfer with slaveAddr member set to 7-Bit Slave address [from Bit1 to 7]
 *          - Set Bit0 of @a xfer->slaveAddr as 1
 *          - Provide appropriate @a addrMask
 *          - Argument @a event must point to function, that handles events from actual slaveAddress and not the GC
 * @warning
 * If the slave has only one byte in its txBuff, once that byte is transfered to master the event handler
 * will be called for event #I2C_EVENT_DONE. If the master attempts to read more bytes in the same transfer
 * then the slave hardware will send 0xFF to master till the end of transfer, event handler will not be
 * called to notify this. For more info see section below<br>
 * <br><b> Last data handling in slave </b><br>
 * If the user wants to implement a slave which will read a byte from a specific location over and over
 * again whenever master reads the slave. If the user initializes the xfer->txBuff as the location to read
 * the byte from and xfer->txSz as 1, then say, if master reads one byte; slave will send the byte read from
 * xfer->txBuff and will call the event handler with #I2C_EVENT_DONE. If the master attempts to read another
 * byte instead of sending the byte read from xfer->txBuff the slave hardware will send 0xFF and no event will
 * occur. To handle this issue, slave should set xfer->txSz to 2, in which case when master reads the byte
 * event handler will be called with #I2C_EVENT_SLAVE_TX, in which the slave implementation can reset the buffer
 * and size back to original location (i.e, xfer->txBuff--, xfer->txSz++), if the master reads another byte
 * in the same transfer, byte read from xfer->txBuff will be sent and #I2C_EVENT_SLAVE_TX will be called again, and
 * the process repeats.
 */
void Chip_I2C_SlaveSetup(I2C_ID_T id,
						 I2C_SLAVE_ID sid,
						 I2C_XFER_T *xfer,
						 I2C_EVENTHANDLER_T event,
						 uint8_t addrMask);

/**
 * @brief	I2C Slave event handler
 * @param	id		: I2C peripheral ID (I2C0, I2C1 ... etc)
 * @return	Nothing
 */
void Chip_I2C_SlaveStateHandler(I2C_ID_T id);

/**
 * @brief	I2C peripheral state change checking
 * @param	id		: I2C peripheral ID (I2C0, I2C1 ... etc)
 * @return	1 if I2C peripheral @a id has changed its state,
 *          0 if there is no state change
 * @note
 * This function must be used by the application when
 * the polling has to be done based on state change.
 */
int Chip_I2C_IsStateChanged(I2C_ID_T id);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __I2C_17XX_40XX_H_ */
