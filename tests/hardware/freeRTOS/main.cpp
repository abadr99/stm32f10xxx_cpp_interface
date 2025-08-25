/**
 * @file main.cpp
 * @author Mohamed Refat
 * @brief 
 * @version 0.1
 * @date 2024-07-08
 * @copyright Copyright (c) 2024
 */

// commit-id:
#include "utils/Types.h"
#include "mcal/stm32f103xx.h"
#include "utils/BitManipulation.h"
#include "mcal/Pin.h"
#include "mcal/Gpio.h"
#include "mcal/Rcc.h"

#include "freeRTOS/FreeRTOS.h"
#include "freeRTOS/task.h"


using namespace stm32::registers::rcc;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::mcal::rcc;
using namespace stm32::type;

void T1_Handler(void* pvParameters);

int main() {
    TaskHandle_t T1Handle = NULL;
    BaseType_t  xReturned;
    Rcc::Init();
    Gpio::Init();

    Rcc::Enable(Peripheral::kIOPC);
    
    Rcc::InitSysClock();
    Rcc::SetExternalClock(kHseCrystal);

    xReturned = xTaskCreate(T1_Handler, "Task1", 128, NULL, 0, &T1Handle);
    if (xReturned != pdPASS) {
        return 0;
    }

    /* Start the scheduler. */
    vTaskStartScheduler();
    while (1) {}
}

void T1_Handler(void* pvParameters) {
    (void)pvParameters;  //  Avoids unused variable warning
    Pin pc13(kPortC, kPin13, PinMode::kOutputPushPull_10MHz);
    Gpio::Set(pc13);
    uint8_t toggleFlag = 1;
    for (;;) {
        if (toggleFlag) {
            Gpio::SetPinValue(pc13, kLow);
            toggleFlag = 0;
        } else {
            Gpio::SetPinValue(pc13, kHigh);
            toggleFlag = 1;
        }
        vTaskDelay(pdMS_TO_TICKS(500));  // Task delay for 500ms
    }
}
