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
#include "utils/inc/Assert.h"
#include "mcal/inc/EXTI.h"

using namespace stm32::registers::exti;
using namespace stm32::registers::afio;
using namespace stm32::registers::rcc;
using namespace stm32::dev::mcal::exti;
using namespace stm32::utils::bit_manipulation;

// Some asserts to make sure EXTI struct members are in correct orders
ASSERT_STRUCT_SIZE(EXTIRegDef, (sizeof(RegWidth_t) * 6));

ASSERT_MEMBER_OFFSET(EXTIRegDef, IMR, 0);
ASSERT_MEMBER_OFFSET(EXTIRegDef, EMR,   sizeof(RegWidth_t) * 1);
ASSERT_MEMBER_OFFSET(EXTIRegDef, RTSR,  sizeof(RegWidth_t) * 2);
ASSERT_MEMBER_OFFSET(EXTIRegDef, FTSR,  sizeof(RegWidth_t) * 3);
ASSERT_MEMBER_OFFSET(EXTIRegDef, SWIER, sizeof(RegWidth_t) * 4);
ASSERT_MEMBER_OFFSET(EXTIRegDef, PR,    sizeof(RegWidth_t) * 5);

void Exti::Enable(const EXTI_Config& config) {
    Exti::Helper_InitAFIOReg(config.line, config.port);

    EXTI->IMR |=  1 << (uint32_t)config.line;

    Exti::Helper_SetTrigger(config.line, config.trigger);
}

void Exti::Disable(const EXTI_Config& config) {
    EXTI->IMR &= ~(1 << (uint32_t)config.line);

    Exti::Helper_ClrTrigger(config.line, config.trigger);
}

void Exti::SetPendingFlag(const EXTI_Config& config) {
    if (Exti::Helper_GetPendingBit(config.line) == 0) { 
      EXTI->PR |= 1 << (uint32_t)config.line;
    }
}

void Exti::ClearPendingFlag(const EXTI_Config& config) {
    if (Exti::Helper_GetPendingBit(config.line) == 1) { 
      EXTI->PR |= 1 << (uint32_t)config.line;
    }
}

uint8_t Exti::GetPendingFlag(const EXTI_Config& config) {
    return Exti::Helper_GetPendingBit(config.line);
}

void Exti::Helper_InitAFIOReg(Line line, Port port) {
    uint8_t startBit = (static_cast<uint8_t>(line) % 4) << 2;
    uint8_t CRx = static_cast<uint8_t>(line) >> 2;

    AFIO->EXTICRx[CRx] = WriteBits<uint32_t>(startBit, startBit + 3, AFIO->EXTICRx[CRx], port);

    RCC->APB2ENR.AFIOEN = 1;
}

void Exti::Helper_SetTrigger(Line line, Trigger trigger) {
    if (trigger == Trigger::kRising || trigger == Trigger::kBoth) {
        EXTI->RTSR |= 1 << static_cast<uint32_t>(line);
    }
    if (trigger == Trigger::kFalling || trigger == Trigger::kBoth) {
        EXTI->FTSR |= 1 << static_cast<uint32_t>(line);
    }
}

void Exti::Helper_ClrTrigger(Line line, Trigger trigger) {
    if (trigger == Trigger::kRising || trigger == Trigger::kBoth) {
        EXTI->RTSR &= ~(1 << static_cast<uint32_t>(line));
    }
    if (trigger == Trigger::kFalling || trigger == Trigger::kBoth) {
        EXTI->FTSR &= ~(1 << static_cast<uint32_t>(line));
    }
}

uint8_t Exti::Helper_GetPendingBit(Line line) {
    uint32_t Bit = static_cast<uint32_t>(line);
    return  EXTI->PR & (1 << Bit);
}