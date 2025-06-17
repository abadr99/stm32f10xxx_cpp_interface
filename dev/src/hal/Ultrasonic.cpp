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

Ultrasonic::Ultrasonic(const Pin& triggerPin, const Pin& echoPin,
                       const TimerConfig &cfg, TimerChannels ch)
    : triggerPin_(triggerPin), echoPin_(echoPin), timer_(cfg), channel_(ch) {
    Rcc::Enable(MapPortToPeripheral(triggerPin_.GetPort()));
    Rcc::Enable(MapPortToPeripheral(echoPin_.GetPort()));
    Gpio::Set(triggerPin_);
    Gpio::Set(echoPin_);
    
    TimerICTypeDef icConfig {
        .selection = kDirectTI,
        .prescaler = 0,
        .filter = 0,
        .polarity = kRisingEdge  // Will change to FallingEdge after first edge
    };
    timer_.ICMode(channel_, icConfig);
}
void Ultrasonic::Trigger() {
    Gpio::SetPinValue(triggerPin_, kLow);
    Systick::Delay_us(2);  // Wait for 2 microseconds
    Gpio::SetPinValue(triggerPin_, kHigh);
    Systick::Delay_us(10);  // Trigger pulse duration
    Gpio::SetPinValue(triggerPin_, kLow);
}
uint16_t Ultrasonic::GetEchoDuration() {
    TimerICTypeDef icConfig {
        .selection = kDirectTI,
        .prescaler = 0,
        .filter = 0,
        .polarity = kRisingEdge
    };
    timer_.ICMode(channel_, icConfig);
    while (timer_.GetCaptureValue(channel_) == 0) { }
    uint16_t risingEdge = timer_.GetCaptureValue(channel_);
    timer_.ClearCaptureFlag(channel_);
    // Switch to falling edge detection
    icConfig.polarity = kFallingEdge;
    timer_.ICMode(channel_, icConfig);
    while (timer_.GetCaptureValue(channel_) == 0) { }
    uint16_t fallingEdge = timer_.GetCaptureValue(channel_);
    return fallingEdge > risingEdge ? (fallingEdge - risingEdge) : 0;
}
float Ultrasonic::MeasureDistanceCM() {
    Trigger();
    uint16_t duration = GetEchoDuration();
    float distance = (duration * 0.0343f) / 2;  // Speed of sound is 343 m/s
    return distance;  // Distance in cm
}
