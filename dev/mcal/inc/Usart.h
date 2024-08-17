/**
 * @file Usart.h
 * @brief
 * @version 0.1
 * @date 2024-06-24
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef DEV_MCAL_INC_USART_H_
#define DEV_MCAL_INC_USART_H_

#include "../../mcal/inc/stm32f103xx.h"
using namespace stm32::registers::usart;

#define USART_TIMEOUT (2000)

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
    explicit Usart(const UsartConfig& config);
    void EnableClk();
    void Init();
    void Transmit(DataValType dataValue);
    DataValType Receive();
    ErrorType RetErrorDetection();
 private:
    enum Flag : uint8_t {kDisabled, kEnabled};
    void _SetBaudRate();
    const UsartConfig& config_;
    volatile UsartRegDef* usartReg;
};

}  // namespace usart
}  // namespace mcal
}  // namespace dev
}  // namespace stm32 // namespace stm32

#endif  //  DEV_MCAL_INC_USART_H_
