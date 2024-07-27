/**
 * @file I2c.h
 * @author Manar Abdelraouf
 * @brief 
 * @version 0.1
 * @date 2024-07-13
 * @copyright Copyright (c) 2024
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
enum ClkSpeed {
    kMin_Sm = 0x04,
    kMin_Fm = 0x01
};
enum DutyCycle : uint16_t{
    kduty_cycle_2 = ((uint16_t)0xBFFF),
    kduty_cycle_16_9 = ((uint16_t)0x4000)
};
enum Mode {
    kSm,
    kFm
};
enum AddressLength {
    k7_bit,
    k10_bit
};
enum State {
    kDisable,
    kEnable
};
enum Address_State {
    kMatched,
    KNot_Matched
};
enum Direction {
    kTransmitter,
    kReceiver
};
struct I2cConfig {
    /*Sm OR Fm*/
    Mode mode;
    DutyCycle dutyCycle;
    /*Up to 400kHz*/
    uint32_t speed;
    uint32_t ownAddress1;
    uint32_t ownAddress2;
    AddressLength addresslength;
    /*Enable OR Disable*/
    State ack;
    State interrupt;
    State dual;
    State clkStretch;
    State buffState;
    State eventState;
    State errorState;
    State genCall;
};
/**
 * @note Don't forget to init SDL & SCL Pins
 * @tparam I2Cx 
 */
template<I2CPeripheral  I2Cx>
class I2c {
 public:
    I2c();
    void Init(const I2cConfig & I2c);
    void MasterTransmit(uint16_t slave, uint8_t * data, uint8_t size);
    void MasterRead(uint16_t slave, uint8_t * data, uint8_t size);
    void SlaveTransmit(uint8_t * data, uint8_t size);
    void SlaveRead(uint8_t * data, uint8_t size);
    void DeInit(const I2cConfig & I2c);

 private:
    volatile I2CRegDef* i2c_reg;
    void Helper_Send_7Bit_Add(uint8_t address, Direction direction);
    void Helper_TransmitData(uint8_t data);
    void Helper_ReceiveData(uint8_t * data);
    void Helper_StartCondition();
    void Helper_StopCondition();
    void Helper_SetClk(const I2cConfig & I2c);
};
}   // namespace i2c
}   // namespace mcal
}   // namespace dev
}   // namespace stm32
#endif  // DEV_MCAL_INC_I2C_H_
