/**
 * @file main.cpp
 * @author 
 * @brief 
 * @version 0.1
 * @date 2024-02-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "utils/inc/BitManipulation.h"
#include "mcal/inc/stm32f103xx.h"
#include "mcal/inc/Rcc.h"
#include "mcal/inc/Pin.h"
#include "mcal/inc/Gpio.h"
using namespace stm32::utils::bit_manipulation;
using namespace stm32::dev::mcal::rcc;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
int main() {
    Rcc::SetExternalClock(kHseCrystal);
    Rcc::InitSysClock();
    Pin pc13(kPortA,kPin13,PinMode::kOutput);
    Gpio::SetOutputMode(pc13, OutputMode::kPushPull_10MHZ);
    Gpio::SetPinValue(pc13, kLow);
    // uint16_t Local_u16Counter;
    while (1) {
        // Gpio::SetPinValue(pc13, kLow);
    	// for(Local_u16Counter = 0 ; Local_u16Counter < 50000 ; Local_u16Counter++)
		// {
		// 	__asm("NOP");
		// }
        // Gpio::SetPinValue(pc13, kLow);
    	// 	for(Local_u16Counter = 0 ; Local_u16Counter < 50000 ; Local_u16Counter++)
		// {
		// 	__asm("NOP");
		// }
    }
}
