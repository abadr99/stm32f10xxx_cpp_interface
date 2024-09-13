/**
 * @file EXTI-test.cpp
 * @author Noura
 * @brief 
 * @version 0.1
 * @date 2024-07-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <gtest/gtest.h>
#include "utils/inc/BitManipulation.h"
#include "mcal/inc/stm32f103xx.h"
#include "mcal/inc/Pin.h"
#include "mcal/inc/Exti.h"

using namespace stm32::util;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::exti;
using namespace stm32::registers::exti;
using namespace stm32::registers::afio;
using namespace stm32::registers::gpio; 

uint32_t AFIOReg[7] = {0x0};
uint32_t EXTIReg[6] = {0x0};

TEST(EXTItest, Enable) {
    EXTI_Config exti;
    exti.port = kPortA;
    exti.line = Line::kExti0;
    exti.trigger = Trigger::kRising;
    Exti::Enable(exti);
    EXPECT_EQ(0x0,    AFIO->EXTICRx[0]);
    EXPECT_EQ(0x1,       EXTI->IMR);
    EXPECT_EQ(0x1,       EXTI->RTSR);
}

TEST(DISABLE_EXTItest, Disable) {
    EXTI_Config exti;
    exti.port = kPortB;
    exti.line = Line::kExti10;
    exti.trigger = Trigger::kFalling;
    Exti::Disable(exti);
    EXPECT_EQ(0x1,      EXTI->IMR);
    EXPECT_EQ(0x0,      EXTI->FTSR);
}

TEST(EXTItest, SetPendingFlag) {
    EXTI_Config exti;
    exti.port = kPortB;
    exti.line = Line::kExti6;
    exti.trigger = Trigger::kFalling;
    Exti::SetPendingFlag(exti);
    EXPECT_EQ(0x40,       EXTI->PR);
}

TEST(EXTItest, ClearPendingFlag) {
    EXTI_Config exti;
    exti.port = kPortB;
    exti.line = Line::kExti16;
    exti.trigger = Trigger::kFalling;
    Exti::ClearPendingFlag(exti);
    EXPECT_EQ(0x40,       EXTI->PR);
}
