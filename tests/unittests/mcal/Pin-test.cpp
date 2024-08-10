/**
 * @file  Pin-test.cpp
 * @author ManarAbdelraoouf
 * @brief Test for Pin Driver
 * @version  0.1
 * @date 2024-04-15
 * @copyright Copyright (c) 2024
 */
#include <gtest/gtest.h>
#include "utils/inc/BitManipulation.h"
#include "mcal/inc/stm32f103xx.h"
#include "mcal/inc/Pin.h"

uint32_t GPIOAReg[7] = {};
uint32_t GPIOBReg[7] = {};
uint32_t GPIOCReg[7] = {};

using namespace stm32::utils::bit_manipulation;  // NOLINT [build/namespaces]
using namespace stm32::dev::mcal::pin;           // NOLINT [build/namespaces]
using namespace stm32::registers::gpio;          // NOLINT [build/namespaces]


TEST(PinTest, SetPort) {
    Pin pin(kPortA, kPin0, PinMode::kOutputPushPull_2MHz);
    pin.SetPort(kPortB);
    EXPECT_EQ(kPortB, pin.GetPort());
    pin.SetPort(kPortC);
    EXPECT_EQ(kPortC, pin.GetPort());
}
TEST(PinTest, SetPinNumber) {
    Pin pin(kPortA, kPin0, PinMode::kOutputPushPull_2MHz);
    pin.SetPinNumber((kPin4));
    EXPECT_EQ(kPin4, pin.GetPinNumber());

    pin.SetPinNumber((PinNumber)4);
    EXPECT_EQ(kPin4, pin.GetPinNumber());

    pin.SetPort(kPortB);
    EXPECT_EQ(kPin4, pin.GetPinNumber());
}

TEST(PinTest, SetPinMode) {
    Pin pin(kPortA, kPin0, PinMode::kOutputPushPull_2MHz);
    pin.SetPinMode(PinMode::kInputFloat);
    EXPECT_EQ(PinMode::kInputFloat, pin.GetPinMode());

    pin.SetPinMode(PinMode::kAlternativePushPull_50MHz);
    EXPECT_EQ(PinMode::kAlternativePushPull_50MHz, pin.GetPinMode());

    pin.SetPinNumber(kPin15);
    EXPECT_EQ(PinMode::kAlternativePushPull_50MHz, pin.GetPinMode());
}

TEST(PinTest, GetPort) {
    Pin pin(kPortA, kPin0, PinMode::kOutputPushPull_10MHz);
    EXPECT_EQ(kPortA, pin.GetPort());
}

TEST(PinTest, GetPinNumber) {
    Pin pin(kPortA, kPin0, PinMode::kOutputPushPull_10MHz);
    EXPECT_EQ(kPin0, pin.GetPinNumber());
}

TEST(PinTest, GetPinMode) {
    Pin pin(kPortA, kPin0, PinMode::kOutputPushPull_10MHz);
    EXPECT_EQ(PinMode::kOutputPushPull_10MHz, pin.GetPinMode());
}
