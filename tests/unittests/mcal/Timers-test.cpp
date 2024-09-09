/**
 * @file Timers-test.cpp
 * @author Manar Abdelraouf
 * @brief 
 * @version 0.1
 * @date 2024-08-22
 * 
 * @copyright Copyright (c) 2024
 */
#include <gtest/gtest.h>
#include "utils/inc/BitManipulation.h"
#include "mcal/inc/stm32f103xx.h"
#include "mcal/inc/Timer.h"

uint32_t TIMER1Reg[22] = {0x0};
uint32_t TIMER2Reg[22] = {0x0};
uint32_t TIMER3Reg[22] = {0x0};
uint32_t TIMER4Reg[22] = {0x0};
uint32_t TIMER5Reg[22] = {0x0};
using namespace stm32::util;
using namespace stm32::dev::mcal::timer;
using namespace stm32::registers::timer;
