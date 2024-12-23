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

// commit-id: 1660278bc36e1dc1cfe4872ddd1f404c1db21bc8

#include "utils/Types.h"
#include "mcal/stm32f103xx.h"
#include "utils/BitManipulation.h"
#include "mcal/Pin.h"
#include "mcal/Gpio.h"
#include "mcal/Rcc.h"
#include "mcal/Usart.h"

using namespace stm32::type;
using namespace stm32::registers::rcc;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::mcal::rcc;
using namespace stm32::dev::mcal::usart;
int main() {
    Rcc::Init();
    Gpio::Init();
    
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
    
    Gpio::SetPinValue(pc13, kHigh);
    uint32_t msg_idx = 0;
    const char msg[] = "Hello \r\n";
    while (msg[msg_idx] != '\0') {
        usart1.Transmit(msg[msg_idx]);
        msg_idx++;
    }
    while (1) {
        const char data = usart1.Receive();
        if (data == 'r') {
            // Turn on the Led
            Gpio::SetPinValue(pc13, kLow);
        } else if (data == 'n') {
            // Turn off the Led
            Gpio::SetPinValue(pc13, kHigh);
        }
    }
}

