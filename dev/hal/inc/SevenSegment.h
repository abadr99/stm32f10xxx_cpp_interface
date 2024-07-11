/**
 * @file SevenSegment.h
 * @author
 * @brief
 * @version 0.1
 * @date 2024-07-7
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef DEV_HAL_INC_SEVENSEGMENT_H_
#define DEV_HAL_INC_SEVENSEGMENT_H_
#include "../../mcal/inc/Pin.h"
using namespace stm32::dev::mcal::pin;
namespace stm32 {
namespace dev {
namespace hal {
namespace ssd {

enum ConnectionType : uint8_t {
    kCommon_Cathode,
    kCommon_Anode,
};
enum  SSdDisplay: uint8_t 
{
    ZERO  = 0x3F,
    ONE   = 0x06,
    TWO   = 0x5B,
    THREE = 0x4F,
    FOUR  = 0x66,
    FIVE  = 0x6D,
    SIX   = 0x7D,
    SEVEN = 0x07,
    EIGHT = 0x7F,
    NINE  = 0x6F
};
/**
*   Note: data pins must are on the same port or port of enable pin 
*         otherwise, you must enable clk of port by yourself to work successfuly
*/ 
template<ConnectionType connectionType>
class SevenSegment {
 public:
    SevenSegment(const Pin *pDataPins, const Pin enablePin);  
    void Init();
    void Enable();
    void Disable();
    void SendNumber(SSdDisplay num);
 private:
    Pin enablePin_;
    Pin pDataPins_[7];
};
}  // namespace ssd
}  // namespace hal
}  // namespace dev
}  // namespace stm32
#endif  // DEV_HAL_INC_SEVENSEGMENT_H_
