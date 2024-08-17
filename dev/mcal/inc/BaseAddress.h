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


#define RCC_BASE_ADDRESS      (0x40021000)

#define GPIOA_BASE_ADDRESS    (0x40010800)
#define GPIOB_BASE_ADDRESS    (0x40010C00)
#define GPIOC_BASE_ADDRESS    (0x40011000)

#define EXTI_BASE_ADDRESS     (0x40010400)

#define AFIO_BASE_ADDRESS     (0x40010000)

#define NVIC_BASE_ADDRESS     (0xE000E100)
#define SCB_BASE_ADDRESS      (0xE000ED00)

#define SYSTICK_BASE_ADDRESS  (0xE000E010)

#define SPI1_BASE_ADDRESS     (0x40013000)
#define SPI2_BASE_ADDRESS     (0x40003800)
#define SYSTICK_BASE_ADDRESS  (0xE000E010)

#define USART1_BASE_ADDRESS   (0x40013800)
#define USART2_BASE_ADDRESS   (0x40004400)
#define USART3_BASE_ADDRESS   (0x40004800)

#define DMA_BASE_ADDRESS      (0x40020000)

#define RTC_BASE_ADDRESS      (0x40002800)


#define I2C1_BASE_ADDRESS  (0x40005400)
#define I2C2_BASE_ADDRESS  (0x40005800)

#define DMA_BASE_ADDRESS    (0x40020000)

#define WWDG_BASE_ADDRESS (0x40003000)
#define IWDG_BASE_ADDRESS (0x40002C00)

#define PWR_BASE_ADDRESS    (0x40007000)
namespace stm32 {
namespace registers {
namespace rcc {
}  // namespace rcc
}  // namespace registers
}  // namespace stm32
#endif  // DEV_MCAL_INC_BASEADDRESS_H_
