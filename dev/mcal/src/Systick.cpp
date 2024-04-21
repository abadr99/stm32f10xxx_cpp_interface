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

ASSERT_MEMBER_OFFSET(SystickRegDef, CTRL,            0);
ASSERT_MEMBER_OFFSET(SystickRegDef, LOAD,         sizeof(RegWidth_t) * 1);
ASSERT_MEMBER_OFFSET(SystickRegDef, VAL,          sizeof(RegWidth_t) * 2);


#define SYSTICK_MAX_VALUE   GetOnes<uint32_t>(24)  //  24 bit

/*Global Pointer to Function isr*/
static void(*PointerToISR)(void) = NULL;

Systick::Systick() {
    SYSTICK->CTRL.ENABLE = 1;
    SYSTICK->CTRL.TICKINT = 0;
}
void Systick::Delay_ms(CLKSource clksource, uint32_t value) {
    STM32_ASSERT((value*1000) <= SYSTICK_MAX_VALUE);
    SYSTICK->CTRL.CLKSOURCE = clksource;
    SYSTICK->LOAD = value * 1000;
    while (SYSTICK->CTRL.COUNTFLAG == 0) {}
    SYSTICK->CTRL.COUNTFLAG = 0;
}
void Systick::Delay_micro_s(CLKSource clksource, uint32_t value) {
    STM32_ASSERT(value <= SYSTICK_MAX_VALUE);
    SYSTICK->CTRL.CLKSOURCE = clksource;
    SYSTICK->LOAD = value;
    while (SYSTICK->CTRL.COUNTFLAG == 0) {}
    SYSTICK->CTRL.COUNTFLAG = 0;
}
void Systick::Delay_By_Exception(CLKSource clksource, uint32_t value, pFunction * func) {
    STM32_ASSERT(func != NULL && value <= SYSTICK_MAX_VALUE);
    SYSTICK->CTRL.CLKSOURCE = clksource;
    SYSTICK->CTRL.TICKINT = 1;
    SYSTICK->LOAD = value;
    PointerToISR = *func;
}
uint32_t Systick::GetElapsedTime(void) {
    return SYSTICK->LOAD - SYSTICK->VAL;
}
void SysTick_Handler(void) {
    PointerToISR();
    SYSTICK->CTRL.COUNTFLAG = 0;
}
