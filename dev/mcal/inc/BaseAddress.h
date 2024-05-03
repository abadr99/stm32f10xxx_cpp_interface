/**
 * @file baseAddress.h
 * @author
 * @brief 
 * @version 0.1
 * @date 2024-03-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef DEV_MCAL_INC_BASEADDRESS_H_
#define DEV_MCAL_INC_BASEADDRESS_H_

#define RCC_BASE_ADDRESS    (0x40021000)

#define GPIOA_BASE_ADDRESS  (0x40010800)
#define GPIOB_BASE_ADDRESS  (0x40010C00)
#define GPIOC_BASE_ADDRESS  (0x40011000)

#define NVIC_BASE_ADDRESS   (0xE000E100)
#define SCB_BASE_ADDRESS    (0xE000ED00)

#define AFIO_BASE_ADDRESS   (0x40010000)

#define SYSTICK_BASE_ADDRESS  (0xE000E010)
namespace stm32 {
namespace registers {
namespace rcc {
}  // namespace rcc
}  // namespace registers
}  // namespace stm32
#endif  // DEV_MCAL_INC_BASEADDRESS_H_
