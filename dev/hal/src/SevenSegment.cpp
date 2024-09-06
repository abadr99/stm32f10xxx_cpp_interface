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

#include "mcal/inc/stm32f103xx.h"

#include "Types.h"
#include "Assert.h"
#include "BitManipulation.h"
#include "Pin.h"

#include "Rcc.h"
#include "Gpio.h"
#include "SevenSegment.h"

using namespace stm32::util;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;          
using namespace stm32::util; 
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
        Gpio::SetPinValue(dataPins_[pin], HANDLE_INACTIVE_VOLTAGE(connectionType));
    }
}

template<ConnectionType connectionType>
void SevenSegment<connectionType>::Enable() {
    if (isEnablePinUsed_) {
        Gpio::SetPinValue(enablePin_, HANDLE_ACTIVE_VOLTAGE(connectionType));
    }
}

template<ConnectionType connectionType>
void SevenSegment<connectionType>::Disable() {
    if (isEnablePinUsed_) {
        Gpio::SetPinValue(enablePin_, HANDLE_INACTIVE_VOLTAGE(connectionType));
    }
}

template<ConnectionType connectionType>
void SevenSegment<connectionType>::SendNumber(SSdDisplay num) {
    STM32_ASSERT(num >= kZero && num <= kNine);
    auto ConvertSSDtoInt = [&](uint8_t idx) -> Gpio::State {
        return (num & (1 << (6 - idx))) == false ? HANDLE_INACTIVE_VOLTAGE(connectionType) 
                                                 : HANDLE_ACTIVE_VOLTAGE(connectionType);
    };
    for (uint8_t i = 0; i < 7; i++) {
        Gpio::State pinState = ConvertSSDtoInt(i);
        Gpio::SetPinValue(dataPins_[i], pinState);
    }
}

INSTANTIATE_CONNECTION_CLASS(SevenSegment)


