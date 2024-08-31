/**
 * @file Nvic.cpp
 * @brief 
 * @version 0.1
 * @date 2024-03-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <stdint.h>
#include "mcal/inc/stm32f103xx.h"
#include "Types.h"
#include "utils/inc/BitSet.h"
#include "utils/inc/Assert.h"
#include "utils/inc/BitManipulation.h"
#include "mcal/inc/Nvic.h"

using namespace stm32::dev::mcal::nvic;
using namespace stm32::registers::nvic;
using namespace stm32::utils::bit_manipulation;
using namespace stm32::utils::types;

void Nvic::EnableInterrupt(Id id) {
    NVIC->ISER[id.Idx()] = SetBit<RegWidth_t>(NVIC->ISER[id.Idx()], id.Pos());
}

void Nvic::DisableInterrupt(Id id) {
    NVIC->ICER[id.Idx()] = SetBit<RegWidth_t>(NVIC->ICER[id.Idx()], id.Pos());
}

void Nvic::SetPendingFlag(Id id) {
    NVIC->ISPR[id.Idx()] = SetBit<RegWidth_t>(NVIC->ISPR[id.Idx()], id.Pos());
}

void Nvic::ClearPendingFlag(Id id) {
    NVIC->ICPR[id.Idx()] = SetBit<RegWidth_t>(NVIC->ICPR[id.Idx()], id.Pos());
}

bit Nvic::GetActiveFlag(Id id) {
    return ExtractBit(NVIC->IABR[id.Idx()], id.Pos());
}

void Nvic::SetPriority(Id id, uint8_t priority) {
    NVIC->IPR[id.Idx()] = priority << 4;
}

void Nvic::SetPriorityGroup(PriorityGroup group) {
    SCB->AIRCR = group;
}
