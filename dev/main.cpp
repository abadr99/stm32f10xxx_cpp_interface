/**
 * @file main.cpp
 * @author Manar Abdelraouf
 * @brief 
 * @version 0.1
 * @date 2024-09-23
 * @copyright Copyright (c) 2024
 */
#include "mcal/stm32f103xx.h"
#include "utils/Types.h"
#include "utils/BitManipulation.h"
#include "mcal/Pin.h"
#include "mcal/Gpio.h"
#include "mcal/Rcc.h"
#include "mcal/Timer.h"
#include "mcal/Systick.h"

using namespace stm32::type;
using namespace stm32::registers::rcc;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::mcal::rcc;
using namespace stm32::dev::mcal::timer;
using namespace stm32::registers::timer;
using namespace stm32::dev::mcal::systick;

int main(void) {

    Systick::Init();
    Rcc::Init();
    Gpio::Init();

    Rcc::InitSysClock(kHse, kClock_1x);
    Rcc::SetExternalClock(kHseCrystal);
    Rcc::Enable(Peripheral::kIOPA);
    Rcc::Enable(Peripheral::kTIM2);
    Rcc::InitSysClock();


    Systick::Enable(kAHB_Div_8);

    Pin servoA0(kPortA, kPin0, PinMode::kAlternativePushPull_50MHz);
    Gpio::Set(servoA0);


    TimerConfig config = {
            .Timerid = kTimer2,
            .Direction = kUP,
            .Prescaler =72,
            .interrupt = kDisable
            };
    Timer tim2(config);

    TimerOCTypeDef oc = {
        .mode = kPWM1,
        .state = kEnable,
        .polarity = kActiveHigh,
		.period = 100
    };
    tim2.OCMode(oc);


   while (1) {

		tim2.SetCompare1(oc, kChannel1, 100);
		Systick::Delay_ms(1000);
        
		tim2.SetCompare1(oc, kChannel1, 20);
		Systick::Delay_ms(1000);
}
}
