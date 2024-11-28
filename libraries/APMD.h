/**
 *******************************************************************************
 * @file    APMD.h
 * @brief   Toshiba APMD Control for motor
 *          TOSHIBA 'TMPM4KNA' Group
 * @version V1.0.0.0
 * $Date:: 2022-09-19 #$
 * 
 * @author Hugo Rodrigues
 *******************************************************************************
 */

#ifndef __APMD_H__
#define __APMD_H__

#include "TMPM4KyA.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/*===================================================================*
      Masks for Registers
 *===================================================================*/
/* Port Output Mode Mask */
#define PORTMD_PORTMD                               (uint32_t)(0x03UL) 

/* PMD Mode Selection Mask */
#define MODESEL_MODESEL0_MASK                       (uint32_t)(0x01UL)
#define MODESEL_MODESEL1_MASK                       (uint32_t)(0x02UL)
#define MODESEL_MODESEL2_MASK                       (uint32_t)(0x04UL)
#define MODESEL_MODESEL3_MASK                       (uint32_t)(0x08UL)
#define MODESEL_DCMPEN_MASK                         (uint32_t)(0x80UL)

/* PMD Control Mask */
#define MDCR_INTPRD_MASK                            (uint32_t)(0x03UL << 1)
#define MDCR_PINT_MASK                              (uint32_t)(0x01UL << 3)
#define MDCR_DTYMD_MASK                             (uint32_t)(0x01UL << 4)
#define MDCR_SYNTMD_MASK                            (uint32_t)(0x01UL << 5)
#define MDCR_DCMEN_MASK                             (uint32_t)(0x01UL << 6)
#define MDCR_DTCREN_MASK                            (uint32_t)(0x01UL << 7)
#define MDCR_DSYNCS_MASK                            (uint32_t)(0x03UL << 8)
#define MDCR_UPWMMD_MASK                            (uint32_t)(0x03UL << 10)
#define MDCR_VPWMMD_MASK                            (uint32_t)(0x03UL << 12)
#define MDCR_WPWMMD_MASK                            (uint32_t)(0x03UL << 14)

/* PMD Output Setting Mask */
#define MDPOT_PSYNCS_MASK                           (uint32_t)(0x03UL) 
#define MDPOT_POLL_MASK                             (uint32_t)(0x01UL << 2)
#define MDPOT_POLH_MASK                             (uint32_t)(0x01UL << 3)
#define MDPOT_SYNCS_MASK                            (uint32_t)(0x03UL << 8)

/* PMD Conduction Control Mask */
#define MDOUT_UOC_MASK                              (uint32_t)(0x03UL)
#define MDOUT_VOC_MASK                              (uint32_t)(0x03UL << 2)
#define MDOUT_WOC_MASK                              (uint32_t)(0x03UL << 4)
#define MDOUT_UPWM_MASK                             (uint32_t)(0x01UL << 8)
#define MDOUT_VPWM_MASK                             (uint32_t)(0x01UL << 9)
#define MDOUT_WPWM_MASK                             (uint32_t)(0x01UL << 10)

/* PMD EMG Control Mask */
#define EMGCR_EMGEN_MASK                            (uint32_t)(0x01UL)
#define EMGCR_EMGRS_MASK                            (uint32_t)(0x01UL << 1)
#define EMGCR_EMGISEL_MASK                          (uint32_t)(0x01UL << 2)
#define EMGCR_INHEN_MASK                            (uint32_t)(0x01UL << 5)
#define EMGCR_EMGIPOL_MASK                          (uint32_t)(0x01UL << 7)
#define EMGCR_EMGMD_MASK                            (uint32_t)(0x03UL << 3)
#define EMGCR_EMGCNT_MASK                           (uint32_t)(0x1FUL << 8)

/* PMD OVV Control Mask */
#define OVVCR_OVVEN_MASK                            (uint32_t)(0x01UL)
#define OVVCR_OVVRS_MASK                            (uint32_t)(0x01UL << 1)
#define OVVCR_OVVISEL_MASK                          (uint32_t)(0x01UL << 2)
#define OVVCR_OVVMD_MASK                            (uint32_t)(0x03UL << 3)
#define OVVCR_ADIN0EN_MASK                          (uint32_t)(0x01UL << 5)
#define OVVCR_ADIN1EN_MASK                          (uint32_t)(0x01UL << 6)
#define OVVCR_OVVIPOL_MASK                          (uint32_t)(0x01UL << 7)
#define OVVCR_OVVCNT_MASK                           (uint32_t)(0x1FUL << 8)
#define OVVCR_OVVRSMD_MASK                          (uint32_t)(0x01UL << 15)

/* PMD Trigger Control Mask */
#define TRGCR_TRG0MD_MASK                           (uint32_t)(0x07UL)
#define TRGCR_TRG0BE_MASK                           (uint32_t)(0x01UL << 3)
#define TRGCR_TRG1MD_MASK                           (uint32_t)(0x07UL << 4)
#define TRGCR_TRG1BE_MASK                           (uint32_t)(0x01UL << 7)
#define TRGCR_TRG2MD_MASK                           (uint32_t)(0x07UL << 8)
#define TRGCR_TRG2BE_MASK                           (uint32_t)(0x01UL << 11)
#define TRGCR_TRG3MD_MASK                           (uint32_t)(0x07UL << 1)
#define TRGCR_TRG3BE_MASK                           (uint32_t)(0x01UL << 15)
#define TRGCR_CARSEL_MASK                           (uint32_t)(0x01UL << 16)

/* PMD Trigger Update Timing Setting Mask */
#define TRGSYNCR_TSYNCS_MASK                        (uint32_t)(0x03UL)

/* PMD Trigger Output Mode Setting Mask */
#define TRGMD_EMGTGE_MASK                           (uint32_t)(0x01UL)
#define TRGMD_TRGOUT_MASK                           (uint32_t)(0x01UL << 1)

/* PMD Trigger Output Selection Mask */
#define TRGSEL_TRGSEL_MASK                          (uint32_t)(0x07UL)

/* PMD Intermediate Buffer Control Mask */
#define MBUFCR_BUFCTR_MASK                          (uint32_t)(0x07UL)

/* PMD Synchronization Control Mask */
#define SYNCCR_PWMSMD_MASK                          (uint32_t)(0x01UL)
#define SYNCCR_EMGSMD_MASK                          (uint32_t)(0x03UL << 4)
#define SYNCCR_OVVSMD_MASK                          (uint32_t)(0x03UL << 6)

/* PMD Debug Output Control Mask */
#define DBGOUTCR_DBGEN_MASK                         (uint32_t)(0x01UL)
#define DBGOUTCR_DBGMD_MASK                         (uint32_t)(0x03UL << 1)
#define DBGOUTCR_IADAEN_MASK                        (uint32_t)(0x01UL << 3)
#define DBGOUTCR_IADBEN_MASK                        (uint32_t)(0x01UL << 4)
#define DBGOUTCR_IADCEN_MASK                        (uint32_t)(0x01UL << 5)
#define DBGOUTCR_IADDEN_MASK                        (uint32_t)(0x01UL << 6)
#define DBGOUTCR_IADEEN_MASK                        (uint32_t)(0x01UL << 7)
#define DBGOUTCR_IPMDEN_MASK                        (uint32_t)(0x01UL << 8)
#define DBGOUTCR_IEMGEN_MASK                        (uint32_t)(0x01UL << 9)
#define DBGOUTCR_IOVVEN_MASK                        (uint32_t)(0x01UL << 10)
#define DBGOUTCR_IVEEN_MASK                         (uint32_t)(0x01UL << 11)
#define DBGOUTCR_IENCEN_MASK                        (uint32_t)(0x01UL << 12)
#define DBGOUTCR_TRG0EN_MASK                        (uint32_t)(0x01UL << 16)
#define DBGOUTCR_TRG1EN_MASK                        (uint32_t)(0x01UL << 17)
#define DBGOUTCR_TRG2EN_MASK                        (uint32_t)(0x01UL << 18)
#define DBGOUTCR_TRG3EN_MASK                        (uint32_t)(0x01UL << 19)
#define DBGOUTCR_TRG4EN_MASK                        (uint32_t)(0x01UL << 20)
#define DBGOUTCR_TRG5EN_MASK                        (uint32_t)(0x01UL << 21)
#define DBGOUTCR_INIFF_MASK                         (uint32_t)(0x01UL << 31)

/*===================================================================*
      Define Registers
 *===================================================================*/
/* PMD Enable Register */
#define MDEN_PWMEN_DISABLE(obj)                     ((obj)->MDEN = (uint32_t)(0x00UL))
#define MDEN_PWMEN_ENABLE(obj)                      ((obj)->MDEN = (uint32_t)(0x01UL))

/* Port Output Mode Register */
#define PORTMD_UPHIGH_LPHIGH(obj)                   ((obj)->PORTMD = (uint32_t)(((obj)->PORTMD & ~PORTMD_PORTMD) | 0x00UL))
#define PORTMD_UPHIGH_LPPMD(obj)                    ((obj)->PORTMD = (uint32_t)(((obj)->PORTMD & ~PORTMD_PORTMD) | 0x01UL))
#define PORTMD_UPPMD_LPHIGH(obj)                    ((obj)->PORTMD = (uint32_t)(((obj)->PORTMD & ~PORTMD_PORTMD) | 0x02UL))
#define PORTMD_UPPMD_LPPMD(obj)                     ((obj)->PORTMD = (uint32_t)(((obj)->PORTMD & ~PORTMD_PORTMD) | 0x03UL))

/* Mode Selection Register */
#define MODESEL_MDSEL0_BUS(obj)                     ((obj)->MODESEL = (uint32_t)(((obj)->MODESEL & ~MODESEL_MODESEL0_MASK) | 0x00UL))
#define MODESEL_MDSEL0_VE(obj)                      ((obj)->MODESEL = (uint32_t)(((obj)->MODESEL & ~MODESEL_MODESEL0_MASK) | 0x01UL))

#define MODESEL_MDSEL1_BUS(obj)                     ((obj)->MODESEL = (uint32_t)(((obj)->MODESEL & ~MODESEL_MODESEL1_MASK) | (0x00UL << 1)))
#define MODESEL_MDSEL1_VE(obj)                      ((obj)->MODESEL = (uint32_t)(((obj)->MODESEL & ~MODESEL_MODESEL1_MASK) | (0x01UL << 1)))

#define MODESEL_MDSEL2_BUS(obj)                     ((obj)->MODESEL = (uint32_t)(((obj)->MODESEL & ~MODESEL_MODESEL2_MASK) | (0x00UL << 2)))
#define MODESEL_MDSEL2_VE(obj)                      ((obj)->MODESEL = (uint32_t)(((obj)->MODESEL & ~MODESEL_MODESEL2_MASK) | (0x01UL << 2)))

#define MODESEL_MDSEL3_BUS(obj)                     ((obj)->MODESEL = (uint32_t)(((obj)->MODESEL & ~MODESEL_MODESEL3_MASK) | (0x00UL << 3)))
#define MODESEL_MDSEL3_VE(obj)                      ((obj)->MODESEL = (uint32_t)(((obj)->MODESEL & ~MODESEL_MODESEL3_MASK) | (0x01UL << 3)))

#define MODESEL_DCMPEN_DISABLE(obj)                 ((obj)->MODESEL = (uint32_t)(((obj)->MODESEL & ~MODESEL_DCMPEN_MASK) | (0x00UL << 7)))
#define MODESEL_DCMPEN_ENABLE(obj)                  ((obj)->MODESEL = (uint32_t)(((obj)->MODESEL & ~MODESEL_DCMPEN_MASK) | (0x01UL << 7)))

/* PMD Control Register */
#define MDCR_INTPRD_HALFPERIOD(obj)                 ((obj)->MDCR = (uint32_t)(((obj)->MDCR & ~MDCR_INTPRD_MASK) | (0x00U << 1)))
#define MDCR_INTPRD_ONEPERIOD(obj)                  ((obj)->MDCR = (uint32_t)(((obj)->MDCR & ~MDCR_INTPRD_MASK) | (0x01U << 1)))
#define MDCR_INTPRD_TWOPERIOD(obj)                  ((obj)->MDCR = (uint32_t)(((obj)->MDCR & ~MDCR_INTPRD_MASK) | (0x02U << 1)))
#define MDCR_INTPRD_FOURPERIOD(obj)                 ((obj)->MDCR = (uint32_t)(((obj)->MDCR & ~MDCR_INTPRD_MASK) | (0x03U << 1)))

#define MDCR_PINT_CENTER(obj)                       ((obj)->MDCR = (uint32_t)(((obj)->MDCR & ~MDCR_PINT_MASK) | (0x00UL << 3)))
#define MDCR_PINT_END(obj)                          ((obj)->MDCR = (uint32_t)(((obj)->MDCR & ~MDCR_PINT_MASK) | (0x01UL << 3)))

#define MDCR_DTYMD_COMMON(obj)                      ((obj)->MDCR = (uint32_t)(((obj)->MDCR & ~MDCR_DTYMD_MASK) | (0x00UL << 4)))
#define MDCR_DTYMD_INDEP(obj)                       ((obj)->MDCR = (uint32_t)(((obj)->MDCR & ~MDCR_DTYMD_MASK) | (0x01UL << 4)))

#define MDCR_SYNTMD_OUT0(obj)                       ((obj)->MDCR = (uint32_t)(((obj)->MDCR & ~MDCR_SYNTMD_MASK) | (0x00UL << 5)))
#define MDCR_SYNTMD_OUT1(obj)                       ((obj)->MDCR = (uint32_t)(((obj)->MDCR & ~MDCR_SYNTMD_MASK) | (0x01UL << 5)))

#define MDCR_DCMEN_DISABLE(obj)                     ((obj)->MDCR = (uint32_t)(((obj)->MDCR & ~MDCR_DCMEN_MASK) | (0x00UL << 6)))
#define MDCR_DCMEN_ENABLE(obj)                      ((obj)->MDCR = (uint32_t)(((obj)->MDCR & ~MDCR_DCMEN_MASK) | (0x01UL << 6)))

#define MDCR_DTCREN_DISABLE(obj)                    ((obj)->MDCR = (uint32_t)(((obj)->MDCR & ~MDCR_DTCREN_MASK) | (0x00UL << 7)))
#define MDCR_DTCREN_ENABLE(obj)                     ((obj)->MDCR = (uint32_t)(((obj)->MDCR & ~MDCR_DTCREN_MASK) | (0x01UL << 7)))

#define MDCR_DSYNCS_INTPERIOD(obj)                  ((obj)->MDCR = (uint32_t)(((obj)->MDCR & ~MDCR_DSYNCS_MASK) | (0x00U << 8)))
#define MDCR_DSYNCS_CENTER(obj)                     ((obj)->MDCR = (uint32_t)(((obj)->MDCR & ~MDCR_DSYNCS_MASK) | (0x01U << 8)))
#define MDCR_DSYNCS_END(obj)                        ((obj)->MDCR = (uint32_t)(((obj)->MDCR & ~MDCR_DSYNCS_MASK) | (0x02U << 8)))
#define MDCR_DSYNCS_CENTER_END(obj)                 ((obj)->MDCR = (uint32_t)(((obj)->MDCR & ~MDCR_DSYNCS_MASK) | (0x03U << 8)))

#define MDCR_UPWMMD_SAWTOOTH(obj)                   ((obj)->MDCR = (uint32_t)(((obj)->MDCR & ~MDCR_UPWMMD_MASK) | (0x00U << 10)))
#define MDCR_UPWMMD_TRIANGLE(obj)                   ((obj)->MDCR = (uint32_t)(((obj)->MDCR & ~MDCR_UPWMMD_MASK) | (0x01U << 10)))
#define MDCR_UPWMMD_SAWTOOTH_REV(obj)               ((obj)->MDCR = (uint32_t)(((obj)->MDCR & ~MDCR_UPWMMD_MASK) | (0x02U << 10)))
#define MDCR_UPWMMD_TRIANGLE_REV(obj)               ((obj)->MDCR = (uint32_t)(((obj)->MDCR & ~MDCR_UPWMMD_MASK) | (0x03U << 10)))

#define MDCR_VPWMMD_SAWTOOTH(obj)                   ((obj)->MDCR = (uint32_t)(((obj)->MDCR & ~MDCR_VPWMMD_MASK) | (0x00U << 12)))
#define MDCR_VPWMMD_TRIANGLE(obj)                   ((obj)->MDCR = (uint32_t)(((obj)->MDCR & ~MDCR_VPWMMD_MASK) | (0x01U << 12)))
#define MDCR_VPWMMD_SAWTOOTH_REV(obj)               ((obj)->MDCR = (uint32_t)(((obj)->MDCR & ~MDCR_VPWMMD_MASK) | (0x02U << 12)))
#define MDCR_VPWMMD_TRIANGLE_REV(obj)               ((obj)->MDCR = (uint32_t)(((obj)->MDCR & ~MDCR_VPWMMD_MASK) | (0x03U << 12)))

#define MDCR_WPWMMD_SAWTOOTH(obj)                   ((obj)->MDCR = (uint32_t)(((obj)->MDCR & ~MDCR_WPWMMD_MASK) | (0x00U << 14)))
#define MDCR_WPWMMD_TRIANGLE(obj)                   ((obj)->MDCR = (uint32_t)(((obj)->MDCR & ~MDCR_WPWMMD_MASK) | (0x01U << 14)))
#define MDCR_WPWMMD_SAWTOOTH_REV(obj)               ((obj)->MDCR = (uint32_t)(((obj)->MDCR & ~MDCR_WPWMMD_MASK) | (0x02U << 14)))
#define MDCR_WPWMMD_TRIANGLE_REV(obj)               ((obj)->MDCR = (uint32_t)(((obj)->MDCR & ~MDCR_WPWMMD_MASK) | (0x03U << 14)))

/* PMD PWM Frequency Register */
#define PWMCR_RATE(obj, param)                      ((obj)->RATE = (uint32_t)(param))

/* PMD PWM Duty Comparison U Register */
#define PWMCR_CMPU(obj, param)                      ((obj)->CMPU = (uint32_t)(param))

/* PMD PWM Duty Comparison V Register */
#define PWMCR_CMPV(obj, param)                      ((obj)->CMPV = (uint32_t)(param))

/* PMD PWM Duty Comparison W Register */
#define PWMCR_CMPW(obj, param)                      ((obj)->CMPW = (uint32_t)(param))

/* PMD V-Phase Phase Difference Register */
#define VPWMPH_CMPV(obj, param)                     ((obj)->VPWMPH = (uint32_t)(param))

/* PMD W-Phase Phase Difference Register */
#define WPWMPH_CMPW(obj, param)                     ((obj)->WPWMPH = (uint32_t)(param))

/* PMD PMD Output Setting Register */
#define MDPOT_PSYNCS_ASYNC(obj)                     ((obj)->MDPOT = (uint32_t)(((obj)->MDPOT & ~MDPOT_PSYNCS_MASK) | (0x00U)))
#define MDPOT_PSYNCS_CENTER(obj)                    ((obj)->MDPOT = (uint32_t)(((obj)->MDPOT & ~MDPOT_PSYNCS_MASK) | (0x01U)))
#define MDPOT_PSYNCS_END(obj)                       ((obj)->MDPOT = (uint32_t)(((obj)->MDPOT & ~MDPOT_PSYNCS_MASK) | (0x02U)))
#define MDPOT_PSYNCS_CENTER_END(obj)                ((obj)->MDPOT = (uint32_t)(((obj)->MDPOT & ~MDPOT_PSYNCS_MASK) | (0x03U)))

#define MDPOT_POLL_LOW(obj)                         ((obj)->MDPOT = (uint32_t)(((obj)->MDPOT & ~MDPOT_POLL_MASK) | (0x00U << 2)))
#define MDPOT_POLL_HIGH(obj)                        ((obj)->MDPOT = (uint32_t)(((obj)->MDPOT & ~MDPOT_POLL_MASK) | (0x01U << 2)))

#define MDPOT_POLH_LOW(obj)                         ((obj)->MDPOT = (uint32_t)(((obj)->MDPOT & ~MDPOT_POLH_MASK) | (0x00U << 3)))
#define MDPOT_POLH_HIGH(obj)                        ((obj)->MDPOT = (uint32_t)(((obj)->MDPOT & ~MDPOT_POLH_MASK) | (0x01U << 3)))

#define MDPOT_SYNCS_ASYNC(obj)                      ((obj)->MDPOT = (uint32_t)(((obj)->MDPOT & ~MDPOT_SYNCS_MASK) | (0x00U << 8)))
#define MDPOT_SYNCS_AENC(obj)                       ((obj)->MDPOT = (uint32_t)(((obj)->MDPOT & ~MDPOT_SYNCS_MASK) | (0x01U << 8)))
#define MDPOT_SYNCS_GENERAL(obj)                    ((obj)->MDPOT = (uint32_t)(((obj)->MDPOT & ~MDPOT_SYNCS_MASK) | (0x02U << 8)))
#define MDPOT_SYNCS_MCMP(obj)                       ((obj)->MDPOT = (uint32_t)(((obj)->MDPOT & ~MDPOT_SYNCS_MASK) | (0x03U << 8)))

/* PMD Conduction Control Register */
#define MDOUT_UOC_LOW_LOW(obj)                      ((obj)->MDOUT = (uint32_t)(((obj)->MDOUT & ~MDOUT_UOC_MASK) | (0x00U)))
#define MDOUT_UOC_LOW_HIGH(obj)                     ((obj)->MDOUT = (uint32_t)(((obj)->MDOUT & ~MDOUT_UOC_MASK) | (0x01U)))
#define MDOUT_UOC_HIGH_LOW(obj)                     ((obj)->MDOUT = (uint32_t)(((obj)->MDOUT & ~MDOUT_UOC_MASK) | (0x02U)))
#define MDOUT_UOC_HIGH_HIGH(obj)                    ((obj)->MDOUT = (uint32_t)(((obj)->MDOUT & ~MDOUT_UOC_MASK) | (0x03U)))

#define MDOUT_VOC_LOW_LOW(obj)                      ((obj)->MDOUT = (uint32_t)(((obj)->MDOUT & ~MDOUT_VOC_MASK) | (0x00U << 2)))
#define MDOUT_VOC_LOW_HIGH(obj)                     ((obj)->MDOUT = (uint32_t)(((obj)->MDOUT & ~MDOUT_VOC_MASK) | (0x01U << 2)))
#define MDOUT_VOC_HIGH_LOW(obj)                     ((obj)->MDOUT = (uint32_t)(((obj)->MDOUT & ~MDOUT_VOC_MASK) | (0x02U << 2)))
#define MDOUT_VOC_HIGH_HIGH(obj)                    ((obj)->MDOUT = (uint32_t)(((obj)->MDOUT & ~MDOUT_VOC_MASK) | (0x03U << 2)))

#define MDOUT_WOC_LOW_LOW(obj)                      ((obj)->MDOUT = (uint32_t)(((obj)->MDOUT & ~MDOUT_WOC_MASK) | (0x00U << 4)))
#define MDOUT_WOC_LOW_HIGH(obj)                     ((obj)->MDOUT = (uint32_t)(((obj)->MDOUT & ~MDOUT_WOC_MASK) | (0x01U << 4)))
#define MDOUT_WOC_HIGH_LOW(obj)                     ((obj)->MDOUT = (uint32_t)(((obj)->MDOUT & ~MDOUT_WOC_MASK) | (0x02U << 4)))
#define MDOUT_WOC_HIGH_HIGH(obj)                    ((obj)->MDOUT = (uint32_t)(((obj)->MDOUT & ~MDOUT_WOC_MASK) | (0x03U << 4)))

#define MDOUT_UPWM_HL(obj)                          ((obj)->MDOUT = (uint32_t)(((obj)->MDOUT & ~MDOUT_UPWM_MASK) | (0x00U << 8)))
#define MDOUT_UPWM_PWM(obj)                         ((obj)->MDOUT = (uint32_t)(((obj)->MDOUT & ~MDOUT_UPWM_MASK) | (0x01U << 8)))

#define MDOUT_VPWM_HL(obj)                          ((obj)->MDOUT = (uint32_t)(((obj)->MDOUT & ~MDOUT_VPWM_MASK) | (0x00U << 9)))
#define MDOUT_VPWM_PWM(obj)                         ((obj)->MDOUT = (uint32_t)(((obj)->MDOUT & ~MDOUT_VPWM_MASK) | (0x01U << 9)))

#define MDOUT_WPWM_HL(obj)                          ((obj)->MDOUT = (uint32_t)(((obj)->MDOUT & ~MDOUT_WPWM_MASK) | (0x00U << 10)))
#define MDOUT_WPWM_PWM(obj)                         ((obj)->MDOUT = (uint32_t)(((obj)->MDOUT & ~MDOUT_WPWM_MASK) | (0x01U << 10)))

/* PMD EMG Control Register */
#define EMGCR_EMGEN_DISABLE(obj)                    ((obj)->EMGCR = (uint32_t)(((obj)->EMGCR & ~EMGCR_EMGEN_MASK) | (0x00U)))
#define EMGCR_EMGEN_ENABLE(obj)                     ((obj)->EMGCR = (uint32_t)(((obj)->EMGCR & ~EMGCR_EMGEN_MASK) | (0x01U)))

#define EMGCR_EMGRS_PROTECTION(obj)                 ((obj)->EMGCR = (uint32_t)(((obj)->EMGCR & ~EMGCR_EMGRS_MASK) | (0x01U << 1)))

#define EMGCR_EMGISEL_ENABLED(obj)                  ((obj)->EMGCR = (uint32_t)(((obj)->EMGCR & ~EMGCR_EMGISEL_MASK) | (0x00U << 2)))
#define EMGCR_EMGISEL_DISABLE(obj)                  ((obj)->EMGCR = (uint32_t)(((obj)->EMGCR & ~EMGCR_EMGISEL_MASK) | (0x01U << 2)))

#define EMGCR_EMGMD_UPZ_LPZ(obj)                    ((obj)->EMGCR = (uint32_t)(((obj)->EMGCR & ~EMGCR_EMGMD_MASK) | (0x03U << 3)))
#define EMGCR_EMGMD_UPON_LPZ(obj)                   ((obj)->EMGCR = (uint32_t)(((obj)->EMGCR & ~EMGCR_EMGMD_MASK) | (0x01U << 3)))
#define EMGCR_EMGMD_UPZ_LPON(obj)                   ((obj)->EMGCR = (uint32_t)(((obj)->EMGCR & ~EMGCR_EMGMD_MASK) | (0x02U << 3))) 

#define EMGCR_INHEN_DISBLE(obj)                     ((obj)->EMGCR = (uint32_t)(((obj)->EMGCR & ~EMGCR_INHEN_MASK) | (0x00U << 5)))
#define EMGCR_INHEN_ENABLE(obj)                     ((obj)->EMGCR = (uint32_t)(((obj)->EMGCR & ~EMGCR_INHEN_MASK) | (0x01U << 5)))

#define EMGCR_EMGIPOL_LOW(obj)                      ((obj)->EMGCR = (uint32_t)(((obj)->EMGCR & ~EMGCR_EMGIPOL_MASK) | (0x00U << 7)))
#define EMGCR_EMGIPOL_HIGH(obj)                     ((obj)->EMGCR = (uint32_t)(((obj)->EMGCR & ~EMGCR_EMGIPOL_MASK) | (0x01U << 7)))

#define EMGCR_EMGCNT(obj, param)                    ((obj)->EMGCR = (uint32_t)(((obj)->EMGCR & ~EMGCR_EMGCNT_MASK) | ((param) << 8)))

/* PMD EMG Release Register */
#define EMGREL_EMGREL(obj, param)                   ((obj)->EMGREL = (uint32_t)(param))

/* PMD OVV Control Register */
#define OVVCR_OVVEN_DISABLE(obj)                    ((obj)->OVVCR = (uint32_t)(((obj)->OVVCR & ~OVVCR_OVVEN_MASK) | (0x00U)))
#define OVVCR_OVVEN_ENABLE(obj)                     ((obj)->OVVCR = (uint32_t)(((obj)->OVVCR & ~OVVCR_OVVEN_MASK) | (0x01U)))

#define OVVCR_OVVRS_PROTECTION(obj)                 ((obj)->OVVCR = (uint32_t)(((obj)->OVVCR & ~OVVCR_OVVRS_MASK) | (0x01U << 1)))

#define OVVCR_OVVISEL_ENABLE(obj)                   ((obj)->OVVCR = (uint32_t)(((obj)->OVVCR & ~OVVCR_OVVISEL_MASK) | (0x00U << 2)))
#define OVVCR_OVVISEL_DISABLE(obj)                  ((obj)->OVVCR = (uint32_t)(((obj)->OVVCR & ~OVVCR_OVVISEL_MASK) | (0x01U << 2)))

#define OVVCR_OVVMD_NORESTRICT(obj)                 ((obj)->OVVCR = (uint32_t)(((obj)->OVVCR & ~OVVCR_OVVMD_MASK) | (0x00U << 3)))
#define OVVCR_OVVMD_UPON_LPOFF(obj)                 ((obj)->OVVCR = (uint32_t)(((obj)->OVVCR & ~OVVCR_OVVMD_MASK) | (0x01U << 3)))
#define OVVCR_OVVMD_UPOFF_LPON(obj)                 ((obj)->OVVCR = (uint32_t)(((obj)->OVVCR & ~OVVCR_OVVMD_MASK) | (0x02U << 3)))
#define OVVCR_OVVMD_ALLOFF(obj)                     ((obj)->OVVCR = (uint32_t)(((obj)->OVVCR & ~OVVCR_OVVMD_MASK) | (0x03U << 3)))

#define OVVCR_ADIN0EN_DISABLE(obj)                  ((obj)->OVVCR = (uint32_t)(((obj)->OVVCR & ~OVVCR_ADIN0EN_MASK) | (0x00U << 5)))
#define OVVCR_ADIN0EN_ENABLE(obj)                   ((obj)->OVVCR = (uint32_t)(((obj)->OVVCR & ~OVVCR_ADIN0EN_MASK) | (0x01U << 5)))

#define OVVCR_ADIN1EN_DISABLE(obj)                  ((obj)->OVVCR = (uint32_t)(((obj)->OVVCR & ~OVVCR_ADIN1EN_MASK) | (0x00U << 6)))
#define OVVCR_ADIN1EN_ENABLE(obj)                   ((obj)->OVVCR = (uint32_t)(((obj)->OVVCR & ~OVVCR_ADIN1EN_MASK) | (0x01U << 6)))

#define OVVCR_OVVIPOL_LOW(obj)                      ((obj)->OVVCR = (uint32_t)(((obj)->OVVCR & ~OVVCR_OVVIPOL_MASK) | (0x00U << 7)))
#define OVVCR_OVVIPOL_HIGH(obj)                     ((obj)->OVVCR = (uint32_t)(((obj)->OVVCR & ~OVVCR_OVVIPOL_MASK) | (0x01U << 7)))

#define OVVCR_OVVCNT(obj, param)                    ((obj)->OVVCR = (uint32_t)(((obj)->OVVCR & ~OVVCR_OVVCNT_MASK) | ((param) << 8)))

#define OVVCR_OVVRSMD_AUTO(obj)                     ((obj)->OVVCR = (uint32_t)(((obj)->OVVCR & ~OVVCR_OVVRSMD_MASK) | (0x00U << 15)))
#define OVVCR_OVVRSMD_PROTECT(obj)                  ((obj)->OVVCR = (uint32_t)(((obj)->OVVCR & ~OVVCR_OVVRSMD_MASK) | (0x01U << 15)))

/* PMD Dead Time Register */
#define DTR_DTR(obj, param)                         ((obj)->DTR = (uint32_t)(param))

/* PMD Trigger Comparison 0 Register */
#define TRGCMP0_TRGCMP0(obj, param)                 ((obj)->TRGCMP0 = (uint32_t)(param))

/* PMD Trigger Comparison 1 Register */
#define TRGCMP1_TRGCMP1(obj, param)                 ((obj)->TRGCMP1 = (uint32_t)(param))

/* PMD Trigger Comparison 0 Register */
#define TRGCMP2_TRGCMP2(obj, param)                 ((obj)->TRGCMP2 = (uint32_t)(param))

/* PMD Trigger Comparison 0 Register */
#define TRGCMP3_TRGCMP3(obj, param)                 ((obj)->TRGCMP3 = (uint32_t)(param))

/* PMD Trigger Control Register */
#define TRGCR_TRG0MD_DISABLE(obj)                   ((obj)->TRGCR = (uint32_t)(((obj)->TRGCR & ~TRGCR_TRG0MD_MASK) | (0x00U)))
#define TRGCR_TRG0MD_FIRSTHALF_TRIANGULAR(obj)      ((obj)->TRGCR = (uint32_t)(((obj)->TRGCR & ~TRGCR_TRG0MD_MASK) | (0x01U)))
#define TRGCR_TRG0MD_SECONDHALF_TRIANGULAR(obj)     ((obj)->TRGCR = (uint32_t)(((obj)->TRGCR & ~TRGCR_TRG0MD_MASK) | (0x02U)))
#define TRGCR_TRG0MD_FIRSTSECONDHALF_TRIANG(obj)    ((obj)->TRGCR = (uint32_t)(((obj)->TRGCR & ~TRGCR_TRG0MD_MASK) | (0x03U)))
#define TRGCR_TRG0MD_END_PWM(obj)                   ((obj)->TRGCR = (uint32_t)(((obj)->TRGCR & ~TRGCR_TRG0MD_MASK) | (0x04U)))
#define TRGCR_TRG0MD_CENTER_PWM(obj)                ((obj)->TRGCR = (uint32_t)(((obj)->TRGCR & ~TRGCR_TRG0MD_MASK) | (0x05U)))
#define TRGCR_TRG0MD_ENDCENTER_PWM(obj)             ((obj)->TRGCR = (uint32_t)(((obj)->TRGCR & ~TRGCR_TRG0MD_MASK) | (0x06U)))

#define TRGCR_TRG0BE_SYNC(obj)                      ((obj)->TRGCR = (uint32_t)(((obj)->TRGCR & ~TRGCR_TRG0BE_MASK) | (0x00U << 3)))
#define TRGCR_TRG0BE_ASYNC(obj)                     ((obj)->TRGCR = (uint32_t)(((obj)->TRGCR & ~TRGCR_TRG0BE_MASK) | (0x01U << 3)))

#define TRGCR_TRG1MD_DISABLE(obj)                   ((obj)->TRGCR = (uint32_t)(((obj)->TRGCR & ~TRGCR_TRG1MD_MASK) | (0x00U << 4)))
#define TRGCR_TRG1MD_FIRSTHALF_TRIANGULAR(obj)      ((obj)->TRGCR = (uint32_t)(((obj)->TRGCR & ~TRGCR_TRG1MD_MASK) | (0x01U << 4)))
#define TRGCR_TRG1MD_SECONDHALF_TRIANGULAR(obj)     ((obj)->TRGCR = (uint32_t)(((obj)->TRGCR & ~TRGCR_TRG1MD_MASK) | (0x02U << 4)))
#define TRGCR_TRG1MD_FIRSTSECONDHALF_TRIANG(obj)    ((obj)->TRGCR = (uint32_t)(((obj)->TRGCR & ~TRGCR_TRG1MD_MASK) | (0x03U << 4)))
#define TRGCR_TRG1MD_END_PWM(obj)                   ((obj)->TRGCR = (uint32_t)(((obj)->TRGCR & ~TRGCR_TRG1MD_MASK) | (0x04U << 4)))
#define TRGCR_TRG1MD_CENTER_PWM(obj)                ((obj)->TRGCR = (uint32_t)(((obj)->TRGCR & ~TRGCR_TRG1MD_MASK) | (0x05U << 4)))
#define TRGCR_TRG1MD_ENDCENTER_PWM(obj)             ((obj)->TRGCR = (uint32_t)(((obj)->TRGCR & ~TRGCR_TRG1MD_MASK) | (0x06U << 4)))

#define TRGCR_TRG1BE_SYNC(obj)                      ((obj)->TRGCR = (uint32_t)(((obj)->TRGCR & ~TRGCR_TRG1BE_MASK) | (0x00U << 7)))
#define TRGCR_TRG1BE_ASYNC(obj)                     ((obj)->TRGCR = (uint32_t)(((obj)->TRGCR & ~TRGCR_TRG1BE_MASK) | (0x01U << 7)))

#define TRGCR_TRG2MD_DISABLE(obj)                   ((obj)->TRGCR = (uint32_t)(((obj)->TRGCR & ~TRGCR_TRG2MD_MASK) | (0x00U << 8)))
#define TRGCR_TRG2MD_FIRSTHALF_TRIANGULAR(obj)      ((obj)->TRGCR = (uint32_t)(((obj)->TRGCR & ~TRGCR_TRG2MD_MASK) | (0x01U << 8)))
#define TRGCR_TRG2MD_SECONDHALF_TRIANGULAR(obj)     ((obj)->TRGCR = (uint32_t)(((obj)->TRGCR & ~TRGCR_TRG2MD_MASK) | (0x02U << 8)))
#define TRGCR_TRG2MD_FIRSTSECONDHALF_TRIANG(obj)    ((obj)->TRGCR = (uint32_t)(((obj)->TRGCR & ~TRGCR_TRG2MD_MASK) | (0x03U << 8)))
#define TRGCR_TRG2MD_END_PWM(obj)                   ((obj)->TRGCR = (uint32_t)(((obj)->TRGCR & ~TRGCR_TRG2MD_MASK) | (0x04U << 8)))
#define TRGCR_TRG2MD_CENTER_PWM(obj)                ((obj)->TRGCR = (uint32_t)(((obj)->TRGCR & ~TRGCR_TRG2MD_MASK) | (0x05U << 8)))
#define TRGCR_TRG2MD_ENDCENTER_PWM(obj)             ((obj)->TRGCR = (uint32_t)(((obj)->TRGCR & ~TRGCR_TRG2MD_MASK) | (0x06U << 8)))

#define TRGCR_TRG2BE_SYNC(obj)                      ((obj)->TRGCR = (uint32_t)(((obj)->TRGCR & ~TRGCR_TRG2BE_MASK) | (0x00U << 11)))
#define TRGCR_TRG2BE_ASYNC(obj)                     ((obj)->TRGCR = (uint32_t)(((obj)->TRGCR & ~TRGCR_TRG2BE_MASK) | (0x01U << 11)))

#define TRGCR_TRG3MD_DISABLE(obj)                   ((obj)->TRGCR = (uint32_t)(((obj)->TRGCR & ~TRGCR_TRG3MD_MASK) | (0x00U << 12)))
#define TRGCR_TRG3MD_FIRSTHALF_TRIANGULAR(obj)      ((obj)->TRGCR = (uint32_t)(((obj)->TRGCR & ~TRGCR_TRG3MD_MASK) | (0x01U << 12)))
#define TRGCR_TRG3MD_SECONDHALF_TRIANGULAR(obj)     ((obj)->TRGCR = (uint32_t)(((obj)->TRGCR & ~TRGCR_TRG3MD_MASK) | (0x02U << 12)))
#define TRGCR_TRG3MD_FIRSTSECONDHALF_TRIANG(obj)    ((obj)->TRGCR = (uint32_t)(((obj)->TRGCR & ~TRGCR_TRG3MD_MASK) | (0x03U << 12)))
#define TRGCR_TRG3MD_END_PWM(obj)                   ((obj)->TRGCR = (uint32_t)(((obj)->TRGCR & ~TRGCR_TRG3MD_MASK) | (0x04U << 12)))
#define TRGCR_TRG3MD_CENTER_PWM(obj)                ((obj)->TRGCR = (uint32_t)(((obj)->TRGCR & ~TRGCR_TRG3MD_MASK) | (0x05U << 12)))
#define TRGCR_TRG3MD_ENDCENTER_PWM(obj)             ((obj)->TRGCR = (uint32_t)(((obj)->TRGCR & ~TRGCR_TRG3MD_MASK) | (0x06U << 12)))

#define TRGCR_TRG3BE_SYNC(obj)                      ((obj)->TRGCR = (uint32_t)(((obj)->TRGCR & ~TRGCR_TRG3BE_MASK) | (0x00U << 15)))
#define TRGCR_TRG3BE_ASYNC(obj)                     ((obj)->TRGCR = (uint32_t)(((obj)->TRGCR & ~TRGCR_TRG3BE_MASK) | (0x01U << 15)))

#define TRGCR_CARSEL_BASE_CARRIER(obj)              ((obj)->TRGCR = (uint32_t)(((obj)->TRGCR & ~TRGCR_CARSEL_MASK) | (0x00U << 16)))
#define TRGCR_CARSEL_PHASE_CARRIER(obj)             ((obj)->TRGCR = (uint32_t)(((obj)->TRGCR & ~TRGCR_CARSEL_MASK) | (0x01U << 16)))

/* PMD Trigger Update Timing Setting Register */
#define TRGSYNCR_TSYNCS_IMMEDIATE(obj)              ((obj)->TRGSYNCR = (uint32_t)(((obj)->TRGSYNCR & ~TRGSYNCR_TSYNCS_MASK) | (0x00U)))
#define TRGSYNCR_TSYNCS_CENTER(obj)                 ((obj)->TRGSYNCR = (uint32_t)(((obj)->TRGSYNCR & ~TRGSYNCR_TSYNCS_MASK) | (0x01U)))
#define TRGSYNCR_TSYNCS_END(obj)                    ((obj)->TRGSYNCR = (uint32_t)(((obj)->TRGSYNCR & ~TRGSYNCR_TSYNCS_MASK) | (0x02U)))
#define TRGSYNCR_TSYNCS_ENDCENTER(obj)              ((obj)->TRGSYNCR = (uint32_t)(((obj)->TRGSYNCR & ~TRGSYNCR_TSYNCS_MASK) | (0x03U)))

/* PMD Trigger Output Mode Setting Register */
#define TRGMD_EMGTGE_DISABLE(obj)                   ((obj)->TRGMD = (uint32_t)(((obj)->TRGMD & ~TRGMD_EMGTGE_MASK) | (0x00U)))
#define TRGMD_EMGTGE_ENABLE(obj)                    ((obj)->TRGMD = (uint32_t)(((obj)->TRGMD & ~TRGMD_EMGTGE_MASK) | (0x01U)))

#define TRGMD_TRGOUT_FIXED(obj)                     ((obj)->TRGMD = (uint32_t)(((obj)->TRGMD & ~TRGMD_TRGOUT_MASK) | (0x00U << 1)))
#define TRGMD_TRGOUT_SELECTED(obj)                  ((obj)->TRGMD = (uint32_t)(((obj)->TRGMD & ~TRGMD_TRGOUT_MASK) | (0x01U << 1)))

/* PMD Trigger Output Selection Register */
#define TRGSEL_TRGSEL_OUT_TRG0(obj)                 ((obj)->TRGSEL = (uint32_t)(((obj)->TRGSEL & ~TRGSEL_TRGSEL_MASK) | (0x00U)))
#define TRGSEL_TRGSEL_OUT_TRG1(obj)                 ((obj)->TRGSEL = (uint32_t)(((obj)->TRGSEL & ~TRGSEL_TRGSEL_MASK) | (0x01U)))
#define TRGSEL_TRGSEL_OUT_TRG2(obj)                 ((obj)->TRGSEL = (uint32_t)(((obj)->TRGSEL & ~TRGSEL_TRGSEL_MASK) | (0x02U)))
#define TRGSEL_TRGSEL_OUT_TRG3(obj)                 ((obj)->TRGSEL = (uint32_t)(((obj)->TRGSEL & ~TRGSEL_TRGSEL_MASK) | (0x03U)))
#define TRGSEL_TRGSEL_OUT_TRG4(obj)                 ((obj)->TRGSEL = (uint32_t)(((obj)->TRGSEL & ~TRGSEL_TRGSEL_MASK) | (0x04U)))
#define TRGSEL_TRGSEL_OUT_TRG5(obj)                 ((obj)->TRGSEL = (uint32_t)(((obj)->TRGSEL & ~TRGSEL_TRGSEL_MASK) | (0x05U)))
#define TRGSEL_TRGSEL_OUT_NOT(obj)                  ((obj)->TRGSEL = (uint32_t)(((obj)->TRGSEL & ~TRGSEL_TRGSEL_MASK) | (0x07U)))

/* PMD Intermediate Buffer Control Register */
#define MBUFCR_BUFCTR_DISABLE(obj)                  ((obj)->MBUFCR = (uint32_t)(((obj)->MBUFCR & ~MBUFCR_BUFCTR_MASK) | (0x00U)))
#define MBUFCR_BUFCTR_UPHASE_END(obj)               ((obj)->MBUFCR = (uint32_t)(((obj)->MBUFCR & ~MBUFCR_BUFCTR_MASK) | (0x01U)))
#define MBUFCR_BUFCTR_UPHASE_CENTER(obj)            ((obj)->MBUFCR = (uint32_t)(((obj)->MBUFCR & ~MBUFCR_BUFCTR_MASK) | (0x02U)))
#define MBUFCR_BUFCTR_UPHASE_THREE_FOURTH(obj)      ((obj)->MBUFCR = (uint32_t)(((obj)->MBUFCR & ~MBUFCR_BUFCTR_MASK) | (0x03U)))
#define MBUFCR_BUFCTR_UPHASE_ONE_FOURTH(obj)        ((obj)->MBUFCR = (uint32_t)(((obj)->MBUFCR & ~MBUFCR_BUFCTR_MASK) | (0x04U)))
#define MBUFCR_BUFCTR_UPHASE_ENDCENTER(obj)         ((obj)->MBUFCR = (uint32_t)(((obj)->MBUFCR & ~MBUFCR_BUFCTR_MASK) | (0x05U)))
#define MBUFCR_BUFCTR_UPHASE_THREEONE_FOURTH(obj)   ((obj)->MBUFCR = (uint32_t)(((obj)->MBUFCR & ~MBUFCR_BUFCTR_MASK) | (0x06U)))

/* PMD Synchronization Control Register */
#define SYNCCR_PWMSMD_DISABLE(obj)                  ((obj)->SYNCCR = (uint32_t)(((obj)->SYNCCR & ~SYNCCR_PWMSMD_MASK) | (0x00U)))
#define SYNCCR_PWMSMD_ENABLE(obj)                   ((obj)->SYNCCR = (uint32_t)(((obj)->SYNCCR & ~SYNCCR_PWMSMD_MASK) | (0x01U)))

#define SYNCCR_EMGSMD_DISABLE(obj)                  ((obj)->SYNCCR = (uint32_t)(((obj)->SYNCCR & ~SYNCCR_EMGSMD_MASK) | (0x00U << 4)))
#define SYNCCR_EMGSMD_ENABLE_EMG_DISABLE(obj)       ((obj)->SYNCCR = (uint32_t)(((obj)->SYNCCR & ~SYNCCR_EMGSMD_MASK) | (0x02U << 4)))
#define SYNCCR_EMGSMD_ENABLE_EMG_ENABLE(obj)        ((obj)->SYNCCR = (uint32_t)(((obj)->SYNCCR & ~SYNCCR_EMGSMD_MASK) | (0x03U << 4)))

#define SYNCCR_OVVSMD_DISABLE(obj)                  ((obj)->SYNCCR = (uint32_t)(((obj)->SYNCCR & ~SYNCCR_OVVSMD_MASK) | (0x00U << 6)))
#define SYNCCR_OVVSMD_ENABLE_OVV_DISABLE(obj)       ((obj)->SYNCCR = (uint32_t)(((obj)->SYNCCR & ~SYNCCR_OVVSMD_MASK) | (0x02U << 6)))
#define SYNCCR_OVVSMD_ENABLE_OVV_ENABLE(obj)        ((obj)->SYNCCR = (uint32_t)(((obj)->SYNCCR & ~SYNCCR_OVVSMD_MASK) | (0x03U << 6)))

/* PMD Debug Output Control Register */
#define DBGOUTCR_DBGEN_DISABLE(obj)                 ((obj)->DBGOUTCR = (uint32_t)(((obj)->DBGOUTCR & ~DBGOUTCR_DBGEN_MASK) | (0x00U)))
#define DBGOUTCR_DBGEN_ENABLE(obj)                  ((obj)->DBGOUTCR = (uint32_t)(((obj)->DBGOUTCR & ~DBGOUTCR_DBGEN_MASK) | (0x01U)))

#define DBGOUTCR_DBGMD_ADC(obj)                     ((obj)->DBGOUTCR = (uint32_t)(((obj)->DBGOUTCR & ~DBGOUTCR_DBGMD_MASK) | (0x00U << 1)))
#define DBGOUTCR_DBGMD_PMD(obj)                     ((obj)->DBGOUTCR = (uint32_t)(((obj)->DBGOUTCR & ~DBGOUTCR_DBGMD_MASK) | (0x01U << 1)))
#define DBGOUTCR_DBGMD_INTERRUPT(obj)               ((obj)->DBGOUTCR = (uint32_t)(((obj)->DBGOUTCR & ~DBGOUTCR_DBGMD_MASK) | (0x02U << 1)))
#define DBGOUTCR_DBGMD_VE(obj)                      ((obj)->DBGOUTCR = (uint32_t)(((obj)->DBGOUTCR & ~DBGOUTCR_DBGMD_MASK) | (0x03U << 1)))

#define DBGOUTCR_IADAEN_DISABLE(obj)                ((obj)->DBGOUTCR = (uint32_t)(((obj)->DBGOUTCR & ~DBGOUTCR_IADAEN_MASK) | (0x00U << 3)))
#define DBGOUTCR_IADAEN_ENABLE(obj)                 ((obj)->DBGOUTCR = (uint32_t)(((obj)->DBGOUTCR & ~DBGOUTCR_IADAEN_MASK) | (0x01U << 3)))

#define DBGOUTCR_IADBEN_DISABLE(obj)                ((obj)->DBGOUTCR = (uint32_t)(((obj)->DBGOUTCR & ~DBGOUTCR_IADBEN_MASK) | (0x00U << 4)))
#define DBGOUTCR_IADBEN_ENABLE(obj)                 ((obj)->DBGOUTCR = (uint32_t)(((obj)->DBGOUTCR & ~DBGOUTCR_IADBEN_MASK) | (0x01U << 4)))

#define DBGOUTCR_IADCEN_DISABLE(obj)                ((obj)->DBGOUTCR = (uint32_t)(((obj)->DBGOUTCR & ~DBGOUTCR_IADCEN_MASK) | (0x00U << 5)))
#define DBGOUTCR_IADCEN_ENABLE(obj)                 ((obj)->DBGOUTCR = (uint32_t)(((obj)->DBGOUTCR & ~DBGOUTCR_IADCEN_MASK) | (0x01U << 5)))

#define DBGOUTCR_IADDEN_DISABLE(obj)                ((obj)->DBGOUTCR = (uint32_t)(((obj)->DBGOUTCR & ~DBGOUTCR_IADDEN_MASK) | (0x00U << 6)))
#define DBGOUTCR_IADDEN_ENABLE(obj)                 ((obj)->DBGOUTCR = (uint32_t)(((obj)->DBGOUTCR & ~DBGOUTCR_IADDEN_MASK) | (0x01U << 6)))

#define DBGOUTCR_IADEEN_DISABLE(obj)                ((obj)->DBGOUTCR = (uint32_t)(((obj)->DBGOUTCR & ~DBGOUTCR_IADEEN_MASK) | (0x00U << 7)))
#define DBGOUTCR_IADEEN_ENABLE(obj)                 ((obj)->DBGOUTCR = (uint32_t)(((obj)->DBGOUTCR & ~DBGOUTCR_IADEEN_MASK) | (0x01U << 7)))

#define DBGOUTCR_IPMDEN_DISABLE(obj)                ((obj)->DBGOUTCR = (uint32_t)(((obj)->DBGOUTCR & ~DBGOUTCR_IPMDEN_MASK) | (0x00U << 8)))
#define DBGOUTCR_IPMDEN_ENABLE(obj)                 ((obj)->DBGOUTCR = (uint32_t)(((obj)->DBGOUTCR & ~DBGOUTCR_IPMDEN_MASK) | (0x01U << 8)))

#define DBGOUTCR_IEMGEN_DISABLE(obj)                ((obj)->DBGOUTCR = (uint32_t)(((obj)->DBGOUTCR & ~DBGOUTCR_IEMGEN_MASK) | (0x00U << 9)))
#define DBGOUTCR_IEMGEN_ENABLE(obj)                 ((obj)->DBGOUTCR = (uint32_t)(((obj)->DBGOUTCR & ~DBGOUTCR_IEMGEN_MASK) | (0x01U << 9)))

#define DBGOUTCR_IOVVEN_DISABLE(obj)                ((obj)->DBGOUTCR = (uint32_t)(((obj)->DBGOUTCR & ~DBGOUTCR_IOVVEN_MASK) | (0x00U << 10)))
#define DBGOUTCR_IOVVEN_ENABLE(obj)                 ((obj)->DBGOUTCR = (uint32_t)(((obj)->DBGOUTCR & ~DBGOUTCR_IOVVEN_MASK) | (0x01U << 10)))

#define DBGOUTCR_IVEEN_DISABLE(obj)                 ((obj)->DBGOUTCR = (uint32_t)(((obj)->DBGOUTCR & ~DBGOUTCR_IVEEN_MASK) | (0x00U << 11)))
#define DBGOUTCR_IVEEN_ENABLE(obj)                  ((obj)->DBGOUTCR = (uint32_t)(((obj)->DBGOUTCR & ~DBGOUTCR_IVEEN_MASK) | (0x01U << 11)))

#define DBGOUTCR_IENCEN_DISABLE(obj)                ((obj)->DBGOUTCR = (uint32_t)(((obj)->DBGOUTCR & ~DBGOUTCR_IENCEN_MASK) | (0x00U << 12)))
#define DBGOUTCR_IENCEN_ENABLE(obj)                 ((obj)->DBGOUTCR = (uint32_t)(((obj)->DBGOUTCR & ~DBGOUTCR_IENCEN_MASK) | (0x01U << 12)))

#define DBGOUTCR_TRG0EN_DISABLE(obj)                ((obj)->DBGOUTCR = (uint32_t)(((obj)->DBGOUTCR & ~DBGOUTCR_TRG0EN_MASK) | (0x00U << 16)))
#define DBGOUTCR_TRG0EN_ENABLE(obj)                 ((obj)->DBGOUTCR = (uint32_t)(((obj)->DBGOUTCR & ~DBGOUTCR_TRG0EN_MASK) | (0x01U << 16)))

#define DBGOUTCR_TRG1EN_DISABLE(obj)                ((obj)->DBGOUTCR = (uint32_t)(((obj)->DBGOUTCR & ~DBGOUTCR_TRG1EN_MASK) | (0x00U << 17)))
#define DBGOUTCR_TRG1EN_ENABLE(obj)                 ((obj)->DBGOUTCR = (uint32_t)(((obj)->DBGOUTCR & ~DBGOUTCR_TRG1EN_MASK) | (0x01U << 17)))

#define DBGOUTCR_TRG2EN_DISABLE(obj)                ((obj)->DBGOUTCR = (uint32_t)(((obj)->DBGOUTCR & ~DBGOUTCR_TRG2EN_MASK) | (0x00U << 18)))
#define DBGOUTCR_TRG2EN_ENABLE(obj)                 ((obj)->DBGOUTCR = (uint32_t)(((obj)->DBGOUTCR & ~DBGOUTCR_TRG2EN_MASK) | (0x01U << 18)))

#define DBGOUTCR_TRG3EN_DISABLE(obj)                ((obj)->DBGOUTCR = (uint32_t)(((obj)->DBGOUTCR & ~DBGOUTCR_TRG3EN_MASK) | (0x00U << 19)))
#define DBGOUTCR_TRG3EN_ENABLE(obj)                 ((obj)->DBGOUTCR = (uint32_t)(((obj)->DBGOUTCR & ~DBGOUTCR_TRG3EN_MASK) | (0x01U << 19)))

#define DBGOUTCR_TRG4EN_DISABLE(obj)                ((obj)->DBGOUTCR = (uint32_t)(((obj)->DBGOUTCR & ~DBGOUTCR_TRG4EN_MASK) | (0x00U << 20)))
#define DBGOUTCR_TRG4EN_ENABLE(obj)                 ((obj)->DBGOUTCR = (uint32_t)(((obj)->DBGOUTCR & ~DBGOUTCR_TRG4EN_MASK) | (0x01U << 20)))

#define DBGOUTCR_TRG5EN_DISABLE(obj)                ((obj)->DBGOUTCR = (uint32_t)(((obj)->DBGOUTCR & ~DBGOUTCR_TRG5EN_MASK) | (0x00U << 21)))
#define DBGOUTCR_TRG5EN_ENABLE(obj)                 ((obj)->DBGOUTCR = (uint32_t)(((obj)->DBGOUTCR & ~DBGOUTCR_TRG5EN_MASK) | (0x01U << 21)))

#define DBGOUTCR_INIFF_OUT_ZERO(obj)                ((obj)->DBGOUTCR = (uint32_t)(((obj)->DBGOUTCR & ~DBGOUTCR_INIFF_MASK) | (0x00U << 31)))
#define DBGOUTCR_INIFF_OUT_ONE(obj)                 ((obj)->DBGOUTCR = (uint32_t)(((obj)->DBGOUTCR & ~DBGOUTCR_INIFF_MASK) | (0x01U << 31)))

/*===================================================================*
                  Functions declaration for A-PMD
*===================================================================*/

void APMD_Init(void);
void APMD_Config(TSB_PMD_TypeDef * PMDx, uint8_t phase, bool comp);
void EMG_Disable(TSB_PMD_TypeDef * PMDx);

void setPWM_Form(TSB_PMD_TypeDef * PMDx);
void setPWM_DeadTime(TSB_PMD_TypeDef * PMDx, uint32_t value);
void setPWM_Frequency(TSB_PMD_TypeDef * PMDx, uint32_t value);
void setPWM_DutyRatio(TSB_PMD_TypeDef * PMDx, uint8_t phase, uint32_t value);

uint32_t getMDEN_reg(TSB_PMD_TypeDef * PMDx);
uint32_t getPORTMD_reg(TSB_PMD_TypeDef * PMDx);
uint32_t getMODESEL_reg(TSB_PMD_TypeDef * PMDx);
uint32_t getMDCR_reg(TSB_PMD_TypeDef * PMDx);
uint32_t getCARSTA_reg(TSB_PMD_TypeDef * PMDx);
uint32_t getBCARI_reg(TSB_PMD_TypeDef * PMDx);
uint32_t getRATE_reg(TSB_PMD_TypeDef * PMDx);
uint32_t getCMPU_reg(TSB_PMD_TypeDef * PMDx);
uint32_t getCMPV_reg(TSB_PMD_TypeDef * PMDx);
uint32_t getCMPW_reg(TSB_PMD_TypeDef * PMDx);
uint32_t getVPWMPH_reg(TSB_PMD_TypeDef * PMDx);
uint32_t getWPWMPH_reg(TSB_PMD_TypeDef * PMDx);
uint32_t getMDPOT_reg(TSB_PMD_TypeDef * PMDx);
uint32_t getMDOUT_reg(TSB_PMD_TypeDef * PMDx);
uint32_t getEMGCR_reg(TSB_PMD_TypeDef * PMDx);
uint32_t getEMGSTA_reg(TSB_PMD_TypeDef * PMDx);
uint32_t getEMGREL_reg(TSB_PMD_TypeDef * PMDx);
uint32_t getOVVCR_reg(TSB_PMD_TypeDef * PMDx);
uint32_t getOVVSTA_reg(TSB_PMD_TypeDef * PMDx);
uint32_t getDTR_reg(TSB_PMD_TypeDef * PMDx);
uint32_t getTRGCMP0_reg(TSB_PMD_TypeDef * PMDx);
uint32_t getTRGCMP1_reg(TSB_PMD_TypeDef * PMDx);
uint32_t getTRGCMP2_reg(TSB_PMD_TypeDef * PMDx);
uint32_t getTRGCMP3_reg(TSB_PMD_TypeDef * PMDx);
uint32_t getTRGCR_reg(TSB_PMD_TypeDef * PMDx);
uint32_t getTRGSYNCR_reg(TSB_PMD_TypeDef * PMDx);
uint32_t getTRGMD_reg(TSB_PMD_TypeDef * PMDx);
uint32_t getTRGSEL_reg(TSB_PMD_TypeDef * PMDx);
uint32_t getMBUFCR_reg(TSB_PMD_TypeDef * PMDx);
uint32_t getSYNCCR_reg(TSB_PMD_TypeDef * PMDx);
uint32_t getDBGOUTCR_reg(TSB_PMD_TypeDef * PMDx);

uint32_t getPWMCR_reg(TSB_PMD_TypeDef * PMDx);


#ifdef __cplusplus
}
#endif

#endif  /* __TSB_APMD_H__ */



