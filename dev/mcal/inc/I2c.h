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
enum ClkSpeed {

};
enum Mode {
	kSm,
	kFm
};
enum AddressLenght {
	k7_bit,
	k10_bit,
	kGeneralCall
};
enum State {
	kDisable,
	kEnable
};
enum Address_State {
	kMatched,
	KNot_Matched
};
struct I2cConfig
{
	/*Sm OR Fm*/
	Mode mode;
	/*Up to 400kHz*/
	uint32_t speed;
	AddressLenght addresslenght;
	uint32_t ownAddress1;
	uint32_t ownAddress2;
	/*Enable OR Disable*/
	State ACK;
	State interrupt;
	State Dual;
	State BuffState;
	State EventState;
	State ErrorState;

};
/**
 * @note Don't forget to init SDL & SCL Pins
 * @tparam I2Cx 
 */
template<I2CPeripheral  I2Cx>
class I2c {
 public:
    I2c();
    void Init(I2cConfig & I2c);
	void StartCondition(I2cConfig & I2c);
	void StopCondition(I2cConfig & I2c);
	void MasterTransmit(uint8_t * Data, uint8_t size);// array w size *************
	void MasterRead();// ************
	void SlaveTransmit(I2cConfig & I2c);// array w size *********
	void SlaveRead(I2cConfig & I2c);//************
	void GeneralCall(State state);
	void SetAck();

 private:
    volatile I2CRegDef* i2c_reg;
	Address_State Helper_SetAddress(AddressLenght lenght);
};
}   // namespace i2c
}   // namespace mcal
}   // namespace dev
}   // namespace stm32
#endif  // DEV_MCAL_INC_I2C_H_
