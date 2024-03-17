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

enum Mode{
    kIN_analog,
    kIN_floating,
    kIN_pullup,
    kIN_pulldown,
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
    static void SetPinDirection(volatile GpioRegDef* GPIOX, Pin pinNum, Mode mode); // NOLINT
    static void SetPinVal(volatile GpioRegDef* GPIOX, Pin pinNum, uint32_t val);
    static uint32_t  GetPinVal(volatile GpioRegDef* GPIOX, Pin pinNum);
};
}  // namespace gpio
}  // namespace mcal
}  // namespace dev
}  // namespace stm32
#endif  // DEV_MCAL_INC_GPIO_H_
