/**
 * @file Timers-test.cpp
 * @author Manar Abdelraouf
 * @brief 
 * @version 0.1
 * @date 2024-08-22
 * 
 * @copyright Copyright (c) 2024
 */
#if 0
#include <gtest/gtest.h>
#include "utils/Types.h"
#include "utils/BitManipulation.h"
#include "mcal/stm32f103xx.h"
#include "mcal/Timer.h"

using namespace stm32::util;
using namespace stm32::dev::mcal::timer;
using namespace stm32::registers::timer;

class TimerTest : public testing::Test {
 protected:
    void SetUp() override {
        using Tim1_addr = Addr<Peripheral::kTIM1>;
        using Tim2_addr = Addr<Peripheral::kTIM2>;
        using Tim3_addr = Addr<Peripheral::kTIM3>;
        using Tim4_addr = Addr<Peripheral::kTIM4>;
        using Tim5_addr = Addr<Peripheral::kTIM5>;

        Tim1_addr::Set(&TIMER1Reg[0]);
        Tim2_addr::Set(&TIMER2Reg[0]);
        Tim3_addr::Set(&TIMER3Reg[0]);
        Tim4_addr::Set(&TIMER4Reg[0]);
        Tim5_addr::Set(&TIMER5Reg[0]);

        TimerConfig tim2_config = {
            .Timerid = kTimer2,
            .Direction = kDown,
            .Prescaler = 4000,  // 4000/4000=1
            .interrupt = kDisable,
            .pfunction = nullptr
        };
        tim2 = new Timer(tim2_config);
    }

    void TearDown() override {
        delete tim2;
    }

    uint32_t TIMER1Reg[22] = {};
    uint32_t TIMER2Reg[22] = {};
    uint32_t TIMER3Reg[22] = {};
    uint32_t TIMER4Reg[22] = {};
    uint32_t TIMER5Reg[22] = {};

    Timer* tim2 = nullptr;
};
TEST_F(TimerTest, DelayMsConfiguresRegisters) {
    TimeBaseTypeDef counter{TimerClkDivision::kDIV2};
    tim2->Delay_ms(counter, 100);

    auto TIM2 = reinterpret_cast<timerRegDef*>(TIMER2Reg);
    EXPECT_EQ(4000 - 1, TIM2->PSC);
    EXPECT_EQ(1, (ExtractBits<uint32_t, 4>(TIM2->CR1.registerVal)));
    EXPECT_EQ(1, (ExtractBits<uint32_t, 7>(TIM2->CR1.registerVal)));
    EXPECT_EQ(100 - 1, TIM2->ARR);
    // EXPECT_EQ(0x0100, (ExtractBits<uint32_t, 8, 9>(TIM2->CR1.registerVal))); fail
}
TEST_F(TimerTest, CmdEnableDisable) {
    auto TIM2 = reinterpret_cast<timerRegDef*>(TIMER2Reg);
    tim2->Cmd(kEnable);
    EXPECT_EQ(1, (ExtractBits<uint32_t, 0>(TIM2->CR1.registerVal)));
    tim2->Cmd(kDisable);
    EXPECT_EQ(0, (ExtractBits<uint32_t, 0>(TIM2->CR1.registerVal)));
}
TEST_F(TimerTest, SetCompare1) {
    TimerOCTypeDef ocConfig{
        OCMode::kPWM1,
        State::kEnable,
        OCPolarity::kActiveHigh,
        1000,
        OCIdleState::kIdleState_Reset
    };
    tim2->SetCompare1(ocConfig, TimerChannels::kChannel1, 250);
    auto TIM2 = reinterpret_cast<timerRegDef*>(TIMER2Reg);
    EXPECT_EQ(1000 - 1, TIM2->ARR);
    EXPECT_EQ(250, TIM2->CCR1);
    EXPECT_EQ(1, (ExtractBits<uint32_t, 0>(TIM2->CCER.registerVal)));
}
TEST_F(TimerTest, OCModeEnable) {
    TimerOCTypeDef ocConfig{
        OCMode::kPWM1,
        State::kEnable,
        OCPolarity::kActiveHigh,
        500,
        OCIdleState::kIdleState_Reset
    };
    tim2->OCMode(ocConfig);
    auto TIM2 = reinterpret_cast<timerRegDef*>(TIMER2Reg);
    EXPECT_EQ(0, (ExtractBits<uint32_t, 1>(TIM2->CCER.registerVal)));
    EXPECT_EQ(1, (ExtractBits<uint32_t, 15>(TIM2->BDTR.registerVal)));
}
#endif
