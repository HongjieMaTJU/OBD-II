/**@brief C_CAN driver
 * c_can0_15xx.h
 *
 *
 *
 *
 *
 *
 *
 *  Created on: 2016年12月15日
 *      Author: Topon.Edison
 *
 *
 *
 *
 *
 *
 *
 */



/*@brief introduction to the c_can funtion of the LPC15xx
 *
 * Controller Area Network (CAN) is the definition of a high performance communication
protocol for serial data communication. The C_CAN controller is designed to provide a full
implementation of the CAN protocol according to the CAN Specification Version 2.0B. The
C_CAN controller allows to build powerful local networks with low-cost multiplex wiring by
supporting distributed real-time control with a very high level of security.
The CAN controller consists of a CAN core, message RAM, a message handler, control
registers, and the APB interface.
 *
 * For communication on a CAN network, individual Message Objects are configured. The
Message Objects and Identifier Masks for acceptance filtering of received messages are
stored in the Message RAM.
 *
 * All functions concerning the handling of messages are implemented in the Message
Handler. Those functions are the acceptance filtering, the transfer of messages between
the CAN Core and the Message RAM, and the handling of transmission requests as well
as the generation of the module interrupt.
The register set of the CAN controller can be accessed directly by an external CPU via the
APB bus. These registers are used to control/configure the CAN Core and the Message
Handler and to access the Message RAM.
 *
 */

#ifndef CHIP_15XX_INC_C_CAN_15XX_H_
#define CHIP_15XX_INC_C_CAN_15XX_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @groupdef of LPC15xx C_CAN Driver(C_CAN0)
 * ingroup CHIP_15XX_Drivers
 */


/**
 *  @brief LPC15XX Controller Area NetWork C_CAN0  block structure
 */

typedef struct                         /*!< CCAN Structure */
{
	__IO uint32_t CNTL;                /*!< CAN control */
	__IO uint32_t STAT;                /*!< status register */
    __I  uint32_t EC;                  /*!< error counter */
    __IO uint32_t BT;                  /*!< bit timing register */
    __I  uint32_t INT;                 /*!< interrupt register */
    __IO uint32_t TEST;                /*!< Test register */
    __IO uint32_t BRPE;                /*!< Baud rate prescaler extension register */
    __I uint32_t RESERVED0;            /*!< Reserved */

    __IO uint32_t IF1_CMDREQ;          /*!< Message interface 1 command request register  for transmit
                                            Message */

    union {                            /*!<to define the bits or bit need be ignored in Message Object or Interface Register */
    	__IO uint32_t IF1_CMDMSK_W;    /*!< Message interface 1 command mask(write direction) */
    	__IO uint32_t IF1_CMDMSK_R;     /*!< Message interface 1 command mask(read direction) */
    };

    __IO uint32_t IF1_MSK1;            /*!< Message interface 1 mask 1 to mask the arbitration bit*/
    __IO uint32_t IF1_MSK2;            /*!< Message interface 1 mask 2 to mask the arbitration bit*/
    __IO uint32_t IF1_ARB1;            /*!< Message interface 1 arbitration 1 */
    __IO uint32_t IF1_ARB2;            /*!< Message interface 1 arbitration 2 */
    __IO uint32_t IF1_MCTRL;           /*!< Message interface 1 message control */
    __IO uint32_t IF1_DA1;             /*!< Message interface 1 data A1 */
    __IO uint32_t IF1_DA2;             /*!< Message interface 1 data A2 */
    __IO uint32_t IF1_DB1;             /*!< Message interface 1 data B1 */
    __IO uint32_t IF1_DB2;             /*!< Message interface 1 data B2 */
    __I uint32_t RESERVED1[13];        /*!< Reserved */

    __IO uint32_t IF2_CMDREQ;          /*!< Message interface 2 command request register  for */

    union
	{
    	__IO uint32_t IF2_CMDMSK_W;    /*!< Message interface 2 command mask(write direction) */
    	__IO uint32_t IF2_CMDMSK_R;    /*!< Message interface 2 command mask(read direction) */
	};


    __IO uint32_t IF2_MSK1;            /*!< Message interface 2 mask 1 */
    __IO uint32_t IF2_MSK2;            /*!< Message interface 2 mask 2 */
    __IO uint32_t IF2_ARB1;            /*!< Message interface 2 arbitration 1 */
    __IO uint32_t IF2_ARB2;            /*!< Message interface 2 arbitration 2 */
    __IO uint32_t IF2_MCTRL;           /*!< Message interface 2 message control */
    __IO uint32_t IF2_DA1;             /*!< Message interface 2 data A1 */
    __IO uint32_t IF2_DA2;             /*!< Message interface 2 data A2 */
    __IO uint32_t IF2_DB1;             /*!< Message interface 2 data B1 */
    __IO uint32_t IF2_DB2;             /*!< Message interface 2 data B2 */
    __I uint32_t RESERVED2[21];        /*!< Reserved */

    __I uint32_t TXREQ1;               /*!< Transmission request 1 */
    __I uint32_t TXREQ2;               /*!< Transmission request 2 */
    __I uint32_t RESERVED3[6];         /*!< Reserved */
    __I uint32_t ND1;                  /*!< New data 1 */
    __I uint32_t ND2;                  /*!< New data 2 */
    __I uint32_t RESERVED4[6];         /*!< Reserved */
    __I uint32_t IR1;                  /*!< Interrupt pending 1 */
    __I uint32_t IR2;                  /*!< Interrupt pending 2 */
    __I uint32_t RESERVED5[6];         /*!< Reserved */
    __I uint32_t MSGV1;                /*!< Message valid 1 */
    __I uint32_t MSGV2;                /*!< Message valid 2 */
    __I uint32_t RESERVED6[6];         /*!< Reserved */
    __IO uint32_t CLKDIV;              /*!< CAN clock divider register */


}LPC_C_CAN_T;


/**
 * @brief C_CAN control register definitions
 */
#define CANCTL_INIT_NORMAL               (0x00 << 0)          /*!< Normal operation */
#define CANCTL_INIT_STARTED              (0x01 << 0)          /*!< Started initialization */
#define CANCTL_IE_DISABLE                (0x00 << 1)          /*!< Disable CAN interrupts */
#define CANCTL_IE_ENABLE                 (0x01 << 1)          /*!< Enable CAN interrupts */
#define CANCTL_SIE_DISABLE               (0x00 << 2)          /*!< Disable status change interrupts */
#define CANCTL_SIE_ENABLE                (0x01 << 2)          /*!< Enable status change interrupts */
#define CANCTL_EIE_DISABLE               (0x00 << 3)          /*!< Disable error interrupt */
#define CANCTL_EIE_ENABLE                (0x01 << 3)          /*!< Enable error interrupt */
#define CANCTL_DAR_DISABLE               (0x01 << 5)          /*!< Disable automatic retransmission */
#define CANCTL_DAR_ENABLE                (0x00 << 5)          /*!< Enable automatic retransmission */
#define CANCTL_CCE_NO_WRITE_ACCESS       (0x00 << 6)          /*!< No write access,the cpu has no write access
                                                                   to the bit timing register */
#define CANCTL_CCE_WRITE_ACCESS          (0x01 << 6)          /*!< Write access,the cpu has write access to the
                                                                   CANBT register while the INIT bit is one */
#define CANCTL_TEST_NORMAL               (0x00 << 7)          /*!< No test mode */
#define CANCTL_TEST_MODE                 (0x01 << 7)          /*!< Test mode */



/**
 *
 * @brief CAN status register definitions
 *
 */
#define  CAN_STAT_LEC_MASK                (0x00000007)        /*!< For the use of reading the last error code */
#define CAN_STAT_LEC_NO_ERROR             (0x00 << 0)         /*!< No error occur */
#define CAN_STAT_LEC_STUFF_ERROR          (0x01 << 0)         /*!< Stuff error */
#define CAN_STAT_LEC_FORM_ERROR           (0x01 << 1)         /*!< Form error */
#define CAN_STAT_LEC_ACK_ERROR            (0x03 << 0)         /*!< Ack error */
#define CAN_STAT_LEC_BIT1_ERROR           (0x01 << 2)         /*!< Bit1 error, sending 1 (recessive bit) but monitored  0(dominant bit) */
#define CAN_STAT_LEC_BIT0_ERROR           (0x05 << 0)         /*!< Bit0 error, sending 0 (recessive bit) but monitored  0(dominant bit) */
#define CAN_STAT_LEC_CRC_ERROR            (0x06 << 0)         /*!< CRC error */
#define CAN_STAT_LEC_UNUSED_ERROR         (0x07 << 0)         /*!< No CAN bus event was detected */
#define CAN_STAT_TXOK_NO                  (0x00 << 3)         /*!< No transmit */
#define CAN_STAT_TXOK_SUCCESS             (0x01 << 3)         /*!< Successful transmit data */
#define CAN_STAT_RXOK_NO                  (0x00 << 4)         /*!< No receive */
#define CAN_STAT_RXOK_SUCCESS             (0x01 << 4)         /*!< Successful receive data */
#define CAN_STAT_EPASS_ACTIVE             (0x00 << 5)         /*!< Error active ,the CAN controller is in the error
                                                                   active state */
#define CAN_STAT_EPASS_PASSIVE            (0x01 << 5)         /*!< Error passive */
#define CAN_STAT_EWARN_BLOW_LIMIT         (0x00 << 6)         /*!< Both error counters are below the error warning limit */
#define CAN_STAT_EWARN_REACHED_LIMIT      (0x01 << 6)         /*!< At limit, one of the error counter in EC reached the limit */
#define CAN_STAT_BOFF_BUS_CONNECTED       (0x00 << 7)         /*!< Bus connected */
#define CAN_STAT_BOFF_BUS_OFF             (0x01 << 7)         /*!< Bus is in busoff state */

/**
 *
 * @brief CAN error counter register definitions
 *
 */




#define CAN_EC_TEC7_0_MASK                (0x000000ff)        /*!< For EC & CAN_EC_TEC7_0_MASK = the num of the transmit errors */
#define CAN_EC_REC6_0_MASK                (0x00007f00)        /*!< For EC & CAN_EC_REC7_0_MASK = the num of the receive errors */
#define CAN_EC_RP_MASK                    (0x00008000)        /*!< The RP mask */


/**
 *
 *@brief CAN Interrupt register definitions
 *
 */
#define CAN_INTERRUPT_SOURCE_MASK         (0x0000ffff)        /*!< For the use of reading the INTID */
#define CAN_STATUS_INTERRUPT              (0x00008000)        /*!< The interrupt source is status change in the status register */


/**
 *
 * @brief CAN message interface command request register
 *
 */
#define IFx_CMDREQ_MN_MASK                (0x0000003f)        /*!< For the use of r/w MN in register */
#define IFx_CMDREQ_BUSY_MASK              (0x00008000)        /*!< For the use of reading the BUSY */


/*
 *
 * @brief CAN message interface command mask register
 *
 */
#define IFx_CMDMSK_DATA_B_TRANSFER        (0x01 << 0)         /*!< Transfer data bytes 4-7 between message object and interface register*/
#define IFx_CMDMSK_DATA_A_TRANSFER        (0x01 << 1)         /*!< Transfer data bytes 0-3 between message object and interface register*/
#define IFx_CMDMSK_TXRQST_TRAN_REQ        (0x01 << 2)         /*!< Request a transmission */
#define IFx_CMDMSK_CTRL_TRANSFER          (0x01 << 4)         /*!< Transfer control bits between message object and interface register */
#define IFx_CMDMSK_ARB_TRANSFER           (0x01 << 5)         /*!< Transfer arbitration bits identifier,DIR,XTD,MSGVAL between the message object buffer and interface register */
#define IFx_CMDMSK_MASK_TRANSFER          (0x01 << 6)         /*!< Transfer identifier MSK + MDIR + MXTD between message object and interface register */
#define IFx_CMDMSK_WR_RD_WRITE            (0x01 << 7)         /*!< Transfer to message object */

/**
 *
 * @brief CAN interface mask register
 *
 */


/**
 *  @brief   Initialize the CAN
 *  @param   Pointer to the selected peripheral
 *  @return  Nothing
 */
void Chip_CAN_Init(LPC_C_CAN_T * pCAN);


/**
 * @brief   Configure the CAN clock
 * @param
 * @return
 */

#ifdef __cplusplus
}
#endif

#endif /* CHIP_15XX_INC_C_CAN_15XX_H_ */
