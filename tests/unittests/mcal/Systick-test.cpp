/**
 * @file Systick-test.cpp
 * @author
 * @brief 
 * @version 0.1
 * @date 2024-04-15
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <gtest/gtest.h>
#include "utils/inc/BitManipulation.h"
#include "mcal/inc/stm32f103xx.h"
#include "mcal/inc/Systick.h"

uint32_t SYSTICKReg[3] = {};

using namespace stm32::utils::bit_manipulation;  // NOLINT [build/namespaces]
using namespace stm32::dev::mcal::systick;  // NOLINT [build/namespaces]
using namespace stm32::registers::systick;  // NOLINT [build/namespaces]

TEST(SystickTest, delay_ms) {
Systick s;
SYSTICK->CTRL.COUNTFLAG = 1;
s.delay_ms(kAHB_Div_8, 1);
EXPECT_EQ(0b001,           (ExtractBits<uint32_t, 0, 2>(SYSTICK->CTRL.registerVal)));   // NOLINT
}
