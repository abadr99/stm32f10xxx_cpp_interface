/**
 * @file Can.cpp
 * @author 
 * @brief 
 * @version 0.1
 * @date 2024-12-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <gtest/gtest.h>
#include "utils/BitManipulation.h"
#include "mcal/stm32f103xx.h"
#include "mcal/Can.h"

using namespace stm32::registers::can;
using namespace stm32::dev::mcal::Can;

uint32_t CanReg[100] = {0x0};   // edit the size of array