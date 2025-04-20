/**
* @file Ultrasonic.cpp
* @brief
* @version 0.1
* @date 2025-03-29
*
* @copyright Copyright (c) 2024
*
*/
#include "mcal/Pin.h"
#include "mcal/Gpio.h"
#include "mcal/Rcc.h"
#include "mcal/Systick.h"
#include "utils/Assert.h"
#include "utils/Util.h"
#include "mcal/Timer.h"
#include "hal/Ultrasonic.h"

using namespace stm32::util;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::systick;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::mcal::rcc;
using namespace stm32::dev::mcal::timer;
using namespace stm32::dev::hal::ultrasonic;

Ultrasonic::Ultrasonic(const Pin& triggerPin, const Pin& echoPin, Timer *timer)
    : triggerPin_(triggerPin), echoPin_(echoPin), timer_(timer) {
    Rcc::Enable(MapPortToPeripheral(triggerPin_.GetPort()));
    Rcc::Enable(MapPortToPeripheral(echoPin_.GetPort()));
    Gpio::Set(triggerPin_);
    Gpio::Set(echoPin_);
    Gpio::SetPinValue(triggerPin_, kLow);
}
void Ultrasonic::Trigger() {
    Gpio::SetPinValue(triggerPin_, kHigh);
    Systick::Delay_us(10);  // Trigger pulse duration
    Gpio::SetPinValue(triggerPin_, kLow);
}
float Ultrasonic::MeasureDistance() {
    TimerICTypeDef ic {
        .selection = kDirectTI,
        .prescaler = 0,
        .filter = 0,
        .polarity = kRisingEdge,
    };
    timer_->ICMode(kChannel1, ic);
    while (timer_->GetCaptureValue(kChannel1) == 0) { }
    uint16_t startTime = timer_->GetCaptureValue(kChannel1);
    timer_->ClearCaptureFlag(kChannel1);
    // Switch to falling edge detection
    ic.polarity = kFallingEdge;
    timer_->ICMode(kChannel1, ic);
    while (timer_->GetCaptureValue(kChannel1) == startTime) { }
    uint16_t endTime = timer_->GetCaptureValue(kChannel1);
    uint16_t duration = endTime - startTime;
    return (static_cast<float>(duration) / 58.0f);
}
