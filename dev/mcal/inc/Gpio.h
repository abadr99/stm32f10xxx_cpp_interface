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
using namespace stm32::registers::gpio; // NOLINT[build/namespaces]
namespace stm32 {
namespace dev {
namespace mcal {
namespace gpio {

enum State{
    kLow,
    kHigh,
};

enum Mode{
    kIN_analog = 0,
    kIN_floating = 4,
    kIN_pullup = 8,
    kIN_pulldown = 20,
    kOP_pushpull_10MHZ = 1,
    kOP_pushpull_2MHZ = 2,
    kOP_pushpull_50MHZ = 3,
    kOP_opendrain_10MHZ = 5,
    kOP_opendrain_2MHZ = 6,
    kOP_opendrain_50MHZ = 7,
    kaf_pushpull_10MHZ = 9,
    kaf_pushpull_2MHZ = 10,
    kaf_pushpull_50MHZ = 11,
    kaf_opendrain_10MHZ = 13,
    kaf_opendrain_2MHZ = 14,
    kaf_opendrain_50MHZ = 15,
};

enum Pin{
    kpin0,
    kpin1,
    kpin2,
    kpin3,
    kpin4,
    kpin5,
    kpin6,
    kpin7,
    kpin8,
    kpin9,
    kpin10,
    kpin11,
    kpin12,
    kpin13,
    kpin14,
    kpin15,
};

class Gpio{
 public:
 /**
 * @brief Set the Mode of a GPIO pin
 * 
 * @param GPIOx     [GPIOA, GPIOB, GPIOC]
 * @param pinNum    [kpin0 --> kpin15]
 * @param mode      options : 1- kIN_analog
 *                            2- kIN_floating
 *                            3- kIN_pullup
 *                            4- kIN_pulldown
 *                            5- kOP_pushpull_10MHZ
 *                            6- kOP_pushpull_2MHZ
 *                            7- kOP_pushpull_50MHZ
 *                            8- kOP_opendrain_10MHZ
 *                            9- kOP_opendrain_2MHZ
 *                            10- kOP_opendrain_50MHZ
 *                            11- kaf_pushpull_10MHZ
 *                            12- kaf_pushpull_2MHZ
 *                            13- kaf_pushpull_50MHZ
 *                            14- kaf_opendrain_10MHZ
 *                            15- kaf_opendrain_2MHZ
 *                            16- kaf_opendrain_50MHZ
 */
    static void SetPinMode(volatile GpioRegDef* GPIOx, Pin pinNum, Mode mode); // NOLINT
/**
 * @brief Set the value of a GPIO pin
 * 
 * @param GPIOx     [GPIOA, GPIOB, GPIOC]
 * @param pinNum    [kpin0 --> kpin15]
 * @param pinState  [klow, khigh]
 */
    static void SetPinValue(volatile GpioRegDef* GPIOx, Pin pinNum, State pinState);  // NOLINT
 /**
 * @brief Get the value of a GPIO pin
 * 
 * @param GPIOx     [GPIOA, GPIOB, GPIOC]
 * @param pinNum    [kpin0 --> kpin15]
 * @param ReturnVal Pointer to store the returned value
 */
    static void GetPinValue(volatile GpioRegDef* GPIOx, Pin pinNum, uint32_t * pPinValue);    // NOLINT
};
}  // namespace gpio
}  // namespace mcal
}  // namespace dev
}  // namespace stm32
#endif  // DEV_MCAL_INC_GPIO_H_
