/**
 * @file Timer.cpp
 * @author Manar Abdelraouf
 * @brief 
 * @version 0.1
 * @date 2024-08-5
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "mcal/stm32f103xx.h"
#include "utils/Assert.h"
#include "mcal/Timer.h"

using namespace stm32::dev::mcal::timer;
using namespace stm32::registers::timer;
using namespace stm32::type;

#define TIMER_EMPTY_MESSAGE               ""

#define TO_STRING(str_)  #str_

#define TIMER_CONFIG_ERROR(error_) \
    TO_STRING(Invalid Timer error_)

pFunction Timer::pGlobalCallBackFunction[5] = {nullptr};

Timer::Timer(const TimerConfig & config): config_(config) {
    switch (config_.Timerid) {
        case kTimer1 : timerReg = (reinterpret_cast<volatile timerRegDef*>(TIMER1)); break;
        case kTimer2 : timerReg = (reinterpret_cast<volatile timerRegDef*>(TIMER2)); break;
        case kTimer3 : timerReg = (reinterpret_cast<volatile timerRegDef*>(TIMER3)); break;
        case kTimer4 : timerReg = (reinterpret_cast<volatile timerRegDef*>(TIMER4)); break;
        case kTimer5 : timerReg = (reinterpret_cast<volatile timerRegDef*>(TIMER5)); break; 
        default: STM32_ASSERT(0, TIMER_EMPTY_MESSAGE); break;
    }
    Init();
}
    
void Timer::Init() {
    STM32_ASSERT(((config_.Timerid >= kTimer1) &&
                 (config_.Timerid <= kTimer5)), TIMER_CONFIG_ERROR(TimerID));
    STM32_ASSERT((config_.Direction == kUP) || 
                 (config_.Direction == kDown), TIMER_CONFIG_ERROR(TimerDirection));
    // Disable Timer at first
    timerReg->CR1.CEN = 0;
    // Set prescaler value
    timerReg->PSC = config_.Prescaler-1;
    // Set counter Direction
    timerReg->CR1.DIR = config_.Direction;
    // Set Interrupt update
    timerReg->DIER.UIE = 1;
    pGlobalCallBackFunction[config_.Timerid] = config_.pfunction;
}
void Timer::Delay_ms(uint16_t value) {
    timerReg->ARR = value-1;
    // Enable Timer at first
    timerReg->CR1.CEN = 1;
}
pFunction Timer::GetFunToISR(TimerID id) {
    STM32_ASSERT((id >= kTimer1) &&
                 (id <= kTimer5), TIMER_CONFIG_ERROR(TimerID));
    return pGlobalCallBackFunction[id];
}

extern "C" void TIM1_UP_IRQHandler(void) {
    pFunction func = Timer::GetFunToISR(kTimer1);
    TIMER1->SR.UIF ^= 1;
    func();
}

extern "C" void TIM2_IRQHandler(void) {
    pFunction func = Timer::GetFunToISR(kTimer2);
    TIMER2->SR.UIF ^= 1;
    func();
}

extern "C" void TIM3_IRQHandler(void) {
    pFunction func = Timer::GetFunToISR(kTimer3);
    TIMER3->SR.UIF ^= 1;
    func();
}

extern "C" void TIM4_IRQHandler(void) {
    pFunction func = Timer::GetFunToISR(kTimer4);
    TIMER4->SR.UIF ^= 1;
    func();
}

extern "C" void TIM5_IRQHandler(void) {
    pFunction func = Timer::GetFunToISR(kTimer5);
    TIMER5->SR.UIF ^= 1;
    func();
}
