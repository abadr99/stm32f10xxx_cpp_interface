/**
 * @file main.cpp
 * @author Mohamed Refat
 * @brief 
 * @version 0.1
 * @date 2024-09-21
 * 
 * @copyright Copyright (c) 2024
 * 
 */

// commit-id: 
#include "mcal/stm32f103xx.h"
#include "utils/Types.h"
#include "utils/BitManipulation.h"
#include "mcal/Pin.h"
#include "mcal/Gpio.h"
#include "mcal/Rcc.h"
#include "mcal/Nvic.h"
#include "mcal/Dma.h"

using namespace stm32::type;
using namespace stm32::registers::rcc;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::mcal::rcc;
using namespace stm32::dev::mcal::nvic;
using namespace stm32::dev::mcal::dma;

volatile uint8_t flag = 0;
void DMA_ISR(void);

int main(void) {
    Rcc::Init();
    Gpio::Init();
    Nvic::Init();
    flag = 0;
    // Initialize system clock and external clock source
    Rcc::InitSysClock();
    Rcc::SetExternalClock(kHseCrystal);
    Rcc::Enable(Peripheral::kIOPC);
    Rcc::Enable(Peripheral::kDMA1);

    Pin pc13(kPortC,  kPin13,  PinMode::kOutputPushPull_10MHz);

    uint32_t src_arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    uint32_t dest_arr[10] = {0};

    DMAConfig conf  =  {
        .channel  =  Channel::kChannel1, 
        .dir  =  Direction::kMem2Mem, 
        .mode = Mode::kNoCircular, 
        .sourceBaseAddr = reinterpret_cast<uint32_t>(src_arr), 
        .destinationBaseAddr = reinterpret_cast<uint32_t>(dest_arr), 
        .bufferSize = 10, 
        .peripheralIncrementState = State::kEnable, 
        .memIncrementState = State::kEnable, 
        .peripheralDataSize = Size::k32bit, 
        .memoryDataSize = Size::k32bit, 
        .channelPriority = Priority::kHigh, 
        .transErrorInterrupt = State::kDisable, 
        .transCompleteInterrupt = State::kEnable, 
    };
    Dma::Init(conf);
    Dma::SetPointerToTransferCompleteISR(Channel::kChannel1, DMA_ISR);
    Dma::Enable(Channel::kChannel1);
    Gpio::Set(pc13);
    Nvic::EnableInterrupt(kDMA1_Channel1_IRQn);
    // Turn off the Led at pc13 pin
    Gpio::SetPinValue(pc13, DigitalVoltage::kHigh);

    while (1) { 
        if (flag  ==  1) {
            if (dest_arr[0]  ==  1 && dest_arr[9]  ==  10) {
                // Turn On The Led
                Gpio::SetPinValue(pc13, DigitalVoltage::kLow);
            }
        }
    }
}

void DMA_ISR(void) {
    flag  =  1;
}
