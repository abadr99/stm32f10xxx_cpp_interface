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
namespace stm32 {
namespace dev   {
namespace mcal  {
namespace usart {

class Usart {
 public:
    static void Init(uint32_t baudRate);
    static void Transmit(uint8_t data);
    static uint8_t Receive();
};
}   // namespace usart
}   // namespace mcal
}   // namespace dev
}   // namespace stm32

#endif  //  DEV_MCAL_INC_USART_H_
