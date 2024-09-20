/**
 * @file SevenSegment.cpp
 * @brief 
 * @version 0.1
 * @date 2024-07-7
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <stdlib.h>

#include "mcal/stm32f103xx.h"

#include "utils/Types.h"
#include "utils/Define.h"
#include "utils/Constant.h"
#include "utils/Assert.h"
#include "utils/BitManipulation.h"
#include "mcal/Pin.h"

#include "mcal/Rcc.h"
#include "mcal/Gpio.h"
#include "hal/SevenSegment.h"

using namespace stm32;
using namespace stm32::type;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;           
using namespace stm32::dev::hal::ssd;


template<ConnectionType connectionType>
SevenSegment<connectionType>::SevenSegment(const Array_t dataPins, const Pin enablePin)   
    : dataPins_(dataPins)
    , enablePin_(enablePin)
    , isEnablePinUsed_(true)
    { /* EMPTY */ }

template<ConnectionType connectionType>
SevenSegment<connectionType>::SevenSegment(const Array_t dataPins)   
    : dataPins_(dataPins)
    , isEnablePinUsed_(false)
    { /* EMPTY */ }

template<ConnectionType connectionType>
void SevenSegment<connectionType>::Init() {
    using namespace stm32::dev::mcal::rcc;
    auto MapToPeripheral = [](Port port) -> Peripheral {
        switch (port) {
            case kPortA:    return Peripheral::kIOPA;
            case kPortB:    return Peripheral::kIOPB;
            case kPortC:    return Peripheral::kIOPC;
        }
        STM32_ASSERT(1);
        return Peripheral::kUnknown;
    };
    // 1] -- ENABLE CLK PORT
    Rcc::Enable(MapToPeripheral(dataPins_[0].GetPort()));

    // 2] -- SET DATA PINS AS OUTPUT (PUSHPULL)
    for (uint8_t pin = 0; pin < 7; pin++) {
        Gpio::Set(dataPins_[pin]);
    }

    // 3] -- HANDLE ENABLE PIN IF USED
    if (isEnablePinUsed_) {
        Rcc::Enable(MapToPeripheral(enablePin_.GetPort()));
        Gpio::Set(enablePin_);  
    }
    
    // 4] -- SET INITIAL STATE OF THE LEDS
    for (uint8_t pin = 0; pin < 7; pin++) {
        Gpio::SetPinValue(dataPins_[pin], constant::DigitalState<connectionType>::kInActiveVoltage);    // NOLINT [whitespace/line_length] 
    }
}

template<ConnectionType connectionType>
void SevenSegment<connectionType>::Enable() {
    if (isEnablePinUsed_) {
        Gpio::SetPinValue(enablePin_, constant::DigitalState<connectionType>::kActiveVoltage);
    }
}

template<ConnectionType connectionType>
void SevenSegment<connectionType>::Disable() {
    if (isEnablePinUsed_) {
        Gpio::SetPinValue(enablePin_, constant::DigitalState<connectionType>::kInActiveVoltage);    
    }
}

template<ConnectionType connectionType>
void SevenSegment<connectionType>::SendNumber(SSdDisplay num) {
    STM32_ASSERT(num >= kZero && num <= kNine);
    auto ConvertSSDtoInt = [&](uint8_t idx) -> DigitalVoltage {
        return (num & (1 << (6 - idx))) == false ? constant::DigitalState<connectionType>::kInActiveVoltage  // NOLINT [whitespace/line_length] 
                                                 : constant::DigitalState<connectionType>::kActiveVoltage;   // NOLINT [whitespace/line_length] 
    };
    for (uint8_t i = 0; i < 7; i++) {
        DigitalVoltage pinState = ConvertSSDtoInt(i);
        Gpio::SetPinValue(dataPins_[i], pinState);
    }
}

INSTANTIATE_CONNECTION_CLASS(SevenSegment)


