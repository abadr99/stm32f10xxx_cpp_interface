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
#if 0
#include <gtest/gtest.h>
#include "utils/Types.h"
#include "utils/BitManipulation.h"
#include "mcal/stm32f103xx.h"
#include "mcal/Pin.h"
#include "mcal/Exti.h"

using namespace stm32::constant;
using namespace stm32::util;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::exti;
using namespace stm32::registers::exti;
using namespace stm32::registers::afio;
using namespace stm32::registers::gpio; 



class ExtiTest : public testing::Test {
 protected:
    void SetUp() override {
        using Exti_addr = Addr<Peripheral::kEXTI>;
        using Afio_addr = Addr<Peripheral::kAFIO>;
        Exti_addr::Set(&EXTIReg[0]);
        Afio_addr::Set(&AFIOReg[0]);
        Exti::Init();
        EXTI = Exti::GetPtr<EXTIRegDef>();
        AFIO = Exti::GetPtr<AfioRegDef>();
    }

    template<typename T, typename F>
    void GenericTest(T* reg, Line line, F extiFunc, uint32_t expectedMask) {
        *reg = 0;
        EXTI_Config exti;
        exti.port = kPortA;
        exti.line = line;
        exti.trigger = Trigger::kRising;
        extiFunc(exti);
        EXPECT_EQ(expectedMask, *reg);
    }

    RegWidth_t AFIOReg[7]  = {};
    RegWidth_t EXTIReg[6]  = {};
    volatile EXTIRegDef* EXTI;
    volatile AfioRegDef* AFIO;
};


TEST_F(ExtiTest, Enable) {
    EXTI_Config exti;
    exti.port = kPortA;
    exti.line = Line::kExti0;
    exti.trigger = Trigger::kRising;
    Exti::Enable(exti);

    EXPECT_EQ(0x1, EXTI->IMR);
    EXPECT_EQ(0x1, EXTI->RTSR);
}

TEST_F(ExtiTest, Disable) {
    EXTI_Config exti;
    exti.port = kPortB;
    exti.line = Line::kExti10;
    exti.trigger = Trigger::kFalling;

    Exti::Disable(exti);

    EXPECT_EQ(0x0, EXTI->IMR);
    EXPECT_EQ(0x0, EXTI->FTSR);
}

TEST_F(ExtiTest, SetPendingFlag) {
    EXTI_Config exti;
    exti.port = kPortB;
    exti.line = Line::kExti6;
    exti.trigger = Trigger::kFalling;

    Exti::SetPendingFlag(exti);
    EXPECT_EQ(0x40, EXTI->PR);
}

TEST_F(ExtiTest, ClearPendingFlag) {
    EXTI_Config exti;
    exti.port = kPortB;
    exti.line = Line::kExti6;
    exti.trigger = Trigger::kFalling;

    Exti::ClearPendingFlag(exti);
    EXPECT_EQ(0x0, EXTI->PR);
}
#endif
