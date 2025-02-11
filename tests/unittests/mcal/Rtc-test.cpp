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
#include <gtest/gtest.h>
#include "utils/BitManipulation.h"
#include "mcal/stm32f103xx.h"
#include "mcal/Rtc.h"

using namespace stm32::util;
using namespace stm32::dev::mcal::rtc;
using namespace stm32::registers::rtc;



class RtcTest : public testing::Test {
 protected:
    using pFunction = stm32::type::pFunction; 
    void SetUp() override {
        using Rtc_addr = Addr<Peripheral::kRTC>;
        Rtc_addr::Set(&RtcReg[0]); 
        Rtc::Init(config);
        RTC = Rtc::GetRtcRegister();
    }
    static void AlarmISR() {}
    static void SecondISR() {}
    static void OverflowISR() {}
    RegWidth_t  RtcReg[10] = {0x0};
    volatile RtcRegDef* RTC;
    RtcConfig config = {0, 0, 0, ISRs[0], ISRs[1], ISRs[2]};
    std::array<pFunction, 3> ISRs = {AlarmISR, SecondISR, OverflowISR};
};

TEST_F(RtcTest, GetCurrentTime) {
    Time currentTime;
    Rtc::GetCurrentTime(&currentTime);
    // Ensure that the time values are within valid ranges
    EXPECT_GE(currentTime.hour, 0);
    EXPECT_LT(currentTime.hour, 24);
    EXPECT_GE(currentTime.minutes, 0);
    EXPECT_LT(currentTime.minutes, 60);
    EXPECT_GE(currentTime.second, 0);
    EXPECT_LT(currentTime.second, 60);
}

TEST_F(RtcTest, InterruptEnable) {
    Rtc::AlarmInterruptEnable();
    EXPECT_EQ(1, static_cast<uint32_t>(RTC->CRH.ALRIE));

    Rtc::SecondInterruptEnable();
    EXPECT_EQ(1, static_cast<uint32_t>(RTC->CRH.SECIE)); 

    Rtc::OverflowInterruptEnable();
    EXPECT_EQ(1, static_cast<uint32_t>(RTC->CRH.OWIE)); 
}


TEST_F(RtcTest, InterruptDisable) {
    Rtc::AlarmInterruptDisable();
    EXPECT_EQ(0, static_cast<uint32_t>(RTC->CRH.ALRIE));

    Rtc::SecondInterruptDisable();
    EXPECT_EQ(0, static_cast<uint32_t>(RTC->CRH.SECIE)); 

    Rtc::OverflowInterruptDisable();
    EXPECT_EQ(0, static_cast<uint32_t>(RTC->CRH.OWIE)); 
}

