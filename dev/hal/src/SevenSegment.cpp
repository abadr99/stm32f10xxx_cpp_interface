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
#include "../../mcal/inc/Gpio.h"
#include "utils/inc/Assert.h"
#include "../inc/SevenSegment.h"


using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::hal::ssd;

#define SSD_NUMBERS {\
    {1, 1, 1, 1, 1, 1, 0, 0}, /* 0 */ \ 
    {0, 1, 1, 0, 0, 0, 0, 0}, /* 1 */ \ 
    {1, 1, 0, 1, 1, 0, 1, 0}, /* 2 */ \ 
    {1, 1, 1, 1, 0, 0, 1, 0}, /* 3 */ \ 
    {0, 1, 1, 0, 0, 1, 1, 0}, /* 4 */ \ 
    {1, 0, 1, 1, 0, 1, 1, 0}, /* 5 */ \ 
    {1, 0, 1, 1, 1, 1, 1, 0}, /* 6 */ \ 
    {1, 1, 1, 0, 0, 0, 0, 0}, /* 7 */ \ 
    {1, 1, 1, 1, 1, 1, 1, 0}, /* 8 */ \ 
    {1, 1, 1, 1, 0, 1, 1, 0}  /* 9 */ \ 
}

volatile uint8_t ssdNumbers[10][8] = SSD_NUMBERS;

template<ConnectionType connectionType>
SevenSegment<connectionType>::SevenSegment(const Pin *pDataPins, Pin enablePin)
    : enablePin_(enablePin) {
    pDataPins_ = reinterpret_cast<Pin*>(malloc(7 * sizeof(Pin)));
    for (uint8_t pin = 0; pin < 7; pin++) {
        pDataPins_[pin] = pDataPins[pin];
    }
}

template<ConnectionType connectionType>
void SevenSegment<connectionType>::Init() {  
    /* Enable Clock */
    Gpio::EnablePort(pDataPins_[0]);
    Gpio::EnablePort(enablePin_);
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
void SevenSegment<connectionType>::SendNumber(uint8_t num) {
    STM32_ASSERT(num >= 0 && num <= 9);
    for (uint8_t pin = 0; pin < 7; pin++) {
        uint8_t mode = ssdNumbers[num][pin] ^ connectionType;
        Gpio::SetPinValue(pDataPins_[pin], static_cast<State>(mode));  
    }
}
template class stm32::dev::hal::ssd::SevenSegment<kCommon_Anode>;
template class stm32::dev::hal::ssd::SevenSegment<kCommon_Cathode>;
