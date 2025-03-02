/**
 * @file MotorController.hpp
 * @brief Indicator that use with elevators to indicate the current floor
 * @version 0.1
 * @date 2024-12-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include <stdint.h>
#include "utils/Types.h"
#include "mcal/Gpio.h"
#include "hal/Led.h"
#include "hal/Buzzer.h"


class Alarm {
public:
    using Led_t = stm32::dev::hal::led::Led<stm32::type::ConnectionType::kForward_Bias>;
    using Buz_t = stm32::dev::hal::buzzer::Buzzer<stm32::type::ConnectionType::kForward_Bias>;
    Alarm();
    void Run(bool v);
private: 
    Led_t led_;
    Buz_t buz_;
};