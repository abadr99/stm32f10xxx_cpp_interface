/**
 * @file Pwr.cpp
 * @author 
 * @brief 
 * @version 0.1
 * @date 2024-07-21
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <gtest/gtest.h>
#include "BitManipulation.h"
#include "stm32f103xx.h"
#include "Power.h"

using namespace stm32::registers::nvic;
using namespace stm32::registers::pwr;
using namespace stm32::dev::mcal::pwr;

uint32_t PwrReg[2] = {0x0};

