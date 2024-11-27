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

#ifndef __ADC_H__
#define __ADC_H__

#include "TMPM4KyA.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/*===================================================================*
                        Masks for Registers
*===================================================================*/
#define ADC_ADR0_MASK                           (uint32_t)(0xFFF0UL) 

/* Control Register 0 Mask */
#define CR0_CNT_MASK                            (uint32_t)(0x01UL) 
#define CR0_SGL_MASK                            (uint32_t)(0x01UL << 1) 
#define CR0_ADEN_MASK                           (uint32_t)(0x01UL << 7) 

/* Control Register 1 Mask */
#define CR1_TRGEN_MASK                          (uint32_t)(0x01UL) 
#define CR1_TRGDMEN_MASK                        (uint32_t)(0x01UL << 4) 
#define CR1_SGLDMEN_MASK                        (uint32_t)(0x01UL << 5) 
#define CR1_CNTDMEN_MASK                        (uint32_t)(0x01UL << 6) 

/* Conversion Clock Setting Register Mask */
#define CLK_VADCLK_MASK                         (uint32_t)(0x07UL)
#define CLK_EXAZ0_MASK                          (uint32_t)(0x0FUL << 3)
#define CLK_EXAZ1_MASK                          (uint32_t)(0x0FUL << 8)

/* Mode Setting Register 0 Mask */
#define MOD0_DACON_MASK                         (uint32_t)(0x01UL)
#define MOD0_RCUT_MASK                          (uint32_t)(0x01UL << 1)

/* Monitor Function Enable Register Mask */
#define CMPEN_CMP0EN_MASK                       (uint32_t)(0x01UL)
#define CMPEN_CMP1EN_MASK                       (uint32_t)(0x01UL << 1)

/* Monitor Function Setting Register 0 Mask */
#define CMPCR0_REGS0_MASK                       (uint32_t)(0x1FUL)
#define CMPCR0_ADBIG0_MASK                      (uint32_t)(0x01UL << 5)
#define CMPCR0_CMPCND0_MASK                     (uint32_t)(0x01UL << 6)
#define CMPCR0_CMPCNT0_MASK                     (uint32_t)(0x07UL << 8)

/* Monitor Function Setting Register 1 Mask */
#define CMPCR1_REGS1_MASK                       (uint32_t)(0x1FUL)
#define CMPCR1_ADBIG1_MASK                      (uint32_t)(0x01UL << 5)
#define CMPCR1_CMPCND1_MASK                     (uint32_t)(0x01UL << 6)
#define CMPCR1_CMPCNT1_MASK                     (uint32_t)(0x01UL << 8)

/* Conversion Result Comparison Register 0 Mask */
#define CMP0_AD0CMP0_MASK                       (uint32_t)(0xFFFUL << 4)
#define CMP1_AD0CMP1_MASK                       (uint32_t)(0xFFFUL << 4)

/* PMD Trigger Program Nummber Selection Register 0 Mask */
#define PSEL0_PMDS0_MASK                        (uint32_t)(0x07UL)
#define PSEL0_PENS0_MASK                        (uint32_t)(0x01UL << 7)

/* PMD Trigger Interrupt Selection Register 0 Mask */
#define PINTS0_INTSEL0_MASK                     (uint32_t)(0x03UL)

/* PMD Trigger Storage Selection Register Mask */
#define PREGS_REGSEL0_MASK                      (uint32_t)(0x07UL)
#define PREGS_REGSEL1_MASK                      (uint32_t)(0x07UL << 4)
#define PREGS_REGSEL2_MASK                      (uint32_t)(0x07UL << 8)
#define PREGS_REGSEL3_MASK                      (uint32_t)(0x07UL << 12)
#define PREGS_REGSEL4_MASK                      (uint32_t)(0x07UL << 16)
#define PREGS_REGSEL5_MASK                      (uint32_t)(0x07UL << 20)
#define PREGS_REGSEL6_MASK                      (uint32_t)(0x07UL << 24)
#define PREGS_REGSEL7_MASK                      (uint32_t)(0x07UL << 28)

/* PMD Trigger Program Register 0 Mask */
#define PSET0_AINSP00_MASK                      (uint32_t)(0x0FUL)
#define PSET0_UVWIS00_MASK                      (uint32_t)(0x03UL << 5)
#define PSET0_ENSP00_MASK                       (uint32_t)(0x01UL << 7)
#define PSET0_AINSP01_MASK                      (uint32_t)(0x1FUL << 8)
#define PSET0_UVWIS01_MASK                      (uint32_t)(0x03UL << 13)
#define PSET0_ENSP01_MASK                       (uint32_t)(0x01UL << 15)
#define PSET0_AINSP02_MASK                      (uint32_t)(0x1FUL << 16)
#define PSET0_UVWIS02_MASK                      (uint32_t)(0x03UL << 21)
#define PSET0_ENSP02_MASK                       (uint32_t)(0x01UL << 23)
#define PSET0_AINSP03_MASK                      (uint32_t)(0x1FUL << 24)
#define PSET0_UVWIS03_MASK                      (uint32_t)(0x03UL << 29)
#define PSET0_ENSP03_MASK                       (uint32_t)(0x01UL << 31)

/* General Purpose Start-Up Factor Program Register 0 Mask */
#define TSET0_AINST0_MASK                       (uint32_t)(0x1FUL)
#define TSET0_TRGS0_MASK                        (uint32_t)(0x03UL << 5)
#define TSET0_ENINT0_MASK                       (uint32_t)(0x01UL << 7)


/*===================================================================*
                        Define Registers
*===================================================================*/
/* Control Register 0 */
#define CR0_CNT_DISABLE(obj)                    ((obj)->CR0 = (uint32_t)(((obj)->CR0 & ~CR0_CNT_MASK) | 0x00UL))
#define CR0_CNT_ENABLE(obj)                     ((obj)->CR0 = (uint32_t)(((obj)->CR0 & ~CR0_CNT_MASK) | 0x01UL))

#define CR0_SGL_START(obj)                      ((obj)->CR0 = (uint32_t)(((obj)->CR0 & ~CR0_SGL_MASK) | (0x01UL << 1)))

#define CR0_ADEN_DISABLE(obj)                   ((obj)->CR0 = (uint32_t)(((obj)->CR0 & ~CR0_ADEN_MASK) | (0x00UL << 7)))
#define CR0_ADEN_ENABLE(obj)                    ((obj)->CR0 = (uint32_t)(((obj)->CR0 & ~CR0_ADEN_MASK) | (0x01UL << 7)))

/* Control Register 1 */
#define CR1_TRGEN_DISABLE(obj)                  ((obj)->CR1 = (uint32_t)(((obj)->CR1 & ~CR1_TRGEN_MASK) | 0x00UL))
#define CR1_TRGEN_ENABLE(obj)                   ((obj)->CR1 = (uint32_t)(((obj)->CR1 & ~CR1_TRGEN_MASK) | 0x01UL))

#define CR1_TRGDMEN_DISABLE(obj)                ((obj)->CR1 = (uint32_t)(((obj)->CR1 & ~CR1_TRGDMEN_MASK) | (0x00UL << 4)))
#define CR1_TRGDMEN_ENABLE(obj)                 ((obj)->CR1 = (uint32_t)(((obj)->CR1 & ~CR1_TRGDMEN_MASK) | (0x01UL << 4)))

#define CR1_SGLDMEN_DISABLE(obj)                ((obj)->CR1 = (uint32_t)(((obj)->CR1 & ~CR1_SGLDMEN_MASK) | (0x00UL << 5)))
#define CR1_SGLDMEN_ENABLE(obj)                 ((obj)->CR1 = (uint32_t)(((obj)->CR1 & ~CR1_SGLDMEN_MASK) | (0x01UL << 5)))

#define CR1_CNTDMEN_DISABLE(obj)                ((obj)->CR1 = (uint32_t)(((obj)->CR1 & ~CR1_CNTDMEN_MASK) | (0x00UL << 6)))
#define CR1_CNTDMEN_ENABLE(obj)                 ((obj)->CR1 = (uint32_t)(((obj)->CR1 & ~CR1_CNTDMEN_MASK) | (0x01UL << 6)))

/* Conversion Clock Setting Register */
#define CLK_VADCLK_ADCLK4(obj)                  ((obj)->CLK = (uint32_t)(((obj)->CLK & ~CLK_VADCLK_MASK) | 0x00UL))
#define CLK_VADCLK_ADCLK8(obj)                  ((obj)->CLK = (uint32_t)(((obj)->CLK & ~CLK_VADCLK_MASK) | 0x01UL))

#define CLK_EXAZ0_SCLKxN(obj)                   ((obj)->CLK = (uint32_t)(((obj)->CLK & ~CLK_EXAZ0_MASK) | (0x00UL << 3)))
#define CLK_EXAZ0_SCLKx2N(obj)                  ((obj)->CLK = (uint32_t)(((obj)->CLK & ~CLK_EXAZ0_MASK) | (0x01UL << 3)))
#define CLK_EXAZ0_SCLKx4N(obj)                  ((obj)->CLK = (uint32_t)(((obj)->CLK & ~CLK_EXAZ0_MASK) | (0x03UL << 3)))

#define CLK_EXAZ1_SCLKxN(obj)                   ((obj)->CLK = (uint32_t)(((obj)->CLK & ~CLK_EXAZ1_MASK) | (0x00UL << 8)))
#define CLK_EXAZ1_SCLKx2N(obj)                  ((obj)->CLK = (uint32_t)(((obj)->CLK & ~CLK_EXAZ1_MASK) | (0x01UL << 8)))
#define CLK_EXAZ1_SCLKx4N(obj)                  ((obj)->CLK = (uint32_t)(((obj)->CLK & ~CLK_EXAZ1_MASK) | (0x03UL << 8)))

/* Mode Setting Register 0 */
#define MOD0_DACON_OFF(obj)                     ((obj)->MOD0 = (uint32_t)(((obj)->MOD0 & ~MOD0_DACON_MASK) | 0x00UL))
#define MOD0_DACON_ON(obj)                      ((obj)->MOD0 = (uint32_t)(((obj)->MOD0 & ~MOD0_DACON_MASK) | 0x01UL))

#define MOD0_RCUT_OFF(obj)                      ((obj)->MOD0 = (uint32_t)(((obj)->MOD0 & ~MOD0_RCUT_MASK) | (0x00UL << 1)))
#define MOD0_RCUT_ON(obj)                       ((obj)->MOD0 = (uint32_t)(((obj)->MOD0 & ~MOD0_RCUT_MASK) | (0x01UL << 1)))

/* Mode Setting Register 1 */
#define MOD1_MOD1(obj, param)                   ((obj)->MOD1 = (uint32_t)(param))

/* Mode Setting Register 2 */
#define MOD2_MOD2(obj, param)                   ((obj)->MOD2 = (uint32_t)(param))

/* Monitor Function Enable Register */
#define CMPEN_CMP0EN_DISABLE(obj)               ((obj)->CMPEN = (uint32_t)(((obj)->CMPEN & ~CMPEN_CMP0EN_MASK) | (0x00UL)))
#define CMPEN_CMP0EN_ENABLE(obj)                ((obj)->CMPEN = (uint32_t)(((obj)->CMPEN & ~CMPEN_CMP0EN_MASK) | (0x01UL)))

#define CMPEN_CMP1EN_DISABLE(obj)               ((obj)->CMPEN = (uint32_t)(((obj)->CMPEN & ~CMPEN_CMP1EN_MASK) | (0x00UL << 1)))
#define CMPEN_CMP1EN_ENABLE(obj)                ((obj)->CMPEN = (uint32_t)(((obj)->CMPEN & ~CMPEN_CMP1EN_MASK) | (0x01UL << 1)))

/* Monitor Function Setting Register 0 */
#define CMPCR0_REGS0(obj, param)                ((obj)->CMPCR0 = (uint32_t)(((obj)->CMPCR0 & ~CMPCR0_REGS0_MASK) | (param)))

#define CMPCR0_ADBIG0(obj, param)               ((obj)->CMPCR0 = (uint32_t)(((obj)->CMPCR0 & ~CMPCR0_ADBIG0_MASK) | (param << 5)))

#define CMPCR0_CMPCND0_CONTINUOUS(obj)          ((obj)->CMPCR0 = (uint32_t)(((obj)->CMPCR0 & ~CMPCR0_CMPCND0_MASK) | (0x00UL << 6)))
#define CMPCR0_CMPCND0_ACCUMULATED(obj)         ((obj)->CMPCR0 = (uint32_t)(((obj)->CMPCR0 & ~CMPCR0_CMPCND0_MASK) | (0x01UL << 6)))

#define CMPCR0_CMPCNT0_CONTINUOUS(obj)          ((obj)->CMPCR0 = (uint32_t)(((obj)->CMPCR0 & ~CMPCR0_CMPCNT0_MASK) | (0x00UL << 8)))
#define CMPCR0_CMPCNT0_ACCUMULATED(obj)         ((obj)->CMPCR0 = (uint32_t)(((obj)->CMPCR0 & ~CMPCR0_CMPCNT0_MASK) | (0x01UL << 8)))

/* Monitor Function Setting Register 1 */
#define CMPCR1_REGS1(obj, param)                ((obj)->CMPCR1 = (uint32_t)(((obj)->CMPCR1 & ~CMPCR1_REGS1_MASK) | (param)))

#define CMPCR1_ADBIG1(obj, param)               ((obj)->CMPCR1 = (uint32_t)(((obj)->CMPCR1 & ~CMPCR1_ADBIG1_MASK) | (param)))

#define CMPCR1_CMPCND1_CONTINUOUS(obj)          ((obj)->CMPCR1 = (uint32_t)(((obj)->CMPCR1 & ~CMPCR1_CMPCND1_MASK) | (0x00UL << 6)))
#define CMPCR1_CMPCND1_ACCUMULATED(obj)         ((obj)->CMPCR1 = (uint32_t)(((obj)->CMPCR1 & ~CMPCR1_CMPCND1_MASK) | (0x01UL << 6)))

#define CMPCR1_CMPCNT1_CONTINUOUS(obj)          ((obj)->CMPCR1 = (uint32_t)(((obj)->CMPCR1 & ~CMPCR1_CMPCNT1_MASK) | (0x00UL << 8)))
#define CMPCR1_CMPCNT1_ACCUMULATED(obj)         ((obj)->CMPCR1 = (uint32_t)(((obj)->CMPCR1 & ~CMPCR1_CMPCNT1_MASK) | (0x01UL << 8)))

/* Conversion Result Comparison Register 0 */
#define CMP0_AD0CMP0(obj, param)                ((obj)->CMP0 = (uint32_t)(((obj)->CMP0 & ~CMP0_AD0CMP0_MASK) | (param)))

#define CMP1_AD0CMP1(obj, param)                ((obj)->CMP1 = (uint32_t)(((obj)->CMP1 & ~CMP1_AD0CMP1_MASK) | (param)))

/* AIN Sampling Time Selection Register */
#define EXAZSEL_EXAZSEL(obj, param)             ((obj)->EXAZSEL = (uint32_t)(param))

/* PMD Trigger Program Nummber Selection Register 0 Mask */
#define PSEL0_PMDS0(obj, param)                 ((obj)->PSEL0 = (uint32_t)(((obj)->PSEL0 & ~PSEL0_PMDS0_MASK) | (param)))

#define PSEL0_PENS0_DISABLE(obj)                ((obj)->PSEL0 = (uint32_t)(((obj)->PSEL0 & ~PSEL0_PENS0_MASK) | (0x00UL << 7)))
#define PSEL0_PENS0_ENABLE(obj)                 ((obj)->PSEL0 = (uint32_t)(((obj)->PSEL0 & ~PSEL0_PENS0_MASK) | (0x01UL << 7)))

/* PMD Trigger Interrupt Selection Register 0 */
#define PINTS0_INTSEL0_NO_INT(obj)              ((obj)->PINTS0 = (uint32_t)(((obj)->PINTS0 & ~PINTS0_INTSEL0_MASK) | (0x00UL)))
#define PINTS0_INTSEL0_INTADA(obj)              ((obj)->PINTS0 = (uint32_t)(((obj)->PINTS0 & ~PINTS0_INTSEL0_MASK) | (0x01UL)))
#define PINTS0_INTSEL0_INTADB(obj)              ((obj)->PINTS0 = (uint32_t)(((obj)->PINTS0 & ~PINTS0_INTSEL0_MASK) | (0x02UL)))

/* PMD Trigger Storage Selection Register */
#define PREGS_REGSEL0(obj, param)               ((obj)->PREGS = (uint32_t)(((obj)->PREGS & ~PREGS_REGSEL0_MASK) | (param)))
#define PREGS_REGSEL1(obj, param)               ((obj)->PREGS = (uint32_t)(((obj)->PREGS & ~PREGS_REGSEL1_MASK) | (param)))
#define PREGS_REGSEL2(obj, param)               ((obj)->PREGS = (uint32_t)(((obj)->PREGS & ~PREGS_REGSEL2_MASK) | (param)))
#define PREGS_REGSEL3(obj, param)               ((obj)->PREGS = (uint32_t)(((obj)->PREGS & ~PREGS_REGSEL3_MASK) | (param)))
#define PREGS_REGSEL4(obj, param)               ((obj)->PREGS = (uint32_t)(((obj)->PREGS & ~PREGS_REGSEL4_MASK) | (param)))
#define PREGS_REGSEL5(obj, param)               ((obj)->PREGS = (uint32_t)(((obj)->PREGS & ~PREGS_REGSEL5_MASK) | (param)))
#define PREGS_REGSEL6(obj, param)               ((obj)->PREGS = (uint32_t)(((obj)->PREGS & ~PREGS_REGSEL6_MASK) | (param)))
#define PREGS_REGSEL7(obj, param)               ((obj)->PREGS = (uint32_t)(((obj)->PREGS & ~PREGS_REGSEL7_MASK) | (param)))

/* PMD Trigger Program Register 0 */
/* reg should be given as a pointer, example: ADA->PSET8 */
#define PSETx_AINSP00(reg, param)               (reg = (uint32_t)((reg & ~PSET0_AINSP00_MASK) | (param)))

#define PSETx_UVWIS00_U(reg)                    (reg = (uint32_t)((reg & ~PSET0_UVWIS00_MASK) | (0x01UL << 5)))
#define PSETx_UVWIS00_V(reg)                    (reg = (uint32_t)((reg & ~PSET0_UVWIS00_MASK) | (0x02UL << 5)))
#define PSETx_UVWIS00_W(reg)                    (reg = (uint32_t)((reg & ~PSET0_UVWIS00_MASK) | (0x03UL << 5)))

#define PSETx_ENSP00_DISABLE(reg)               (reg = (uint32_t)((reg & ~PSET0_ENSP00_MASK) | (0x00UL << 7)))
#define PSETx_ENSP00_ENABLE(reg)                (reg = (uint32_t)((reg & ~PSET0_ENSP00_MASK) | (0x01UL << 7)))

#define PSETx_AINSP01(reg, param)               (reg = (uint32_t)((reg & ~PSET0_AINSP01_MASK) | (param << 8)))

#define PSETx_UVWIS01_U(reg)                    (reg = (uint32_t)((reg & ~PSET0_UVWIS01_MASK) | (0x01UL << 13)))
#define PSETx_UVWIS01_V(reg)                    (reg = (uint32_t)((reg & ~PSET0_UVWIS01_MASK) | (0x02UL << 13)))
#define PSETx_UVWIS01_W(reg)                    (reg = (uint32_t)((reg & ~PSET0_UVWIS01_MASK) | (0x03UL << 13)))

#define PSETx_ENSP01_DISABLE(reg)               (reg = (uint32_t)((reg & ~PSET0_ENSP01_MASK) | (0x00UL << 15)))
#define PSETx_ENSP01_ENABLE(reg)                (reg = (uint32_t)((reg & ~PSET0_ENSP01_MASK) | (0x01UL << 15)))

#define PSETx_AINSP02(reg, param)               (reg = (uint32_t)((reg & ~PSET0_AINSP02_MASK) | (param << 16)))

#define PSETx_UVWIS02_U(reg)                    (reg = (uint32_t)((reg & ~PSET0_UVWIS02_MASK) | (0x01UL << 21)))
#define PSETx_UVWIS02_V(reg)                    (reg = (uint32_t)((reg & ~PSET0_UVWIS02_MASK) | (0x02UL << 21)))
#define PSETx_UVWIS02_W(reg)                    (reg = (uint32_t)((reg & ~PSET0_UVWIS02_MASK) | (0x03UL << 21)))

#define PSETx_ENSP02_DISABLE(reg)               (reg = (uint32_t)((reg & ~PSET0_ENSP02_MASK) | (0x00UL << 23)))
#define PSETx_ENSP02_ENABLE(reg)                (reg = (uint32_t)((reg & ~PSET0_ENSP02_MASK) | (0x01UL << 23)))

#define PSETx_AINSP03(reg, param)               (reg = (uint32_t)((reg & ~PSET0_AINSP03_MASK) | (param << 24)))

#define PSETx_UVWIS03_U(reg)                    (reg = (uint32_t)((reg & ~PSET0_UVWIS03_MASK) | (0x01UL << 29)))
#define PSETx_UVWIS03_V(reg)                    (reg = (uint32_t)((reg & ~PSET0_UVWIS03_MASK) | (0x02UL << 29)))
#define PSETx_UVWIS03_W(reg)                    (reg = (uint32_t)((reg & ~PSET0_UVWIS03_MASK) | (0x03UL << 29)))

#define PSETx_ENSP03_DISABLE(reg)               (reg = (uint32_t)((reg & ~PSET0_ENSP03_MASK) | (0x00UL << 31)))
#define PSETx_ENSP03_ENABLE(reg)                (reg = (uint32_t)((reg & ~PSET0_ENSP03_MASK) | (0x01UL << 31)))

/* General Purpose Start-Up Factor Program Register 0 */
/* reg should be given as a pointer, example: ADB->TSET5 */
#define TSETx_AINST0(reg, param)                (reg = (uint32_t)((reg & ~TSET0_AINST0_MASK) | (param)))

#define TSETx_TRGS0_NO_CONV(reg)                (reg = (uint32_t)((reg & ~TSET0_TRGS0_MASK) | (0x00UL << 5)))
#define TSETx_TRGS0_CONTINUOUS(reg)             (reg = (uint32_t)((reg & ~TSET0_TRGS0_MASK) | (0x01UL << 5)))
#define TSETx_TRGS0_SINGLE_CONV(reg)            (reg = (uint32_t)((reg & ~TSET0_TRGS0_MASK) | (0x02UL << 5)))
#define TSETx_TRGS0_GENERAL(reg)                (reg = (uint32_t)((reg & ~TSET0_TRGS0_MASK) | (0x03UL << 5)))

#define TSETx_ENINT0_DISABLE(reg)               (reg = (uint32_t)((reg & ~TSET0_ENINT0_MASK) | (0x00UL << 7)))
#define TSETx_ENINT0_ENABLE(reg)                (reg = (uint32_t)((reg & ~TSET0_ENINT0_MASK) | (0x01UL << 7)))


/*===================================================================*
                  Functions declaration for ADCx
*===================================================================*/
void ADC_Init(TSB_AD_TypeDef * ADx);
void ADC_CG_Config(TSB_AD_TypeDef * ADx);
void ADC_Config(TSB_AD_TypeDef * ADx);
void ADC_Conversion_Setting(TSB_AD_TypeDef * ADx);
void ADC_Conversion_Start(TSB_AD_TypeDef * ADx);
uint32_t ADC_Read(TSB_AD_TypeDef * ADx, uint8_t num);
uint32_t ADC_Read_Samples(TSB_AD_TypeDef * ADx, uint8_t num, uint16_t samples);

uint32_t getADC_CR0(TSB_AD_TypeDef * ADx); 
uint32_t getADC_CR1(TSB_AD_TypeDef * ADx);
uint32_t getADC_ST(TSB_AD_TypeDef * ADx);
uint32_t getADC_CLK(TSB_AD_TypeDef * ADx);
uint32_t getADC_MOD0(TSB_AD_TypeDef * ADx);
uint32_t getADC_MOD1(TSB_AD_TypeDef * ADx);
uint32_t getADC_MOD2(TSB_AD_TypeDef * ADx);
uint32_t getADC_CMPEN(TSB_AD_TypeDef * ADx);
uint32_t getADC_CMPCR0(TSB_AD_TypeDef * ADx);
uint32_t getADC_CMPCR1(TSB_AD_TypeDef * ADx);
uint32_t getADC_CMP0(TSB_AD_TypeDef * ADx);
uint32_t getADC_CMP1(TSB_AD_TypeDef * ADx);
//uint32_t getADC_EXAZSEL(TSB_AD_TypeDef * ADx);
uint32_t getADC_PSEL0(TSB_AD_TypeDef * ADx);
uint32_t getADC_PINTS0(TSB_AD_TypeDef * ADx);
uint32_t getADC_PREGS(TSB_AD_TypeDef * ADx);
uint32_t getADC_REGx(TSB_AD_TypeDef * ADx, uint8_t num);

/*===================================================================*
                        Typedef Structures
*===================================================================*/
enum _conversionType
{
    Single_Conversion,
    Continuous_Conversion,
    General_Purpose,
    PMD_Trigger
};

typedef struct
{
    enum _conversionType typex;
} ADxConversionType;

#ifdef __cplusplus
}
#endif

#endif  /* __TSB_ADC_H__ */


