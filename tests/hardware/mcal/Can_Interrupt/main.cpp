/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-08
 * @copyright Copyright (c) 2024
 */
#include "utils/Types.h"
#include "mcal/stm32f103xx.h"
#include "utils/BitManipulation.h"
#include "utils/Util.h"
#include "mcal/Pin.h"
#include "mcal/Gpio.h"
#include "mcal/Rcc.h"
#include "mcal/Can.h"
#include "mcal/Nvic.h"
#include "utils/Logger.h"


using namespace stm32::registers::rcc;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::mcal::rcc;
using namespace stm32::dev::mcal::can;
using namespace stm32::dev::mcal::nvic;
using namespace stm32::utils::logger;
using namespace stm32::util;
using namespace stm32::type;

CanTxMsg txMsg;
CanRxMsg rxMsg;


Pin pc13;

void TxMailboxCompleteCallback() {
    Gpio::SetPinValue(pc13, kHigh);
}


void RxFifo0Callback() {
    Can::Receive(rxMsg, FifoNumber::kFIFO0);
    Gpio::SetPinValue(pc13, kLow);
    Can::Transmit(txMsg, TxMailboxCompleteCallback);
}


void ErrorCallback() {
    for (uint8_t i =0; i < 5; i++) {
        Gpio::SetPinValue(pc13, kHigh);
        BusyWait<100000>([](){ return true; });
        Gpio::SetPinValue(pc13, kLow);
        BusyWait<100000>([](){ return true; });
    }
}


int main() {
    Rcc::Init();
    Gpio::Init();
    Nvic::Init();


    Rcc::InitSysClock();
    Rcc::SetExternalClock(kHseCrystal);
    Rcc::Enable(Peripheral::kCAN);
    Rcc::Enable(Peripheral::kIOPC);

    pc13.SetPort(Port::kPortC);
    pc13.SetPinNumber(PinNumber::kPin13);
    pc13.SetPinMode(PinMode::kOutputPushPull_10MHz);
    Gpio::Set(pc13);

    CanConfig conf = {
       .opMode = OperatingMode::kNormal,
       .testMode = TestMode::kLoopBack,
       .priority = FifoPriority::kID,
       .receivedFifoLock = ReceivedFifo::kUnLocked,
       .baudRatePrescaler = 1,
       .sjw = TimeQuanta::kTq2,
       .bs1 = TimeQuanta::kTq12,
       .bs2 = TimeQuanta::kTq3,
       .TTCM = State::kDisable,
       .ABOM = State::kDisable,
       .AWUM = State::kDisable,
       .NART = State::kDisable,
       .error = CanError::kNoEr
    };
    Can::Init(conf);


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
    Can::FilterInit(filterConf);


    
    // Can::SetCallback(CallbackId::kTxMailbox0Complete, TxMailboxCompleteCallback);
    // Can::SetCallback(CallbackId::kTxMailbox1Complete, TxMailboxCompleteCallback);
    // Can::SetCallback(CallbackId::kTxMailbox2Complete, TxMailboxCompleteCallback);
    Can::SetCallback(CallbackId::kFifo0MessagePending, RxFifo0Callback);
    Can::SetCallback(CallbackId::kError, ErrorCallback);

    // Can::EnableInterrupt(Interrupts::kTxMailBoxEmpty);
    Can::EnableInterrupt(Interrupts::kFifo0MessagePending);
    // Can::EnableInterrupt(Interrupts::kErorrWarning);
    // Can::EnableInterrupt(Interrupts::kErrorPassive);
    // Can::EnableInterrupt(Interrupts::kBusOff);
    // Can::EnableInterrupt(Interrupts::kError);
    
    Nvic::EnableInterrupt(InterruptID::kUSB_LP_CAN1_RX0_IRQn);
    Nvic::EnableInterrupt(InterruptID::kUSB_HP_CAN1_TX_IRQn);
    
    txMsg.stdId = 0x123;
    txMsg.extId = 0;
    txMsg.ide = IdType::kStId;
    txMsg.rtr = RemoteTxReqType::kData;
    txMsg.dlc = 8;
    for (uint8_t i = 0; i < 8; i++) {
        txMsg.data[i] = i;
    }

    Can::Start();

    Can::Transmit(txMsg, TxMailboxCompleteCallback);
    while (1) {
        // for (uint32_t i = 0; i < 100000; i++) {
        //     __asm("NOP");
        // }
        
        // 1-second delay using BusyWait
        // BusyWait<1000000>([](){ return true; });
    }
}
