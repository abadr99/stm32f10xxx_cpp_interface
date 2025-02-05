/**
 * @file main.cpp
 * @author Mohamed Refat
 * @brief 
 * @version 0.1
 * @date 2025-02-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */
// commit-id:

#include "utils/Types.h"
#include "mcal/stm32f103xx.h"
#include "utils/BitManipulation.h"
#include "mcal/Pin.h"
#include "mcal/Gpio.h"
#include "mcal/Rcc.h"
#include "mcal/Can.h"

using namespace stm32::type;
using namespace stm32::registers::rcc;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::mcal::rcc;
using namespace stm32::dev::mcal::can;
int main() {
    Rcc::Init();
    Gpio::Init();
    
    Rcc::InitSysClock();
    Rcc::SetExternalClock(kHseCrystal);
    Rcc::Enable(Peripheral::kIOPC);
    Rcc::Enable(Peripheral::kCAN);

    CanConfig conf = { 
        .opMode = OperatingMode::kNormal,
        .testMode = TestMode::kCombined,
        .priority = FifoPriority::kID,
        .receivedFifoLock = ReceivedFifo::kUnLocked,
        .baudRatePrescaler = 1,
        .sjw = TimeQuanta::kTq2,
        .bs1 = TimeQuanta::kTq12,
        .bs2 = TimeQuanta::kTq3,
        .TTCM = State::kDisable,
        .ABOM = State::kDisable,
        .AWUM = State::kDisable,
        .NART = State::kDisable
    };

    Can::Init(conf);

    CanTxMsg txMsg = {
        .stdId = 0xAA,
        .extId = 0x00,
        .ide   = IdType::kStId,
        .rtr   = RemoteTxReqType::kData,
        .dlc   = 8,
        .data  = {'E', 'D', 'F', 'B', 'M', 'E', 'C', '\0'}
    };

    CanRxMsg rxMsg;

    FilterConfig filterConf = {
        .idHigh     = 0x0000,
        .idLow      = 0x0000,
        .maskIdHigh = 0x0000,
        .maskIdLow  = 0x0000,
        .fifoAssign = FifoNumber::kFIFO0,
        .bank       = 0,
        .mode       = FilterMode::kMask,
        .scale      = FilterScale::k32bit,
        .activation = State::kEnable
    };

    Pin pc13(kPortC, kPin13, PinMode::kOutputPushPull_10MHz);
    Gpio::Set(pc13);

    Can::FilterInit(filterConf);

    Can::Transmit(txMsg);
    
    while (1) {
        Can::Receive(rxMsg, FifoNumber::kFIFO0);
        if (txMsg.data[0] == 'E') {
            Gpio::SetPinValue(pc13, kLow);
        } else {
            Gpio::SetPinValue(pc13, kHigh);
        }
    }
}
