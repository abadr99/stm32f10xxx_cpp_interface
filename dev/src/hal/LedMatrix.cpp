/**
 * @file LedMatrix.cpp
 * @brief 
 * @version 0.1
 * @date 2024-07-7
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <stdlib.h>
#include "mcal/stm32f103xx.h"
#include "utils/Assert.h"
#include "utils/BitManipulation.h"
#include "utils/Font.h"
#include "mcal/Pin.h"
#include "mcal/Gpio.h"
#include "mcal/Systick.h"
#include "hal/LedMatrix.h"

using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio; 
using namespace stm32::utils::bit_manipulation;   
using namespace stm32::dev::mcal::systick;       
using namespace stm32::utils::font;
using namespace stm32::dev::hal::ledMatrix;

#define ACTIVE_VOLT_STATE(connectionType)    (connectionType == kCommon_Row_Anode ? kHigh : kLow)  
#define DEACTIVE_VOLT_STATE(connectionType)  (connectionType == kCommon_Row_Anode ? kLow  : kHigh) 

template <ConnectionType connectionType>
LedMatrix<connectionType>::LedMatrix(const Array_t rowPins, const Array_t colPins) 
    : rowPins_(rowPins) , colPins_(colPins) {} 

template <ConnectionType connectionType>
void LedMatrix<connectionType>::Init() {
    // SET [ROW & COL] PINS AC OUTPUT [PUSHPULL]
    for (uint8_t pin = 0; pin < 8; pin++) { PinMode GetPinMode();
        STM32_ASSERT((rowPins_[pin].GetPinMode() >= PinMode::kOutputPushPull_10MHz) &&
                     (rowPins_[pin].GetPinMode() <= PinMode::kOutputPushPull_50MHz));

        STM32_ASSERT((colPins_[pin].GetPinMode() >= PinMode::kOutputPushPull_10MHz) &&
                     (colPins_[pin].GetPinMode() <= PinMode::kOutputPushPull_50MHz));
        Gpio::Set(rowPins_[pin]);
        Gpio::Set(colPins_[pin]);
    }

    // SET THE INITIAL STATE OF THE LEDS
    for (uint8_t pin = 0; pin < 8; pin++) {
        Gpio::SetPinValue(rowPins_[pin], DEACTIVE_VOLT_STATE(connectionType));
        Gpio::SetPinValue(colPins_[pin], ACTIVE_VOLT_STATE(connectionType));
    }
}

template <ConnectionType connectionType>
void LedMatrix<connectionType>::DrawChar(uint8_t character) {
    Font::Array_t charData = font_.GetCharData(character);
    for (uint8_t row = 0; row < Font::charHight; row++) {
        // ACTIVATE THE CURRENT ROW 
        Gpio::SetPinValue(rowPins_[row], ACTIVE_VOLT_STATE(connectionType));
        
        // SET COL STATE
        for (uint8_t col = 0; col < Font::charWidth; col++) {        
            if (ExtractBits<uint8_t>(charData[row], col)) {
                Gpio::SetPinValue(colPins_[col], DEACTIVE_VOLT_STATE(connectionType));
            } else {
                Gpio::SetPinValue(colPins_[col], ACTIVE_VOLT_STATE(connectionType));
            }
        }

        // DELAY TO ALLOW THE ROW TO BE VISIBLE
        Systick::Delay_ms(1);

        // DEACTIVATE THE CURRENT ROW 
        Gpio::SetPinValue(rowPins_[row], DEACTIVE_VOLT_STATE(connectionType));
    }
}

template <ConnectionType connectionType>
void  LedMatrix<connectionType>::ClearDisblay() {
    for (uint8_t pin = 0; pin < 8; pin++) {
        Gpio::SetPinValue(rowPins_[pin], DEACTIVE_VOLT_STATE(connectionType));
        Gpio::SetPinValue(colPins_[pin], ACTIVE_VOLT_STATE(connectionType));
    }
}

template class LedMatrix<kCommon_Row_Anode>;
template class LedMatrix<kCommon_Row_Cathode>;
