/**
 * @file I2c.h
 * @author Manar Abdelraouf
 * @brief 
 * @version 0.1
 * @date 2024-07-13
 */
#ifndef DEV_MCAL_INC_I2C_H_
#define DEV_MCAL_INC_I2C_H_
using namespace stm32::registers::i2c;

namespace stm32 {
namespace dev   {
namespace mcal  {
namespace i2c   {


enum I2CPeripheral {
    kI2C1,
    kI2C2
};

class I2c {
 public:
    explicit I2c(I2CPeripheral peripheral);
    

 private:
    volatile I2CRegDef* i2c_reg;
};
}   // namespace i2c
}   // namespace mcal
}   // namespace dev
}   // namespace stm32
#endif  // DEV_MCAL_INC_I2C_H_
