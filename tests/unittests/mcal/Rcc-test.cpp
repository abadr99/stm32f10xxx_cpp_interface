/**
 * @file RCc-test.cpp

 * @brief
 * @version 0.1
 * @date 2024-03-12
 * @copyright Copyright (c) 2024
 *
 */
#include <gtest/gtest.h>

#include "utils/BitManipulation.h"
#include "mcal/stm32f103xx.h"
#include "mcal/Rcc.h"

using namespace stm32::util;                      // NOLINT [build/namespaces]
using namespace stm32::dev::mcal::rcc;            // NOLINT [build/namespaces]
using namespace stm32::registers::rcc;            // NOLINT [build/namespaces]
using ExpectedVal = uint32_t;                     // NOLINT [build/namespaces]

class RccTest : public testing::Test {
  protected:
    void SetUp() override {
        using Rcc_addr = stm32::constant::Address<Peripheral::kRCC>;
        Rcc_addr::SetTestAddr(&RccReg[0]);
        RCC = stm32::dev::mcal::rcc::Rcc::GetRccRegisters(); 
        Rcc::Init(); 
    }
    volatile RccRegDef* RCC;
    void TestMultiplicationFactor(PLL_MulFactor M, ExpectedVal E) {
        Rcc::InitSysClock(kHse, M);
        EXPECT_EQ(E, (ExtractBits<uint32_t, 18, 21>(RCC->CFGR.registerVal)));
    }

    void TestAHBPrescaler(AHP_ClockDivider A, ExpectedVal E) {
        Rcc::SetAHBPrescaler(A);
        EXPECT_EQ(E, (ExtractBits<uint32_t, 4, 7>(RCC->CFGR.registerVal)));
    }

    void TestMCO(McoModes M,  ExpectedVal E) {
        Rcc::SetMCOPinClk(M);
        EXPECT_EQ(E, (ExtractBits<uint32_t, 24, 26>(RCC->CFGR.registerVal)));
    }
    RegWidth_t RccReg[10];
};

TEST_F(RccTest, InitSysClock) {
    // Testing HSI clock source with kClock_1x
    RCC->CR.HSIRDY = 1;
    Rcc::InitSysClock(kHsi, kClock_1x);
    EXPECT_EQ(1,    (ExtractBits<uint32_t, 0>(RCC->CR.registerVal)));
    EXPECT_EQ(0b00, (ExtractBits<uint32_t, 0, 1>(RCC->CFGR.registerVal)));
    RCC->CR.HSIRDY = 0;

    // Testing HSE clock source with kClock_1x
    RCC->CR.HSERDY = 1;
    Rcc::InitSysClock(kHse, kClock_1x);
    EXPECT_EQ(1,    (ExtractBits<uint32_t, 16>(RCC->CR.registerVal)));
    EXPECT_EQ(0b01, (ExtractBits<uint32_t, 0, 1>(RCC->CFGR.registerVal)));
    EXPECT_EQ(1,    (ExtractBits<uint32_t, 19>(RCC->CR.registerVal)));
    RCC->CR.HSERDY = 0;

    // Testing PLL clock source
    RCC->CR.PLLRDY = 1;

    // Testing HSE as a PLLsource
    Rcc::InitSysClock(kHse, kClock_2x);
    EXPECT_EQ(0b0000, (ExtractBits<uint32_t, 18, 21>(RCC->CFGR.registerVal)));
    EXPECT_EQ(1,      (ExtractBits<uint32_t, 16>(RCC->CR.registerVal)));
    EXPECT_EQ(1,      (ExtractBits<uint32_t, 16>(RCC->CFGR.registerVal)));
    EXPECT_EQ(1,      (ExtractBits<uint32_t, 24>(RCC->CR.registerVal)));
    EXPECT_EQ(0,      (ExtractBits<uint32_t, 17>(RCC->CFGR.registerVal)));
    EXPECT_EQ(0b10,   (ExtractBits<uint32_t, 0, 1>(RCC->CFGR.registerVal)));

    // Testing kHseDivBy2 as a PLLsource
    Rcc::InitSysClock(kHseDivBy2, kClock_2x);
    EXPECT_EQ(1, (ExtractBits<uint32_t, 17>(RCC->CFGR.registerVal)));

    // Testing HSI as a PLLsource
    Rcc::InitSysClock(kHsi, kClock_2x);
    EXPECT_EQ(1, (ExtractBits<uint32_t, 0>(RCC->CR.registerVal)));
    EXPECT_EQ(0, (ExtractBits<uint32_t, 16>(RCC->CFGR.registerVal)));

    // Testing multiplication factor
    TestMultiplicationFactor(kClock_3x, 0b0001);
    TestMultiplicationFactor(kClock_4x, 0b0010);
    TestMultiplicationFactor(kClock_5x, 0b0011);
    TestMultiplicationFactor(kClock_6x, 0b0100);
    TestMultiplicationFactor(kClock_7x, 0b0101);
    TestMultiplicationFactor(kClock_8x, 0b0110);
    TestMultiplicationFactor(kClock_9x, 0b0111);
    TestMultiplicationFactor(kClock_10x, 0b1000);
    TestMultiplicationFactor(kClock_11x, 0b1001);
    TestMultiplicationFactor(kClock_12x, 0b1010);
    TestMultiplicationFactor(kClock_13x, 0b1011);
    TestMultiplicationFactor(kClock_14x, 0b1100);
    TestMultiplicationFactor(kClock_15x, 0b1101);
    TestMultiplicationFactor(kClock_16x, 0b1110);

    RCC->CR.PLLRDY = 0;
}

// TEST(RccTest, ConfigureExternalClock) {
//     Rcc::SetExternalClock(kHseCrystal);
//     EXPECT_EQ(0,          (ExtractBits<uint32_t, 18>(RCC->CR.registerVal)));
// }

// TEST(RccTest, SetAHBPrescaler) {
//     TestAHBPrescaler(kAhpNotDivided, 0);
//     TestAHBPrescaler(kAhpDiv2,       0b1000);
//     TestAHBPrescaler(kAhpDiv4,       0b1001);
//     TestAHBPrescaler(kAhpDiv8,       0b1010);
//     TestAHBPrescaler(kAhpDiv16,      0b1011);
//     TestAHBPrescaler(kAhpDiv64,      0b1100);
//     TestAHBPrescaler(kAhpDiv128,     0b1101);
//     TestAHBPrescaler(kAhpDiv256,     0b1110);
//     TestAHBPrescaler(kAhpDiv512,     0b1111);
// }

// TEST(RccTest, SetAPB1Prescaler) {
//     // no div
//     Rcc::SetAPB1Prescaler(kApbNotDivided);
//     EXPECT_EQ(0b000, (ExtractBits<uint32_t, 8, 10>(RCC->CFGR.registerVal)));

//     // 2
//     Rcc::SetAPB1Prescaler(kApbDiv2);
//     EXPECT_EQ(0b100, (ExtractBits<uint32_t, 8, 10>(RCC->CFGR.registerVal)));

//     // 4
//     Rcc::SetAPB1Prescaler(kApbDiv4);
//     EXPECT_EQ(0b101, (ExtractBits<uint32_t, 8, 10>(RCC->CFGR.registerVal)));

//     // 8
//     Rcc::SetAPB1Prescaler(kApbDiv8);
//     EXPECT_EQ(0b110, (ExtractBits<uint32_t, 8, 10>(RCC->CFGR.registerVal)));

//     // 16
//     Rcc::SetAPB1Prescaler(kApbDiv16);
//     EXPECT_EQ(0b111, (ExtractBits<uint32_t, 8, 10>(RCC->CFGR.registerVal)));
// }

// TEST(RccTest, SetAPB2Prescaler) {
//     // no div
//     Rcc::SetAPB2Prescaler(kApbNotDivided);
//     EXPECT_EQ(0b000, (ExtractBits<uint32_t, 11, 13>(RCC->CFGR.registerVal)));
//     // 2
//     Rcc::SetAPB2Prescaler(kApbDiv2);
//     EXPECT_EQ(0b100, (ExtractBits<uint32_t, 11, 13>(RCC->CFGR.registerVal)));
//     // 4
//     Rcc::SetAPB2Prescaler(kApbDiv4);
//     EXPECT_EQ(0b101, (ExtractBits<uint32_t, 11, 13>(RCC->CFGR.registerVal)));
//     // 8
//     Rcc::SetAPB2Prescaler(kApbDiv8);
//     EXPECT_EQ(0b110, (ExtractBits<uint32_t, 11, 13>(RCC->CFGR.registerVal)));
//     // 16
//     Rcc::SetAPB2Prescaler(kApbDiv16);
//     EXPECT_EQ(0b111, (ExtractBits<uint32_t, 11, 13>(RCC->CFGR.registerVal)));
// }

// TEST(RccTest, SetMCOPinClk) {
//     TestMCO(kMcoNoClock,     0b000);
//     TestMCO(kMcoSystemClock, 0b100);
//     TestMCO(kMcoHsi,         0b101);
//     TestMCO(kMcoHse,         0b110);
//     TestMCO(kMcoPll,         0b111);
// }

// TEST(RccTest, AdjustInternalClock) {
//     Rcc::AdjustInternalClock(5);
//     EXPECT_EQ(5,   (ExtractBits<uint32_t, 3, 7>(RCC->CR.registerVal)));
// }
