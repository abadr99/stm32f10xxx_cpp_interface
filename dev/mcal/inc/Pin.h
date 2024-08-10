/**
 * @file Pin.h
 * @brief
 * @version 0.1
 * @date 2024-03-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef DEV_MCAL_INC_PIN_H_
#define DEV_MCAL_INC_PIN_H_
#include "../../utils/inc/BitSet.h"
namespace stm32 {
namespace dev   {
namespace mcal  {
namespace pin   {
    
// NOTE: ORDER MATTERS
enum class PinMode : uint8_t {
    kAnalog,

    kInputFloat,
    kInputPullUp,
    kInputPullDown,
    
    kOutputOpenDrain_2MHz,
    kOutputOpenDrain_10MHz,
    kOutputOpenDrain_50MHz,

    kOutputPushPull_2MHz,
    kOutputPushPull_10MHz,
    kOutputPushPull_50MHz,
    
    kAlternativeOpenDrain_2MHz,
    kAlternativeOpenDrain_10MHz,
    kAlternativeOpenDrain_50MHz,

    kAlternativePushPull_2MHz,
    kAlternativePushPull_10MHz,
    kAlternativePushPull_50MHz,
};

enum PinNumber {
    kPin0, kPin1, kPin2, kPin3, kPin4, kPin5, kPin6, kPin7, kPin8, kPin9,
    kPin10, kPin11, kPin12, kPin13, kPin14, kPin15,
};

enum Port {
    kPortA,
    kPortB,
    kPortC
};

// TODO(@abadr99): Check if we need inheritance
class Pin {
 public:
    Pin() : data_(0) {}
    Pin(Port port, PinNumber pinNumber, PinMode pinMode);
    void SetPort(Port port);
    void SetPinNumber(PinNumber pinNumber);
    void SetPinMode(PinMode pinMode);
    Port GetPort();
    PinNumber GetPinNumber();
    PinMode GetPinMode();
    bool IsInput();
    bool IsOutput();
    bool IsAlternative();
    bool IsAnalog();
 private:
    using DataType = stm32::utils::bitset::BitSet<uint16_t>;
    /**
     * @brief Holds important class data as following:
     *      Bits 0 .. 1: Holds port
     *      Bits 2 .. 5: Holds pin number
     *      Bits 6 .. 9: Holds Pin Mode
     */
    DataType data_;
};

}   // namespace pin
}   // namespace mcal
}   // namespace dev
}   // namespace stm32

#endif   // DEV_MCAL_INC_PIN_H_
