/**
 * @file I2c-test.cpp
 * @author Manar Abdelraouf
 * @brief 
 * @version 0.1
 * @date 2024-07-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <gtest/gtest.h>
#include "utils/BitManipulation.h"
#include "mcal/stm32f103xx.h"
#include "mcal/I2c.h"

uint32_t I2c1Reg[9] = {0x0};
uint32_t I2c2Reg[9] = {0x0};
using namespace stm32::util;
using namespace stm32::dev::mcal::i2c;
using namespace stm32::registers::i2c;
