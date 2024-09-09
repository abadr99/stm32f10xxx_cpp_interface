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
#include "utils/inc/BitManipulation.h"
#include "mcal/inc/stm32f103xx.h"
#include "mcal/inc/Pin.h"

using namespace stm32::util;
using namespace stm32::registers::gpio;

// volatile GpioRegDef *GPIOx[3] = {GPIOA, GPIOB, GPIOC};
