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
#include "utils/inc/Assert.h"
#include "utils/inc/BitManipulation.h"
#include "mcal/inc/Pin.h"
#include "mcal/inc/Gpio.h"
#include "hal/inc/SevenSegment.h"

using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;          
using namespace stm32::utils::bit_manipulation; 
using namespace stm32::dev::hal::ssd;



/*template<ConnectionType connectionType>
SevenSegment<connectionType>::SevenSegment(const Pin *pDataPins, const Pin enablePin) {   
    // enablePin_(enablePin)
    for (uint8_t pin = 0; pin < 7; pin++) {
        pDataPins_[pin] = pDataPins[pin];
    }
}
*/
template<ConnectionType connectionType>
void SevenSegment<connectionType>::Init() {  
    /* Enable Clock */
   // Gpio::EnablePort(pDataPins_[0]);
   // Gpio::EnablePort(enablePin_);
    /* Set pins as output push pull */
    for (uint8_t pin = 0; pin < 7; pin++) {
        Gpio::SetOutputMode(pDataPins_[pin], OutputMode::kPushPull_2MHZ);
    } 
    Gpio::SetOutputMode(enablePin_, OutputMode::kPushPull_2MHZ);  
    /* if connection type is common anod, then is active low 
       so that pins will set as high mode to make it disable in the beginning */ 
    if (connectionType == kCommon_Anode) {
        for (uint8_t pin = 0; pin < 7; pin++) {
            Gpio::SetPinValue(pDataPins_[pin], State::kHigh);
        }
    }
}

template<ConnectionType connectionType>
void SevenSegment<connectionType>::Enable() {
    Gpio::SetPinValue(enablePin_, static_cast<State>(connectionType));
}

template<ConnectionType connectionType>
void SevenSegment<connectionType>::Disable() {
    Gpio::SetPinValue(enablePin_, static_cast<State>(!connectionType));
}

template<ConnectionType connectionType>
void SevenSegment<connectionType>::SendNumber(SSdDisplay num) {
    STM32_ASSERT(num >= 0 && num <= 9);
    uint8_t pattern = static_cast<uint8_t>(num);
    for (uint8_t i = 0; i < 7; i++) {
        bool mode =(pattern & (1 << (6 - i)));
        Gpio::SetPinValue(pDataPins_[i], static_cast<State>(mode));  
    }
}
template class SevenSegment<kCommon_Anode>;
template class SevenSegment<kCommon_Cathode>;

