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

extern uint32_t RccReg[10];


#endif  // TESTS_UNITTESTS_MCAL_BASEADDRESS_TEST_H_
