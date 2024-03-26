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
using namespace stm32::dev::mcal::pin; // NOLINT[build/namespaces]
using namespace stm32::registers::gpio; // NOLINT[build/namespaces]
namespace stm32 {
namespace dev {
namespace mcal {
namespace gpio {

enum State{
    kLow,
    kHigh,
};


class Gpio{
 public:
/**
 * @brief Set the value of a GPIO pin
 * 
 * @param GPIOx     [GPIOA, GPIOB, GPIOC]
 * @param pinNum    [kpin0 --> kpin15]
 * @param pinState  [klow, khigh]
 */
void SetPinValue(Pin pin, State pinState);
 /**
 * @brief Get the value of a GPIO pin
 * 
 * @param GPIOx     [GPIOA, GPIOB, GPIOC]
 * @param pinNum    [kpin0 --> kpin15]
 * @param ReturnVal Pointer to store the returned value
 */
   // static void GetPinValue(volatile GpioRegDef* GPIOx, Pin pinNum, uint32_t * pPinValue);    // NOLINT
};
}  // namespace gpio
}  // namespace mcal
}  // namespace dev
}  // namespace stm32
#endif  // DEV_MCAL_INC_GPIO_H_
