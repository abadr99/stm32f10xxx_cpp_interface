// /**
//  * @file main.cpp
//  * @author your name (you@domain.com)
//  * @brief 
//  * @version 0.1
//  * @date 2024-07-08
//  * 
//  * @copyright Copyright (c) 2024
//  * 
//  */
// #include "mcal/inc/stm32f103xx.h"

// int main() {
//     while (1) {}
// }

/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */


#include "utils/inc/Types.h"
#include "mcal/inc/stm32f103xx.h"
#include "utils/inc/BitManipulation.h"
#include "mcal/inc/Pin.h"
#include "mcal/inc/Gpio.h"
#include "mcal/inc/Rcc.h"
#include "utils/inc/Logger.h"


using namespace stm32::registers::rcc;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::mcal::rcc;
using namespace stm32::utils::logger;
using namespace stm32::type;

int main() {
    Rcc::InitSysClock();
    Rcc::SetExternalClock(kHseCrystal);
    Rcc::Enable(Peripheral::kIOPC);
    Rcc::Enable(Peripheral::kUSART1);  // Logger Usart

    Logger::Init();
    Pin pc13(kPortC, kPin13, PinMode::kOutputPushPull_10MHz);
    Gpio::Set(pc13);

    uint32_t Local_u16Counter = 0;
    while (1) {
        Gpio::SetPinValue(pc13, kHigh);
        for (Local_u16Counter = 0; Local_u16Counter < 50000; Local_u16Counter++) {
            __asm("NOP");
        }
        Gpio::SetPinValue(pc13, kLow);
        for (Local_u16Counter = 0; Local_u16Counter < 50000; Local_u16Counter++) {
             __asm("NOP");
        }
    }
}
