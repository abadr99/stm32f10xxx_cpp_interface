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
#include "mcal/inc/Rcc.h"
#include "mcal/inc/I2c.h"

using namespace stm32::dev::mcal::rcc;
using namespace stm32::dev::mcal::i2c; // NOLINT[build/namespaces]
using namespace stm32::registers::i2c; // NOLINT[build/namespaces]

template<I2CPeripheral  I2Cx>
I2c<I2Cx>::I2c() {
    i2c_reg = (I2Cx==kI2C1) ? I2C1 : I2C2 ;
}
template<I2CPeripheral  I2Cx>
void I2c<I2Cx>::Init(I2cConfig & I2c) {
    /*Disable I2C*/
    i2c_reg->CR1.PE = 0;

    i2c_reg->CR1.ACK = I2c.ACK;
    /*speed from I2C_CR2 */
    rcc::Rcc::SetAPB1Prescaler(kApbNotDivided);
    i2c_reg->CR2.FREQ = I2c.speed; 

    i2c_reg->CR2.ITBUFEN = I2c.BuffState;
    i2c_reg->CR2.ITEVTEN = I2c.EventState;
    i2c_reg->CR2.ITERREN = I2c.ErrorState;

    i2c_reg ->OAR1 = (I2c.ownAddress1 | I2c.addresslenght);

    if (I2c.Dual == kEnable) {
        i2c_reg->OAR2 = (I2c.ownAddress2 | I2c.addresslenght);
    }
    // CCR 


    /*Enable I2c*/
    i2c_reg->CR1.PE = 1;
}

template<I2CPeripheral  I2Cx>
void I2c<I2Cx>::StartCondition(I2cConfig & I2c) {
//Set the START bit in the I2C_CR1 register to generate a Start condition
}
template<I2CPeripheral  I2Cx>
void I2c<I2Cx>::StopCondition(I2cConfig & I2c){
// sets:
//  The STOPF bit and generates an interrupt if the ITEVFEN bit is set.
}
template<I2CPeripheral  I2Cx>
void I2c<I2Cx>::SlaveTransmit(I2cConfig & I2c) {
    /*
    // if (kMatched== Helper_SetAddress<I2Cx>()) {
         If ENDUAL=1, the software has to read the DUALF bit to check which slave address
has been acknowledged.
    // }
*/
 //must ADDR Cleard
 // Slave send data from DR to SDA line (via shift reg)
 /* while ( ADDR is 1 && DR is NOt filled) {
 streching
 }
recive ACK
//The TxE bit is set by hardware with an interrupt if the ITEVFEN and the ITBUFEN bits
//are set.
// If TxE is set and some data were not written in the I2C_DR register before the end of the
// next data transmission, the BTF bit is set and the interface waits until BTF is cleared by a
// read to I2C_SR1 followed by a write to the I2C_DR register, stretching SCL low.
// AF
*/
}
template<I2CPeripheral  I2Cx>
void I2c<I2Cx>::SlaveRead(I2cConfig & I2c) {
    /*
    // if (kMatched== Helper_SetAddress<I2Cx>()) {
         If ENDUAL=1, the software has to read the DUALF bit to check which slave address
has been acknowledged.
    // }
//must ADDR Cleard
//read Data from SDA line (via shift reg) to DR
// Send ACK if set 
//The RxNE bit is set by hardware and an interrupt is generated if the ITEVFEN and
ITBUFEN bit is set.
// If RxNE is set and the data in the DR register is not read before the end of the next data
// reception, the BTF bit is set and the interface waits until BTF is cleared by a read from
// I2C_SR1 followed by a read from the I2C_DR register, stretching SCL low
//STOPF
*/
}
template<I2CPeripheral  I2Cx>
void I2c<I2Cx>::GeneralCall(State state) {

        i2c_reg->CR1.ENGC = state ;
}

template<I2CPeripheral  I2Cx>
Address_State I2c<I2Cx>::Helper_SetAddress(AddressLenght lenght) {
/*
    -if (start condition == 1) {
    -send from SDL to shift register ;
    if ( I2C.Adrresslength == 10) {
        -In 10-bit addressing mode, the comparison includes the header sequence (11110xx0),
        where xx denotes the two most significant bits of the address.
        if ( matched ){};
        else if (Not matched) {
        exit}
    }
            -Then it is compared with the address of the interface (OAR1) and with
        OAR2 (if ENDUAL=1) or the General Call address (if ENGC = 1). 
        if (matched) {
        if (Ack is set ) {
 An acknowledge pulse if the ACK bit is set*/

}
// After checking the SR1 register content, the user should perform the complete clearing sequence for each
// flag found set.
// Thus, for ADDR and STOPF flags, the following sequence is required inside the I2C interrupt routine:
// READ SR1
// if (ADDR == 1) {READ SR1; READ SR2}
// if (STOPF == 1) {READ SR1; WRITE CR1}
// The purpose is to make sure that both ADDR and STOPF flags are cleared if both are found set.

