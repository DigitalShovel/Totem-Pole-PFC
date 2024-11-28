/**
 *******************************************************************************
 * @file    DS_UART.h
 * @brief   Toshiba Asynchronous Serial Communication Circuit
 *          TOSHIBA 'TMPM4KNA' Group
 * @version V1.0.0.0
 * $Date:: 2022-09-29 #$
 * 
 * @author Hugo Rodrigues
 *******************************************************************************
 */

#ifndef __UART_H__
#define __UART_H__
 
#include "TMPM4KyA.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define bufferSize                              700
#define jsonBufferSize                          700

/*===================================================================*
                        Masks for Registers
*===================================================================*/
/* Middle Speed Register Mask */
#define CGSYSCR_MCKSELGST_MASK                  (uint32_t)(0x03UL << 22)

/* Software Reset Register Mask */
#define SWRST_SWRST_MASK                        (uint32_t)(0x03UL) 

/* Control Register 0 Mask */
#define CR0_SM_MASK                             (uint32_t)(0x03UL) 
#define CR0_PE_MASK                             (uint32_t)(0x01UL << 2) 
#define CR0_EVEN_MASK                           (uint32_t)(0x01UL << 3) 
#define CR0_SBLEN_MASK                          (uint32_t)(0x01UL << 4)
#define CR0_DIR_MASK                            (uint32_t)(0x01UL << 5)
#define CR0_IV_MASK                             (uint32_t)(0x01UL << 6)
#define CR0_WU_MASK                             (uint32_t)(0x01UL << 8)
#define CR0_RTSE_MASK                           (uint32_t)(0x01UL << 9)
#define CR0_CTSE_MASK                           (uint32_t)(0x01UL << 10)
#define CR0_NF_MASK                             (uint32_t)(0x07UL << 12)
#define CR0_LPB_MASK                            (uint32_t)(0x01UL << 15)
#define CR0_HBSEN_MASK                          (uint32_t)(0x01UL << 16)
#define CR0_HBSMD_MASK                          (uint32_t)(0x01UL << 17)
#define CR0_HBSST_MASK                          (uint32_t)(0x01UL << 18)

/* Control Register 1 Mask */
#define CR1_DMARE_MASK                          (uint32_t)(0x01UL)
#define CR1_DMATE_MASK                          (uint32_t)(0x01UL << 1)
#define CR1_INTERR_MASK                         (uint32_t)(0x01UL << 2)
#define CR1_INTRXWE_MASK                        (uint32_t)(0x01UL << 4)
#define CR1_INTRXFE_MASK                        (uint32_t)(0x01UL << 5)
#define CR1_INTTXWE_MASK                        (uint32_t)(0x01UL << 6)
#define CR1_INTTXFE_MASK                        (uint32_t)(0x01UL << 7)
#define CR1_RIL_MASK                            (uint32_t)(0x07UL << 8)
#define CR1_TIL_MASK                            (uint32_t)(0x07UL << 12)

/* Clock Control Register Mask */
#define CLK_PRSEL_MASK                          (uint32_t)(0x0FUL << 4)

/* Baud Rate Register Mask */
#define BRD_BRN_MASK                            (uint32_t)(0xFFFFUL) 
#define BRD_BRK_MASK                            (uint32_t)(0x3FUL << 16)  
#define BRD_KEN_MASK                            (uint32_t)(0x01UL << 23)     

/* Transfer Enable Register Mask */
#define TRANS_RXE_MASK                          (uint32_t)(0x01UL)
#define TRANS_TXE_MASK                          (uint32_t)(0x01UL << 1)
#define TRANS_TXTRG_MASK                        (uint32_t)(0x01UL << 2)
#define TRANS_BK_MASK                           (uint32_t)(0x01UL << 3)

/* Data Register Mask */
#define DR_DR_MASK                              (uint32_t)(0x1FFUL)

/* Status Register Mask */
#define SR_RXFF_MASK                            (uint32_t)(0x01UL << 5)
#define SR_RXEND_MASK                           (uint32_t)(0x01UL << 6)
#define SR_TXFF_MASK                            (uint32_t)(0x01UL << 13)
#define SR_TXEND_MASK                           (uint32_t)(0x01UL << 14)

/* FIFO Clear Register Mask */
#define FIFOCLR_RFCLR_MASK                      (uint32_t)(0x01UL)
#define FIFOCLR_TFCLR_MASK                      (uint32_t)(0x01UL << 1)

/* Error Register Mask */
#define ERR_BERR_MASK                           (uint32_t)(0x01UL)
#define ERR_FERR_MASK                           (uint32_t)(0x01UL << 1)
#define ERR_PERR_MASK                           (uint32_t)(0x01UL << 2)
#define ERR_OVRERR_MASK                         (uint32_t)(0x01UL << 3)
#define ERR_TRGERR_MASK                         (uint32_t)(0x01UL << 4)



/*===================================================================*
                        Define Registers
*===================================================================*/
/* Software Reset Register */
#define SWRST_SWRST(obj, param)                 ((obj)->SWRST = (uint32_t)(param))

/* Control Register 0 */
#define CR0_SM_7_BIT(obj)                       ((obj)->CR0 = (uint32_t)(((obj)->CR0 & ~CR0_SM_MASK) | (0x00UL)))
#define CR0_SM_8_BIT(obj)                       ((obj)->CR0 = (uint32_t)(((obj)->CR0 & ~CR0_SM_MASK) | (0x01UL)))
#define CR0_SM_9_BIT(obj)                       ((obj)->CR0 = (uint32_t)(((obj)->CR0 & ~CR0_SM_MASK) | (0x10UL)))

#define CR0_PE_DISABLE(obj)                     ((obj)->CR0 = (uint32_t)(((obj)->CR0 & ~CR0_PE_MASK) | (0x00UL << 2)))
#define CR0_PE_ENABLE(obj)                      ((obj)->CR0 = (uint32_t)(((obj)->CR0 & ~CR0_PE_MASK) | (0x01UL << 2)))

#define CR0_EVEN_ODD(obj)                       ((obj)->CR0 = (uint32_t)(((obj)->CR0 & ~CR0_EVEN_MASK) | (0x00UL << 3)))
#define CR0_EVEN_EVEN(obj)                      ((obj)->CR0 = (uint32_t)(((obj)->CR0 & ~CR0_EVEN_MASK) | (0x01UL << 3)))

#define CR0_SBLEN_1_BIT(obj)                    ((obj)->CR0 = (uint32_t)(((obj)->CR0 & ~CR0_SBLEN_MASK) | (0x00UL << 4)))
#define CR0_SBLEN_2_BIT(obj)                    ((obj)->CR0 = (uint32_t)(((obj)->CR0 & ~CR0_SBLEN_MASK) | (0x01UL << 4)))

#define CR0_DIR_LSB_FIRST(obj)                  ((obj)->CR0 = (uint32_t)(((obj)->CR0 & ~CR0_DIR_MASK) | (0x00UL << 5)))
#define CR0_DIR_MSB_FIRST(obj)                  ((obj)->CR0 = (uint32_t)(((obj)->CR0 & ~CR0_DIR_MASK) | (0x01UL << 5)))

#define CR0_IV_DISABLE(obj)                     ((obj)->CR0 = (uint32_t)(((obj)->CR0 & ~CR0_IV_MASK) | (0x00UL << 6)))
#define CR0_IV_ENABLE(obj)                      ((obj)->CR0 = (uint32_t)(((obj)->CR0 & ~CR0_IV_MASK) | (0x01UL << 6)))

#define CR0_WU_DISABLE(obj)                     ((obj)->CR0 = (uint32_t)(((obj)->CR0 & ~CR0_WU_MASK) | (0x00UL << 7)))
#define CR0_WU_ENABLE(obj)                      ((obj)->CR0 = (uint32_t)(((obj)->CR0 & ~CR0_WU_MASK) | (0x01UL << 7)))

#define CR0_RTSE_DISABLE(obj)                   ((obj)->CR0 = (uint32_t)(((obj)->CR0 & ~CR0_RTSE_MASK) | (0x00UL << 8)))
#define CR0_RTSE_ENABLE(obj)                    ((obj)->CR0 = (uint32_t)(((obj)->CR0 & ~CR0_RTSE_MASK) | (0x01UL << 8)))

#define CR0_CTSE_DISABLE(obj)                   ((obj)->CR0 = (uint32_t)(((obj)->CR0 & ~CR0_CTSE_MASK) | (0x00UL << 9)))
#define CR0_CTSE_ENABLE(obj)                    ((obj)->CR0 = (uint32_t)(((obj)->CR0 & ~CR0_CTSE_MASK) | (0x01UL << 9)))

#define CR0_NF_NONE(obj)                        ((obj)->CR0 = (uint32_t)(((obj)->CR0 & ~CR0_NF_MASK) | (0x00UL << 12)))
#define CR0_NF_2_CYClES_T0CLK(obj)              ((obj)->CR0 = (uint32_t)(((obj)->CR0 & ~CR0_NF_MASK) | (0x01UL << 12)))
#define CR0_NF_4_CYClES_T0CLK(obj)              ((obj)->CR0 = (uint32_t)(((obj)->CR0 & ~CR0_NF_MASK) | (0x02UL << 12)))
#define CR0_NF_8_CYClES_T0CLK(obj)              ((obj)->CR0 = (uint32_t)(((obj)->CR0 & ~CR0_NF_MASK) | (0x03UL << 12)))
#define CR0_NF_2_CYClES_TFCLK(obj)              ((obj)->CR0 = (uint32_t)(((obj)->CR0 & ~CR0_NF_MASK) | (0x04UL << 12)))
#define CR0_NF_3_CYClES_TFCLK(obj)              ((obj)->CR0 = (uint32_t)(((obj)->CR0 & ~CR0_NF_MASK) | (0x05UL << 12)))
#define CR0_NF_4_CYClES_TFCLK(obj)              ((obj)->CR0 = (uint32_t)(((obj)->CR0 & ~CR0_NF_MASK) | (0x06UL << 12)))
#define CR0_NF_5_CYClES_TFCLK(obj)              ((obj)->CR0 = (uint32_t)(((obj)->CR0 & ~CR0_NF_MASK) | (0x07UL << 12)))

#define CR0_LPB_DISABLE(obj)                    ((obj)->CR0 = (uint32_t)(((obj)->CR0 & ~CR0_LPB_MASK) | (0x00UL << 15)))
#define CR0_LPB_ENABLE(obj)                     ((obj)->CR0 = (uint32_t)(((obj)->CR0 & ~CR0_LPB_MASK) | (0x01UL << 15)))

#define CR0_HBSEN_DISABLE(obj)                  ((obj)->CR0 = (uint32_t)(((obj)->CR0 & ~CR0_HBSEN_MASK) | (0x00UL << 16)))
#define CR0_HBSEN_ENABLE(obj)                   ((obj)->CR0 = (uint32_t)(((obj)->CR0 & ~CR0_HBSEN_MASK) | (0x01UL << 16)))

#define CR0_HBSMD_1PIN(obj)                     ((obj)->CR0 = (uint32_t)(((obj)->CR0 & ~CR0_HBSMD_MASK) | (0x00UL << 17)))
#define CR0_HBSMD_2PIN(obj)                     ((obj)->CR0 = (uint32_t)(((obj)->CR0 & ~CR0_HBSMD_MASK) | (0x01UL << 17)))

#define CR0_HBSST_TXDA(obj)                     ((obj)->CR0 = (uint32_t)(((obj)->CR0 & ~CR0_HBSST_MASK) | (0x00UL << 18)))
#define CR0_HBSST_TXDB(obj)                     ((obj)->CR0 = (uint32_t)(((obj)->CR0 & ~CR0_HBSST_MASK) | (0x01UL << 18)))

/* Control Register 1 */
#define CR1_DMARE_DISABLE(obj)                  ((obj)->CR1 = (uint32_t)(((obj)->CR1 & ~CR1_DMARE_MASK) | (0x00UL)))
#define CR1_DMARE_ENABLE(obj)                   ((obj)->CR1 = (uint32_t)(((obj)->CR1 & ~CR1_DMARE_MASK) | (0x01UL)))

#define CR1_DMATE_DISABLE(obj)                  ((obj)->CR1 = (uint32_t)(((obj)->CR1 & ~CR1_DMATE_MASK) | (0x00UL << 1)))
#define CR1_DMATE_ENABLE(obj)                   ((obj)->CR1 = (uint32_t)(((obj)->CR1 & ~CR1_DMATE_MASK) | (0x01UL << 1)))

#define CR1_INTERR_DISABLE(obj)                 ((obj)->CR1 = (uint32_t)(((obj)->CR1 & ~CR1_INTERR_MASK) | (0x00UL << 2)))
#define CR1_INTERR_ENABLE(obj)                  ((obj)->CR1 = (uint32_t)(((obj)->CR1 & ~CR1_INTERR_MASK) | (0x01UL << 2)))

#define CR1_INTRXWE_DISABLE(obj)                ((obj)->CR1 = (uint32_t)(((obj)->CR1 & ~CR1_INTRXWE_MASK) | (0x00UL << 4)))
#define CR1_INTRXWE_ENABLE(obj)                 ((obj)->CR1 = (uint32_t)(((obj)->CR1 & ~CR1_INTRXWE_MASK) | (0x01UL << 4)))

#define CR1_INTRXFE_DISABLE(obj)                ((obj)->CR1 = (uint32_t)(((obj)->CR1 & ~CR1_INTRXFE_MASK) | (0x00UL << 5)))
#define CR1_INTRXFE_ENABLE(obj)                 ((obj)->CR1 = (uint32_t)(((obj)->CR1 & ~CR1_INTRXFE_MASK) | (0x01UL << 5)))

#define CR1_INTTXWE_DISABLE(obj)                ((obj)->CR1 = (uint32_t)(((obj)->CR1 & ~CR1_INTTXWE_MASK) | (0x00UL << 6)))
#define CR1_INTTXWE_ENABLE(obj)                 ((obj)->CR1 = (uint32_t)(((obj)->CR1 & ~CR1_INTTXWE_MASK) | (0x01UL << 6)))

#define CR1_INTTXFE_DISABLE(obj)                ((obj)->CR1 = (uint32_t)(((obj)->CR1 & ~CR1_INTTXFE_MASK) | (0x00UL << 7)))
#define CR1_INTTXFE_ENABLE(obj)                 ((obj)->CR1 = (uint32_t)(((obj)->CR1 & ~CR1_INTTXFE_MASK) | (0x01UL << 7)))

#define CR1_RIL(obj, param)                     ((obj)->CR1 = (uint32_t)(param))

#define CR1_TIL(obj, param)                     ((obj)->CR1 = (uint32_t)(param))

/* Clock Control Register */
#define CLK_PRSEL_1_1(obj)                      ((obj)->CLK = (uint32_t)(((obj)->CLK & ~CLK_PRSEL_MASK) | (0x00UL << 4)))
#define CLK_PRSEL_1_2(obj)                      ((obj)->CLK = (uint32_t)(((obj)->CLK & ~CLK_PRSEL_MASK) | (0x01UL << 4)))
#define CLK_PRSEL_1_4(obj)                      ((obj)->CLK = (uint32_t)(((obj)->CLK & ~CLK_PRSEL_MASK) | (0x02UL << 4)))
#define CLK_PRSEL_1_8(obj)                      ((obj)->CLK = (uint32_t)(((obj)->CLK & ~CLK_PRSEL_MASK) | (0x03UL << 4)))
#define CLK_PRSEL_1_16(obj)                     ((obj)->CLK = (uint32_t)(((obj)->CLK & ~CLK_PRSEL_MASK) | (0x04UL << 4)))
#define CLK_PRSEL_1_32(obj)                     ((obj)->CLK = (uint32_t)(((obj)->CLK & ~CLK_PRSEL_MASK) | (0x05UL << 4)))
#define CLK_PRSEL_1_64(obj)                     ((obj)->CLK = (uint32_t)(((obj)->CLK & ~CLK_PRSEL_MASK) | (0x06UL << 4)))
#define CLK_PRSEL_1_128(obj)                    ((obj)->CLK = (uint32_t)(((obj)->CLK & ~CLK_PRSEL_MASK) | (0x07UL << 4)))
#define CLK_PRSEL_1_256(obj)                    ((obj)->CLK = (uint32_t)(((obj)->CLK & ~CLK_PRSEL_MASK) | (0x08UL << 4)))
#define CLK_PRSEL_1_512(obj)                    ((obj)->CLK = (uint32_t)(((obj)->CLK & ~CLK_PRSEL_MASK) | (0x09UL << 4)))

/* Baud Rate Register */
#define BRD_BRN(obj, param)                     ((obj)->BRD = (uint32_t)(((obj)->BRD & ~BRD_BRN_MASK) | (param)))

#define BRD_BRK(obj, param)                     ((obj)->BRD = (uint32_t)(((obj)->BRD & ~BRD_BRK_MASK) | (param << 16)))

#define BRD_KEN_DISABLE(obj)                    ((obj)->BRD = (uint32_t)(((obj)->BRD & ~BRD_KEN_MASK) | (0x00UL << 23)))
#define BRD_KEN_ENABLE(obj)                     ((obj)->BRD = (uint32_t)(((obj)->BRD & ~BRD_KEN_MASK) | (0x01UL << 23)))

/* Transfer Enable Register */
#define TRANS_RXE_DISABLE(obj)                  ((obj)->TRANS = (uint32_t)(((obj)->TRANS & ~TRANS_RXE_MASK) | (0x00UL)))
#define TRANS_RXE_ENABLE(obj)                   ((obj)->TRANS = (uint32_t)(((obj)->TRANS & ~TRANS_RXE_MASK) | (0x01UL)))

#define TRANS_TXE_DISABLE(obj)                  ((obj)->TRANS = (uint32_t)(((obj)->TRANS & ~TRANS_TXE_MASK) | (0x00UL << 1)))
#define TRANS_TXE_ENABLE(obj)                   ((obj)->TRANS = (uint32_t)(((obj)->TRANS & ~TRANS_TXE_MASK) | (0x01UL << 1)))

#define TRANS_TXTRG_DISABLE(obj)                ((obj)->TRANS = (uint32_t)(((obj)->TRANS & ~TRANS_TXTRG_MASK) | (0x00UL << 2)))
#define TRANS_TXTRG_ENABLE(obj)                 ((obj)->TRANS = (uint32_t)(((obj)->TRANS & ~TRANS_TXTRG_MASK) | (0x01UL << 2)))

#define TRANS_BK_NO_TRANSMISSION(obj)           ((obj)->TRANS = (uint32_t)(((obj)->TRANS & ~TRANS_BK_MASK) | (0x00UL << 3)))
#define TRANS_BK_TRANSMISSION(obj)              ((obj)->TRANS = (uint32_t)(((obj)->TRANS & ~TRANS_BK_MASK) | (0x01UL << 3)))

/* Data Register */
#define DR_DR(obj, param)                       ((obj)->DR = (uint32_t)(((obj)->DR & ~DR_DR_MASK) | (param)))

/* Status Register */
#define SR_RXFF_CLEAR(obj)                      ((obj)->SR = (uint32_t)(((obj)->SR & ~SR_RXFF_MASK) | (0x01UL << 5)))
#define SR_RXEND_CLEAR(obj)                     ((obj)->SR = (uint32_t)(((obj)->SR & ~SR_RXEND_MASK) | (0x01UL << 6)))

#define SR_TXFF_CLEAR(obj)                      ((obj)->SR = (uint32_t)(((obj)->SR & ~SR_TXFF_MASK) | (0x01UL << 13)))
#define SR_TXEND_CLEAR(obj)                     ((obj)->SR = (uint32_t)(((obj)->SR & ~SR_TXEND_MASK) | (0x01UL << 14)))

/* FIFO Clear Register */
#define FIFOCLR_RFCLR_CLEAR(obj)                ((obj)->FIFOCLR = (uint32_t)(((obj)->FIFOCLR & ~FIFOCLR_RFCLR_MASK) | (0x01UL)))
#define FIFOCLR_TFCLR_CLEAR(obj)                ((obj)->FIFOCLR = (uint32_t)(((obj)->FIFOCLR & ~FIFOCLR_TFCLR_MASK) | (0x01UL << 1)))

/* Error Register */
#define ERR_BERR_CLEAR(obj)                     ((obj)->ERR = (uint32_t)(((obj)->ERR & ~ERR_BERR_MASK) | (0x01UL)))
#define ERR_FERR_CLEAR(obj)                     ((obj)->ERR = (uint32_t)(((obj)->ERR & ~ERR_FERR_MASK) | (0x01UL << 1)))
#define ERR_PERR_CLEAR(obj)                     ((obj)->ERR = (uint32_t)(((obj)->ERR & ~ERR_PERR_MASK) | (0x01UL << 2)))
#define ERR_OVRERR_CLEAR(obj)                   ((obj)->ERR = (uint32_t)(((obj)->ERR & ~ERR_OVRERR_MASK) | (0x01UL << 3)))
#define ERR_TRGERR_CLEAR(obj)                   ((obj)->ERR = (uint32_t)(((obj)->ERR & ~ERR_TRGERR_MASK) | (0x01UL << 4)))

/*===================================================================*
                  Functions declaration for UARTx
*===================================================================*/
void UART_Init(TSB_UART_TypeDef * UARTx, uint32_t baudRate);
void UART_Software_Reset(TSB_UART_TypeDef * UARTx);
void UART_Set_BaudRate(TSB_UART_TypeDef * UARTx, uint32_t baudRate);
void UART_send(TSB_UART_TypeDef * UARTx, char *msg, int buffer);
void sendUART_TEST(TSB_UART_TypeDef * UARTx, char *message);
void UART_receive(TSB_UART_TypeDef * UARTx, int rcvCharLength);
void UART_Set_ClkSupply(uint8_t port);

uint8_t getRLVL_reg(TSB_UART_TypeDef * UARTx);
bool getOVRERR_reg(TSB_UART_TypeDef * UARTx);
uint32_t getSWRST_reg(TSB_UART_TypeDef * UARTx);
uint32_t getCR0_reg(TSB_UART_TypeDef * UARTx);
uint32_t getCR1_reg(TSB_UART_TypeDef * UARTx);
uint32_t getCLK_reg(TSB_UART_TypeDef * UARTx);
uint32_t getBRD_reg(TSB_UART_TypeDef * UARTx);
uint32_t getTRANS_reg(TSB_UART_TypeDef * UARTx);
uint32_t getDR_reg(TSB_UART_TypeDef * UARTx);
uint32_t getSR_reg(TSB_UART_TypeDef * UARTx);
uint32_t getFIFOCLR_reg(TSB_UART_TypeDef * UARTx);
uint32_t getERR_reg(TSB_UART_TypeDef * UARTx);

extern char sendMSG[bufferSize];
extern char rcvBuffer[bufferSize];
void sendUART(TSB_UART_TypeDef * UARTx, char *message);

void json_parse_init(void);
char* read_json_parse(char *jsonBuf, char *strings);

#ifdef __cplusplus
}
#endif

#endif  /* __TSB_UART_H__ */


