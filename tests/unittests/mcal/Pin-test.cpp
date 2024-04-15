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
    Pin pin(kPortA, kPin0, PinMode::kOutput);
    pin.SetPort(kPortB);
    EXPECT_EQ(kPortB, pin.GetPort());
    pin.SetPort(kPortC);
    EXPECT_EQ(kPortC, pin.GetPort());
}
TEST(PinTest, SetPinNumber) {
    Pin pin(kPortA, kPin0, PinMode::kOutput);
    pin.SetPinNumber((kPin4));
    EXPECT_EQ(kPin4, pin.GetPinNumber());

    pin.SetPinNumber((PinNumber)4);
    EXPECT_EQ(kPin4, pin.GetPinNumber());

    pin.SetPort(kPortB);
    EXPECT_EQ(kPin4, pin.GetPinNumber());
/*  // Test unexpected number of pin
    pin.SetPinNumber((PinNumber)16);
    EXPECT_NE(kPin0, pin.GetPinNumber());
*/
}

TEST(PinTest, SetPinMode) {
    Pin pin(kPortA, kPin0, PinMode::kOutput);
    pin.SetPinMode(PinMode::kInput);
    EXPECT_EQ(PinMode::kInput, pin.GetPinMode());

    pin.SetPinMode(PinMode::kAlternative);
    EXPECT_EQ(PinMode::kAlternative, pin.GetPinMode());

    pin.SetPinNumber(kPin15);
    EXPECT_EQ(PinMode::kAlternative, pin.GetPinMode());
}

TEST(PinTest, SetInputMode) {
    Pin pin(kPortA, kPin0, PinMode::kInput);
    // Test Ananlog Mode
    pin.SetInputMode(InputMode::kAnalog);
    EXPECT_EQ(0b00, (ExtractBits<uint32_t, 2, 3>(GPIOA->CRL)));
    pin.SetPinNumber((kPin4));
    EXPECT_EQ(0b00, (ExtractBits<uint32_t, 18, 19>(GPIOA->CRL)));
    pin.SetPinNumber((kPin15));
    EXPECT_EQ(0b00, (ExtractBits<uint32_t, 30, 31>(GPIOA->CRH)));

    // Test Analog Pull UP/Down
    pin.SetInputMode(InputMode::kPulldown);
    EXPECT_EQ(0b0, (ExtractBits<uint32_t, 15>(GPIOA->ODR)));
    pin.SetInputMode(InputMode::kPullup);
    EXPECT_EQ(0b1, (ExtractBits<uint32_t, 15>(GPIOA->ODR)));

    // Test Floating Mode

    pin.SetInputMode(InputMode::kFloating);
    EXPECT_EQ(0b01, (ExtractBits<uint32_t, 30, 31>(GPIOA->CRH)));  //#### doesn't detect 0b01 , always read 0b00 ####
    
    // Test Floating Pull UP/Down
    pin.SetInputMode(InputMode::kPulldown);
    EXPECT_EQ(0b0, (ExtractBits<uint32_t, 8>(GPIOA->ODR)));
    pin.SetInputMode(InputMode::kPullup);
    EXPECT_EQ(0b1, (ExtractBits<uint32_t, 8>(GPIOA->ODR)));

}
/*
TEST(PinTest, SetOutputMode) {
    Pin pin(kPortA, kPin0, PinMode::kOutput);
    // Test Push Pull Speed 10MHZ  of Pin 0
    pin.SetOutputMode(OutputMode::kPushPull_10MHZ);
    EXPECT_EQ(0b00, (ExtractBits<uint32_t, 2, 3>(GPIOA->CRL)));
    EXPECT_EQ(0b01, (ExtractBits<uint32_t, 0, 1>(GPIOA->CRL)));
    // Test Push Pull Speed 2MHZ  of Pin 9
    pin.SetPinNumber(kPin9);
    pin.SetOutputMode(OutputMode::kPushPull_2MHZ);
    EXPECT_EQ(0b00, (ExtractBits<uint32_t, 6, 7>(GPIOA->CRH)));
    EXPECT_EQ(0b10, (ExtractBits<uint32_t, 4, 5>(GPIOA->CRH)));  // #### doesn't detect 0b10 , always read 0b00 ####
    // Test Push Pull Speed 50MHZ  of Pin 14
    pin.SetPinNumber(kPin14);
    pin.SetOutputMode(OutputMode::kPushPull_50MHZ);
    EXPECT_EQ(0b00, (ExtractBits<uint32_t, 26, 27>(GPIOA->CRH)));
    EXPECT_EQ(0b11, (ExtractBits<uint32_t, 24, 25>(GPIOA->CRH)));  // #### doesn't detect 0b11 , always read 0b00 ####

    // Test Open Drain Speed 10MHZ  of Pin 0
    pin.SetPinNumber(kPin0);
    pin.SetOutputMode(OutputMode::kPushPull_10MHZ);
    EXPECT_EQ(0b01, (ExtractBits<uint32_t, 2, 3>(GPIOA->CRL)));
    EXPECT_EQ(0b01, (ExtractBits<uint32_t, 0, 1>(GPIOA->CRL)));
    // Test Open Drain Speed 2MHZ  of Pin 9
    pin.SetPinNumber(kPin9);
    pin.SetOutputMode(OutputMode::kPushPull_2MHZ);
    EXPECT_EQ(0b01, (ExtractBits<uint32_t, 6, 7>(GPIOA->CRH)));
    EXPECT_EQ(0b10, (ExtractBits<uint32_t, 4, 5>(GPIOA->CRH)));
    // Test Open Drain Speed 50MHZ  of Pin 14
    pin.SetPinNumber(kPin14);
    pin.SetOutputMode(OutputMode::kPushPull_50MHZ);
    EXPECT_EQ(0b01, (ExtractBits<uint32_t, 26, 27>(GPIOA->CRH)));
    EXPECT_EQ(0b11, (ExtractBits<uint32_t, 24, 25>(GPIOA->CRH)));
}

TEST(PinTest, SetAlternativeMode) {
    Pin pin(kPortA, kPin0, PinMode::kOutput);
    // Test Push Pull Speed 10MHZ  of Pin 0
    pin.SetAlternativeMode(AlternativeMode::kPushPull_10MHZ);
    EXPECT_EQ(0b10, (ExtractBits<uint32_t, 2, 3>(GPIOA->CRL)));
    EXPECT_EQ(0b01, (ExtractBits<uint32_t, 0, 1>(GPIOA->CRL)));
    // Test Push Pull Speed 2MHZ  of Pin 9
    pin.SetPinNumber(kPin9);
    pin.SetAlternativeMode(AlternativeMode::kPushPull_2MHZ);
    EXPECT_EQ(0b10, (ExtractBits<uint32_t, 6, 7>(GPIOA->CRH)));
    EXPECT_EQ(0b10, (ExtractBits<uint32_t, 4, 5>(GPIOA->CRH)));
    // Test Push Pull Speed 50MHZ  of Pin 14
    pin.SetPinNumber(kPin14);
    pin.SetAlternativeMode(AlternativeMode::kPushPull_50MHZ);
    EXPECT_EQ(0b10, (ExtractBits<uint32_t, 26, 27>(GPIOA->CRH)));
    EXPECT_EQ(0b11, (ExtractBits<uint32_t, 24, 25>(GPIOA->CRH)));

    // Test Open Drain Speed 10MHZ  of Pin 0
    pin.SetPinNumber(kPin0);
    pin.SetAlternativeMode(AlternativeMode::kPushPull_10MHZ);
    EXPECT_EQ(0b11, (ExtractBits<uint32_t, 2, 3>(GPIOA->CRL)));
    EXPECT_EQ(0b01, (ExtractBits<uint32_t, 0, 1>(GPIOA->CRL)));
    // Test Open Drain Speed 2MHZ  of Pin 9
    pin.SetPinNumber(kPin9);
    pin.SetAlternativeMode(AlternativeMode::kPushPull_2MHZ);
    EXPECT_EQ(0b11, (ExtractBits<uint32_t, 6, 7>(GPIOA->CRH)));
    EXPECT_EQ(0b10, (ExtractBits<uint32_t, 4, 5>(GPIOA->CRH)));
    // Test Open Drain Speed 50MHZ  of Pin 14
    pin.SetPinNumber(kPin14);
    pin.SetAlternativeMode(AlternativeMode::kPushPull_50MHZ);
    EXPECT_EQ(0b11, (ExtractBits<uint32_t, 26, 27>(GPIOA->CRH)));
    EXPECT_EQ(0b11, (ExtractBits<uint32_t, 24, 25>(GPIOA->CRH)));
}
*/
TEST(PinTest, GetPort) {
    Pin pin(kPortA, kPin0, PinMode::kOutput);
    EXPECT_EQ(kPortA, pin.GetPort());
}

TEST(PinTest, GetPinNumber) {
    Pin pin(kPortA, kPin0, PinMode::kOutput);
    EXPECT_EQ(kPin0, pin.GetPinNumber());
}

TEST(PinTest, GetPinMode) {
    Pin pin(kPortA, kPin0, PinMode::kOutput);
    EXPECT_EQ(PinMode::kOutput, pin.GetPinMode());
}
