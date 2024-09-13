/**
 * @file Iwdg-test.cpp
 * @author noura36
 * @brief 
 * @version 0.1
 * @date 2024-09-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <gtest/gtest.h>
#include "utils/inc/BitManipulation.h"
#include "mcal/inc/stm32f103xx.h"
#include "mcal/inc/Iwdg.h"

uint32_t IwdgReg[4] = {0x0};
using namespace stm32::util;
using namespace stm32::dev::mcal::iwdg;
using namespace stm32::registers::iwdg;

TEST(IwdgTest, IwdgConstractor) {
    Iwdg(kDiv4, 1000);
    EXPECT_EQ(0, IWDG->PR);
    EXPECT_EQ(1000, IWDG->RLD);
    EXPECT_EQ(0xCCCC, IWDG->KR);
}
TEST(IwdgTest, Refresh) {
    Iwdg watchdog(kDiv16, 2000);
    watchdog.Refresh();
    EXPECT_EQ(0xAAAA, IWDG->KR);
}
