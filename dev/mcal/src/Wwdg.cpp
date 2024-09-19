/**
 * @file Wwdg.cpp
 * @author Noran
 * @version 0.1
 * @date 2024-05-1
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "mcal/inc/stm32f103xx.h"
#include "utils/inc/Types.h"
#include "utils/inc/Assert.h"
#include "mcal/inc/Nvic.h"
#include "mcal/inc/Wwdg.h"

using namespace stm32::registers::rcc; 
using namespace stm32::dev::mcal::nvic;
using namespace stm32::dev::mcal::wwdg;
using namespace stm32::registers::wwdg;

#define TO_STRING(str_)  #str_

#define WWDG_CONFIG_ERROR(error_) \
    TO_STRING(Invalid Wwdg error_)

#define CHECK_WWDG_CONFIG() \
    STM32_ASSERT((config_.windowValue < 0x80), WWDG_CONFIG_ERROR(Window Value)); \
    STM32_ASSERT((config_.counterValue >= 0x40), WWDG_CONFIG_ERROR(Counter Value Lower Bound)); \
    STM32_ASSERT((config_.counterValue < 0x80), WWDG_CONFIG_ERROR(Counter Value Upper Bound)); \
    STM32_ASSERT((config_.counterValue > config_.windowValue), \
                  WWDG_CONFIG_ERROR(Counter_and_Window Relationship)); \
    STM32_ASSERT((config_.prescaler >= kDiv2) && (config_.prescaler <= kDiv8), \
                  WWDG_CONFIG_ERROR(Prescaler));

Wwdg::Wwdg(const Config& config) : config_(config) {
    CHECK_WWDG_CONFIG();
    Init();
}

void Wwdg::Init() {
    // Set prescaler
    WWDG->CFR.WDGTB = static_cast<RegWidth_t>(config_.prescaler);
    
    // Set window value
    WWDG->CFR.W = config_.windowValue;

    // Set counter value and enable WWDG
    WWDG->CR.T = config_.counterValue;
    WWDG->CR.WDGA = 1;
}

void Wwdg::EnableInterrupt() {
    // Enable Early Wakeup Interrupt
    WWDG->CFR.EWI = 1;
    Nvic::EnableInterrupt(kWWDG_IRQn);
}

void Wwdg::DisableInterrupt() {
    // Disable Early Wakeup Interrupt
    WWDG->CFR.EWI = 0;
    Nvic::DisableInterrupt(kWWDG_IRQn);
}

bool Wwdg::IsEarlyWakeupFlagSet()  {
    return WWDG->SR.EWIF != 0;
}

void Wwdg::ClearEarlyWakeupFlag() {
    WWDG->SR.registerVal = 0;
}
