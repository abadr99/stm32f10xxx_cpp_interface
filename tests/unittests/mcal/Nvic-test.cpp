/**
 * @file Nvic-test.cpp

 * @brief
 * @version 0.1
 * @date 2024-04-25
 * @copyright Copyright (c) 2024
 *
 */
#include <gtest/gtest.h>
#include "utils/inc/BitManipulation.h"
#include "mcal/inc/stm32f103xx.h"
#include "mcal/inc/Nvic.h"


uint32_t NvicReg[7] = {};
uint32_t ScbReg[18] = {};

using namespace stm32::utils::bit_manipulation;
using namespace stm32::dev::mcal::nvic;
using namespace stm32::registers::nvic;
