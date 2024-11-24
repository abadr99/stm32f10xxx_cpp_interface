/**
 * @file EXTI.cpp
 * @author
 * @brief 
 * @version 0.1
 * @date 2024-04-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */
// --- INCLUDES
#include "mcal/stm32f103xx.h"
#include "mcal/Pin.h"
#include "utils/BitManipulation.h"
#include "utils/Assert.h"
#include "mcal/Exti.h"

// --- IMPORT USED NAMESPACES
using namespace stm32;
using namespace stm32::type;
using namespace stm32::registers::exti;
using namespace stm32::registers::afio;
using namespace stm32::registers::rcc;
using namespace stm32::dev::mcal::exti;

// --- CHECK 'EXTI' LAYOUT
ASSERT_STRUCT_SIZE(EXTIRegDef, (sizeof(RegWidth_t) * 6));
ASSERT_MEMBER_OFFSET(EXTIRegDef, IMR, 0);
ASSERT_MEMBER_OFFSET(EXTIRegDef, EMR,   sizeof(RegWidth_t) * 1);
ASSERT_MEMBER_OFFSET(EXTIRegDef, RTSR,  sizeof(RegWidth_t) * 2);
ASSERT_MEMBER_OFFSET(EXTIRegDef, FTSR,  sizeof(RegWidth_t) * 3);
ASSERT_MEMBER_OFFSET(EXTIRegDef, SWIER, sizeof(RegWidth_t) * 4);
ASSERT_MEMBER_OFFSET(EXTIRegDef, PR,    sizeof(RegWidth_t) * 5);
#define TO_STRING(str_)  #str_

#define EXTI_CONFIG_ERROR(error_) \
    TO_STRING(Invalid Exti error_)

// --- INITIALIZE 'Exti' STATIC MEMBER VARIABLE
pFunction Exti::pGlobalCallBackFunctions[7] = {nullptr};

volatile EXTIRegDef* Exti::EXTI = nullptr;

void Exti::Enable(const EXTI_Config& config) {
    STM32_ASSERT(((config.trigger >= kRising) 
                && (config.trigger <= kBoth)), EXTI_CONFIG_ERROR(Trigger));
    STM32_ASSERT(((config.line >= kExti0) && (config.line <= kExti19)),
                  EXTI_CONFIG_ERROR(line));
    EXTI = reinterpret_cast<volatile EXTIRegDef*>(Addr<Peripheral::kEXTI >::getBaseAddr());
    Exti::InitAFIOReg(config.line, config.port);
    EXTI->IMR = util::SetBit<uint32_t>(EXTI->IMR, config.line);
    Exti::SetTrigger(config.line, config.trigger);
}

void Exti::Disable(const EXTI_Config& config) {
    EXTI->IMR = util::ClearBit<uint32_t>(EXTI->IMR, config.line);
    Exti::ClrTrigger(config.line, config.trigger);
}

void Exti::SetPendingFlag(const EXTI_Config& config) {
    if (Exti::GetPendingBit(config.line) == 1) { 
        return;  // EARLY EXIT
    }
    EXTI->PR = util::SetBit<uint32_t>(EXTI->PR, config.line);
}

void Exti::ClearPendingFlag(const EXTI_Config& config) {
    if (Exti::GetPendingBit(config.line) == 0) { 
        return;     // EARLY EXIT
    }
    EXTI->PR = util::SetBit<uint32_t>(EXTI->PR, config.line);
}

bool Exti::GetPendingFlag(const EXTI_Config& config) {
    return Exti::GetPendingBit(config.line);
}

void Exti::SetpCallBackFunction(Line line, void (*pCallBackFun)(void)) {
    STM32_ASSERT((line >= kExti0) && (line <= kExti19), EXTI_CONFIG_ERROR(Line));
    if (line >= Line::kExti5 && line <= Line::kExti9) {
        pGlobalCallBackFunctions[5] = pCallBackFun;
    } else if (line >= Line::kExti10 && line <= Line::kExti15) {
        pGlobalCallBackFunctions[6] = pCallBackFun;
    } else {
        pGlobalCallBackFunctions[static_cast<uint8_t>(line)] = pCallBackFun;
    }
}
pFunction Exti::GetpCallBackFunction(Line line) {  
    STM32_ASSERT(((line >= kExti5) && (line <= kExti9)) 
                || ((line >= kExti10) && (line <= kExti15)), EXTI_CONFIG_ERROR(Line)); 
    pFunction pRetFunction = nullptr;
    if (line >= Line::kExti5 && line <= Line::kExti9) {
        return pGlobalCallBackFunctions[5];
    } else if (line >= Line::kExti10 && line <= Line::kExti15) {
        return pGlobalCallBackFunctions[6];
    }
    return pRetFunction = pGlobalCallBackFunctions[static_cast<uint8_t>(line)];
}

void Exti::InitAFIOReg(Line line, Port port) {
    uint8_t startBit = (static_cast<uint8_t>(line) % 4) << 2;
    uint8_t CRx = static_cast<uint8_t>(line) >> 2;
    AFIO->EXTICRx[CRx] = util::WriteBits<uint32_t>(startBit, startBit + 3, AFIO->EXTICRx[CRx], port);       // NOLINT
}

void Exti::SetTrigger(Line line, Trigger trigger) {
    STM32_ASSERT(((trigger >= kRising) && (trigger <= kBoth)), EXTI_CONFIG_ERROR(Trigger));
    STM32_ASSERT((line >= kExti0) && (line <= kExti19), EXTI_CONFIG_ERROR(Line));
    if (trigger == Trigger::kRising || trigger == Trigger::kBoth) {
        EXTI->RTSR = util::SetBit<uint32_t>(EXTI->RTSR, line);
    }
    if (trigger == Trigger::kFalling || trigger == Trigger::kBoth) {
        EXTI->FTSR = util::SetBit<uint32_t>(EXTI->FTSR, line);
    }
}

void Exti::ClrTrigger(Line line, Trigger trigger) {
    STM32_ASSERT(((trigger >= kRising) && (trigger <= kBoth)), EXTI_CONFIG_ERROR(Trigger));
    STM32_ASSERT((line >= kExti0) && (line <= kExti19), EXTI_CONFIG_ERROR(Line));
    if (trigger == Trigger::kRising || trigger == Trigger::kBoth) {
        EXTI->RTSR = util::ClearBit<uint32_t>(EXTI->RTSR, line);
    }
    if (trigger == Trigger::kFalling || trigger == Trigger::kBoth) {
        EXTI->RTSR = util::ClearBit<uint32_t>(EXTI->RTSR, line);
    }
}

bool Exti::GetPendingBit(Line line) {
    uint32_t Bit = static_cast<uint32_t>(line);
    return util::ExtractBit<uint32_t>(EXTI->PR, Bit);
}


// ISRs
#define EXTI_ISR(N)\
    extern "C" void EXTI##N##_IRQHandler(void) {\
        /* Clear pending flag to ensure that the same ISR won't execute again */\
        auto exti_reg = reinterpret_cast<volatile EXTIRegDef*>(Addr<Peripheral::kEXTI >::getBaseAddr());\
        exti_reg->PR |= (1 << static_cast<uint8_t>(Line::kExti##N));\
        pFunction fun = Exti::GetpCallBackFunction(Line::kExti##N);\
        if (fun != nullptr) {\
            fun();\
        }\
    }\

EXTI_ISR(0)
EXTI_ISR(1)
EXTI_ISR(2)
EXTI_ISR(3)
EXTI_ISR(4)

// TODO(@Manar): ISR for EXTI9_5 and EXTI15_10 are not implemented yet.
extern "C" void EXTI9_5_IRQHandler(void) {
}

extern "C" void EXTI15_10_IRQHandler(void) {
}
