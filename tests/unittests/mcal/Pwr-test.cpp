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
#include "utils/BitManipulation.h"
#include "mcal/stm32f103xx.h"
#include "mcal/Power.h"

using namespace stm32::registers::nvic;
using namespace stm32::registers::pwr;
using namespace stm32::dev::mcal::pwr;

uint32_t PwrReg[2] = {0x0};

