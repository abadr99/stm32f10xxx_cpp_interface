/**
 * @file Usart.h
 * @brief
 * @version 0.1
 * @date 2024-06-24
 *
 * @copyright Copyright (c) 2024
 *  
 */
#ifndef DEV_INC_MCAL_USART_H_
#define DEV_INC_MCAL_USART_H_

#include "mcal/stm32f103xx.h"

namespace stm32 {
namespace dev {
namespace mcal {
namespace usart {

enum UsartNum : uint8_t {
    kUsart1,
    kUsart2,
    kUsart3,
};

enum UsartMode : uint8_t {
    kRx = 0b01,
    kTx,
    kRxTx,
};

enum StopBitsNum : uint8_t {
    kSb_1_,
    kSb_0_5_,
    kSb_2_,
    kSb_1_5_,
};

enum WordLength : uint8_t {
    kDataBits_8_,
    kDataBits_9_,
};

enum ParityMode : uint8_t {
    kNo_Parity   = 0b00,
    kEven_Parity = 0b01,
    kOdd_Parity  = 0b11,
};

enum HwFlowControl : uint8_t {
    kNone,
    kRTS,
    kCTS,
    kRTS_CTS,      
};

enum ErrorType : uint8_t {
    kParityError,
    kFrameError,
    kNoiseError,
    kOverRunError,
    kSuccess,
};

struct UsartConfig {
    UsartNum number;
    UsartMode mode;
    StopBitsNum numOfSB;
    WordLength dataBits;
    ParityMode parityMode;
    HwFlowControl flowControlState;
    uint32_t baudRate;  // clock peripheral is 8MHZ considering that system clock is HSI
};

class Usart {
 public:
    using DataValType = uint16_t;
    using pFunction = stm32::type::pFunction;
    explicit Usart(const UsartConfig& config);
    void Init();
    void Transmit(DataValType dataValue);
    void Transmit(DataValType dataValue, pFunction pISR);
    DataValType Receive();
    void Receive(DataValType *pData, pFunction pISR);
    ErrorType RetErrorDetection();
    UsartNum GetUsartNum();
    static pFunction Helper_GetTransmitCompleteISR(UsartNum number);
    static pFunction Helper_GetReceiveReadyISR(UsartNum number);
    static void Helper_SetReceivedData(UsartNum number, DataValType data);

 private:
    enum Flag : uint8_t {kDisabled, kEnabled};
    const UsartConfig& config_;
    volatile stm32::registers::usart::UsartRegDef* usartReg;
    static volatile DataValType *pReceivedData_[3];
    static pFunction pTransmitCompleteFun_[3];
    static pFunction pReceiveReadyFun_[3];
    void _SetBaudRate();
    static void SetTransmitCompleteISR(UsartNum number, pFunction pISR);
    static void SetReceiveReadyISR(UsartNum number, pFunction pISR);
};

}  // namespace usart
}  // namespace mcal
}  // namespace dev
}  // namespace stm32 // namespace stm32

#endif  //  DEV_INC_MCAL_USART_H_
