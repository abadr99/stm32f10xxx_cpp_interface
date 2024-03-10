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

#ifndef DEV_MCAL_INC_BASEADDRESS_TEST_H_
#define DEV_MCAL_INC_BASEADDRESS_TEST_H_

namespace stm32 {
namespace registers {
namespace rcc {

uint32_t RccReg[10]={};
#define RCC_BASE_ADDRESS (RccReg)
c
}  // namespace rcc
}  // namespace registers
}  // namespace stm32

#endif  // DEV_MCAL_INC_BASEADDRESS_TEST_H_
