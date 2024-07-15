/**
 * @file I2c.cpp
 * @author Manar Abdelraouf
 * @brief 
 * @version 0.1
 * @date 2024-07-13
 */

#include <stdint.h>
#include "mcal/inc/stm32f103xx.h"
#include "utils/inc/BitSet.h"
#include "utils/inc/Assert.h"
#include "utils/inc/BitManipulation.h"
#include "mcal/inc/I2c.h"

using namespace stm32::dev::mcal::i2c; // NOLINT[build/namespaces]
using namespace stm32::registers::i2c; // NOLINT[build/namespaces]


I2c::I2c(I2CPeripheral peripheral) {
    i2c_reg = (peripheral==kI2C1) ? I2C1 : I2C2 ;
}
