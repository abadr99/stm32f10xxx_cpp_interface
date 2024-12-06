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
#include "mcal/stm32f103xx.h"
#include "utils/Types.h"
#include "utils/BitSet.h"
#include "utils/Assert.h"
#include "utils/BitManipulation.h"
#include "mcal/Nvic.h"

using namespace stm32;
using namespace stm32::type;
using namespace stm32::dev::mcal::nvic;
using namespace stm32::registers::nvic;

static volatile NvicRegDef*  NVIC = reinterpret_cast<volatile NvicRegDef*>
                                    (Addr<Peripheral::kNVIC>::getBaseAddr());
static volatile SCBRegDef*  SCB = reinterpret_cast<volatile SCBRegDef*>
                                  (Addr<Peripheral::kSCB>::getBaseAddr());

Id::Id(InterruptID id) : id_(id) {}
uint8_t Id::Pos() {return util::ExtractBits<int8_t, 0, 4>(id_);}
uint8_t Id::Idx() {return util::ExtractBits<int8_t, 5, 7>(id_);}
InterruptID Id::Val() {return id_;}

void Nvic::EnableInterrupt(Id id) {
    NVIC->ISER[id.Idx()] = util::SetBit<RegWidth_t>(NVIC->ISER[id.Idx()], id.Pos());
}

void Nvic::DisableInterrupt(Id id) {
    NVIC->ICER[id.Idx()] = util::SetBit<RegWidth_t>(NVIC->ICER[id.Idx()], id.Pos());
}

void Nvic::SetPendingFlag(Id id) {
    NVIC->ISPR[id.Idx()] = util::SetBit<RegWidth_t>(NVIC->ISPR[id.Idx()], id.Pos());
}

void Nvic::ClearPendingFlag(Id id) {
    NVIC->ICPR[id.Idx()] = util::SetBit<RegWidth_t>(NVIC->ICPR[id.Idx()], id.Pos());
}

bit Nvic::GetActiveFlag(Id id) {
    return util::ExtractBit(NVIC->IABR[id.Idx()], id.Pos());
}

void Nvic::SetPriority(Id id, uint8_t priority) {
    NVIC->IPR[id.Val()] = priority << 4;
}

void Nvic::SetPriorityGroup(PriorityGroup group) {
    SCB->AIRCR = group;
}

void Nvic::Reset() {
    for (uint8_t i = 0 ; i < 3 ; ++i) {
        NVIC->ISER[i] = 0;
        NVIC->ICER[i] = 0;
        NVIC->ISPR[i] = 0;
        NVIC->ICPR[i] = 0;
        NVIC->IPR[i]  = 0; 
    }
}
