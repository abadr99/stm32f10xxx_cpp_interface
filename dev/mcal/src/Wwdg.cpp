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

Wwdg::Wwdg(const Config& config) : config_(config) {
        // Validate configuration
        assert(config_.windowValue < 0x80 && "Window value must be less than 0x80");
        assert(config_.counterValue >= 0x40 && "Counter value must be above 0x40");
        assert(config_.counterValue > config_.windowValue
               && "Counter value must be greater than window value");

        // Enable WWDG clock
        RCC->APB1ENR.WWDGEN = 1;
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
void Wwdg::enableInterrupt() {
        // Enable Early Wakeup Interrupt
        WWDG->CFR.EWI = 1;
        Nvic::EnableInterrupt(kWWDG);
}

void Wwdg::disableInterrupt() {
        // Disable Early Wakeup Interrupt
        WWDG->CFR.EWI = 0;
       Nvic::DisableInterrupt(kWWDG);
}

bool Wwdg::isEarlyWakeupFlagSet()  {
        return WWDG->SR.EWIF != 0;
}

void Wwdg::clearEarlyWakeupFlag() {
        WWDG->SR.registerVal = 0;
}
