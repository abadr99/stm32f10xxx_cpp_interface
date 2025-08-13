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
    using pFunc = std::function<void(Id)>;

    void SetUp() override {
        using Nvic_addr = Addr<Peripheral::kNVIC>; 
        using Scb_addr = Addr<Peripheral::kSCB>;
        Nvic_addr::Set(&NvicReg[0]); 
        Scb_addr::Set(&ScbReg[0]);
        Nvic::Init();
        NVIC = Nvic::GetPtr<NvicRegDef>();
        SCB = Nvic::GetPtr<SCBRegDef>();
    }  

    template<typename T>
    void GenericTest(T* regArr, InterruptID id, pFunc interruptFunc) {
        regArr[id / 32] = 0;
        interruptFunc(Id(id));
        EXPECT_TRUE((ExtractBit<RegWidth_t>(regArr[id / 32], (id % 32))));
    }

    void PriorityTest(InterruptID id, uint8_t priority) {
        NVIC->IPR[id] = 0;
        Nvic::SetPriority(Id(id), priority);
        EXPECT_EQ(priority,   (ExtractBits<RegWidth_t, 4, 7>(NVIC->IPR[id])));
    }

    void PriorityGroupTest(PriorityGroup group) {
        SCB->AIRCR = 0;
        Nvic::SetPriorityGroup(group);
        EXPECT_EQ(group,   (ExtractBits<RegWidth_t, 0, 31>(SCB->AIRCR)));
    }

    RegWidth_t NvicReg[905];
    RegWidth_t ScbReg[18];
    volatile NvicRegDef* NVIC; 
    volatile SCBRegDef*  SCB;
};


TEST_F(NvicTest, EnableInterrupt) {
    GenericTest(NVIC->ISER, InterruptID::kTIM4_IRQn, Nvic::EnableInterrupt);
    GenericTest(NVIC->ISER, InterruptID::kWWDG_IRQn, Nvic::EnableInterrupt);
    GenericTest(NVIC->ISER, InterruptID::kI2C1_ER_IRQn, Nvic::EnableInterrupt);
    GenericTest(NVIC->ISER, InterruptID::kRTCAlarm_IRQn, Nvic::EnableInterrupt);
}

TEST_F(NvicTest, DisableInterrupt) {
    GenericTest(NVIC->ICER, InterruptID::kTIM4_IRQn, Nvic::DisableInterrupt);
    GenericTest(NVIC->ICER, InterruptID::kWWDG_IRQn, Nvic::DisableInterrupt);
    GenericTest(NVIC->ICER, InterruptID::kI2C1_ER_IRQn, Nvic::DisableInterrupt);
    GenericTest(NVIC->ICER, InterruptID::kRTCAlarm_IRQn, Nvic::DisableInterrupt);
}

TEST_F(NvicTest, SetPendingFlag) {
    GenericTest(NVIC->ISPR, InterruptID::kTIM4_IRQn, Nvic::SetPendingFlag);
    GenericTest(NVIC->ISPR, InterruptID::kWWDG_IRQn, Nvic::SetPendingFlag);
    GenericTest(NVIC->ISPR, InterruptID::kI2C1_ER_IRQn, Nvic::SetPendingFlag);
    GenericTest(NVIC->ISPR, InterruptID::kRTCAlarm_IRQn, Nvic::SetPendingFlag);
}

TEST_F(NvicTest, ClearPendingFlag) {
    GenericTest(NVIC->ICPR, InterruptID::kTIM4_IRQn, Nvic::ClearPendingFlag);
    GenericTest(NVIC->ICPR, InterruptID::kWWDG_IRQn, Nvic::ClearPendingFlag);
    GenericTest(NVIC->ICPR, InterruptID::kI2C1_ER_IRQn, Nvic::ClearPendingFlag);
    GenericTest(NVIC->ICPR, InterruptID::kRTCAlarm_IRQn, Nvic::ClearPendingFlag);
}

TEST_F(NvicTest, SetPriority) {
    PriorityTest(InterruptID::kTIM4_IRQn, 4);
    PriorityTest(InterruptID::kWWDG_IRQn, 5);
    PriorityTest(InterruptID::kI2C1_ER_IRQn, 1);
    PriorityTest(InterruptID::kRTCAlarm_IRQn, 3);
}

TEST_F(NvicTest, SetPriorityGroup) {
    PriorityGroupTest(kSCB_4GROUP_0SUBGROUP);
    PriorityGroupTest(kSCB_3GROUP_1SUBGROUP);
    PriorityGroupTest(kSCB_2GROUP_2SUBGROUP);
    PriorityGroupTest(kSCB_1GROUP_3SUBGROUP);
    PriorityGroupTest(kSCB_0GROUP_4SUBGROUP);
}



