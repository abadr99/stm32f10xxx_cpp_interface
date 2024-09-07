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

#include "Pin.h"
#include "Array.h"

using namespace stm32::dev::mcal::pin;

namespace stm32 {
namespace dev {
namespace hal {
namespace ssd {

enum SSdDisplay: uint8_t {
    kZero  = 0x3F,
    kOne   = 0x06,
    kTwo   = 0x5B,
    kThree = 0x4F,
    kFour  = 0x66,
    kFive  = 0x6D,
    kSix   = 0x7D,
    kSeven = 0x07,
    kEight = 0x7F,
    kNine  = 0x6F,
};

// NOTE: DATA PINS AND ENABLE PIN SHOULD BE CONNECTED TO THE SAME PORT, 
//       OTHERWISE ENABLE DIFFERENT PORT'S CLOCK BY YOURSELF.  
template<stm32::type::ConnectionType connectionType>
class SevenSegment {
 public:
    using Array_t = stm32::util::Array<Pin, 7>;
    SevenSegment(const Array_t dataPins, const Pin enablePin);  
    explicit SevenSegment(const Array_t dataPins);  
    void Init();
    void Enable();
    void Disable();
    void SendNumber(SSdDisplay num);

 private:
    Array_t dataPins_;
    Pin     enablePin_;
    bool    isEnablePinUsed_;
};
}  // namespace ssd
}  // namespace hal
}  // namespace dev
}  // namespace stm32
#endif  // DEV_HAL_INC_SEVENSEGMENT_H_
