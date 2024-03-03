/**
 * @file BitManipulation-test.cpp

 * @brief 
 * @version 0.1
 * @date 2024-03-03
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdint.h>
#include <gtest/gtest.h>

#include "utils/inc/BitManipulation.h"

using namespace stm32::dev::utils::bit_manipulation;  // NOLINT [build/namespaces]

TEST(ExtractBits, BasicTest) {
    uint32_t bits = 0xAA;
    uint32_t test = ExtractBits<uint32_t, 1>(bits);
    EXPECT_EQ(1, test);
}
