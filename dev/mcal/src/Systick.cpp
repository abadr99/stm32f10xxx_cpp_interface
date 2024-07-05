/**
 * @file Systick.cpp
 * @author ManarAbdelraouf
 * @version 0.1
 * @date 2024-04-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "mcal/inc/stm32f103xx.h"
#include "utils/inc/Types.h"
#include "utils/inc/BitManipulation.h"
#include "mcal/inc/Systick.h"
#include "utils/inc/Assert.h"

using namespace stm32::utils::bit_manipulation;
using namespace stm32::dev::mcal::systick;
using namespace stm32::registers::systick;

// Some asserts to make sure SYSTICK struct members are in correct orders
ASSERT_STRUCT_SIZE(SystickRegDef, (sizeof(RegWidth_t) * 3));

ASSERT_MEMBER_OFFSET(SystickRegDef, CTRL, 0);
ASSERT_MEMBER_OFFSET(SystickRegDef, LOAD, sizeof(RegWidth_t) * 1);
ASSERT_MEMBER_OFFSET(SystickRegDef, VAL,  sizeof(RegWidth_t) * 2);


#define SYSTICK_MAX_VALUE   GetOnes<uint32_t>(24)  //  24 bit

pFunction Systick::PointerToISR = nullptr;

void Systick::Enable(CLKSource clksource) {
    SYSTICK->CTRL.ENABLE = 1;
    SYSTICK->CTRL.TICKINT = 0;
    SYSTICK->CTRL.CLKSOURCE = clksource;
    Helper_SetPointerToISR(nullptr);
}

void Systick::Delay_ms(uint32_t value) {
    STM32_ASSERT((value*1000) <= SYSTICK_MAX_VALUE);
    SYSTICK->LOAD = value * 1000;
    while (SYSTICK->CTRL.COUNTFLAG == 0) {}
    SYSTICK->CTRL.COUNTFLAG = 0;
}

void Systick::Delay_us(uint32_t value) {
    STM32_ASSERT(value <= SYSTICK_MAX_VALUE);
    SYSTICK->LOAD = value;
    while (SYSTICK->CTRL.COUNTFLAG == 0) {}
    SYSTICK->CTRL.COUNTFLAG = 0;
}

void Systick::Delay_By_Exception(uint32_t value, pFunction func) {
    STM32_ASSERT(func != nullptr && value <= SYSTICK_MAX_VALUE);
    SYSTICK->CTRL.TICKINT = 1;
    SYSTICK->LOAD = value;
    Helper_SetPointerToISR(func);
}

uint32_t Systick::GetElapsedTime() {
    return SYSTICK->LOAD - SYSTICK->VAL;
}

void Systick::Disable() {
    SYSTICK->CTRL.ENABLE = 0;
    SYSTICK->CTRL.CLKSOURCE = kAHB;
    Helper_SetPointerToISR(nullptr);
}

void Systick::Helper_SetPointerToISR(pFunction func) {
    Systick::PointerToISR = func;
}
pFunction Systick::Helper_GetPointerToISR() {
    return Systick::PointerToISR;
}

// void SysTick_Handler(void) {
//     Helper_GetPointerToISR()();
//     SYSTICK->CTRL.COUNTFLAG = 0;
// }
