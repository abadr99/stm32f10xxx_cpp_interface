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

#define TO_STRING(str_)  #str_

#define WWDG_configERROR(error_) \
    TO_STRING(Invalid Wwdg error_)

#define CHECK_WWDG_CONFIG() \
    STM32_ASSERT((config.windowValue < 0x80), WWDG_configERROR(Window Value)); \
    STM32_ASSERT((config.counterValue >= 0x40), WWDG_configERROR(Counter Value Lower Bound)); \
    STM32_ASSERT((config.counterValue < 0x80), WWDG_configERROR(Counter Value Upper Bound)); \
    STM32_ASSERT((config.counterValue > config.windowValue), \
                  WWDG_configERROR(Counter_and_Window Relationship)); \
    STM32_ASSERT((config.prescaler >= kDiv2) && (config.prescaler <= kDiv8), \
                  WWDG_configERROR(Prescaler));

volatile WWDGRegDef* Wwdg::WWDG = nullptr;

template<typename T>
volatile T* Wwdg::GetPtr() { return nullptr; }

template<>
volatile WWDGRegDef* Wwdg::GetPtr<WWDGRegDef>() {
    return WWDG; 
}


void Wwdg::Init() {
    WWDG = reinterpret_cast<volatile WWDGRegDef*>(Addr<Peripheral::kWWDG >::Get());
}
void Wwdg::ApplyConfig(const Config& config) {
    CHECK_WWDG_CONFIG();
    // Set prescaler
    WWDG->CFR.WDGTB = static_cast<RegWidth_t>(config.prescaler);
    
    // Set window value
    WWDG->CFR.W = config.windowValue;

    // Set counter value and enable WWDG
    WWDG->CR.T = config.counterValue;
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
