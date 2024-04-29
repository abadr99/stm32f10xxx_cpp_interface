/**
 * @file EXTI.cpp
 * @author Manar
 * @brief 
 * @version 0.1
 * @date 2024-04-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "mcal/inc/stm32f103xx.h"
#include "mcal/inc/Pin.h"
#include "utils/inc/BitManipulation.h"
#include "mcal/inc/EXTI.h"

using namespace stm32::registers::exti;
using namespace stm32::registers::afio;
using namespace stm32::dev::mcal::exti;
using namespace stm32::utils::bit_manipulation;

void Exti::Enable(const EXTI_Config& config) {
    Exti::Helper_InitAFIOReg(config);
    EXTI->IMR |=  1 << (uint32_t)config.line;

    if (config.trigger == Trigger::Rising || config.trigger == Trigger::Both) {
        EXTI->RTSR |= 1 << (uint32_t)config.line;
    }
    if (config.trigger == Trigger::Falling || config.trigger == Trigger::Both) {
        EXTI->FTSR |= 1 << (uint32_t)config.line;
    }
}

void Exti::Disable(const EXTI_Config& config) {
    EXTI->IMR &= ~(1 << (uint32_t)config.line);

    if (config.trigger == Trigger::Rising || config.trigger == Trigger::Both) {
        EXTI->RTSR &= ~(1 << (uint32_t)config.line);
    }
    if (config.trigger == Trigger::Falling || config.trigger == Trigger::Both) {
        EXTI->FTSR &= ~(1 << (uint32_t)config.line);
    }
}
/*
void Exti::SetPendingFlag(const EXTI_Config& config) {
    uint32_t status = ExtractBits<uint32_t, (uint8_t)config.line>(EXTI->PR);
    if (status == 0) { 
    EXTI->PR |= 1 << (uint32_t)config.line;
    }
}

void Exti::ClearPendingFlag(const EXTI_Config& config) {
    uint32_t status = ExtractBits<uint32_t, (uint8_t)config.line>(EXTI->PR);
    if (status == 1) { 
    EXTI->PR |= 1 << (uint32_t)config.line;
    }
}

uint8_t Exti::GetPendingFlag(const EXTI_Config& config) {
   return ExtractBits<uint32_t, (uint8_t)config.line>(EXTI->PR);
}
*/
void Exti::Helper_InitAFIOReg(const EXTI_Config& config) {
    uint8_t startBit = ((uint8_t)config.line %4) << 2;
    AFIO->EXTICRx[(uint8_t)config.line >> 2] 
                            = WriteBits<uint32_t>(startBit, startBit + 3,
                                                  AFIO->EXTICRx[(uint8_t)config.line >> 2],
                                                  config.port);
}
