#include <stdint.h>
#include <gtest/gtest.h>

#include "utils/inc/BitManipulation.h"

using namespace stm32::dev::utils::bit_manipulation;

TEST(ExtractBits, BasicTest) { 
    uint32_t bits = 0xAA;
    uint32_t test = ExtractBits<uint32_t, 1>(bits);
    EXPECT_EQ(1, test);
}