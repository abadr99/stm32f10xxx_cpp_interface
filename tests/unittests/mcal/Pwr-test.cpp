/**
 * @file Pwr.cpp
 * @author 
 * @brief 
 * @version 0.1
 * @date 2025-08-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#if 0
#include <gtest/gtest.h>
#include "utils/Types.h"
#include "utils/BitManipulation.h"
#include "mcal/stm32f103xx.h"
#include "mcal/Power.h"
#include "mcal/Nvic.h"

using namespace stm32::util;
using namespace stm32::registers::nvic;
using namespace stm32::registers::pwr;
using namespace stm32::dev::mcal::nvic;
using namespace stm32::dev::mcal::pwr;

class PwrTest : public testing::Test {
 protected:
    void SetUp() override {
        using Pwr_addr = Addr<Peripheral::kPWR>;
        using Scb_addr = Addr<Peripheral::kSCB>;
        Pwr_addr::Set(&PwrReg[0]);
        Scb_addr::Set(&ScbReg[0]);
        Pwr::Init();
        PWR = Pwr::GetPtr<PwrRegDef>();
        SCB = Nvic::GetPtr<SCBRegDef>();
    }

    RegWidth_t PwrReg[2]  = {};
    RegWidth_t ScbReg[18];
    volatile PwrRegDef* PWR;
    volatile SCBRegDef*  SCB;
};
TEST_F(PwrTest, WakeupPinState) {
    Pwr::WakeupPinState(State::kEnable);
    EXPECT_EQ(1, (ExtractBits<uint32_t, 8>(PWR->CSR.registerVal)));
}

TEST_F(PwrTest, ClearFlag) {
    Pwr::ClearFlag(PwrFlag::kWU);
    EXPECT_EQ(1, (ExtractBits<uint32_t, 2>(PWR->CR.registerVal)));

    Pwr::ClearFlag(PwrFlag::kSB);
    EXPECT_EQ(1, (ExtractBits<uint32_t, 3>(PWR->CR.registerVal)));
}
#endif
