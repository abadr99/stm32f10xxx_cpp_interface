/**
 * @file stmf103xxbaseTest.h
 * @author
 * @brief 
 * @version 0.1
 * @date 2024-03-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef TESTS_UNITTESTS_MCAL_BASEADDRESS_TEST_H_
#define TESTS_UNITTESTS_MCAL_BASEADDRESS_TEST_H_

#include <stdint.h>

#define RCC_BASE_ADDRESS (&RccReg[0])

#define GPIOA_BASE_ADDRESS      (&GPIOAReg[0])
#define GPIOB_BASE_ADDRESS      (&GPIOBReg[0])
#define GPIOC_BASE_ADDRESS      (&GPIOCReg[0])

#define SPI1_BASE_ADDRESS        (&SpiReg[0])
#define SPI2_BASE_ADDRESS        (&SpiReg[1])

#define NVIC_BASE_ADDRESS   (&NvicReg[0])
#define SCB_BASE_ADDRESS    (&ScbReg[0])

#define SYSTICK_BASE_ADDRESS  (&SYSTICKReg[0])

#define USART1_BASE_ADDRESS      (&USART1Reg[0])
#define USART2_BASE_ADDRESS      (&USART2Reg[0])
#define USART3_BASE_ADDRESS      (&USART3Reg[0])
#define AFIO_BASE_ADDRESS  (&AFIOReg[0])
#define EXTI_BASE_ADDRESS  (&EXTIReg[0])

#define I2C1_BASE_ADDRESS   (&I2c1Reg[0])
#define I2C2_BASE_ADDRESS   (&I2c2Reg[0])

#define DMA_BASE_ADDRESS    (&DmaReg[0])

#define RTC_BASE_ADDRESS    (&RtcReg[0])

#define WWDG_BASE_ADDRESS   (&WwdgReg[0])
extern uint32_t RccReg[10];

extern uint32_t GPIOAReg[7];
extern uint32_t GPIOBReg[7];
extern uint32_t GPIOCReg[7];

extern uint32_t SYSTICKReg[3];
extern uint32_t SpiReg[9];

extern uint32_t NvicReg[905];
extern uint32_t ScbReg[18];

extern uint32_t AFIOReg[7];
extern uint32_t EXTIReg[6];

extern uint32_t USART1Reg[7];
extern uint32_t USART2Reg[7];
extern uint32_t USART3Reg[7];

extern uint32_t I2c1Reg[9];
extern uint32_t I2c2Reg[9];

extern uint32_t WwdgReg[3];





extern uint32_t DmaReg[30];
extern uint32_t RtcReg[10];

#endif  // TESTS_UNITTESTS_MCAL_BASEADDRESS_TEST_H_
