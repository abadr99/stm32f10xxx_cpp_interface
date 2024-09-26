/**
 * @file main.cpp
 * @author Manar Abdelraouf
 * @brief 
 * @version 0.1
 * @date 2024-09-23
 * @copyright Copyright (c) 2024
 */
// commit-id: 
#include <stdint.h>
#include "utils/Types.h"
#include "mcal/stm32f103xx.h"
#include "BitManipulation.h"
#include "mcal/Pin.h"
#include "mcal/Gpio.h"
#include "mcal/Rcc.h"
#include "mcal/Nvic.h"
#include "mcal/Timer.h"
#include "hal/Led.h"
using namespace stm32::type;
using namespace stm32::registers::rcc;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::mcal::rcc;
using namespace stm32::dev::mcal::timer;
using namespace stm32::dev::mcal::nvic;
using namespace stm32::type;
using namespace stm32::dev::hal::led;

void func(void);
int main(void) {
    Rcc::InitSysClock(kHse, kClock_1x);
    Rcc::SetExternalClock(kHseCrystal);
    Rcc::Enable(Peripheral::kIOPC);
    Rcc::Enable(Peripheral::kTIM2);

    Id id_config(kTIM2_IRQn);
    Nvic::EnableInterrupt(id_config);

    TimerConfig tim2_config = {
            .Timerid = kTimer2,
            .Direction = kDown,
            .Prescaler = 4000,  // 4000/4000=1
            .pfunction = func
            };
    Timer tim2(tim2_config);
while(1) {
    tim2.Delay_ms(1000);
}
}
void func(void) {
    static uint32_t c = 0;
    Pin pLed(kPortC, kPin15, PinMode::kOutputPushPull_10MHz);
    Led<ConnectionType::kForward_Bias> led(pLed);
    if (c % 2 == 0) {
        led.TurnOn();
        c++;
    } else {    
        led.TurnOff();
        c++;
    }
}
