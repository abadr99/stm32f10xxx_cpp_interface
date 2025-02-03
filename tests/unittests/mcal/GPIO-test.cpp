/**
 * @file GPIO-test.cpp
 * @author Mohamed Refat
 * @brief 
 * @version 0.1
 * @date 2024-04-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <gtest/gtest.h>
#include "utils/BitManipulation.h"
#include "mcal/stm32f103xx.h"
#include "mcal/Pin.h"
#include "mcal/Gpio.h"

using namespace stm32::util;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::registers::gpio;

#define SET_ADDRESS(port)\
    Addr<Peripheral::kIOP##port>::Set(&Gpio##port##Reg[0]);

#define SET_TEST_ADDRESS()\
    SET_ADDRESS(A)\
    SET_ADDRESS(B)\
    SET_ADDRESS(C)

#define SA(idx, port)\
    GPIOx[idx] = Gpio::GetPtr<kPort##port>();

#define SET_GPIOx_ADDRESS()\
    SA(0, A)\
    SA(1, B)\
    SA(2, C)


class GpioTest : public testing::Test {
 protected:
    using DigitalVoltage = stm32::type::DigitalVoltage;
    void SetUp() override {
        SET_TEST_ADDRESS();
        Gpio::Init();
        SET_GPIOx_ADDRESS();
    }

    template<Port port, PinNumber pinNumber>
    void SetModeTest(PinMode mode) {
        pin.SetPort(port);
        pin.SetPinNumber(pinNumber);
        pin.SetPinMode(mode);
        Gpio::SetPinMode(pin, mode);
        EXPECT_EQ(static_cast<uint8_t>(mode), 
            (ExtractBits<RegWidth_t>(GetModeReg(), GetStartBit(), GetStartBit() + 3)));
    }

    template<Port port, PinNumber pinNumber, PinMode mode>
    void SetPinValueTest(DigitalVoltage state) {
        pin.SetPort(port);
        pin.SetPinNumber(pinNumber);
        pin.SetPinMode(mode);
        Gpio::SetPinValue(pin, state);
        EXPECT_EQ(static_cast<uint8_t>(state), 
        (ExtractBits<RegWidth_t, static_cast<uint8_t>(pinNumber)>
            (GPIOx[pin.GetPort()]->ODR)));      
    }

    uint8_t GetStartBit() {
        if (pin.GetPinNumber() <= 7) {
            return (pin.GetPinNumber() * 4);
        } else {
            return ((pin.GetPinNumber() - 8) * 4);
        }
    }

    RegWidth_t GetModeReg() {
        if (pin.GetPinNumber() <= 7) {
            return GPIOx[pin.GetPort()]->CRL;
        } else {
            return GPIOx[pin.GetPort()]->CRH;
        }  
    }

    volatile GpioRegDef *GPIOx[3];
    RegWidth_t GpioAReg[7];
    RegWidth_t GpioBReg[7];
    RegWidth_t GpioCReg[7];
    Pin pin;
};

TEST_F(GpioTest, SetPinMode) {
    SetModeTest<kPortA, kPin7>(PinMode::kOutputPushPull_10MHz);
    SetModeTest<kPortB, kPin1>(PinMode::kAlternativeOpenDrain_10MHz);
    SetModeTest<kPortC, kPin9>(PinMode::kInputPullDown);
}

TEST_F(GpioTest, SetPinValue) {
    SetPinValueTest<kPortC, kPin9, PinMode::kInputPullDown>(DigitalVoltage::kHigh);
    SetPinValueTest<kPortA, kPin7, PinMode::kOutputPushPull_10MHz>(DigitalVoltage::kLow);
    SetPinValueTest<kPortB, kPin1, PinMode::kAlternativeOpenDrain_10MHz>(DigitalVoltage::kHigh);
}

