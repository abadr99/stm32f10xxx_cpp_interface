/**
 * @file LKA.cpp
 * @author
 * @brief
* @version 0.1
* @date 2025-04-17
*
* @copyright Copyright (c) 2025
*
*/
#include "utils/Util.h"
#include "mcal/Pin.h"
#include "mcal/Gpio.h"
#include "mcal/Nvic.h"
#include "mcal/Rcc.h"
#include "mcal/Exti.h"
#include "mcal/Systick.h"
#include "mcal/Can.h"
#include "hal/IR.h"
#include "hal/DC_Motor.h"
#include "hal/LKA.h"

using namespace stm32::util;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::mcal::rcc;
using namespace stm32::dev::mcal::nvic;
using namespace stm32::dev::mcal::exti;
using namespace stm32::dev::mcal::systick;
using namespace stm32::dev::mcal::can;
using namespace stm32::dev::hal::dc_motor;
using namespace stm32::dev::hal::ir;
using namespace stm32::dev::app::lka;
LKA* LKA::instance = nullptr;

LKA::LKA(const Pin& leftIrPin, const Pin& rightIrPin
        , const DC_Motor& leftMotor, const DC_Motor& rightMotor)
    :leftIrPin_(leftIrPin), rightIrPin_(rightIrPin),
    leftMotor(leftMotor), rightMotor(rightMotor) {
    EXTI_Config extiIr1 = {leftIrPin.GetPort(), kExti1, kBoth};
    EXTI_Config extiIr2 = {rightIrPin.GetPort(), kExti2, kBoth};
    Exti::SetpCallBackFunction(kExti1, Callback1);
    Exti::SetpCallBackFunction(kExti2, Callback2);
    Exti::Enable(extiIr1);
    Exti::Enable(extiIr2);
    Nvic::EnableInterrupt(kEXTI1_IRQn);
    Nvic::EnableInterrupt(kEXTI2_IRQn);
    LKA::instance = this;
    Systick::Init();
    Systick::Enable(kAHB_Div_8);
}
void CAN_CONFIG() {
    CanConfig conf = {
      .opMode = OperatingMode::kNormal,
      .testMode = TestMode::kNormal,
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
Pin pa12_tx(kPortA, kPin12, PinMode::kAlternativePushPull_2MHz);
Pin pa11_rx(kPortA, kPin11, PinMode::kInputFloat);
Gpio::Set(pa12_tx);
Gpio::Set(pa11_rx);

Can::FilterInit(filterConf);
#define CAN_TX 1
Can::Start();
}
void LKA::Callback1() {
    instance->LkaRightHandler();
}
void LKA::Callback2() {
    instance->LkaLeftHandler();
}

void LKA::LkaRightHandler() {
    if (rightIrPin_.GetIrStatus() == 1) {
        leftMotor.Stop();
        rightMotor.ClockWise();
     } else if (rightIrPin_.GetIrStatus() == 0) {
       leftMotor.ClockWise();
       rightMotor.ClockWise();
     }
//     CanTxMsg txMsg = {
//        .stdId = 0x123,
//        .extId = 0x00,
//        .ide   = IdType::kStId,
//        .rtr   = RemoteTxReqType::kData,
//        .dlc   = 8,
//        .data  = {'R', 'I', 'G', 'H', 'T', '\0'}
//    };
//    Can::Transmit(txMsg);
     Pin pc13(kPortC, kPin13, PinMode::kOutputPushPull_10MHz);
     Gpio::Set(pc13);
     Gpio::SetPinValue(pc13, kHigh);
}
void LKA::LkaLeftHandler() {
     if (leftIrPin_.GetIrStatus() == 1) {
        rightMotor.Stop();
        leftMotor.ClockWise();
     } else if (leftIrPin_.GetIrStatus() == 0) {
       rightMotor.ClockWise();
       leftMotor.ClockWise();
     }
//     CanTxMsg txMsg = {
//        .stdId = 0x123,
//        .extId = 0x00,
//        .ide   = IdType::kStId,
//        .rtr   = RemoteTxReqType::kData,
//        .dlc   = 8,
//        .data  = {'L', 'E', 'F', 'T', '\0'}
//    };
//    Can::Transmit(txMsg);
     Pin pc13(kPortC, kPin13, PinMode::kOutputPushPull_10MHz);
     Gpio::Set(pc13);
     Gpio::SetPinValue(pc13, kLow);
}
