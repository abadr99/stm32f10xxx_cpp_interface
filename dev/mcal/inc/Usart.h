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

#define USART_TIMEOUT (500)

namespace stm32 {
namespace registers { namespace usart { struct UsartRegDef; } }
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
    UsartMode mode;
    StopBitsNum numOfSB;
    WordLength dataBits;
    ParityMode parityMode;
    HwFlowControl flowControlState;
    uint32_t baudRate;  // clock peripheral is 8MHZ considering that system clock is HSI
};
template<uint32_t USART_ADDRESS>
class Usart {
    #ifndef UNIT_TEST
    static_assert(USART_ADDRESS == USART1 || 
                  USART_ADDRESS == USART2 || 
                  USART_ADDRESS == USART3, 
                  "Invalid USART");
    #endif  // UNIT_TEST
 public:
    using DataValType = uint16_t;
    explicit Usart(const UsartConfig& config);
    void EnableClk();
    void Init();
    void Transmit(DataValType dataValue);
    DataValType Receive();
    ErrorType RetErrorDetection();
 private:
    enum Flag : uint8_t {kEnabled, kDisabled};
    void _SetBaudRate();
    const UsartConfig& config_;
};

}  // namespace usart
}  // namespace mcal
}  // namespace dev
}  // namespace stm32 // namespace stm32

#endif  //  DEV_MCAL_INC_USART_H_