/**
 * @file RCc-test.cpp

 * @brief 
 * @version 0.1
 * @date 2024-03-12
 * @copyright Copyright (c) 2024
 * 
 */
#include <gtest/gtest.h>
#include "utils/inc/BitManipulation.h"
#include "mcal/inc/stm32f103xx.h"
#include "mcal/inc/Rcc.h"

uint32_t RccReg[10] = {};

using namespace stm32::utils::bit_manipulation;  // NOLINT [build/namespaces]
using namespace stm32::dev::mcal::rcc;  // NOLINT [build/namespaces]
using namespace stm32::registers::rcc;  // NOLINT [build/namespaces]

TEST(RccTest, InitSysClock) {
// Testing HSI clocksource with kClock_1x
RCC->CR.HSIRDY = 1;
Rcc::InitSysClock(kHsi, kClock_1x);
EXPECT_EQ(1,           (ExtractBits<uint32_t, 0>(RCC->CR.registerVal)));
EXPECT_EQ(0b00,        (ExtractBits<uint32_t, 0, 1>(RCC->CFGR.registerVal)));
RCC->CR.HSIRDY = 0;
// Testing HSE clocksource with kClock_1x
RCC->CR.HSERDY = 1;
Rcc::InitSysClock(kHse, kClock_1x);
EXPECT_EQ(1,           (ExtractBits<uint32_t, 16>(RCC->CR.registerVal)));
EXPECT_EQ(0b01,        (ExtractBits<uint32_t, 0, 1>(RCC->CFGR.registerVal)));
EXPECT_EQ(1,           (ExtractBits<uint32_t, 19>(RCC->CR.registerVal)));
RCC->CR.HSERDY = 0;
// Testing PLL clocksource
RCC->CR.PLLRDY = 1;
// Testing HSE as a PLLsource
Rcc::InitSysClock(kHse, kClock_2x);
EXPECT_EQ(0b0000,      (ExtractBits<uint32_t, 18, 21>(RCC->CFGR.registerVal))); // NOLINT
EXPECT_EQ(1,           (ExtractBits<uint32_t, 16>(RCC->CR.registerVal)));
EXPECT_EQ(1,           (ExtractBits<uint32_t, 16>(RCC->CFGR.registerVal)));
EXPECT_EQ(1,           (ExtractBits<uint32_t, 24>(RCC->CR.registerVal)));
EXPECT_EQ(0,           (ExtractBits<uint32_t, 17>(RCC->CFGR.registerVal)));
EXPECT_EQ(0b10,        (ExtractBits<uint32_t, 0, 1>(RCC->CFGR.registerVal)));
// Testing kHseDivBy2 as a PLLsource
Rcc::InitSysClock(kHseDivBy2, kClock_2x);
EXPECT_EQ(1,           (ExtractBits<uint32_t, 17>(RCC->CFGR.registerVal)));
// Testing HSI as a PLLsource
Rcc::InitSysClock(kHsi, kClock_2x);
EXPECT_EQ(1,           (ExtractBits<uint32_t, 0>(RCC->CR.registerVal)));
EXPECT_EQ(0,           (ExtractBits<uint32_t, 16>(RCC->CFGR.registerVal)));
// Testing multiplication factor
Rcc::InitSysClock(kHse, kClock_3x);
EXPECT_EQ(0b0001,      (ExtractBits<uint32_t, 18, 21>(RCC->CFGR.registerVal))); // NOLINT
Rcc::InitSysClock(kHse, kClock_4x);
EXPECT_EQ(0b0010,      (ExtractBits<uint32_t, 18, 21>(RCC->CFGR.registerVal))); // NOLINT
Rcc::InitSysClock(kHse, kClock_5x);
EXPECT_EQ(0b0011,      (ExtractBits<uint32_t, 18, 21>(RCC->CFGR.registerVal))); // NOLINT
Rcc::InitSysClock(kHse, kClock_6x);
EXPECT_EQ(0b0100,      (ExtractBits<uint32_t, 18, 21>(RCC->CFGR.registerVal))); // NOLINT
Rcc::InitSysClock(kHse, kClock_7x);
EXPECT_EQ(0b0101,      (ExtractBits<uint32_t, 18, 21>(RCC->CFGR.registerVal))); // NOLINT
Rcc::InitSysClock(kHse, kClock_8x);
EXPECT_EQ(0b0110,      (ExtractBits<uint32_t, 18, 21>(RCC->CFGR.registerVal))); // NOLINT
Rcc::InitSysClock(kHse, kClock_9x);
EXPECT_EQ(0b0111,      (ExtractBits<uint32_t, 18, 21>(RCC->CFGR.registerVal))); // NOLINT
Rcc::InitSysClock(kHse, kClock_10x);
EXPECT_EQ(0b1000,      (ExtractBits<uint32_t, 18, 21>(RCC->CFGR.registerVal))); // NOLINT
Rcc::InitSysClock(kHse, kClock_11x);
EXPECT_EQ(0b1001,      (ExtractBits<uint32_t, 18, 21>(RCC->CFGR.registerVal))); // NOLINT
Rcc::InitSysClock(kHse, kClock_12x);
EXPECT_EQ(0b1010,      (ExtractBits<uint32_t, 18, 21>(RCC->CFGR.registerVal))); // NOLINT
Rcc::InitSysClock(kHse, kClock_13x);
EXPECT_EQ(0b1011,      (ExtractBits<uint32_t, 18, 21>(RCC->CFGR.registerVal))); // NOLINT
Rcc::InitSysClock(kHse, kClock_14x);
EXPECT_EQ(0b1100,      (ExtractBits<uint32_t, 18, 21>(RCC->CFGR.registerVal))); // NOLINT
Rcc::InitSysClock(kHse, kClock_15x);
EXPECT_EQ(0b1101,      (ExtractBits<uint32_t, 18, 21>(RCC->CFGR.registerVal))); // NOLINT
Rcc::InitSysClock(kHse, kClock_16x);
EXPECT_EQ(0b1110,      (ExtractBits<uint32_t, 18, 21>(RCC->CFGR.registerVal))); // NOLINT
RCC->CR.PLLRDY = 0;
}

TEST(RccTest, ConfigureExternalClock) {
Rcc::SetExternalClock(kHseCrystal);
EXPECT_EQ(0,          (ExtractBits<uint32_t, 18>(RCC->CR.registerVal)));
}

TEST(RccTest, SetAHBPrescaler) {
// no div
Rcc::SetAHBPrescaler(kAhpNotDivided);
EXPECT_EQ(0b0000,      (ExtractBits<uint32_t, 4, 7>(RCC->CFGR.registerVal)));
// 2
Rcc::SetAHBPrescaler(kAhpDiv2);
EXPECT_EQ(0b1000,      (ExtractBits<uint32_t, 4, 7>(RCC->CFGR.registerVal)));
// 4
Rcc::SetAHBPrescaler(kAhpDiv4);
EXPECT_EQ(0b1001,      (ExtractBits<uint32_t, 4, 7>(RCC->CFGR.registerVal)));
// 8
Rcc::SetAHBPrescaler(kAhpDiv8);
EXPECT_EQ(0b1010,      (ExtractBits<uint32_t, 4, 7>(RCC->CFGR.registerVal)));
// 16
Rcc::SetAHBPrescaler(kAhpDiv16);
EXPECT_EQ(0b1011,      (ExtractBits<uint32_t, 4, 7>(RCC->CFGR.registerVal)));
// 64
Rcc::SetAHBPrescaler(kAhpDiv64);
EXPECT_EQ(0b1100,      (ExtractBits<uint32_t, 4, 7>(RCC->CFGR.registerVal)));
// 128
Rcc::SetAHBPrescaler(kAhpDiv128);
EXPECT_EQ(0b1101,      (ExtractBits<uint32_t, 4, 7>(RCC->CFGR.registerVal)));
// 256
Rcc::SetAHBPrescaler(kAhpDiv256);
EXPECT_EQ(0b1110,      (ExtractBits<uint32_t, 4, 7>(RCC->CFGR.registerVal)));
// 512
Rcc::SetAHBPrescaler(kAhpDiv512);
EXPECT_EQ(0b1111,      (ExtractBits<uint32_t, 4, 7>(RCC->CFGR.registerVal)));
}

TEST(RccTest, SetAPB1Prescaler) {
// no div
Rcc::SetAPB1Prescaler(kApbNotDivided);
EXPECT_EQ(0b000,       (ExtractBits<uint32_t, 8, 10>(RCC->CFGR.registerVal)));
// 2
Rcc::SetAPB1Prescaler(kApbDiv2);
EXPECT_EQ(0b100,       (ExtractBits<uint32_t, 8, 10>(RCC->CFGR.registerVal)));
// 4
Rcc::SetAPB1Prescaler(kApbDiv4);
EXPECT_EQ(0b101,       (ExtractBits<uint32_t, 8, 10>(RCC->CFGR.registerVal)));
// 8
Rcc::SetAPB1Prescaler(kApbDiv8);
EXPECT_EQ(0b110,       (ExtractBits<uint32_t, 8, 10>(RCC->CFGR.registerVal)));
// 16
Rcc::SetAPB1Prescaler(kApbDiv16);
EXPECT_EQ(0b111,       (ExtractBits<uint32_t, 8, 10>(RCC->CFGR.registerVal)));
}

TEST(RccTest, SetAPB2Prescaler) {
// no div
Rcc::SetAPB2Prescaler(kApbNotDivided);
EXPECT_EQ(0b000,       (ExtractBits<uint32_t, 11, 13>(RCC->CFGR.registerVal)));
// 2
Rcc::SetAPB2Prescaler(kApbDiv2);
EXPECT_EQ(0b100,       (ExtractBits<uint32_t, 11, 13>(RCC->CFGR.registerVal)));
// 4
Rcc::SetAPB2Prescaler(kApbDiv4);
EXPECT_EQ(0b101,       (ExtractBits<uint32_t, 11, 13>(RCC->CFGR.registerVal)));
// 8
Rcc::SetAPB2Prescaler(kApbDiv8);
EXPECT_EQ(0b110,       (ExtractBits<uint32_t, 11, 13>(RCC->CFGR.registerVal)));
// 16
Rcc::SetAPB2Prescaler(kApbDiv16);
EXPECT_EQ(0b111,       (ExtractBits<uint32_t, 11, 13>(RCC->CFGR.registerVal)));
}

TEST(RccTest, SetMCOPinClk) {
// no clock
Rcc::SetMCOPinClk(kMcoNoClock);
EXPECT_EQ(0b000,       (ExtractBits<uint32_t, 24, 26>(RCC->CFGR.registerVal)));
// system clock
Rcc::SetMCOPinClk(kMcoSystemClock);
EXPECT_EQ(0b100,       (ExtractBits<uint32_t, 24, 26>(RCC->CFGR.registerVal)));
// HSI clock
Rcc::SetMCOPinClk(kMcoHsi);
EXPECT_EQ(0b101,       (ExtractBits<uint32_t, 24, 26>(RCC->CFGR.registerVal)));
// HSE clock
Rcc::SetMCOPinClk(kMcoHse);
EXPECT_EQ(0b110,       (ExtractBits<uint32_t, 24, 26>(RCC->CFGR.registerVal)));
// PLL clock
Rcc::SetMCOPinClk(kMcoPll);
EXPECT_EQ(0b111,       (ExtractBits<uint32_t, 24, 26>(RCC->CFGR.registerVal)));
}

TEST(RccTest, AdjustInternalClock) {
Rcc::AdjustInternalClock(5);
EXPECT_EQ(5,   (ExtractBits<uint32_t, 3, 7>(RCC->CR.registerVal)));
}
