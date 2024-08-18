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

void Timer1::Init(TimerConfign & timer) {
    /*Disable Timer at first*/
    TIM1->CR1.CEN = 0;
}



