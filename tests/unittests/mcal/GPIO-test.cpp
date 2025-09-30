/**
 * @file GPIO-test.cpp
 * @author 
 * @brief 
 * @version 0.1
 * @date 2025-09-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#if 0
#include <gtest/gtest.h>
#include "utils/Types.h"
#include "utils/Util.h"
#include "utils/BitManipulation.h"
#include "mcal/stm32f103xx.h"
#include "mcal/Pin.h"
#include "mcal/Gpio.h"

using namespace stm32::util;
using namespace stm32::registers::gpio;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;

class GpioTest : public testing::Test {
 protected:
    void SetUp() override {
        using GpioA_addr = Addr<Peripheral::kIOPA>;
        using GpioB_addr = Addr<Peripheral::kIOPB>;
        using GpioC_addr = Addr<Peripheral::kIOPC>;

        GpioA_addr::Set(&GpioReg[0]);
        GpioB_addr::Set(&GpioReg[1]);
        GpioC_addr::Set(&GpioReg[2]);
        Gpio::Init();
        GPIOA = reinterpret_cast<volatile GpioRegDef*>(&GpioReg[0]);
        GPIOB = reinterpret_cast<volatile GpioRegDef*>(&GpioReg[1]);
        GPIOC = reinterpret_cast<volatile GpioRegDef*>(&GpioReg[2]);
    }

    uint32_t GpioReg[3] = {};
    volatile GpioRegDef* GPIOA;
    volatile GpioRegDef* GPIOB;
    volatile GpioRegDef* GPIOC;
};
TEST_F(GpioTest, SetPinMode) {
    Pin pin(kPortA, kPin5, PinMode::kOutputPushPull_10MHz);
    Gpio::SetPinMode(pin, PinMode::kOutputPushPull_10MHz);
    EXPECT_EQ((static_cast<uint32_t>(PinMode::kOutputPushPull_10MHz)), 
        (ExtractBits<uint32_t, 20, 23>(GPIOA->CRL)));
}
TEST_F(GpioTest, SetPinValue) {
    Pin pin(kPortA, kPin5, PinMode::kOutputPushPull_10MHz);
    Gpio::SetPinValue(pin, stm32::type::DigitalVoltage::kHigh);
    EXPECT_EQ(1, (ExtractBits<uint32_t, 5>(GPIOA->ODR)));

    Gpio::SetPinValue(pin, stm32::type::DigitalVoltage::kLow);
    EXPECT_EQ(0, (ExtractBits<uint32_t, 5>(GPIOA->ODR)));
}
TEST_F(GpioTest, GetPinValue) {
    Pin pin(kPortA, kPin5, PinMode::kInputFloat);
    Gpio::SetPinValue(pin, stm32::type::DigitalVoltage::kHigh);
    // You need to manually set the value in IDR before calling GetPinValue, 
    // since in a real MCU, the input register reflects the actual pin state.
    GPIOA->IDR = SetBit<uint32_t>(GPIOA->IDR, 5);
    EXPECT_EQ(1, Gpio::GetPinValue(pin));

    Gpio::SetPinValue(pin, stm32::type::DigitalVoltage::kLow);
    GPIOA->IDR = ClearBit<uint32_t>(GPIOA->IDR, 5);
    EXPECT_EQ(0, Gpio::GetPinValue(pin));
}
#endif
