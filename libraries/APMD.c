/**
 *******************************************************************************
 * @file    APMD.c
 * @brief   Toshiba APMD Control for motor
 *          TOSHIBA 'TMPM4KNA' Group
 * @version V1.0.0.0
 * @date:: 2022-09-19 #$
 * 
 * @author Hugo Rodrigues
 *******************************************************************************
 */

#include "APMD.h"
//#include "../CMSIS/TMPM4KNA.h"
#include "TMPM4KyA.h"
#include <stdbool.h>
#include <stdint.h>
#include <math.h>


/*  Number of PWM phases: 0x00 -> None | 0x01 -> One | 0x02 -> Two | 0x03 - Three  */
#define PMD0_PHASE_Val                      (uint8_t) 0x02
#define PMD1_PHASE_Val                      (uint8_t) 0x00
#define PMD2_PHASE_Val                      (uint8_t) 0x01

/*  True = Will use the compliment pin for each phase | False = Will not use    */
#define PMD0_PHASE_COMPLIMENT               (bool) true
#define PMD1_PHASE_COMPLIMENT               (bool) false
#define PMD2_PHASE_COMPLIMENT               (bool) false


/*===================================================================*
      Initialize the PMDx Based on configuration
*===================================================================*/
void APMD_Init(void){
    switch(PMD0_PHASE_Val){
        case 0x01:
            APMD_Config(TSB_PMD0, 1, PMD0_PHASE_COMPLIMENT);
            break;
        case 0x02:
            APMD_Config(TSB_PMD0, 2, PMD0_PHASE_COMPLIMENT);
            break;
        case 0x03:
            APMD_Config(TSB_PMD0, 3, PMD0_PHASE_COMPLIMENT);
            break;
        default:
            break;
    }

    switch(PMD1_PHASE_Val){
        case 0x01:
            APMD_Config(TSB_PMD1, 1, PMD1_PHASE_COMPLIMENT);
            break;
        case 0x02:
            APMD_Config(TSB_PMD1, 2, PMD1_PHASE_COMPLIMENT);
            break;
        case 0x03:
            APMD_Config(TSB_PMD1, 3, PMD1_PHASE_COMPLIMENT);
            break;
        default:
            break;
    }

    switch(PMD2_PHASE_Val){
        case 0x01:
            APMD_Config(TSB_PMD2, 1, PMD2_PHASE_COMPLIMENT);
            break;
        case 0x02:
            APMD_Config(TSB_PMD2, 2, PMD2_PHASE_COMPLIMENT);
            break;
        case 0x03:
            APMD_Config(TSB_PMD2, 3, PMD2_PHASE_COMPLIMENT);
            break;
        default:
            break;
    }
}

void APMD_Config(TSB_PMD_TypeDef * PMDx, uint8_t phase, bool comp){
    switch((intptr_t)PMDx){
        /* Configure A-PMD0 */
        case (intptr_t)TSB_PMD0 : 
            TSB_CG_FSYSMENA_IPMENA01 = 1;   // Clock Enable Port B
            TSB_CG_FSYSMENB_IPMENB09 = 1;   // Clock Enable PMD0
            TSB_CG_FSYSENA_IPENA01 = 1;     // Clock Enable Ramp
            PORTMD_UPPMD_LPHIGH(PMDx);      // Set the PWM to have a PMD output on Upper-Phase

            if (phase == 1){
                /* Set the Clock supply and stop register A for Phase U */
                TSB_PB_CR_PB0C = 1;             // Enables PB0 as output
                TSB_PB_FR4_PB0F4 = 1;           // Enables the function output on PB0

                if (comp){
                    /* U Phase and X Phase (Compliment) Control Register */
                    PORTMD_UPPMD_LPPMD(PMDx);       // Set the PWM to have a PMD output on Upper-Phase and Lower-Phase
                    TSB_PB_CR_PB1C = 1;             // Enables PB1 as output
                    TSB_PB_FR4_PB1F4 = 1;           // Enables the function output on PB1
                }
                else {
                    TSB_PB_CR_PB1C = 0;             // Disable PB1 as output
                    TSB_PB_FR4_PB1F4 = 0;           // Disable the function output on PB1
                }
            }

            if (phase == 2){
                /* Set the Clock supply and stop register A for Phase U, V */
                TSB_PB_CR_PB0C = 1;             // Enables PB0 as output
                TSB_PB_FR4_PB0F4 = 1;           // Enables the function output on PB0
                TSB_PB_CR_PB2C = 1;             // Enables PB2 as output
                TSB_PB_FR4_PB2F4 = 1;           // Enables the function output on PB2

                if (comp){
                    /* U, V Phase and X, Y Phase (Compliment) Control Register */
                    PORTMD_UPPMD_LPPMD(PMDx);       // Set the PWM to have a PMD output on Upper-Phase and Lower-Phase
                    TSB_PB_CR_PB1C = 1;             // Enables PB1 as output
                    TSB_PB_FR4_PB1F4 = 1;           // Enables the function output on PB1
                    TSB_PB_CR_PB3C = 1;             // Enables PB3 as output
                    TSB_PB_FR4_PB3F4 = 1;           // Enables the function output on PB3
                }
                else {
                    TSB_PB_CR_PB1C = 0;             // Disable PB1 as output
                    TSB_PB_FR4_PB1F4 = 0;           // Disable the function output on PB1
                    TSB_PB_CR_PB3C = 0;             // Disable PB3 as output
                    TSB_PB_FR4_PB3F4 = 0;           // Disable the function output on PB3
                }
            }

            if (phase == 3){
                /* Set the Clock supply and stop register A for Phase U, V, W */
                TSB_PB_CR_PB0C = 1;             // Enables PB0 as output
                TSB_PB_FR4_PB0F4 = 1;           // Enables the function output on PB0
                TSB_PB_CR_PB2C = 1;             // Enables PB2 as output
                TSB_PB_FR4_PB2F4 = 1;           // Enables the function output on PB2
                TSB_PB_CR_PB4C = 1;             // Enables PB4 as output
                TSB_PB_FR4_PB4F4 = 1;           // Enables the function output on PB4

                if (comp){
                    /* U, V, W Phase and X, Y, Z Phase (Compliment) Control Register */
                    PORTMD_UPPMD_LPPMD(PMDx);       // Set the PWM to have a PMD output on Upper-Phase and Lower-Phase
                    TSB_PB_CR_PB1C = 1;             // Enables PB1 as output
                    TSB_PB_FR4_PB1F4 = 1;           // Enables the function output on PB1
                    TSB_PB_CR_PB3C = 1;             // Enables PB3 as output
                    TSB_PB_FR4_PB3F4 = 1;           // Enables the function output on PB3
                    TSB_PB_CR_PB5C = 1;             // Enables PB5 as output
                    TSB_PB_FR4_PB5F4 = 1;           // Enables the function output on PB5
                }
                else {
                    TSB_PB_CR_PB1C = 0;             // Disable PB1 as output
                    TSB_PB_FR4_PB1F4 = 0;           // Disable the function output on PB1
                    TSB_PB_CR_PB3C = 0;             // Disable PB3 as output
                    TSB_PB_FR4_PB3F4 = 0;           // Disable the function output on PB3
                    TSB_PB_CR_PB5C = 0;             // Disable PB5 as output
                    TSB_PB_FR4_PB5F4 = 0;           // Disable the function output on PB5
                }
            }
            break;

        /* Configure A-PMD1 */
        case (intptr_t)TSB_PMD1 : 
            TSB_CG_FSYSMENA_IPMENA04 = 1;   // Clock Enable Port E
            TSB_CG_FSYSMENB_IPMENB10 = 1;   // Clock Enable PMD1
            PORTMD_UPPMD_LPHIGH(PMDx);      // Set the PWM to have a PMD output on Upper-Phase

            if (phase == 1){
                /* Set the Clock supply and stop register A for Phase U */
                TSB_PE_CR_PE0C = 1;             // Enables PE0 as output
                TSB_PE_FR6_PE0F6 = 1;           // Enables the function output on PE0

                if (comp){
                    /* U Phase and X Phase (Compliment) Control Register */
                    PORTMD_UPPMD_LPPMD(PMDx);       // Set the PWM to have a PMD output on Upper-Phase and Lower-Phase
                    TSB_PE_CR_PE1C = 1;             // Enables PE1 as output
                    TSB_PE_FR6_PE1F6 = 1;           // Enables the function output on PE1
                }
                else {
                    TSB_PE_CR_PE1C = 0;             // Disable PE1 as output
                    TSB_PE_FR6_PE1F6 = 0;           // Disable the function output on PE1
                }
            }

            if (phase == 2){
                /* Set the Clock supply and stop register A for Phase U, V */
                TSB_PE_CR_PE0C = 1;             // Enables PE0 as output
                TSB_PE_FR6_PE0F6 = 1;           // Enables the function output on PE0
                TSB_PE_CR_PE2C = 1;             // Enables PE2 as output
                TSB_PE_FR6_PE2F6 = 1;           // Enables the function output on PE2

                if (comp){
                    /* U, V Phase and X, W Phase (Compliment) Control Register */
                    PORTMD_UPPMD_LPPMD(PMDx);       // Set the PWM to have a PMD output on Upper-Phase and Lower-Phase
                    TSB_PE_CR_PE1C = 1;             // Enables PE1 as output
                    TSB_PE_FR6_PE1F6 = 1;           // Enables the function output on PE1
                    TSB_PE_CR_PE3C = 1;             // Enables PE3 as output
                    TSB_PE_FR6_PE3F6 = 1;           // Enables the function output on PE3
                }
                else {
                    TSB_PE_CR_PE1C = 0;             // Disable PE1 as output
                    TSB_PE_FR6_PE1F6 = 0;           // Disable the function output on PE1
                    TSB_PE_CR_PE3C = 0;             // Disable PE3 as output
                    TSB_PE_FR6_PE3F6 = 0;           // Disable the function output on PE3
                }
            }

            if (phase == 3){
                /* Set the Clock supply and stop register A for Phase U, V, W */
                TSB_PE_CR_PE0C = 1;             // Enables PE0 as output
                TSB_PE_FR6_PE0F6 = 1;           // Enables the function output on PE0
                TSB_PE_CR_PE2C = 1;             // Enables PE2 as output
                TSB_PE_FR6_PE2F6 = 1;           // Enables the function output on PE2
                TSB_PE_CR_PE4C = 1;             // Enables PE4 as output
                TSB_PE_FR6_PE4F6 = 1;           // Enables the function output on PE4

                if (comp){
                    /* U, V, W Phase and X, Y, Z Phase (Compliment) Control Register */
                    PORTMD_UPPMD_LPPMD(PMDx);       // Set the PWM to have a PMD output on Upper-Phase and Lower-Phase
                    TSB_PE_CR_PE1C = 1;             // Enables PE1 as output
                    TSB_PE_FR6_PE1F6 = 1;           // Enables the function output on PE1
                    TSB_PE_CR_PE3C = 1;             // Enables PE3 as output
                    TSB_PE_FR6_PE3F6 = 1;           // Enables the function output on PE3
                    TSB_PE_CR_PE5C = 1;             // Enables PE5 as output
                    TSB_PE_FR4_PE5F4 = 1;           // Enables the function output on PE5
                }
                else {
                    TSB_PE_CR_PE1C = 0;             // Disable PE1 as output
                    TSB_PE_FR6_PE1F6 = 0;           // Disable the function output on PE1
                    TSB_PE_CR_PE3C = 0;             // Disable PE3 as output
                    TSB_PE_FR6_PE3F6 = 0;           // Disable the function output on PE3
                    TSB_PE_CR_PE5C = 0;             // Disable PE5 as output
                    TSB_PE_FR4_PE5F4 = 0;           // Disable the function output on PE5
                }
            }
            break;

        /* Configure A-PMD2 */
        default :
            TSB_CG_FSYSMENA_IPMENA16 = 1;   // Clock Enable Port U
            TSB_CG_FSYSMENB_IPMENB11 = 1;   // Clock Enable PMD2
            PORTMD_UPPMD_LPHIGH(PMDx);      // Set the PWM to have a PMD output on Upper-Phase
            
            if (phase == 1){
                /* Set the Clock supply and stop register A for Phase U */
                TSB_PU_CR_PU0C = 1;             // Enables PU0 as output
                TSB_PU_FR6_PU0F6 = 1;           // Enables the function output on PU0

                if (comp){
                    /* U Phase and X Phase (Compliment) Control Register */
                    PORTMD_UPPMD_LPPMD(PMDx);       // Set the PWM to have a PMD output on Upper-Phase and Lower-Phase
                    TSB_PU_CR_PU1C = 1;             // Enables PU1 as output
                    TSB_PU_FR6_PU1F6 = 1;           // Enables the function output on PU1
                }
                else {
                    TSB_PU_CR_PU1C = 0;             // Disable PU1 as output
                    TSB_PU_FR6_PU1F6 = 0;           // Disable the function output on PU1
                }
            }

            if (phase == 2){
                /* Set the Clock supply and stop register A for Phase U, V */
                TSB_PU_CR_PU0C = 1;             // Enables PU0 as output
                TSB_PU_FR6_PU0F6 = 1;           // Enables the function output on PU0
                TSB_PU_CR_PU2C = 1;             // Enables PU2 as output
                TSB_PU_FR6_PU2F6 = 1;           // Enables the function output on PU2

                if (comp){
                    /* U, V Phase and X, W Phase (Compliment) Control Register */
                    PORTMD_UPPMD_LPPMD(PMDx);       // Set the PWM to have a PMD output on Upper-Phase and Lower-Phase
                    TSB_PU_CR_PU1C = 1;             // Enables PU1 as output
                    TSB_PU_FR6_PU1F6 = 1;           // Enables the function output on PU1
                    TSB_PU_CR_PU3C = 1;             // Enables PU3 as output
                    TSB_PU_FR6_PU3F6 = 1;           // Enables the function output on PU3
                }
                else {
                    TSB_PU_CR_PU1C = 0;             // Disable PU1 as output
                    TSB_PU_FR6_PU1F6 = 0;           // Disable the function output on PU1
                    TSB_PU_CR_PU3C = 0;             // Disable PU3 as output
                    TSB_PU_FR6_PU3F6 = 0;           // Disable the function output on PU3
                }
            }

            if (phase == 3){
                /* Set the Clock supply and stop register A for Phase U, V, W */
                TSB_PU_CR_PU0C = 1;             // Enables PU0 as output
                TSB_PU_FR6_PU0F6 = 1;           // Enables the function output on PU0
                TSB_PU_CR_PU2C = 1;             // Enables PU2 as output
                TSB_PU_FR6_PU2F6 = 1;           // Enables the function output on PU2
                TSB_PU_CR_PU4C = 1;             // Enables PU4 as output
                TSB_PU_FR6_PU4F6 = 1;           // Enables the function output on PU4

                if (comp){
                    /* U, V, W Phase and X, Y, Z Phase (Compliment) Control Register */
                    PORTMD_UPPMD_LPPMD(PMDx);       // Set the PWM to have a PMD output on Upper-Phase and Lower-Phase
                    TSB_PU_CR_PU1C = 1;             // Enables PU1 as output
                    TSB_PU_FR6_PU1F6 = 1;           // Enables the function output on PU1
                    TSB_PU_CR_PU3C = 1;             // Enables PU3 as output
                    TSB_PU_FR6_PU3F6 = 1;           // Enables the function output on PU3
                    TSB_PU_CR_PU5C = 1;             // Enables PU5 as output
                    TSB_PU_FR6_PU5F6 = 1;           // Enables the function output on PU5
                }
                else {
                    TSB_PU_CR_PU1C = 0;             // Disable PU1 as output
                    TSB_PU_FR6_PU1F6 = 0;           // Disable the function output on PU1
                    TSB_PU_CR_PU3C = 0;             // Disable PU3 as output
                    TSB_PU_FR6_PU3F6 = 0;           // Disable the function output on PU3
                    TSB_PU_CR_PU5C = 0;             // Disable PU5 as output
                    TSB_PU_FR6_PU5F6 = 0;           // Disable the function output on PU5
                }
            }
            break;
    }
    EMG_Disable(PMDx);
    EMGCR_EMGISEL_DISABLE(PMDx);                    // Disable the EMG Input Port
    //MDEN_PWMEN_ENABLE(PMDx);                        // Enable the PWM function
}

/*===================================================================
        Disable the EMG function by setting to 0x5A and 0xA5
 ===================================================================*/
void EMG_Disable(TSB_PMD_TypeDef * PMDx){
    EMGREL_EMGREL(PMDx, 0x5A);
    EMGREL_EMGREL(PMDx, 0xA5);
    EMGCR_EMGEN_DISABLE(PMDx);
}

/*===================================================================
    Set PWM Form (Sawtooth, Triangle, Reversed Sawtooth, etc)
 ===================================================================*/
void setPWM_Form(TSB_PMD_TypeDef * PMDx){
    MDEN_PWMEN_DISABLE(PMDx);       // Disable PWM to change its configuration

    MDCR_DTYMD_INDEP(PMDx);         // Duty Mode independent for each phase
    MDCR_DSYNCS_CENTER(PMDx);       // Update timing of the execution buffer at each phase PWM center

    /* Wave Form Shape ( Sawtooth, Triangle, Reversed Sawtooth, Reversed Triangle) */
    MDCR_UPWMMD_TRIANGLE(PMDx);     // U-phase PWM Carrier is a Triangle Wave
    MDCR_VPWMMD_TRIANGLE(PMDx);     // V-phase PWM Carrier is a Triangle Wave
    MDCR_WPWMMD_TRIANGLE(PMDx);     // V-phase PWM Carrier is a Triangle Wave

    /* Output the U,V,W Phases to a PWM Signal */
    MDOUT_UPWM_PWM(PMDx);           // Set U-Phase output to a PWM
    MDOUT_VPWM_PWM(PMDx);          // Set V-Phase output to a PWM
    MDOUT_WPWM_PWM(PMDx);           // Set W-Phase output to a PWM

    /* Dead Time Correction */
    MDCR_DTCREN_ENABLE(PMDx);       // Enables Dead Time Correction

    /* Output Polarity for Upper and Lower Phase */
    MDPOT_POLH_HIGH(PMDx);          // Upper-Phase High Active
    MDPOT_POLL_HIGH(PMDx);          // Lower-Phase High Active

    /* Update Timing of the Execution Buffer */
    MDPOT_PSYNCS_END(PMDx);         // Each Phase PWM Center
    MDPOT_SYNCS_GENERAL(PMDx);      // General purpose timer interrupt

    //MDEN_PWMEN_ENABLE(PMDx);        // Enable the PWM function
}

/*===================================================================
    Set PWM Dead Time (DT = value * 4/fsys (fsys = System Clock))
 ===================================================================*/
void setPWM_DeadTime(TSB_PMD_TypeDef * PMDx, uint32_t value){
    MDEN_PWMEN_DISABLE(PMDx);       // Disable PWM to change its configuration
    DTR_DTR(PMDx, value);           // Set the Dead Time based on the input value
    //MDEN_PWMEN_ENABLE(PMDx);        // Enable PWM Register
}

/*===================================================================
    Set PWM Frequency (Freq = fsys*value/2^24 (fsys = System Clock))
 ===================================================================*/
void setPWM_Frequency(TSB_PMD_TypeDef * PMDx, uint32_t value){
    PWMCR_RATE(PMDx, value);     // Set the frequency of the PWM
}

/*===================================================================
    Set PWM Duty Ratio (0x8000 = 100% | 0x4000 = 50% | 0x0000 = 0%)
 ===================================================================*/
void setPWM_DutyRatio(TSB_PMD_TypeDef * PMDx, uint8_t phase, uint32_t value){
    if (phase == 'U')
        PWMCR_CMPU(PMDx, value);     // Set the Duty Ratio to its %
    if (phase == 'V')
        PWMCR_CMPV(PMDx, value);     // Set the Duty Ratio to its %
    if (phase == 'W')
        PWMCR_CMPW(PMDx, value);     // Set the Duty Ratio to its %
}

/*===================================================================
                    Read Register Value
 ===================================================================*/
uint32_t getMDEN_reg(TSB_PMD_TypeDef * PMDx){
    return PMDx->MDEN;
}

uint32_t getPORTMD_reg(TSB_PMD_TypeDef * PMDx){
    return PMDx->PORTMD;
}

uint32_t getMODESEL_reg(TSB_PMD_TypeDef * PMDx){
    return PMDx->MODESEL;
}

uint32_t getMDCR_reg(TSB_PMD_TypeDef * PMDx){
    return PMDx->MDCR;
}

uint32_t getCARSTA_reg(TSB_PMD_TypeDef * PMDx){
    return PMDx->CARSTA;
}

uint32_t getBCARI_reg(TSB_PMD_TypeDef * PMDx){
    return PMDx->CARSTA;
}

uint32_t getRATE_reg(TSB_PMD_TypeDef * PMDx){
    return PMDx->RATE;
}

uint32_t getCMPU_reg(TSB_PMD_TypeDef * PMDx){
    return PMDx->CMPU;
}

uint32_t getCMPV_reg(TSB_PMD_TypeDef * PMDx){
    return PMDx->CMPV;
}

uint32_t getCMPW_reg(TSB_PMD_TypeDef * PMDx){
    return PMDx->CMPW;
}

uint32_t getVPWMPH_reg(TSB_PMD_TypeDef * PMDx){
    return PMDx->VPWMPH;
}

uint32_t getWPWMPH_reg(TSB_PMD_TypeDef * PMDx){
    return PMDx->WPWMPH;
}

uint32_t getMDPOT_reg(TSB_PMD_TypeDef * PMDx){
    return PMDx->MDPOT;
}

uint32_t getMDOUT_reg(TSB_PMD_TypeDef * PMDx){
    return PMDx->MDOUT;
}

uint32_t getEMGCR_reg(TSB_PMD_TypeDef * PMDx){
    return PMDx->EMGCR;
}

uint32_t getEMGSTA_reg(TSB_PMD_TypeDef * PMDx){
    return PMDx->EMGSTA;
}

uint32_t getEMGREL_reg(TSB_PMD_TypeDef * PMDx){
    return PMDx->EMGREL;
}

uint32_t getOVVCR_reg(TSB_PMD_TypeDef * PMDx){
    return PMDx->OVVCR;
}

uint32_t getOVVSTA_reg(TSB_PMD_TypeDef * PMDx){
    return PMDx->OVVSTA;
}

uint32_t getDTR_reg(TSB_PMD_TypeDef * PMDx){
    return PMDx->DTR;
}

uint32_t getTRGCMP0_reg(TSB_PMD_TypeDef * PMDx){
    return PMDx->TRGCMP0;
}

uint32_t getTRGCMP1_reg(TSB_PMD_TypeDef * PMDx){
    return PMDx->TRGCMP1;
}

uint32_t getTRGCMP2_reg(TSB_PMD_TypeDef * PMDx){
    return PMDx->TRGCMP2;
}

uint32_t getTRGCMP3_reg(TSB_PMD_TypeDef * PMDx){
    return PMDx->TRGCMP3;
}

uint32_t getTRGCR_reg(TSB_PMD_TypeDef * PMDx){
    return PMDx->TRGCR;
}

uint32_t getTRGSYNCR_reg(TSB_PMD_TypeDef * PMDx){
    return PMDx->TRGSYNCR;
}

uint32_t getTRGMD_reg(TSB_PMD_TypeDef * PMDx){
    return PMDx->TRGMD;
}

uint32_t getTRGSEL_reg(TSB_PMD_TypeDef * PMDx){
    return PMDx->TRGSEL;
}

uint32_t getMBUFCR_reg(TSB_PMD_TypeDef * PMDx){
    return PMDx->MBUFCR;
}

uint32_t getSYNCCR_reg(TSB_PMD_TypeDef * PMDx){
    return PMDx->SYNCCR;
}

uint32_t getDBGOUTCR_reg(TSB_PMD_TypeDef * PMDx){
    return PMDx->DBGOUTCR;
}
/*===================================================================*/

