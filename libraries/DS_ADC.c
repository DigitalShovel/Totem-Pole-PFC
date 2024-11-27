/**
*******************************************************************************
* @file    DS_ADC.c
* @brief   Toshiba 12-bit Analog to Digital Converter Circuit
*          TOSHIBA 'TMPM4KNA' Group
* @version V1.0.0.0
* @date    2022-10-31
* 
* @author Hugo Rodrigues
*******************************************************************************
*/

#include "TMPM4KyA.h"
#include "DS_ADC.h"
#include "sys_timer.h"
//#include "DS_APMD.h"
#include <stdbool.h>
#include <stdint.h>


/*===================================================================*
                Analog to Digital Conversion Initialization
*===================================================================*/

ADxConversionType ADxType;

void ADC_Init(TSB_AD_TypeDef * ADx){
    ADxType.typex = Single_Conversion;      // Sets the type of reading for the ADC

    ADC_CG_Config(ADx);
    ADC_Config(ADx);
    ADC_Conversion_Setting(ADx);
}

void ADC_CG_Config(TSB_AD_TypeDef * ADx){
    switch((intptr_t)ADx){
        case (intptr_t)TSB_ADA : 
            /* Configure PORT L ADA09(PL6), ADA13(PL5), ADA16(PL0), ADA17(PL2), ADA18(PL4) */
            TSB_CG_FSYSMENA_IPMENA10 = 1;       // Clock enable of PORT L
            /* PL0 */
            TSB_PL_CR_PL0C = 0;                 // Sets Pin PL0 as input
            TSB_PL_OD_PL0OD = 0;                // Sets Open-Drain OFF
            TSB_PL_IE_PL0IE = 0;                // Sets Input as disable
            TSB_PL_PUP_PL0UP = 0;               // Disable pull-up
            TSB_PL_PDN_PL0DN = 0;               // Disable pull-down
            /* PL2 */
            TSB_PL_CR_PL2C = 0;                 // Sets Pin PL2 as input
            TSB_PL_OD_PL2OD = 0;                // Sets Open-Drain OFF
            TSB_PL_IE_PL2IE = 0;                // Sets Input as disable
            TSB_PL_PUP_PL2UP = 0;               // Disable pull-up
            TSB_PL_PDN_PL2DN = 0;               // Disable pull-down
            /* PL4 */
            TSB_PL_CR_PL4C = 0;                 // Sets Pin PL4 as input
            TSB_PL_OD_PL4OD = 0;                // Sets Open-Drain OFF
            TSB_PL_IE_PL4IE = 0;                // Sets Input as disable
            TSB_PL_PUP_PL4UP = 0;               // Disable pull-up
            TSB_PL_PDN_PL4DN = 0;               // Disable pull-down
            /* PL5 */
            TSB_PL_CR_PL5C = 0;                 // Sets Pin PL5 as input
            TSB_PL_OD_PL5OD = 0;                // Sets Open-Drain OFF
            TSB_PL_IE_PL5IE = 0;                // Sets Input as disable
            TSB_PL_PUP_PL5UP = 0;               // Disable pull-up
            TSB_PL_PDN_PL5DN = 0;               // Disable pull-down
            /* PL6 */
            TSB_PL_CR_PL6C = 0;                 // Sets Pin PL6 as input
            TSB_PL_OD_PL6OD = 0;                // Sets Open-Drain OFF
            TSB_PL_IE_PL6IE = 0;                // Sets Input as disable
            TSB_PL_PUP_PL6UP = 0;               // Disable pull-up
            TSB_PL_PDN_PL6DN = 0;               // Disable pull-down

            TSB_CG_FSYSMENB_IPMENB02 = 1;       // Clock enable of ADC Unit A
            TSB_CG_SPCLKEN_ADCKEN0 = 1;         // Clock enable for ADC Unit A
            break;

        case (intptr_t)TSB_ADC : 
            /* Configure PORT J ADC01(PJ1), ADC02(PJ2), ADC03(PJ3), ADC04(PJ4) */
            TSB_CG_FSYSMENA_IPMENA08 = 1;       // Clock enable of PORT J
            /* PJ1 */
            TSB_PJ_CR_PJ1C = 0;                 // Sets Pin PJ1 as input
            TSB_PJ_OD_PJ1OD = 0;                // Sets Open-Drain OFF
            TSB_PJ_IE_PJ1IE = 0;                // Sets Input as disable
            TSB_PJ_PUP_PJ1UP = 0;               // Disable pull-up
            TSB_PJ_PDN_PJ1DN = 0;               // Disable pull-down
            /* PJ2 */
            TSB_PJ_CR_PJ2C = 0;                 // Sets Pin PJ2 as input
            TSB_PJ_OD_PJ2OD = 0;                // Sets Open-Drain OFF
            TSB_PJ_IE_PJ2IE = 0;                // Sets Input as disable
            TSB_PJ_PUP_PJ2UP = 0;               // Disable pull-up
            TSB_PJ_PDN_PJ2DN = 0;               // Disable pull-down
            /* PJ3 */
            TSB_PJ_CR_PJ3C = 0;                 // Sets Pin PJ3 as input
            TSB_PJ_OD_PJ3OD = 0;                // Sets Open-Drain OFF
            TSB_PJ_IE_PJ3IE = 0;                // Sets Input as disable
            TSB_PJ_PUP_PJ3UP = 0;               // Disable pull-up
            TSB_PJ_PDN_PJ3DN = 0;               // Disable pull-down
            /* PJ4 */
            TSB_PJ_CR_PJ4C = 0;                 // Sets Pin PJ4 as input
            TSB_PJ_OD_PJ4OD = 0;                // Sets Open-Drain OFF
            TSB_PJ_IE_PJ4IE = 0;                // Sets Input as disable
            TSB_PJ_PUP_PJ4UP = 0;               // Disable pull-up
            TSB_PJ_PDN_PJ4DN = 0;               // Disable pull-down

            TSB_CG_FSYSMENB_IPMENB04 = 1;       // Clock enable of ADC Unit C
            TSB_CG_SPCLKEN_ADCKEN2 = 1;         // Clock enable for ADC Unit C
            break;

        default:
            break;
    }
}

void ADC_Config(TSB_AD_TypeDef * ADx){
    MOD0_DACON_ON(ADx);                 // DAC On
    wait(3);                            // Wait 3 us
    MOD0_RCUT_OFF(ADx);                 // Normal Operation
    CLK_EXAZ0_SCLKx2N(ADx);             // SCLK period x 2n (SCLK = 40MHz)
    MOD1_MOD1(ADx, 0x306122);           // Conversion time 0.96 us (SCLK = 40 MHz)
    //MOD1_MOD1(ADx, 0x308012);         // Conversion time 0.91 us (SCLK = 30 MHz)
    //MOD1_MOD1(ADx, 0x104011);         // Conversion time 1.09 us (SCLK = 20 MHz)
}

void ADC_Conversion_Setting(TSB_AD_TypeDef * ADx){
    switch (ADxType.typex){
        case Single_Conversion:
            TSETx_TRGS0_SINGLE_CONV(ADx->TSET0);
            TSETx_TRGS0_SINGLE_CONV(ADx->TSET1);
            TSETx_TRGS0_SINGLE_CONV(ADx->TSET2);
            break;
        case Continuous_Conversion:
            TSETx_TRGS0_CONTINUOUS(ADx->TSET0);
            TSETx_TRGS0_CONTINUOUS(ADx->TSET1);
            TSETx_TRGS0_CONTINUOUS(ADx->TSET2);
            break;
        case General_Purpose:
            TSETx_TRGS0_GENERAL(ADx->TSET0);
            TSETx_TRGS0_GENERAL(ADx->TSET1);
            TSETx_TRGS0_GENERAL(ADx->TSET2);
            break;
        case PMD_Trigger:
            break;
        default:
            TSETx_TRGS0_NO_CONV(ADx->TSET0);
            TSETx_TRGS0_NO_CONV(ADx->TSET1);
            TSETx_TRGS0_NO_CONV(ADx->TSET2);
            break;
    }
    switch((intptr_t)ADx){
        case (intptr_t)TSB_ADA :
            /* Store the value of AINA18 to register TSET0 */
            TSETx_AINST0(ADx->TSET0, 0x12);     // AINA18 - PL4
            /* Store the value of AINA16 to register TSET1 */
            TSETx_AINST0(ADx->TSET1, 0x10);     // AINA16 - PL0

            /* Disable the interrupt control for the ADC */
            TSETx_ENINT0_DISABLE(ADx->TSET0);
            TSETx_ENINT0_DISABLE(ADx->TSET1);
            break;
        case (intptr_t)TSB_ADC :
            /* Store the value of AINC01 to register TSET0 */
            TSETx_AINST0(ADx->TSET0, 0x01);     // AINC01 - PJ1
            /* Store the value of AINC02 to register TSET1 */
            TSETx_AINST0(ADx->TSET1, 0x02);     // AINC02 - PJ2
            /* Store the value of AINC03 to register TSET2 */
            TSETx_AINST0(ADx->TSET2, 0x03);     // AINC03 - PJ3

            /* Disable the interrupt control for the ADC */
            TSETx_ENINT0_DISABLE(ADx->TSET0);
            TSETx_ENINT0_DISABLE(ADx->TSET1);
            TSETx_ENINT0_DISABLE(ADx->TSET2);
            break;
        default:
            break;
    }
}

void ADC_Conversion_Start(TSB_AD_TypeDef * ADx){
    CR0_ADEN_ENABLE(ADx);
    switch (ADxType.typex){
        case Single_Conversion:
            CR0_SGL_START(ADx);
            break;
        case Continuous_Conversion:
            while((getADC_ST(ADx) & 0x08) >> 4){}
            CR0_CNT_ENABLE(ADx);
            break;
        default:
            break;
    }
}

uint32_t getADC_CR0(TSB_AD_TypeDef * ADx){
    return (ADx->CR0);
}

uint32_t getADC_CR1(TSB_AD_TypeDef * ADx){
    return (ADx->CR1);
}

uint32_t getADC_ST(TSB_AD_TypeDef * ADx){
    return (ADx->ST);
}

uint32_t getADC_CLK(TSB_AD_TypeDef * ADx){
    return(ADx->CLK);
}

uint32_t getADC_MOD0(TSB_AD_TypeDef * ADx){
    return(ADx->MOD0);
}

uint32_t getADC_MOD1(TSB_AD_TypeDef * ADx){
    return(ADx->MOD1);
}

uint32_t getADC_MOD2(TSB_AD_TypeDef * ADx){
    return(ADx->MOD2);
}

uint32_t getADC_CMPEN(TSB_AD_TypeDef * ADx){
    return(ADx->CMPEN);
}

uint32_t getADC_CMPCR0(TSB_AD_TypeDef * ADx){
    return(ADx->CMPCR0);
}

uint32_t getADC_CMPCR1(TSB_AD_TypeDef * ADx){
    return(ADx->CMPCR1);
}

uint32_t getADC_CMP0(TSB_AD_TypeDef * ADx){
    return(ADx->CMP0);
}

uint32_t getADC_CMP1(TSB_AD_TypeDef * ADx){
    return(ADx->CMP1);
}

/*uint32_t getADC_EXAZSEL(TSB_AD_TypeDef * ADx){
    return(ADx->EXAZSEL);
}*/

uint32_t getADC_PSEL0(TSB_AD_TypeDef * ADx){
    return(ADx->PSEL0);
}

uint32_t getADC_PINTS0(TSB_AD_TypeDef * ADx){
    return(ADx->PINTS0);
}

uint32_t getADC_PREGS(TSB_AD_TypeDef * ADx){
    return(ADx->PREGS);
}

uint32_t getADC_PSET0(TSB_AD_TypeDef * ADx){
    return(ADx->PSET0);
}

uint32_t getADC_TSET0(TSB_AD_TypeDef * ADx){
    return(ADx->TSET0);
}

/* Changed from the original */
uint32_t getADC_REGx(TSB_AD_TypeDef * ADx, uint8_t num){
    switch (num){
        case 1:
            return (ADx->REG0);
            break;
        case 2:
            return (ADx->REG1);
            break;
        case 3:
            return (ADx->REG2);
            break;
        default :
            return 0;
            break;
    }
}

uint32_t ADC_Read(TSB_AD_TypeDef * ADx, uint8_t num){
    ADC_Conversion_Start(ADx);

    while((getADC_REGx(ADx, num) & 0x01) != 0x01){}
    while((getADC_ST(ADx) & 0x04)){}
    return ((getADC_REGx(ADx, num) & ADC_ADR0_MASK) >> 4);
}

uint32_t ADC_Read_Samples(TSB_AD_TypeDef * ADx, uint8_t num, uint16_t samples){
    int i = 0;
    uint32_t read_bits = 0;
    uint32_t sample_average = 0;
    for(i=0; i < samples; i++){
        read_bits = ADC_Read(ADx, num);
        sample_average = sample_average + read_bits;
    }
    return (sample_average/samples); 
}
