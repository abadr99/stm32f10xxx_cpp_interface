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
#include "utils/BitManipulation.h"
#include "mcal/stm32f103xx.h"
#include "mcal/Pin.h"
#include "mcal/Exti.h"

using namespace stm32::util;
using namespace stm32::constant;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::exti;
using namespace stm32::registers::exti;
using namespace stm32::registers::afio;

class ExtiTest : public testing::Test {
 protected:
    using pFunc = std::function<RegWidth_t(RegWidth_t, uint8_t)>;
    using pControlFunc = std::function<void(EXTI_Config)>;

    void SetUp() override {
        using Exti_addr = Addr<Peripheral::kEXTI>;
        using Afio_addr = Addr<Peripheral::kAFIO>;
        Exti_addr::Set(&ExtiReg[0]);
        Afio_addr::Set(&AfioReg[0]);
        Exti::Init();
        EXTI = Exti::GetPtr<EXTIRegDef>();
        AFIO = Exti::GetPtr<AfioRegDef>();
    }

    template<Trigger trigger, uint8_t EV>
    void ControlTest(Port port, Line line) {
        exti.SetConfig(port, line, trigger);
        InitReg<EV>(line);  
        GetControlFunc<EV>()(exti);
        EXPECT_EQ(EV, ExtractBit<RegWidth_t>(EXTI->IMR, static_cast<uint8_t>(line)));
        TriggerTest<trigger>(line, EV);
    }   
    
    template<Port port, Line line, Trigger trigger>
    void SetPendingTest() {
        exti.SetConfig(port, line, trigger);
        // Clear flag by writing  1 into the bit of EXTI->IMR
        EXTI->IMR  = SetBit<RegWidth_t>(static_cast<uint8_t>(line), (EXTI->IMR)); 
        ControlTest<trigger, 1>(port, line);
        Exti::SetPendingFlag(exti);
        EXPECT_EQ(1, ExtractBit<RegWidth_t>(EXTI->SWIER, static_cast<uint8_t>(line)));
    }

    template<Port port, Line line, Trigger trigger>
    void ClearPendingTest() {
        exti.SetConfig(port, line, trigger);
        Exti::ClearPendingFlag(exti);
        if (Exti::GetPendingFlag(exti)) {
            EXPECT_EQ(1, ExtractBit<RegWidth_t>(EXTI->PR, static_cast<uint8_t>(line)));
        }   
    }

    template<Trigger trigger>
    void TriggerTest(Line line, uint8_t EV) {
        if (trigger == kBoth) {
           EXPECT_EQ(EV, ExtractBit<RegWidth_t>(GetReg<kRising>(), static_cast<uint8_t>(line)));
           EXPECT_EQ(EV, ExtractBit<RegWidth_t>(GetReg<kFalling>(), static_cast<uint8_t>(line)));
        } else {
            EXPECT_EQ(EV, ExtractBit<RegWidth_t>(GetReg<trigger>(), static_cast<uint8_t>(line)));
        }
    }

    template<uint8_t EV>
    void InitReg(Line line) {
        pFunc func = GetFunc<EV>();
        EXTI->IMR  = func(static_cast<uint8_t>(line), (EXTI->IMR)); 
        EXTI->RTSR = func(static_cast<uint8_t>(line), (EXTI->RTSR));
        EXTI->FTSR = func(static_cast<uint8_t>(line), (EXTI->FTSR)); 
    }

    template<uint8_t EV>
    pFunc GetFunc();

    template<uint8_t EV>
    pControlFunc GetControlFunc();

    template<Trigger trigger>
    RegWidth_t GetReg();

    RegWidth_t ExtiReg[6];
    RegWidth_t AfioReg[7];
    volatile EXTIRegDef* EXTI;
    volatile AfioRegDef* AFIO;
    EXTI_Config exti;
};
  
TEST_F(ExtiTest, Enable) {
    ControlTest<kFalling, 1>(kPortB, kExti10);
    ControlTest<kRising, 1>(kPortA, kExti1);
    ControlTest<kBoth, 1>(kPortC, kExti15);
}

TEST_F(ExtiTest, Disable) {
    ControlTest<kFalling, 0>(kPortB, kExti10);
    ControlTest<kRising, 0>(kPortA, kExti1);
    ControlTest<kBoth, 0>(kPortC, kExti15);
}

TEST_F(ExtiTest, SetPendingFlag) {
    SetPendingTest<kPortB, kExti10, kFalling>();
    SetPendingTest<kPortA, kExti1, kRising>();
    SetPendingTest<kPortC, kExti15, kBoth>();
}

TEST_F(ExtiTest, ClearPendingFlag) {
    ClearPendingTest<kPortB, kExti10, kFalling>();
    ClearPendingTest<kPortA, kExti1, kRising>();
    ClearPendingTest<kPortC, kExti15, kBoth>();
}

template <>
RegWidth_t ExtiTest::GetReg<kRising>() { return EXTI->RTSR; }

template <>
RegWidth_t ExtiTest::GetReg<kFalling>() { return EXTI->FTSR; }

template<>
ExtiTest::pFunc ExtiTest::GetFunc<false>() { return SetBit<RegWidth_t>; }

template<>
ExtiTest::pFunc ExtiTest::GetFunc<true>() { return ClearBit<RegWidth_t>; }

template<>
ExtiTest::pControlFunc ExtiTest::GetControlFunc<true>() { return Exti::Enable; }

template<>
ExtiTest::pControlFunc ExtiTest::GetControlFunc<false>() { return Exti::Disable; }

