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
enum Direction{
    kinput,
    koutput
};
enum Mode{
    kanalog,
    kfloating,
    kpullup,
    kpulldown,
    kpushpull,
    kopendrain,
    kaf_pushpull,
    kaf_opendrain
};
enum Speed{
    k10MHZ,
    k2MHZ,
    k50MHZ,
    knoSpeed
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
    template<Speed speed = knoSpeed>
    static void SetPinDirection(Pin pinNum, Direction direction, Mode mode);
    static void SetPinVal(Pin pinNum, uint32_t val);
    static uint32_t  GetPinVal(Pin pinNum);
};
}  // namespace gpio
}  // namespace mcal
}  // namespace dev
}  // namespace stm32
#endif  // DEV_MCAL_INC_GPIO_H_
