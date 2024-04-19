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
#include "Nvic.h"

using namespace stm32::dev::mcal::nvic; // NOLINT[build/namespaces]
using namespace stm32::registers::nvic; // NOLINT[build/namespaces]

void Nvic:: EnableInterrupt(interruptID id) {
NVIC->ISER[((uint32_t)id) >> 5] = (1 << ((uint32_t)id) & 0x1f);
}
void Nvic:: DisableInterrupt(interruptID id) {
NVIC->ICER[((uint32_t)id) >> 5] = (1 << ((uint32_t)id) & 0x1f);
}
void Nvic:: SetPendingFlag(interruptID id) {
NVIC->ISPR[((uint32_t)id) >> 5] = (1 << ((uint32_t)id) & 0x1f);
}
void Nvic:: ClearPendingFlag(interruptID id) {
NVIC->ICPR[((uint32_t)id) >> 5] = (1 << ((uint32_t)id) & 0x1f);
}
uint8_t Nvic:: GetActiveFlag(interruptID id) {
    return (NVIC->IABR[((uint32_t)id) >> 5] >> ((((uint32_t)id) & 0x1f)) & 0x1);
}
void Nvic:: SetPriority(interruptID id, uint8_t priority) {
    NVIC->IPR[id] = priority << 4;
}
