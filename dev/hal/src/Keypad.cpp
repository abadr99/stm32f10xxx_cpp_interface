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
#include "mcal/inc/stm32f103xx.h"
#include "mcal/inc/Pin.h"
#include "mcal/inc/Gpio.h"
#include "hal/inc/Keypad.h"

using  namespace stm32::dev::mcal::pin;
using  namespace stm32::dev::mcal::gpio;
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
    for (uint8_t numRow =0 ; numRow <rowsNum; numRow++) {
        Gpio::SetInputMode(KeypadRow[numRow], InputMode::kPullup);
    }
    for (uint8_t numCol =0; numCol <colNum; numCol++) {
        Gpio::SetOutputMode(KeypadCol[numCol], OutputMode::kPushPull_2MHZ);
        Gpio::SetPinValue(KeypadCol[numCol], State::kHigh);
    }
}

uint8_t Keypad::GetPressed(uint8_t** keypadButtons) {
    uint8_t buttonVal = 0xff;
    for (uint8_t numCol =0; numCol <colNum; numCol++) {
        Gpio::SetPinValue(KeypadCol[numCol], kLow);
        for (uint8_t numRow =0 ; numRow <rowsNum; numRow++) {
            if (Gpio::GetPinValue(KeypadRow[numRow]) == kLow) {
                buttonVal = keypadButtons[numRow][numCol];
            }
            while (Gpio::GetPinValue(KeypadRow[numRow]) == kLow) {
            }
            Gpio::SetPinValue(KeypadCol[numCol], kHigh);
            return buttonVal;
        }
        Gpio::SetPinValue(KeypadCol[numCol], kHigh);
    }
    return buttonVal;
}
Keypad::~Keypad() {
    free(KeypadRow);
    free(KeypadCol);
}
