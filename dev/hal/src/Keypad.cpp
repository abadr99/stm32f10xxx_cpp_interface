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
#include "stm32f103xx.h"
#include "Assert.h"
#include "Util.h"
#include "Rcc.h"
#include "Pin.h"
#include "Gpio.h"
#include "Keypad.h"

using namespace stm32::util;
using namespace stm32::type;
using namespace stm32::dev::mcal::rcc;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::hal::keypad;

Keypad::Keypad(uint8_t numRows, uint8_t numCols) :rowsNum(numRows), colNum(numCols) {
    KeypadRow = static_cast<Pin*>(malloc(rowsNum * sizeof(Pin)));
    KeypadCol = static_cast<Pin*>(malloc(colNum * sizeof(Pin)));
}

void Keypad::SetRowArr(const Pin* rows) {
    for (uint8_t numRow =0 ; numRow <rowsNum; numRow++) {
        KeypadRow[numRow] = rows[numRow];
        Rcc::Enable(MapPortToPeripheral(KeypadRow[numRow].GetPort()));
    }
}

void Keypad::setColArr(const Pin* cols) {
    for (uint8_t numCol =0; numCol <colNum; numCol++) {
        KeypadCol[numCol] = cols[numCol];
        Rcc::Enable(MapPortToPeripheral(KeypadCol[numCol].GetPort()));
    }
}

void Keypad::Init() {
    for (uint8_t numRow = 0 ; numRow <rowsNum; numRow++) {
        Gpio::Set(KeypadRow[numRow]);
    }
    for (uint8_t numCol = 0; numCol <colNum; numCol++) {
        STM32_ASSERT(KeypadCol[numCol].IsOutput());
        Gpio::Set(KeypadCol[numCol]);
        Gpio::SetPinValue(KeypadCol[numCol], DigitalVoltage::kHigh);
    }
}

uint8_t Keypad::GetPressed(const uint8_t* const* keypadButtons) {
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
