/**
 * @file Nvic-test.cpp
 * @author Manar
 * @version 0.1
 * @date 2024-06-23
 * @copyright Copyright (c) 2024
 */

#include <gtest/gtest.h>
#include "utils/BitManipulation.h"
#include "utils/Types.h"
#include "mcal/stm32f103xx.h"
#include "mcal/Nvic.h"

using namespace stm32::util; 
using namespace stm32::dev::mcal::nvic; 
using namespace stm32::registers::nvic; 

class NvicTest : public testing::Test {
 protected:
    void SetUp() override {
        using Nvic_addr = Addr<Peripheral::kNVIC>; 
        //Id id(InterruptID::kTIM4_IRQn);
        Nvic_addr::Set(&NvicReg[0]);
        NVIC = reinterpret_cast<volatile NvicRegDef*>(Nvic_addr::Get());
    }    

    void TestEnable(InterruptID id) {
        Id ID(id);
        NVIC->ISER[id / 32] = ClearBit<RegWidth_t>(NVIC->ISER[id / 32], (id % 32));
        Nvic::EnableInterrupt(ID);
        EXPECT_EQ(1,    (ExtractBit<uint32_t>(NVIC->ISER[id / 32], (id % 32))));
    }

    RegWidth_t NvicReg[905];
    volatile NvicRegDef* NVIC; 
    //Id id(InterruptID::kTIM4_IRQn);
};


TEST_F(NvicTest, EnableInterrupt) {
    TestEnable(InterruptID::kTIM4_IRQn);
    TestEnable(InterruptID::kWWDG_IRQn);
    TestEnable(InterruptID::kI2C1_ER_IRQn);
    TestEnable(InterruptID::kRTCAlarm_IRQn);
}

#if 0
uint32_t NvicReg[905] = {};
uint32_t ScbReg[18] = {};

using namespace stm32::util;
using namespace stm32::dev::mcal::nvic;
using namespace stm32::registers::nvic;

static volatile NvicRegDef*  NVIC;
static volatile SCBRegDef*  SCB;

TEST(NvicTest, EnableInterrupt) {
    Nvic::Reset();
    Nvic::EnableInterrupt(kEXTI0_IRQn);
    EXPECT_EQ(1,   (ExtractBits<uint32_t, 6>(NVIC->ISER[0])));
    Nvic::EnableInterrupt(kUSART3_IRQn);
    EXPECT_EQ(1,   (ExtractBits<uint32_t, 7>(NVIC->ISER[1])));
}

TEST(NvicTest, DisableInterrupt) {
    Nvic::Reset();
    Nvic::DisableInterrupt(kEXTI0_IRQn);
    EXPECT_EQ(1,   (ExtractBits<uint32_t, 6>(NVIC->ICER[0])));
    Nvic::DisableInterrupt(kUSART3_IRQn);
    EXPECT_EQ(1,   (ExtractBits<uint32_t, 7>(NVIC->ICER[1])));
}

TEST(NvicTest, SetPendingFlag) {
    Nvic::Reset();
    Nvic::SetPendingFlag(kEXTI0_IRQn);
    EXPECT_EQ(1,   (ExtractBits<uint32_t, 6>(NVIC->ISPR[0])));
    Nvic::SetPendingFlag(kUSART3_IRQn);
    EXPECT_EQ(1,   (ExtractBits<uint32_t, 7>(NVIC->ISPR[1])));
}

TEST(NvicTest, ClearPendingFlag) {
    Nvic::Reset();
    Nvic::ClearPendingFlag(kEXTI0_IRQn);
    EXPECT_EQ(1,   (ExtractBits<uint32_t, 6>(NVIC->ICPR[0])));
    Nvic::ClearPendingFlag(kUSART3_IRQn);
    EXPECT_EQ(1,   (ExtractBits<uint32_t, 7>(NVIC->ICPR[1])));
}

TEST(NvicTest, SetPriority) {
    Nvic::Reset();
    Nvic::SetPriority(kEXTI0_IRQn, 5);
    EXPECT_EQ(5,   (ExtractBits<uint32_t, 4, 7>(NVIC->IPR[kEXTI0_IRQn])));
    EXPECT_EQ(80,  (ExtractBits<uint32_t, 0, 7>(NVIC->IPR[kEXTI0_IRQn])));
}

TEST(NvicTest, SetPriorityGroup) {
    Nvic::Reset();
    Nvic::SetPriorityGroup(kSCB_0GROUP_4SUBGROUP);
    EXPECT_EQ(kSCB_0GROUP_4SUBGROUP,   (ExtractBits<uint32_t, 0, 31>(SCB->AIRCR)));
}
#endif
