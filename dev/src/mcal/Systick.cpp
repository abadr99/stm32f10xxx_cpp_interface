/**
 * @file Systick.cpp
 * @author ManarAbdelraouf
 * @version 0.1
 * @date 2024-04-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "mcal/stm32f103xx.h"
#include "utils/Types.h"
#include "utils/Util.h"
#include "utils/Constant.h"
#include "utils/BitManipulation.h"
#include "mcal/Systick.h"
#include "utils/Assert.h"

using namespace stm32;
using namespace stm32::type;
using namespace stm32::dev::mcal::systick;
using namespace stm32::registers::systick;

#define TO_STRING(str_)  #str_

#define SYSTICK_CONFIG_ERROR(error_) \
    TO_STRING(Invalid Systick error_)

// ------- ASSERTS TO ENSURE SYSTICK LAYOUT
ASSERT_STRUCT_SIZE(SystickRegDef, (sizeof(RegWidth_t) * 3));
ASSERT_MEMBER_OFFSET(SystickRegDef, CTRL, 0);
ASSERT_MEMBER_OFFSET(SystickRegDef, LOAD, sizeof(RegWidth_t) * 1);
ASSERT_MEMBER_OFFSET(SystickRegDef, VAL,  sizeof(RegWidth_t) * 2);

// ------- DEFINE SOME USEFUL CONSTANTS
static constexpr uint32_t kSystickMaxVal = util::GetOnes<uint32_t>(24);

typename Systick::pFunction Systick::PointerToISR = nullptr;

void Systick::Enable(CLKSource clksource) {
    STM32_ASSERT((clksource == kAHB_Div_8) || 
                 (clksource == kAHB), SYSTICK_CONFIG_ERROR(CLKSource));
    SYSTICK->CTRL.ENABLE = 1;
    SYSTICK->CTRL.TICKINT = 0;
    SYSTICK->CTRL.CLKSOURCE = clksource;
    SetPointerToISR(nullptr);
}

void Systick::SetCounterValue(uint32_t value) {
// STM32_ASSERT(value <= kSystickMaxVal);
    SYSTICK->CTRL.ENABLE = 1;
    SYSTICK->LOAD = value;
    util::BusyWait([&](){ return SYSTICK->CTRL.COUNTFLAG == 0; });
    SYSTICK->CTRL.COUNTFLAG = 0;
    SYSTICK->CTRL.ENABLE = 0;
}

void Systick::Delay_ms(uint32_t time_ms) {
    auto GetDivisor = []() {
        return SYSTICK->CTRL.CLKSOURCE == 1 ? 1000   // STK_CLK_AHB
                                            : 8000;  // STK_CLK_AHB_DIV_8
    };

    uint32_t loadValue = time_ms * (constant::kCpuFreq / GetDivisor());
    SetCounterValue(loadValue);
}

void Systick::Delay_us(uint32_t time_us) {
    auto GetDivisor = []() {
        return SYSTICK->CTRL.CLKSOURCE == 1 ? 1000000   // STK_CLK_AHB
                                            : 8000000;  // STK_CLK_AHB_DIV_8
    };
    uint32_t loadValue = (time_us * (constant::kCpuFreq / GetDivisor()));
    // DISABLE SYSTICK
    SYSTICK->CTRL.ENABLE = 0;
    SetCounterValue(loadValue);
}

void Systick::Delay_By_Exception(uint32_t value, pFunction func) {
// STM32_ASSERT(func != NULL && value <= kSystickMaxVal);
    SYSTICK->LOAD = value;
    SetPointerToISR(func);
    SYSTICK->CTRL.TICKINT = 1;
}

uint32_t Systick::GetElapsedTime() {
    return SYSTICK->LOAD - SYSTICK->VAL;
}

void Systick::Disable() {
    SYSTICK->CTRL.ENABLE = 0;
    SYSTICK->CTRL.CLKSOURCE = kAHB;
    SetPointerToISR(nullptr);
}

void Systick::SetPointerToISR(pFunction func) {
    Systick::PointerToISR = func;
}
typename Systick::pFunction Systick::GetPointerToISR() {
    return Systick::PointerToISR;
}

extern "C" void SysTick_Handler(void) {
    typename Systick::pFunction fun = Systick::GetPointerToISR();
    if (fun != NULL) {
        fun();
        SYSTICK->CTRL.ENABLE = 0;
        SYSTICK->VAL = 1;
    }
}

