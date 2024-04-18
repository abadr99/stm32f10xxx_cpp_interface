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
void nvic::EnableInterrupt(interruptID id) {
NVIC->ISER[((uint32_t)id) >> 5] = (1 << ((uint32_t)id) & 0x1f);
}
void nvic::DisableInterrupt(interruptID id) {
NVIC->ICER[((uint32_t)id) >> 5] = (1 << ((uint32_t)id) & 0x1f);
}
void nvic::SetPendingFlag(interruptID id) {
NVIC->ISPR[((uint32_t)id) >> 5] = (1 << ((uint32_t)id) & 0x1f);
}
void nvic::ClearPendingFlag(interruptID id) {
NVIC->ICPR[((uint32_t)id) >> 5] = (1 << ((uint32_t)id) & 0x1f);
}
