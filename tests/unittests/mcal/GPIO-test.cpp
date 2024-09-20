/**
 * @file GPIO-test.cpp
 * @author Mohamed Refat
 * @brief 
 * @version 0.1
 * @date 2024-04-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <gtest/gtest.h>
#include "BitManipulation.h"
#include "stm32f103xx.h"
#include "Pin.h"

using namespace stm32::util;
using namespace stm32::registers::gpio;

// volatile GpioRegDef *GPIOx[3] = {GPIOA, GPIOB, GPIOC};
