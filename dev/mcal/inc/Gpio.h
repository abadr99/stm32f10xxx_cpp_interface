/**
 * @file Gpio.h
 * @author
 * @brief
 * @version 0.1
 * @date 2024-03-16
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef DEV_MCAL_INC_GPIO_H_
#define DEV_MCAL_INC_GPIO_H_

namespace stm32 {
namespace dev {
namespace mcal {
namespace gpio {

enum State{
    kLow,
    kHigh,
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
class Gpio{
 public:
    using Pin = stm32::dev::mcal::pin::Pin;
    using Port = stm32::dev::mcal::pin::Port;

    static void SetPinValue(Pin pin, State pinState);
    static uint32_t  GetPinValue(Pin pin);
    static void SetInputMode(Pin pin, InputMode inputMode);
    static void SetOutputMode(Pin pin, OutputMode outputMode);
    static void SetAlternativeMode(Pin pin, AlternativeMode alternativeMode);
 private:
    static void Helper_SetInputMode(Pin pin, InputMode inputMode);
    static void Helper_SetOutputMode(Pin pin, OutputMode outputMode);
    static void Helper_AlternateMode(Pin pin, AlternativeMode alternateMode);
};
}  // namespace gpio
}  // namespace mcal
}  // namespace dev
}  // namespace stm32
#endif  // DEV_MCAL_INC_GPIO_H_
