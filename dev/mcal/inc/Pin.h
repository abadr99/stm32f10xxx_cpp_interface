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

namespace stm32 {
namespace dev   {
namespace mcal  {
namespace pin   {

enum class PinMode {
    kInput,
    kOutput,
    kAlternative,
};

enum class InputMode {
    kAnalog     = 0,
    kFloating   = 4,
    kPullup     = 8,
    kPulldown   = 20,
};

enum class OutputMode {
    kPushPull_10MHZ  = 1,
    kPushPull_2MHZ   = 2,
    kPushPull_50MHZ  = 3,
    kOpenDrain_10MHZ = 5,
    kOpenDrain_2MHZ  = 6,
    kOpenDrain_50MHZ = 7,
};

enum class AlternativeMode {
    kPushPull_10MHZ   = 9,
    kPushPull_2MHZ    = 10,
    kPushPull_50MHZ   = 11,
    kOpenDrain_10MHZ  = 13,
    kOpenDrain_2MHZ   = 14,
    kOpenDrain_50MHZ  = 15,
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
    // TODO(@abadr99): Check if we need default ctor in the future
    Pin(Port port, PinNumber pinNumber, PinMode pinMode);
    void SetPort(Port port);
    void SetPinNumber(PinNumber pinNumber);
    void SetPinMode(PinMode pinMode);
    void SetInputMode(InputMode inputMode);
    void SetOutputMode(OutputMode outputMode);
    void SetAlternativeMode(AlternativeMode alternativeMode);
    Port GetPort() const;
    PinNumber GetPinNumber() const;
    PinMode GetPinMode() const;
 private:
    using DataType = stm32::utils::bitset::BitSet<uint8_t>;
    DataType data_;  /** < Holds important class data as following:
                           Bits 0 .. 1: Holds port 
                           Bits 2 .. 5: Holds pin number
                           Bits 6 .. 7: Holds Pin Mode >*/
};

}   // namespace pin
}   // namespace mcal
}   // namespace dev
}   // namespace stm32

#endif // DEV_MCAL_INC_PIN_H_