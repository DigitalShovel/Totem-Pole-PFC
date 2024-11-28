/**
*******************************************************************************
* @file    DS_UART.c
* @brief   Toshiba Asynchronous Serial Communication Circuit
*          TOSHIBA 'TMPM4KNA' Group
* @version V1.0.0.0
* @date    2022-09-29 #$
* 
* @author Hugo Rodrigues
*******************************************************************************
*/

#include "DS_UART.h"
#include "APMD.h"
#include "TMPM4KyA.h"
#include "jsmn.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/* UART PORT 0 */
#define UART0_TX_Pin                "PC0"   				        // PC0, PC1, PN0 or PN1 or (None for disable)
#define UART0_RX_Pin                "PC1"   				        // PC0, PC1, PN0 or PN1 or (None for disable)

/* UART PORT 1 */
#define UART1_TX_Pin                "None"   				        // PC4, PC5, PU5 or PU6 or (None for disable) 
#define UART1_RX_Pin                "None"   				        // PC4, PC5, PU5 or PU6 or (None for disable)

/* UART PORT 2 */
#define UART2_TX_Pin                "None"   				        // PF0, PF1, PU0 or PU1 or (None for disable)
#define UART2_RX_Pin                "None"   				        // PF0, PF1, PU0 or PU1 or (None for disable)

/* UART PORT 3 */
#define UART3_TX_Pin                "None"   				        // PF3, PF4, PF6 or PF7 or (None for disable)
#define UART3_RX_Pin                "None"   				        // PF3, PF4, PF6 or PF7 or (None for disable)

/*===================================================================*
            Initialize the UARTx Based on configuration
*===================================================================*/
void UART_Init(TSB_UART_TypeDef * UARTx, uint32_t baudRate){
    if(UARTx == TSB_UART0){
        /* Set the Clock Supply */
        UART_Set_ClkSupply(port);
        /* Set the Baud Rate */
        UART_Set_BaudRate(UARTx, baudRate);

        CR1_INTTXWE_ENABLE(UARTx);                                  // Enable the interrupt for Transmission completion
        CR1_INTRXWE_ENABLE(UARTx);                                  // Enable the interrupt for Receive completion
        CR1_INTERR_ENABLE(UARTx);                                   // Enable the interrupt for Error control

        //CR1_DMATE_ENABLE(UARTx);

        TRANS_RXE_ENABLE(UARTx);                                    // Enable the Reception control
        TRANS_TXE_ENABLE(UARTx);                                    // Enable the Transmission control
    }
}

void UART_Software_Reset(TSB_UART_TypeDef * UARTx){
    SWRST_SWRST(UARTx, 0x02);                                       // Write 0b10 (Page 27 - "UART-C Reference Manual")
    SWRST_SWRST(UARTx, 0x01);                                       // Write 0b01 (Page 27 - "UART-C Reference Manual")
}

void UART_Set_BaudRate(TSB_UART_TypeDef * UARTx, uint32_t baudRate){
    UART_Software_Reset(UARTx);                                     // Reset UART 
    while( TSB_UART0->SWRST == 0x80 ){}                             // Wait till reset is done
    CLK_PRSEL_1_1(UARTx);                                           // Prescale the clock to 1/1
    CR0_SM_8_BIT(UARTx);                                            // Data frame has 8 bit
    // Check the value of fsysm (Middle Speed System Clock)
    uint8_t MCKSEL_Val = ((TSB_CG->SYSCR & CGSYSCR_MCKSELGST_MASK) >> 22);
    uint32_t middle_speed_sys_clock = 0;
    switch(MCKSEL_Val){
        case(0):
            middle_speed_sys_clock = SystemCoreClock;
            break;
        case(1):
            middle_speed_sys_clock = SystemCoreClock/2;
            break;
        default:
            middle_speed_sys_clock = SystemCoreClock/4;
            break;
    }
    uint16_t BRB_val = (((middle_speed_sys_clock)/baudRate)/16);           // Calculate the baud rate based on system clock     
    BRD_BRN(UARTx, BRB_val);                                        // Change the baud rate
    BRD_KEN_ENABLE(UARTx);                                          // Enable the dividing control
}

void UART_send(TSB_UART_TypeDef * UARTx, char *msg, int bitpos){
    TRANS_TXE_DISABLE(UARTx);                                       // Disable the Transmission Control
    DR_DR(UARTx, msg[bitpos]);                                      // Read data inside the data transmit register
    while( UARTx->SR & 0x8000 ){}                                   // Wait for data transmit to finish
    SR_TXFF_CLEAR(UARTx);                                           // Clears the Transmit FIFO Flag back to 1st stage
    SR_TXEND_CLEAR(UARTx);                                          // Clears the Transmission completion flag
    TRANS_TXE_ENABLE(UARTx);                                        // Enable the Transmission Control
}

void sendUART(TSB_UART_TypeDef * UARTx, char *message){
    int i;
    for (i = 0; i <= bufferSize; i++){
        if(message[i] != NULL){
            UART_send(UARTx, message, i);
        }
        else{
            break;
        }
    }
}

/*void sendUART(TSB_UART_TypeDef * UARTx, char *message){
    memset(sendMSG, 0, bufferSize);                                 // Clear the memory that contains the buffer
    strcpy(sendMSG, message);                                       // Concatenate the String with the char buffer
    NVIC_EnableIRQ( INTSC0TX_IRQn );                                // Enables the Transmit interrupt function
    UART_send(UARTx, sendMSG, 0);                                   // Send the buffer to the UART_send function
}*/

void UART_receive(TSB_UART_TypeDef * UARTx, int rcvCharLength){
    TRANS_RXE_DISABLE(UARTx);                                       // Disable the Reception Control
    rcvBuffer[rcvCharLength] = (char)(getDR_reg(UARTx) & 0xFF);     // Move the data from the data receive register to the buffer
    while( UARTx->SR & 0x80 ){}                                     // Wait for data receive to finish
    SR_RXFF_CLEAR(UARTx);                                           // Clears the Receive FIFO flag back to 1st stage
    SR_RXEND_CLEAR(UARTx);                                          // Clears the Reception completion flag
    TRANS_RXE_ENABLE(UARTx);                                        // Enable the Reception Control 
}

void UART_Set_ClkSupply(uint8_t port){
    /* PORT 0 */
    if(port == 0){
        TSB_CG_FSYSMENA_IPMENA21 = 1;                               // Clock Enable of UART ch0
        if(UART0_TX_Pin == "PC0"){  
            TSB_CG_FSYSMENA_IPMENA02 = 1;       		            // Clock Enable of PORT C
            TSB_PC_CR_PC0C = 1;                 		            // Set PC0 as an Ouput 
            TSB_PC_FR1_PC0F1 = 1;               		            // Set PC0 as TXD Function
            TSB_PC_IE_PC0IE = 0;                		            // Clear PC0 Interrupt Event
        }

        else if(UART0_TX_Pin == "PC1"){
            TSB_CG_FSYSMENA_IPMENA02 = 1;       		            // Clock Enable of PORT C
            TSB_PC_CR_PC1C = 1;                 		            // Set PC1 as an Ouput 
            TSB_PC_FR2_PC1F2 = 1;               		            // Set PC1 as TXD Function
            TSB_PC_IE_PC1IE = 0;                		            // Clear PC1 Interrupt Event
        }

        else if(UART0_TX_Pin == "PN0"){
            TSB_CG_FSYSMENA_IPMENA12 = 1;       		            // Clock Enable of PORT N
            TSB_PN_CR_PN0C = 1;                 		            // Set PN0 as an Ouput 
            TSB_PN_FR1_PN0F1 = 1;               		            // Set PN0 as TXD Function
            TSB_PN_IE_PN0IE = 0;                		            // Clear PN0 Interrupt Event
        }

        else if(UART0_TX_Pin == "PN1"){
            TSB_CG_FSYSMENA_IPMENA12 = 1;       		            // Clock Enable of PORT N
            TSB_PN_CR_PN1C = 1;                 		            // Set PN1 as an Ouput 
            TSB_PN_FR2_PN1F2 = 1;               		            // Set PN1 as TXD Function
            TSB_PN_IE_PN1IE = 0;                		            // Clear PN1 Interrupt Event
        }  
        if(UART0_RX_Pin == "PC0"){
            TSB_CG_FSYSMENA_IPMENA02 = 1;       		            // Clock Enable of PORT C
            TSB_PC_CR_PC0C = 0;                 		            // Set PC0 as an Input
            TSB_PC_FR2_PC0F2 = 1;               		            // Set PC0 as RXD Function
            TSB_PC_IE_PC0IE = 1;                		            // Set PC0 Interrupt Event
        }

        else if(UART0_RX_Pin == "PC1"){
            TSB_CG_FSYSMENA_IPMENA02 = 1;       		            // Clock Enable of PORT C
            TSB_PC_CR_PC1C = 0;                 		            // Set PC1 as an Input
            TSB_PC_FR1_PC1F1 = 1;               		            // Set PC1 as RXD Function
            TSB_PC_IE_PC1IE = 1;                		            // Set PC1 Interrupt Event
        } 

        else if(UART0_RX_Pin == "PN0"){
            TSB_CG_FSYSMENA_IPMENA12 = 1;       		            // Clock Enable of PORT N
            TSB_PN_CR_PN0C = 0;                 		            // Set PN0 as an Input 
            TSB_PN_FR2_PN0F2 = 1;               		            // Set PN0 as RXD Function
            TSB_PN_IE_PN0IE = 1;                		            // Set PN0 Interrupt Event
        }

        else if(UART0_RX_Pin == "PN1"){
            TSB_CG_FSYSMENA_IPMENA12 = 1;       		            // Clock Enable of PORT N
            TSB_PN_CR_PN1C = 0;                 		            // Set PN1 as an Input 
            TSB_PN_FR1_PN1F1 = 1;               		            // Set PN1 as RXD Function
            TSB_PN_IE_PN1IE = 1;                		            // Set PN1 Interrupt Event
        }
    }
    /* PORT 1 */
    else if(port == 1){
        TSB_CG_FSYSMENA_IPMENA22 = 1;                               // Clock Enable of UART ch1
        if(UART1_TX_Pin == "PC4"){  
            TSB_CG_FSYSMENA_IPMENA02 = 1;       		            // Clock Enable of PORT C
            TSB_PC_CR_PC4C = 1;                 		            // Set PC4 as an Ouput 
            TSB_PC_FR1_PC4F1 = 1;               		            // Set PC4 as TXD Function
            TSB_PC_IE_PC4IE = 0;                		            // Clear PC4 Interrupt Event
        }

        else if(UART1_TX_Pin == "PC5"){
            TSB_CG_FSYSMENA_IPMENA02 = 1;       		            // Clock Enable of PORT C
            TSB_PC_CR_PC5C = 1;                 		            // Set PC5 as an Ouput 
            TSB_PC_FR2_PC5F2 = 1;               		            // Set PC5 as TXD Function
            TSB_PC_IE_PC5IE = 0;                		            // Clear PC5 Interrupt Event
        }

        else if(UART1_TX_Pin == "PU5"){
            TSB_CG_FSYSMENA_IPMENA16 = 1;       		            // Clock Enable of PORT U
            TSB_PU_CR_PU5C = 1;                 		            // Set PU5 as an Ouput 
            TSB_PU_FR1_PU5F1 = 1;               		            // Set PU5 as TXD Function
            TSB_PU_IE_PU5IE = 0;                		            // Clear PU5 Interrupt Event
        }

        else if(UART1_TX_Pin == "PU6"){
            TSB_CG_FSYSMENA_IPMENA16 = 1;       		            // Clock Enable of PORT U
            TSB_PU_CR_PU6C = 1;                 		            // Set PU6 as an Ouput 
            TSB_PU_FR2_PU6F2 = 1;               		            // Set PU6 as TXD Function
            TSB_PU_IE_PU6IE = 0;                		            // Clear PU6 Interrupt Event
        }  
        if(UART1_RX_Pin == "PC4"){
            TSB_CG_FSYSMENA_IPMENA02 = 1;       		            // Clock Enable of PORT C
            TSB_PC_CR_PC4C = 0;                 		            // Set PC4 as an Input
            TSB_PC_FR2_PC4F2 = 1;               		            // Set PC4 as RXD Function
            TSB_PC_IE_PC4IE = 1;                		            // Set PC4 Interrupt Event
        }

        else if(UART1_RX_Pin == "PC5"){
            TSB_CG_FSYSMENA_IPMENA02 = 1;       		            // Clock Enable of PORT C
            TSB_PC_CR_PC5C = 0;                 		            // Set PC5 as an Input
            TSB_PC_FR1_PC5F1 = 1;               		            // Set PC5 as RXD Function
            TSB_PC_IE_PC5IE = 1;                		            // Set PC5 Interrupt Event
        } 

        else if(UART1_RX_Pin == "PU5"){
            TSB_CG_FSYSMENA_IPMENA16 = 1;       		            // Clock Enable of PORT U
            TSB_PU_CR_PU5C = 0;                 		            // Set PU5 as an Input 
            TSB_PU_FR2_PU5F2 = 1;               		            // Set PU5 as RXD Function
            TSB_PU_IE_PU5IE = 1;                		            // Set PU5 Interrupt Event
        }

        else if(UART1_RX_Pin == "PU6"){
            TSB_CG_FSYSMENA_IPMENA16 = 1;       		            // Clock Enable of PORT U
            TSB_PU_CR_PU6C = 0;                 		            // Set PU6 as an Input 
            TSB_PU_FR1_PU6F1 = 1;               		            // Set PU6 as RXD Function
            TSB_PU_IE_PU6IE = 1;                		            // Set PU6 Interrupt Event
        }
    }
    /* PORT 2 */
    else if(port == 2){
        TSB_CG_FSYSMENA_IPMENA23 = 1;                               // Clock Enable of UART ch2
        if(UART2_TX_Pin == "PF0"){  
            TSB_CG_FSYSMENA_IPMENA05 = 1;       		            // Clock Enable of PORT F
            TSB_PF_CR_PF0C = 1;                 		            // Set PF0 as an Ouput 
            TSB_PF_FR1_PF0F1 = 1;               		            // Set PF0 as TXD Function
            TSB_PF_IE_PF0IE = 0;                		            // Clear PF0 Interrupt Event
        }

        else if(UART2_TX_Pin == "PF1"){
            TSB_CG_FSYSMENA_IPMENA05 = 1;       		            // Clock Enable of PORT F
            TSB_PF_CR_PF1C = 1;                 		            // Set PF1 as an Ouput 
            TSB_PF_FR2_PF1F2 = 1;               		            // Set PF1 as TXD Function
            TSB_PF_IE_PF1IE = 0;                		            // Clear PF1 Interrupt Event
        }

        else if(UART2_TX_Pin == "PU0"){
            TSB_CG_FSYSMENA_IPMENA16 = 1;       		            // Clock Enable of PORT U
            TSB_PU_CR_PU0C = 1;                 		            // Set PU0 as an Ouput 
            TSB_PU_FR1_PU0F1 = 1;               		            // Set PU0 as TXD Function
            TSB_PU_IE_PU0IE = 0;                		            // Clear PU0 Interrupt Event
        }

        else if(UART2_TX_Pin == "PU1"){
            TSB_CG_FSYSMENA_IPMENA16 = 1;       		            // Clock Enable of PORT U
            TSB_PU_CR_PU1C = 1;                 		            // Set PU1 as an Ouput 
            TSB_PU_FR2_PU1F2 = 1;               		            // Set PU1 as TXD Function
            TSB_PU_IE_PU1IE = 0;                		            // Clear PU1 Interrupt Event
        }  
        if(UART2_RX_Pin == "PF0"){
            TSB_CG_FSYSMENA_IPMENA05 = 1;       		            // Clock Enable of PORT C
            TSB_PF_CR_PF0C = 0;                 		            // Set PF0 as an Input
            TSB_PF_FR2_PF0F2 = 1;               		            // Set PF0 as RXD Function
            TSB_PF_IE_PF0IE = 1;                		            // Set PF0 Interrupt Event
        }

        else if(UART2_RX_Pin == "PF1"){
            TSB_CG_FSYSMENA_IPMENA05 = 1;       		            // Clock Enable of PORT C
            TSB_PF_CR_PF1C = 0;                 		            // Set PF1 as an Input
            TSB_PF_FR1_PF1F1 = 1;               		            // Set PF1 as RXD Function
            TSB_PF_IE_PF1IE = 1;                		            // Set PF1 Interrupt Event
        } 

        else if(UART2_RX_Pin == "PU0"){
            TSB_CG_FSYSMENA_IPMENA16 = 1;       		            // Clock Enable of PORT U
            TSB_PU_CR_PU0C = 0;                 		            // Set PU0 as an Input 
            TSB_PU_FR2_PU0F2 = 1;               		            // Set PU0 as RXD Function
            TSB_PU_IE_PU0IE = 1;                		            // Set PU0 Interrupt Event
        }

        else if(UART2_RX_Pin == "PU1"){
            TSB_CG_FSYSMENA_IPMENA16 = 1;       		            // Clock Enable of PORT U
            TSB_PU_CR_PU1C = 0;                 		            // Set PU1 as an Input 
            TSB_PU_FR1_PU1F1 = 1;               		            // Set PU1 as RXD Function
            TSB_PU_IE_PU1IE = 1;                		            // Set PU1 Interrupt Event
        }
    }
    /* PORT 3 */
    else if(port == 3){
        TSB_CG_FSYSMENA_IPMENA24 = 1;                               // Clock Enable of UART ch3
        if(UART3_TX_Pin == "PF3"){  
            TSB_CG_FSYSMENA_IPMENA05 = 1;       		            // Clock Enable of PORT F
            TSB_PF_CR_PF3C = 1;                 		            // Set PF3 as an Ouput 
            TSB_PF_FR1_PF3F1 = 1;               		            // Set PF3 as TXD Function
            TSB_PF_IE_PF3IE = 0;                		            // Clear PF3 Interrupt Event
        }

        else if(UART3_TX_Pin == "PF4"){
            TSB_CG_FSYSMENA_IPMENA05 = 1;       		            // Clock Enable of PORT F
            TSB_PF_CR_PF4C = 1;                 		            // Set PF4 as an Ouput 
            TSB_PF_FR2_PF4F2 = 1;               		            // Set PF4 as TXD Function
            TSB_PF_IE_PF4IE = 0;                		            // Clear PF4 Interrupt Event
        }

        else if(UART3_TX_Pin == "PF6"){
            TSB_CG_FSYSMENA_IPMENA05 = 1;       		            // Clock Enable of PORT F
            TSB_PF_CR_PF6C = 1;                 		            // Set PF6 as an Ouput 
            TSB_PF_FR1_PF6F1 = 1;               		            // Set PF6 as TXD Function
            TSB_PF_IE_PF6IE = 0;                		            // Clear PF6 Interrupt Event
        }

        else if(UART3_TX_Pin == "PF7"){
            TSB_CG_FSYSMENA_IPMENA05 = 1;       		            // Clock Enable of PORT F
            TSB_PF_CR_PF7C = 1;                 		            // Set PF7 as an Ouput 
            TSB_PF_FR2_PF7F2 = 1;               		            // Set PF7 as TXD Function
            TSB_PF_IE_PF7IE = 0;                		            // Clear PF7 Interrupt Event
        }  
        if(UART3_RX_Pin == "PF3"){
            TSB_CG_FSYSMENA_IPMENA05 = 1;       		            // Clock Enable of PORT F
            TSB_PF_CR_PF3C = 0;                 		            // Set PF3 as an Input
            TSB_PF_FR2_PF3F2 = 1;               		            // Set PF3 as RXD Function
            TSB_PF_IE_PF3IE = 1;                		            // Set PF3 Interrupt Event
        }

        else if(UART3_RX_Pin == "PF4"){
            TSB_CG_FSYSMENA_IPMENA05 = 1;       		            // Clock Enable of PORT F
            TSB_PF_CR_PF4C = 0;                 		            // Set PF4 as an Input
            TSB_PF_FR1_PF4F1 = 1;               		            // Set PF4 as RXD Function
            TSB_PF_IE_PF4IE = 1;                		            // Set PF4 Interrupt Event
        } 

        else if(UART3_RX_Pin == "PF6"){
            TSB_CG_FSYSMENA_IPMENA05 = 1;       		            // Clock Enable of PORT F
            TSB_PF_CR_PF6C = 0;                 		            // Set PF6 as an Input 
            TSB_PF_FR2_PF6F2 = 1;               		            // Set PF6 as RXD Function
            TSB_PF_IE_PF6IE = 1;                		            // Set PF6 Interrupt Event
        }

        else if(UART3_RX_Pin == "PF7"){
            TSB_CG_FSYSMENA_IPMENA05 = 1;       		            // Clock Enable of PORT F
            TSB_PF_CR_PF7C = 0;                 		            // Set PF7 as an Input 
            TSB_PF_FR1_PF7F1 = 1;               		            // Set PF7 as RXD Function
            TSB_PF_IE_PF7IE = 1;                		            // Set PF7 Interrupt Event
        }
    }
}


uint8_t getRLVL_reg(TSB_UART_TypeDef * UARTx){
    return (UARTx->SR & 0x0F);
}

bool getOVRERR_reg(TSB_UART_TypeDef * UARTx){
    return (UARTx->ERR & 0x08);
}

uint32_t getSWRST_reg(TSB_UART_TypeDef * UARTx){
    return UARTx->SWRST;
}

uint32_t getCR0_reg(TSB_UART_TypeDef * UARTx){
    return UARTx->CR0;
}

uint32_t getCR1_reg(TSB_UART_TypeDef * UARTx){
    return UARTx->CR1;
}

uint32_t getCLK_reg(TSB_UART_TypeDef * UARTx){
    return UARTx->CLK;
}

uint32_t getBRD_reg(TSB_UART_TypeDef * UARTx){
    return UARTx->BRD;
}

uint32_t getTRANS_reg(TSB_UART_TypeDef * UARTx){
    return UARTx->TRANS;
}

uint32_t getDR_reg(TSB_UART_TypeDef * UARTx){
    return UARTx->DR;
}

uint32_t getSR_reg(TSB_UART_TypeDef * UARTx){
    return UARTx->SR;
}

uint32_t getFIFOCLR_reg(TSB_UART_TypeDef * UARTx){
    return UARTx->FIFOCLR;
}

uint32_t getERR_reg(TSB_UART_TypeDef * UARTx){
    return UARTx->ERR;
}

/*********************** JSON PARSE ***************************/

jsmn_parser p;
jsmntok_t t[bufferSize];
char JSON_STRING[bufferSize];
char JSON_STR_BUF[jsonBufferSize];
static int jsoneq(const char *json, jsmntok_t *tok, const char *s);

void json_parse_init(void){
    jsmn_init(&p);
}

static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
  if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start &&
      strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
    return 0;
  }
  return -1;
}

char* read_json_parse(char *jsonBuf, char *strings){
    int r, i; 
    json_parse_init();
    memset(JSON_STR_BUF, 0, bufferSize);
    strncpy(JSON_STRING, jsonBuf, bufferSize);
    r = jsmn_parse(&p, JSON_STRING, strlen(JSON_STRING), t,
                 sizeof(t) / sizeof(t[0]));
    for(i = 1; i < r; i++){
        if (jsoneq(JSON_STRING, &t[i], strings) == 0) {
			sprintf(JSON_STR_BUF, "%.*s\n", t[i + 1].end - t[i + 1].start, JSON_STRING + t[i + 1].start);
			//sendUART(TSB_UART0, JSON_STR_BUF);
		}
    }
    return JSON_STR_BUF;
}

/********************** END OF JSON PARSE **************************/
