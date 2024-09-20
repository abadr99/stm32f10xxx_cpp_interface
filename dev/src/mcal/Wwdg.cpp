/**
 * @file Wwdg.cpp
 * @author Noran
 * @version 0.1
 * @date 2024-05-1
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "mcal/stm32f103xx.h"
#include "utils/Types.h"
#include "utils/Assert.h"
#include "mcal/Nvic.h"
#include "mcal/Wwdg.h"

using namespace stm32::registers::rcc; 
using namespace stm32::dev::mcal::nvic;
using namespace stm32::dev::mcal::wwdg;
using namespace stm32::registers::wwdg;

Wwdg::Wwdg(const Config& config) : config_(config) {
    // Validate configuration
    STM32_ASSERT(config_.windowValue < 0x80);
    STM32_ASSERT(config_.counterValue >= 0x40);
    STM32_ASSERT(config_.counterValue > config_.windowValue);
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
