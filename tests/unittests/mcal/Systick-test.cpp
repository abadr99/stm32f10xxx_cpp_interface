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
#include <thread>
#include "utils/BitManipulation.h"
#include "mcal/stm32f103xx.h"
#include "mcal/Systick.h"


using namespace stm32::constant;
using namespace stm32::util;
using namespace stm32::dev::mcal::systick;
using namespace stm32::registers::systick;


#define DELAY_TEST(mul, delay)\
    Systick::Enable(kAHB_Div_8);\
    Systick::delay(1);\
    value = 1 * mul;\
    EXPECT_EQ(value, static_cast<uint32_t>(SYSTICK->LOAD));\
    Systick::Disable();\
    Systick::Enable(kAHB);\
    Systick::delay(1);\
    value = 8 * mul;\
    EXPECT_EQ(value, static_cast<uint32_t>(SYSTICK->LOAD));\
    Systick::Disable();

class SystickTest : public testing::Test {
 protected:
    void SetUp() override {
        using Systick_addr = Addr<Peripheral::kSYSTICK>;
        Systick_addr::Set(&SystickReg[0]); 
        Systick::Init();
        SYSTICK = Systick::GetPtr();
    }

    RegWidth_t SystickReg[3] = {0x0};
    volatile SystickRegDef*  SYSTICK;
    uint32_t value;
};

TEST_F(SystickTest, Enable) {
    Systick::Enable(kAHB_Div_8);
    EXPECT_EQ(1, static_cast<uint32_t>(SYSTICK->CTRL.ENABLE));
    EXPECT_EQ(0, static_cast<uint32_t>(SYSTICK->CTRL.CLKSOURCE));
    Systick::Disable();
    Systick::Enable(kAHB);
    EXPECT_EQ(1, static_cast<uint32_t>(SYSTICK->CTRL.ENABLE));
    EXPECT_EQ(1, static_cast<uint32_t>(SYSTICK->CTRL.CLKSOURCE));
    Systick::Disable();
}

TEST_F(SystickTest, Disable) {
    Systick::Enable(kAHB_Div_8);
    Systick::Disable();
    EXPECT_EQ(0, static_cast<uint32_t>(SYSTICK->CTRL.ENABLE));
    EXPECT_EQ(1, static_cast<uint32_t>(SYSTICK->CTRL.CLKSOURCE));
}

TEST_F(SystickTest, Delay) {
    DELAY_TEST(1, Delay_us);
    DELAY_TEST(1000, Delay_ms);
}