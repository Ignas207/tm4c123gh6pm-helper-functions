/**
 * @file helper_functions.h
 * @author Ignas Brazauskas
 * @brief Provides macros and other usefull stuff
 * @version 1.0
 * @date 2022-10-31
 *
 */
#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include "tm4c123gh6pm.h"

typedef unsigned char uint8_t;
typedef char int8_t;
typedef unsigned short uint16_t;
typedef short int16_t;
typedef unsigned long uint32_t;
typedef long int32_t;
// typedef long long int64_t;
// typedef unsigned long long uint64_t;

#define SET_BIT(REG, BIT) ((REG) |= (BIT))
#define CLEAR_BIT(REG, BIT) ((REG) &= ~(BIT))
#define READ_BIT(REG, BIT) ((REG) & (BIT))
#define CLEAR_REG(REG) ((REG) = (0x0))
#define WRITE_REG(REG, VAL) ((REG) = (VAL))
#define READ_REG(REG) ((REG))
#define MODIFY_REG(REG, CLEARMASK, SETMASK) WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#define DATA_R_MASK (0x3FCU)
#define DIR_R_MASK (0x400U)
#define IS_R_MASK (0x404U)
#define AFSEL_R_MASK (0x420U)
#define AMSEL_R_MASK (0x528U)
#define DEN_R_MASK (0x51CU)
#define LOCK_R_MASK (0x520U)
#define CR_R_MASK (0x524U)
#define PUR_R_MASK (0x510U)
#define PCTL_R_MASK (0x52CU)

/**
 * @brief Simple delay for a max of 256 tiks.
 *
 */
#define SIMPLE_DELAY(TIKS)      \
    do                          \
    {                           \
        volatile uint8_t i = 0; \
        do                      \
        {                       \
            i++;                \
        } while (i < (TIKS));   \
                                \
    } while (0)

// #define PORTF_LOCKING_FIX

/**
 * @brief Configures the ports pins.
 *
 * @param PORT GPIO_PORTX_DATA_BITS_R register!
 * @param PIN_OUT output pin to set
 * @param PIN_IN input pin to set
 * @param AMSEL analog config
 * @param AFSEL alt function config
 * @param PCTL
 * @param PUR Pins to pull-up
 * @param DEN digital IO config (pin to enable)
 *
 */
#define PORT_CONFIG(PORT, PIN_OUT, PIN_IN, AMSEL, PCTL, AFSEL, PUR, DEN)         \
    do                                                                           \
    {                                                                            \
        SET_BIT(SYSCTL_RCGC2_R, (1 << (((PORT)-GPIO_PORTA_DATA_BITS_R) >> 12))); \
        SIMPLE_DELAY(3);                                                         \
        SET_BIT((PORT) + AMSEL_R_MASK, (AMSEL));                                 \
        SET_BIT((PORT) + PCTL_R_MASK, (PCTL));                                   \
        SET_BIT((PORT) + DIR_R_MASK, ~(PIN_IN) + (PIN_OUT));                     \
        SET_BIT((PORT) + AFSEL_R_MASK, (AFSEL));                                 \
        SET_BIT((PORT) + PUR_R_MASK, (PUR));                                     \
        SET_BIT((PORT) + DEN_R_MASK, (DEN));                                     \
    } while (0)

// if ((PORT) == GPIO_PORTF_DATA_R) \
//             if(~(PIN_OUT)&1 || ~(PIN_IN)&1 ) \
//             { \
                
//             } \

#endif