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

#if 0
#include <gtest/gtest.h>
#include "utils/BitManipulation.h"
#include "utils/Types.h"
#include "mcal/stm32f103xx.h"
#include "mcal/Systick.h"


using namespace stm32::constant;
using namespace stm32::util;
using namespace stm32::dev::mcal::systick;
using namespace stm32::registers::systick;

class SystickTest : public testing::Test {
 protected:
    void SetUp() override {
        using Systick_addr = Addr<Peripheral::kSYSTICK>;
        Systick_addr::Set(&SYSTICKReg[0]);
        Systick::Init();
        SYSTICK = Systick::GetPtr<SystickRegDef>();
    }

    RegWidth_t SYSTICKReg[3]  = {};
    volatile SystickRegDef* SYSTICK;
};

TEST_F(SystickTest, Delay_ms) {
    Systick::Enable(kAHB_Div_8);
    SYSTICK->CTRL.COUNTFLAG = 1;
    Systick::Delay_ms(1);
    EXPECT_EQ(0b010, (ExtractBits<uint32_t, 0, 2>(SYSTICK->CTRL.registerVal)));
    EXPECT_EQ(1000, SYSTICK->LOAD);
    Systick::Disable();
}
TEST_F(SystickTest, Delay_us) {
    Systick::Enable(kAHB);
    SYSTICK->CTRL.COUNTFLAG = 1;
    Systick::Delay_us(10);
    EXPECT_EQ(0b110, (ExtractBits<uint32_t, 0, 2>(SYSTICK->CTRL.registerVal)));
    EXPECT_EQ(80, SYSTICK->LOAD);
    Systick::Disable();
}
#endif

