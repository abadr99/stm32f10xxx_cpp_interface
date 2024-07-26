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

uint32_t SYSTICKReg[3] = {0x0};

using namespace stm32::utils::bit_manipulation;
using namespace stm32::dev::mcal::systick;
using namespace stm32::registers::systick;

TEST(SystickTest, Delay_ms) {
    Systick::Enable(kAHB_Div_8);
    SYSTICK->CTRL.COUNTFLAG = 1;
    Systick::Delay_ms(1);
    EXPECT_EQ(0b000, (ExtractBits<uint32_t, 0, 2>(SYSTICK->CTRL.registerVal)));
    EXPECT_EQ(1000, SYSTICK->LOAD);
    Systick::Disable();
}

TEST(SystickTest, Delay_us) {
    Systick::Enable(kAHB);
    SYSTICK->CTRL.COUNTFLAG = 1;
    Systick::Delay_us(10);
    EXPECT_EQ(0b100, (ExtractBits<uint32_t, 0, 2>(SYSTICK->CTRL.registerVal)));
    EXPECT_EQ(80, SYSTICK->LOAD);
    Systick::Disable();
}
