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
#include "mcal/inc/stm32f103xx.h"
#include "utils/inc/Assert.h"
#include "mcal/inc/Timer.h"

using namespace stm32::dev::mcal::timer;
using namespace stm32::registers::timer;
using namespace stm32::type;

pFunction Timer::pGlobalCallBackFunction[5] = {nullptr};

Timer::Timer(const TimerConfig & config): config_(config) {
    switch (config_.Timerid) {
        case kTimer1 : timerReg = (reinterpret_cast<volatile timerRegDef*>(TIMER1)); break;
        case kTimer2 : timerReg = (reinterpret_cast<volatile timerRegDef*>(TIMER2)); break;
        case kTimer3 : timerReg = (reinterpret_cast<volatile timerRegDef*>(TIMER3)); break;
        case kTimer4 : timerReg = (reinterpret_cast<volatile timerRegDef*>(TIMER4)); break;
        case kTimer5 : timerReg = (reinterpret_cast<volatile timerRegDef*>(TIMER5)); break; 
        default: break;
    } 
}
    
void Timer::Init(const TimerConfig & config) {
    // Disable Timer at first
    timerReg->CR1.CEN = 0;
    // Set Reload value
    timerReg->ARR = config.ReloadValue;
    // Set counter Direction
    timerReg->CR1.DIR = config.Direction;
    // Set prescaler value
    timerReg->PSC = config.Prescaler;
    // Set Interrupt update
    timerReg->DIER.UIE = 1;
    pGlobalCallBackFunction[config.Timerid] = config.pfunction;
    // Enable Timer at first
    timerReg->CR1.CEN = 1;
}
pFunction Timer::Helper_GetFunToISR(TimerID id) {
    return pGlobalCallBackFunction[id];
}
extern "C" void TIM1_UP_IRQHandler(void) {
    pFunction func = Timer::Helper_GetFunToISR(kTimer1);
    TIMER1->SR.UIF ^= 1;
    func();
}
extern "C" void TIM2_IRQHandler(void) {
    pFunction func = Timer::Helper_GetFunToISR(kTimer2);
    TIMER2->SR.UIF ^= 1;
    func();
}
extern "C" void TIM3_IRQHandler(void) {
    pFunction func = Timer::Helper_GetFunToISR(kTimer3);
    TIMER3->SR.UIF ^= 1;
    func();
}
extern "C" void TIM4_IRQHandler(void) {
    pFunction func = Timer::Helper_GetFunToISR(kTimer4);
    TIMER4->SR.UIF ^= 1;
    func();
}
extern "C" void TIM5_IRQHandler(void) {
    pFunction func = Timer::Helper_GetFunToISR(kTimer5);
    TIMER5->SR.UIF ^= 1;
    func();
}
