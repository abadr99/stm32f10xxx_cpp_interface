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
#include "utils/inc/BitSet.h"
#include "utils/inc/Assert.h"
#include "utils/inc/BitManipulation.h"
#include "mcal/inc/Nvic.h"

using namespace stm32::dev::mcal::nvic; // NOLINT[build/namespaces]
using namespace stm32::registers::nvic; // NOLINT[build/namespaces]

void Nvic::EnableInterrupt(InterruptID id) {
    NVIC->ISER[static_cast<uint32_t>(id) >> 5] = (1 << (static_cast<uint32_t>(id) & 0x1f));
}
void Nvic::DisableInterrupt(InterruptID id) {
    NVIC->ICER[static_cast<uint32_t>(id) >> 5] = (1 << (static_cast<uint32_t>(id)) & 0x1f);
}
void Nvic::SetPendingFlag(InterruptID id) {
    NVIC->ISPR[static_cast<uint32_t>(id) >> 5] = (1 << ((static_cast<uint32_t>(id)) & 0x1f));
}
void Nvic::ClearPendingFlag(InterruptID id) {
    NVIC->ICPR[static_cast<uint32_t>(id) >> 5] = (1 << (static_cast<uint32_t>(id)) & 0x1f);
}
bool Nvic::GetActiveFlag(InterruptID id) {
    return ((NVIC->IABR[static_cast<uint32_t>(id) >> 5] >> (static_cast<uint32_t>(id) & 0x1f)) & 0x1);  //  NOLINT
}
void Nvic::SetPriority(InterruptID id, uint8_t priority) {
    NVIC->IPR[id] = priority << 4;
}
void Nvic::SetPriorityGroup(PriorityGroup group) {
    SCB->AIRCR = group;
}
