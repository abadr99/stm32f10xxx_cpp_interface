/**
 * @file main.cpp

 * @brief 
 * @version 0.1
 * @date 2024-03-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <iostream>
#include "gtest/gtest.h"

TEST(SampleTest, BasicAssertion) {
    EXPECT_EQ(1 + 1, 2);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    std::cerr << "[gtest]: Run all tests";
    return RUN_ALL_TESTS();
}
