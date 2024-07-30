/**
 * @file main.cpp
 * @author Mohamed Refat
 * @brief 
 * @version 0.1
 * @date 2024-07-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "mcal/inc/stm32f103xx.h"
#include "utils/inc/BitManipulation.h"
#include "utils/inc/Types.h"
#include "mcal/inc/Pin.h"
#include "mcal/inc/Gpio.h"
#include "mcal/inc/Rcc.h"
#include "mcal/inc/Nvic.h"
#include "mcal/inc/EXTI.h"
#include "mcal/inc/Systick.h"


using namespace stm32::registers::rcc;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::mcal::rcc;
using namespace stm32::dev::mcal::nvic;
using namespace stm32::dev::mcal::exti;
using namespace stm32::dev::mcal::systick;

volatile uint8_t flag = 0;
void EXTI1_ISR(void);

int main(void)
{
    // Initialize system clock and external clock source
    Rcc::InitSysClock();
    Rcc::SetExternalClock(kHseCrystal);

    // Enable GPIO port C and configure pin PC13 as an output
    Gpio::EnablePort(kPortC);
    Pin pc13(kPortC, kPin13, PinMode::kOutput);
    Gpio::SetOutputMode(pc13, OutputMode::kPushPull_10MHZ);
    // Turn of the Led at pc13 pin
    Gpio::SetPinValue(pc13, kHigh);

    // Configure external interrupt on EXTI1, set callback function, and enable interrupt
    EXTI_Config EXTI1_Config = {kPortA, Line::kEXTI1, Trigger::kBoth};
    Exti::SetpCallBackFunction(Line::kEXTI1, EXTI1_ISR);
    Exti::Enable(EXTI1_Config);

    Nvic::EnableInterrupt(kEXTI1_IRQn);
    Nvic::SetPendingFlag(kEXTI1_IRQn);

    // Enter an infinite loop to toggle the GPIO pin based on the interrupt flag
    while (1) { 
        if (flag == 1) {
            // Turn on the LED
            Gpio::SetPinValue(pc13, kLow);
        } else {
            Gpio::SetPinValue(pc13, kHigh);
        }
    }
}

void EXTI1_ISR(void) {
    flag = 1;
}
