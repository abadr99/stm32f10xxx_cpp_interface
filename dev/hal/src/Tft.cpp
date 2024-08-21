/**
 * @file Tft.cpp
 * @author noura36
 * @brief
 * @version 0.1
 * @date 2024-08-21
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "Spi.h"
#include "Systick.h"
#include "Gpio.h"
#include "Pin.h"
#include "Tft.h"

void Tft::SendCommand(uint8_t command) {
    Gpio::SetPinValue(A0, kLow);
    Spi::Write(command);
}
