/**
 * @file main.cpp
 * @author Mohamed Refat
 * @brief 
 * @version 0.1
 * @date 2024-07-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

// commit-id: a5020f63948e1e8a5aa0cf6949409dc7bf34a49e

#include "Types.h"
#include "stm32f103xx.h"
#include "BitManipulation.h"
#include "Pin.h"
#include "Rcc.h"
#include "Nvic.h"
#include "Gpio.h"
#include "Usart.h"

using namespace stm32::type;
using namespace stm32::registers::rcc;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::mcal::rcc;
using namespace stm32::dev::mcal::nvic;
using namespace stm32::dev::mcal::usart;
volatile int  flag = 0;
void TransmitISR(void) {
    flag  = 1;
}
int main() {
    flag = 0;
    Rcc::InitSysClock();
    Rcc::SetExternalClock(kHseCrystal);
    Rcc::Enable(Peripheral::kIOPA);
    Rcc::Enable(Peripheral::kIOPC);
    Rcc::Enable(Peripheral::kUSART1);

    Pin pc13(kPortC, kPin13, PinMode::kOutputPushPull_10MHz);
    Pin rx1(kPortA,  kPin10, PinMode::kInputFloat);
    Pin tx1(kPortA,  kPin9,  PinMode::kAlternativePushPull_10MHz);

    Gpio::Set(pc13);
    Gpio::Set(rx1);
    Gpio::Set(tx1);


    UsartConfig usart1_conf = {kUsart1, kRxTx, kSb_1_, kDataBits_8_, kNo_Parity,  kNone, 9600};
    Usart usart1(usart1_conf);
    usart1.Init();
    

    Gpio::SetPinValue(pc13, DigitalVoltage::kHigh);
    Usart::DataValType data = 0;
    usart1.Transmit(48, TransmitISR);
    usart1.Receive(&data, nullptr);
    Nvic::EnableInterrupt(kUSART1_IRQn);
    while (1) {
        if (flag) {
        if (data == 'r') {
            // Turn on the Led
            Gpio::SetPinValue(pc13, DigitalVoltage::kLow);
        } else if (data == 'n') {
            // Turn off the Led
            Gpio::SetPinValue(pc13, DigitalVoltage::kHigh);
        }
        }
    }
}
