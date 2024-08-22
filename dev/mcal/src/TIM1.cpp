/**
 * @file TIM1.cpp
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
#include "mcal/inc/TIM1.h"

using namespace stm32::dev::mcal::timer1;
using namespace stm32::registers::timer;


pFunction Timer1::pGlobalCallBackFunction = nullptr;

Timer1::Timer1(TimerConfign & timer) {
    // Disable Timer at first
    TIM1->CR1.CEN = 0;
    // Set Reload value
    TIM1->ARR = timer.ReloadValue;
    // Set counter Direction
    TIM1->CR1.DIR = timer.Direction;
    // Set Interrupt update
    TIM1->DIER.UIE = 1;
    pGlobalCallBackFunction = timer.pfunction;
    TIM1->DIER.CC1IE = 1;
    // Enable Timer at first
    TIM1->CR1.CEN = 1;
}
pFunction Timer1::Helper_GetFunToISR() {
    return pGlobalCallBackFunction;
}
extern "C" void TIM1_UP_IRQHandle(void)
{
    pFunction func = Timer1::Helper_GetFunToISR();
    func();
}
