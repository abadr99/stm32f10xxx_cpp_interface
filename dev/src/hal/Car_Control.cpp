/**
 * @file Car_Control.cpp
 * @brief
 * @version 0.1
 * @date 2025-02-07
 * 
 * Copyright Copyright (c) 2025
 */
#include "hal/DC_Motor.h"
#include "hal/HC05.h"
#include "hal/Car_Control.h"

using namespace stm32::dev::hal::dc_motor;
using namespace stm32::dev::hal::bluetooth;
using namespace stm32::dev::app::car_control;

Car_Control::Car_Control(const DC_Motor& leftMotor, const DC_Motor& rightMotor, const HC05& bt) 
                : leftMotor(leftMotor), rightMotor(rightMotor), bt(bt) {}
void Car_Control::ProcessCommand() {
    char command = static_cast<char>(bt.Receive());
    if (command == 'F') {
         // Forward
         leftMotor.ClockWise();
         rightMotor.ClockWise();
    } else if (command == 'B') {
         // Forward
         leftMotor.AntiClockWise();
         rightMotor.AntiClockWise();
    } else if (command == 'R') {
         // Right
         leftMotor.ClockWise();
         rightMotor.Stop();
    } else if (command == 'L') {
         // Left
         leftMotor.Stop();
         rightMotor.ClockWise();
    } else {
         // Stop
         leftMotor.Stop();
         rightMotor.Stop();
    }
}
