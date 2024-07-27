/**
 * @file Array-test.cpp
 * @author abadr99 (abdelrhmanezzbadr@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdint.h>
#include <gtest/gtest.h>

#include "Array.h"

using namespace stm32::utils::array;

TEST(ArrayTest, BasicTest1) {
    Array<int, 5> arr;
    EXPECT_EQ(arr.Size(), 5);
    for (int i = 0 ; i < 5 ; ++i) {
        arr[i] = i * 2;
    }
    for (int i = 0 ; i < 5 ; ++i) {
        EXPECT_EQ(arr[i], i*2);
    }
}

TEST(ArrayTest, BasicTest2) {
    Array<int, 5> arr;
    EXPECT_EQ(arr.Size(), 5);
    for (int i = 0 ; i < 5 ; ++i) {
        arr[i] = i * 2;
    }
    Array<int, 5> arr1(arr);
    for (int i = 0 ; i < 5 ; ++i) {
        EXPECT_EQ(arr1[i], i*2);
    }
}
