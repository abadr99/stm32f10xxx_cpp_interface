/**
 * @file Ultrasonic.cpp
 * @brief 
 * @version 0.1
 * @date 2025-03-28
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "mcal/Pin.h"
#include "mcal/Gpio.h"
#include "mcal/Rcc.h"
#include "mcal/Systick.h"
#include "mcal/Timer.h"
#include "utils/Util.h"
#include "hal/Ultrasonic.h"

using namespace stm32;
using namespace stm32::type;
using namespace stm32::util;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::systick;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::mcal::rcc;
using namespace stm32::dev::mcal::timer;
using namespace stm32::dev::hal::ultrasonic;

Ultrasonic::Ultrasonic(const UltrasonicConfig& config, Timer *timer) 
    : config_(config), timer_(timer) {
    Rcc::Enable(MapPortToPeripheral(config_.trigger.GetPort()));
    Rcc::Enable(MapPortToPeripheral(config_.echo.GetPort()));
    switch (timer->GetID()) {
        case kTimer1: Rcc::Enable(Peripheral::kTIM1); break;
        case kTimer2: Rcc::Enable(Peripheral::kTIM2); break;
        case kTimer3: Rcc::Enable(Peripheral::kTIM3); break;
        case kTimer4: Rcc::Enable(Peripheral::kTIM4); break;
        case kTimer5: Rcc::Enable(Peripheral::kTIM5); break;
        default: STM32_ASSERT(0, "Invalid Timer ID"); break;
    }
    Gpio::Set(config_.trigger);
    Gpio::Set(config_.echo);
}
void Ultrasonic::Trigger() {
    Gpio::SetPinValue(config_.trigger, DigitalVoltage::kHigh);
    Systick::Delay_us(10);  // 10 microseconds
    Gpio::SetPinValue(config_.trigger, DigitalVoltage::kLow);
}
uint32_t Ultrasonic::MeasureEchoDuration() {
    util::BusyWait<constant::TimeOut::kDefault>([this]()
                    {return Gpio::GetPinValue(config_.echo) == DigitalVoltage::kHigh;});
    if (Gpio::GetPinValue(config_.echo) == DigitalVoltage::kLow) { return 0; }
    auto TimerReg = Timer::GetPtr(timer_->GetID());
    TimerReg->CNT = 0;
    timer_->Cmd(kEnable);
    util::BusyWait<constant::TimeOut::kDefault>([this]()
                    {return Gpio::GetPinValue(config_.echo) == DigitalVoltage::kLow;});
    if (Gpio::GetPinValue(config_.echo) == DigitalVoltage::kHigh) {
        timer_->Cmd(kDisable);
        return 0;
    }
    timer_->Cmd(kDisable);
    return TimerReg->CNT;
}
uint32_t Ultrasonic::GetDistance() {
    Trigger();
    uint32_t duration = MeasureEchoDuration();
    if (duration > 0) {
        float distanceCm = (duration * 0.0343) / 2.0f;  // Convert to cm
        return static_cast<uint32_t>(distanceCm);
    } else { return 0; }
}
