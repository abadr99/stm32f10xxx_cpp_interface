/**
 * @file Peripherals.h
 * @author
 * @brief 
 * @version 0.1
 * @date 2024-09-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

// Peripheral-name   Bridge     
#define PERIPHERALS\
    P(DMA1,        AHB)  /* AHB BEGINS --- */ \
    P(DMA2,        AHB) \
    P(SRAM,        AHB) \
    P(FLITF,       AHB) \
    P(CRC,         AHB)   /* AHB ENDS --- */ \
    P(TIM2,        APB1)  /* APB1 BEGINS --- */\
    P(TIM3,        APB1) \
    P(TIM4,        APB1) \
    P(TIM5,        APB1) \
    P(TIM6,        APB1) \
    P(TIM7,        APB1) \
    P(WWDG,        APB1) \
    P(SPI2,        APB1) \
    P(SPI3,        APB1) \
    P(USART2,      APB1) \
    P(USART3,      APB1) \
    P(USART4,      APB1) \
    P(USART5,      APB1) \
    P(I2C1,        APB1) \
    P(I2C2,        APB1) \
    P(CAN,         APB1) \
    P(BKP,         APB1) \
    P(PWR,         APB1) \
    P(DAC,         APB1)  /* APB1 ENDS --- */\
    P(AFIO,        APB2)  /* APB2 BEGINS --- */\
    P(IOPA,        APB2) \
    P(IOPB,        APB2) \
    P(IOPC,        APB2) \
    P(IOPD,        APB2) \
    P(IOPE,        APB2) \
    P(ADC1,        APB2) \
    P(ADC2,        APB2) \
    P(TIM1,        APB2) \
    P(SPI1,        APB2) \
    P(USART1,      APB2) /* APB2 ENDS --- */

namespace stm32 {
namespace peripherals {
    enum class Peripheral {
        kRCC,
        // -- CORE PERIPHERALS 
        kNVIC,
        kSCB,
        kSYSTICK,
        // -- MCU PERIPHERALS
        kEXTI,
        kRTC,
        kIWDG,
        kFLASH,
        #define P(name_, ignore_)       k##name_,
        PERIPHERALS
        #undef P
        kUnknown,
    };
}  // namespace peripherals
}  // namespace stm32

