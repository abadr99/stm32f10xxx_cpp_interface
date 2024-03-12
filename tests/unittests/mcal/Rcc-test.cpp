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

using namespace stm32::dev::mcal::rcc;  // NOLINT [build/namespaces]
using RegWidth_t = stm32::utils::types::RegWidth_t;
#define ExtractBits  (stm32::utils::bit_manipulation::ExtractBits)
TEST(RccTest, SetAHBPrescaler) {
// no div
Rcc::SetAHBPrescaler(kAhpNotDivided);
EXPECT_EQ(0b0000,       (ExtractBits<RegWidth_t, 4, 7>(RCC->CFGR)));
// 2
Rcc::SetAHBPrescaler(kAhpDiv2);
EXPECT_EQ(0b1000,       (ExtractBits<RegWidth_t, 4, 7>(RCC->CFGR)));
// 4
Rcc::SetAHBPrescaler(kAhpDiv4);
EXPECT_EQ(0b1001,       (ExtractBits<RegWidth_t, 4, 7>(RCC->CFGR)));
// 8
Rcc::SetAHBPrescaler(kAhpDiv8);
EXPECT_EQ(0b1010,       (ExtractBits<RegWidth_t, 4, 7>(RCC->CFGR)));
// 16
Rcc::SetAHBPrescaler(kAhpDiv16);
EXPECT_EQ(0b1011,       (ExtractBits<RegWidth_t, 4, 7>(RCC->CFGR)));
// 64
Rcc::SetAHBPrescaler(kAhpDiv64);
EXPECT_EQ(0b1100,       (ExtractBits<RegWidth_t, 4, 7>(RCC->CFGR)));
// 128
Rcc::SetAHBPrescaler(kAhpDiv128);
EXPECT_EQ(0b1101,       (ExtractBits<RegWidth_t, 4, 7>(RCC->CFGR)));
// 256
Rcc::SetAHBPrescaler(kAhpDiv256);
EXPECT_EQ(0b1110,       (ExtractBits<RegWidth_t, 4, 7>(RCC->CFGR)));
// 512
Rcc::SetAHBPrescaler(kAhpDiv512);
EXPECT_EQ(0b1111,       (ExtractBits<RegWidth_t, 4, 7>(RCC->CFGR)));}
