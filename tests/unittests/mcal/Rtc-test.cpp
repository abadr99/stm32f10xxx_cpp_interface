/**
 * @file Rtc-test.cpp
 * @author Mohamed Refat
 * @brief 
 * @version 0.1
 * @date 2024-07-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#if 0
#include <gtest/gtest.h>
#include "utils/Types.h"
#include "utils/BitManipulation.h"
#include "mcal/stm32f103xx.h"
#include "mcal/Rtc.h"

using namespace stm32::util;
using namespace stm32::dev::mcal::rtc;
using namespace stm32::registers::rtc;

class RtcTest : public testing::Test {
 protected:
    void SetUp() override {
        using Rtc_addr = Addr<Peripheral::kRTC>;
        Rtc_addr::Set(&RtcReg[0]);
        Rtc::Init();
        RTC = Rtc::GetRtcRegister();
    }

    uint32_t RtcReg[10] = {};
    volatile RtcRegDef* RTC;
};
TEST_F(RtcTest, AlarmInterruptEnableDisable) {
    Rtc::AlarmInterruptEnable();
    EXPECT_EQ(1, (ExtractBits<uint32_t, 1>(RTC->CRH.registerVal)));
    Rtc::AlarmInterruptDisable();
    EXPECT_EQ(0, (ExtractBits<uint32_t, 1>(RTC->CRH.registerVal)));
}
TEST_F(RtcTest, SecondInterruptEnableDisable) {
    Rtc::SecondInterruptEnable();
    EXPECT_EQ(1, (ExtractBits<uint32_t, 0>(RTC->CRH.registerVal)));
    Rtc::SecondInterruptDisable();
    EXPECT_EQ(0, (ExtractBits<uint32_t, 0>(RTC->CRH.registerVal)));
}
TEST_F(RtcTest, OverflowInterruptEnableDisable) {
    Rtc::OverflowInterruptEnable();
    EXPECT_EQ(1, (ExtractBits<uint32_t, 2>(RTC->CRH.registerVal)));
    Rtc::OverflowInterruptDisable();
    EXPECT_EQ(0, (ExtractBits<uint32_t, 2>(RTC->CRH.registerVal)));
}
#endif
