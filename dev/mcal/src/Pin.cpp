/**
 * @file Pin.cpp
 * @brief 
 * @version 0.1
 * @date 2024-03-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdint.h>
#include "mcal/inc/stm32f103xx.h"
#include "utils/inc/BitSet.h"
#include "utils/inc/Assert.h"
#include "mcal/inc/Pin.h"

using  namespace stm32::dev::mcal::pin;
using  namespace stm32::registers::gpio;
using  namespace stm32::utils::bitset;
void Pin::SetPort(Port port)
{
    data_.SetValue<0,1>(port);
}
void Pin::SetPinNumber(PinNumber pinNumber)
{
    data_.SetValue<2,5>(pinNumber);
}
void Pin::SetPinMode(PinMode pinMode)
{
    data_.SetValue<6,7>(static_cast<uint8_t>(pinMode));
}


void Pin::SetInputMode(InputMode inputMode)
{
    STM32_ASSERT( data_[6] == static_cast<uint8_t>(PinMode::kInput));
    Helper_SetInputMode(inputMode);
}
void Pin::SetOutputMode(OutputMode outputMode)
{

}
void Pin::SetAlternativeMode(AlternativeMode alternativeMode)
{
    
}


Port Pin::GetPort()
{
    return static_cast<Port>(data_[0]);
}
PinNumber Pin::GetPinNumber()
{
    return static_cast<PinNumber>(data_[2]);
}
PinMode Pin::GetPinMode()
{
    return static_cast<PinMode>(data_[6]);

}


void Pin::Helper_SetInputMode(InputMode inputMode)
{
    if ( data_[2] <= static_cast<uint8_t>(PinNumber::kPin7))
    {
        switch (data_[0])
        {
            case Port::kPortA: {
                GPIOA->CRL &= (0b1111 << data_[2]*4);  //Clear bits before modify it
                GPIOA->CRL &= (static_cast<uint8_t>(inputMode) << data_[2]*4);
                break;
            }

            case Port::kPortB: {
                GPIOB->CRL &= (0b1111 << data_[2]*4);  //Clear bits before modify it
                GPIOB->CRL &= (static_cast<uint8_t>(inputMode) << data_[2]*4);
                break;
            }

            case Port::kPortC: {
                GPIOC->CRL &= (0b1111 << data_[2]*4);  //Clear bits before modify it
                GPIOC->CRL &= (static_cast<uint8_t>(inputMode) << data_[2]*4);
                break;
            }
        }
    }else if ( data_[2] <= static_cast<uint8_t>(PinNumber::kPin15))
    {
        switch (data_[0])
        {
            case Port::kPortA: {
                GPIOA->CRH &= (0b1111 << data_[2]*4);  //Clear bits before modify it
                GPIOA->CRH &= (static_cast<uint8_t>(inputMode) << data_[2]*4);
                break;
            }

            case Port::kPortB: {
                GPIOB->CRH &= (0b1111 << data_[2]*4);  //Clear bits before modify it
                GPIOB->CRH &= (static_cast<uint8_t>(inputMode) << data_[2]*4);
                break;
            }

            case Port::kPortC: {
                GPIOC->CRH &= (0b1111 << data_[2]*4);  //Clear bits before modify it
                GPIOC->CRH &= (static_cast<uint8_t>(inputMode) << data_[2]*4);
                break;
            }
        }
    }

}