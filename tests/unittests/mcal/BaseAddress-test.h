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

#define AFIO_BASE_ADDRESS  (&AFIOReg[0])
#define EXTI_BASE_ADDRESS  (&EXTIReg[0])

extern uint32_t RccReg[10];
extern uint32_t GPIOAReg[7];
extern uint32_t GPIOBReg[7];
extern uint32_t GPIOCReg[7];
extern uint32_t SYSTICKReg[3];
extern uint32_t SpiReg[8];


extern uint32_t AFIOReg[7];
extern uint32_t EXTIReg[6];

extern uint32_t NvicReg[905];
extern uint32_t ScbReg[18];

extern uint32_t SYSTICKReg[3];

#endif  // TESTS_UNITTESTS_MCAL_BASEADDRESS_TEST_H_
