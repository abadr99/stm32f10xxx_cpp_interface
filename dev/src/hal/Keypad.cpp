/**
 * @file Keypad.cpp
 * @brief 
 * @version 0.1
 * @date 2024-04-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdint.h>
#include <cstdlib>
#include "mcal/stm32f103xx.h"
#include "utils/Assert.h"
#include "mcal/Pin.h"
#include "mcal/Gpio.h"
#include "hal/Keypad.h"

using namespace stm32::type;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::hal::keypad;


Keypad::Keypad(uint8_t numRows, uint8_t numCols) {
    rowsNum = numRows;
    colNum = numCols;
    KeypadRow = static_cast<Pin*>(malloc(rowsNum * sizeof(Pin)));
    KeypadCol = static_cast<Pin*>(malloc(colNum * sizeof(Pin)));
}

void Keypad::SetRowArr(Pin* rows) {
    for (uint8_t numRow =0 ; numRow <rowsNum; numRow++) {
        KeypadRow[numRow] = rows[numRow];
    }
}

void Keypad::setColArr(Pin* cols) {
    for (uint8_t numCol =0; numCol <colNum; numCol++) {
        KeypadCol[numCol] = cols[numCol];
    }
}

void Keypad::KeypadInit() {
    for (uint8_t numRow = 0 ; numRow <rowsNum; numRow++) {
        Gpio::SetPinMode(KeypadRow[numRow], PinMode::kInputPullUp);
    }
    for (uint8_t numCol = 0; numCol <colNum; numCol++) {
        STM32_ASSERT(KeypadCol[numCol].IsOutput(), CONFIG_ERROR(_KYBD, _CONFIG));
        Gpio::Set(KeypadCol[numCol]);
        Gpio::SetPinValue(KeypadCol[numCol], DigitalVoltage::kHigh);
    }
}

uint8_t Keypad::GetPressed(uint8_t** keypadButtons) {
    using State = DigitalVoltage;
    uint8_t buttonVal = 0xff;
    for (uint8_t numCol =0; numCol <colNum; numCol++) {
        Gpio::SetPinValue(KeypadCol[numCol], State::kLow);
        for (uint8_t numRow =0 ; numRow <rowsNum; numRow++) {
            if (Gpio::GetPinValue(KeypadRow[numRow]) == State::kLow) {
                buttonVal = keypadButtons[numRow][numCol];
            }
            while (Gpio::GetPinValue(KeypadRow[numRow]) == State::kLow) {
            }
            Gpio::SetPinValue(KeypadCol[numCol], State::kHigh);
            return buttonVal;
        }
        Gpio::SetPinValue(KeypadCol[numCol], State::kHigh);
    }
    return buttonVal;
}

Keypad::~Keypad() {
    free(KeypadRow);
    free(KeypadCol);
}