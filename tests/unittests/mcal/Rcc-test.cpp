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


TEST(RccTest, SetAHBPrescaler) {
// no div
Rcc::SetAHBPrescaler(kAhpNotDivided);
EXPECT_EQ(0b0000,       (ExtractBits<uint32_t, 4, 7>(RCC->CFGR.registerVal)));
// 2
Rcc::SetAHBPrescaler(kAhpDiv2);
EXPECT_EQ(0b1000,       (ExtractBits<uint32_t, 4, 7>(RCC->CFGR.registerVal)));
// 4
Rcc::SetAHBPrescaler(kAhpDiv4);
EXPECT_EQ(0b1001,       (ExtractBits<uint32_t, 4, 7>(RCC->CFGR.registerVal)));
// 8
Rcc::SetAHBPrescaler(kAhpDiv8);
EXPECT_EQ(0b1010,       (ExtractBits<uint32_t, 4, 7>(RCC->CFGR.registerVal)));
// 16
Rcc::SetAHBPrescaler(kAhpDiv16);
EXPECT_EQ(0b1011,       (ExtractBits<uint32_t, 4, 7>(RCC->CFGR.registerVal)));
// 64
Rcc::SetAHBPrescaler(kAhpDiv64);
EXPECT_EQ(0b1100,       (ExtractBits<uint32_t, 4, 7>(RCC->CFGR.registerVal)));
// 128
Rcc::SetAHBPrescaler(kAhpDiv128);
EXPECT_EQ(0b1101,       (ExtractBits<uint32_t, 4, 7>(RCC->CFGR.registerVal)));
// 256
Rcc::SetAHBPrescaler(kAhpDiv256);
EXPECT_EQ(0b1110,       (ExtractBits<uint32_t, 4, 7>(RCC->CFGR.registerVal)));
// 512
Rcc::SetAHBPrescaler(kAhpDiv512);
EXPECT_EQ(0b1111,       (ExtractBits<uint32_t, 4, 7>(RCC->CFGR.registerVal)));
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

