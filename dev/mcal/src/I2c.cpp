/**
 * @file I2c.cpp
 * @author Manar Abdelraouf
 * @brief 
 * @version 0.1
 * @date 2024-07-13
 * @copyright Copyright (c) 2024
 */

#include <stdint.h>
#include "mcal/inc/stm32f103xx.h"
#include "utils/inc/BitSet.h"
#include "utils/inc/Assert.h"
#include "utils/inc/BitManipulation.h"
#include "mcal/inc/Rcc.h"
#include "mcal/inc/I2c.h"

using namespace stm32::dev::mcal::rcc;
using namespace stm32::registers::rcc;
using namespace stm32::dev::mcal::i2c;
using namespace stm32::registers::i2c;

template<I2CPeripheral  I2Cx>
I2c<I2Cx>::I2c() {
    i2c_reg = (I2Cx == kI2C1) ? I2C1 : I2C2;
}
template<I2CPeripheral  I2Cx>
void I2c<I2Cx>::Init(const I2cConfig & I2c) {
    /*Disable I2C*/
    i2c_reg->CR1.PE = 0;

    i2c_reg->CR1.ACK = I2c.ack;
    i2c_reg->CR1.NOSTRETCH = ~(I2c.clkStretch);
    i2c_reg->CR1.ENGC = I2c.genCall;

    rcc::Rcc::SetAPB1Prescaler(kApbNotDivided);

    i2c_reg->CR2.FREQ = I2c.speed; 
    i2c_reg->CR2.ITBUFEN = I2c.buffState;
    i2c_reg->CR2.ITEVTEN = I2c.eventState;
    i2c_reg->CR2.ITERREN = I2c.errorState;

    i2c_reg ->OAR1 = (I2c.ownAddress1 | I2c.addresslength);

    if (I2c.dual == kEnable) {
        i2c_reg->OAR2 = (I2c.ownAddress2 | I2c.addresslength);
    }
    // CCR 
    Helper_SetClk(I2c);

    /*Enable I2c*/
    i2c_reg->CR1.PE = 1;
}
template<I2CPeripheral  I2Cx>
void I2c<I2Cx>::MasterTransmit(uint16_t slave, uint8_t * data, uint8_t size) {
    Helper_StartCondition();
    Helper_Send_7Bit_Add(slave, kTransmitter);
    for (uint8_t index = 0; index < size; index ++) {
        Helper_TransmitData(data[index]);
    }
    Helper_StopCondition();
}
template<I2CPeripheral  I2Cx>
void I2c<I2Cx>::MasterRead(uint16_t slave, uint8_t * data, uint8_t size) {
    Helper_StartCondition();
    Helper_Send_7Bit_Add(slave, kReceiver);
    for (uint8_t index = 0; index < size; index ++) {
        Helper_ReceiveData(&data[index]);
    }
    Helper_StopCondition();
}
template<I2CPeripheral  I2Cx>
void I2c<I2Cx>::SlaveTransmit(uint8_t * data, uint8_t size) {
    Helper_StartCondition();
    for (uint8_t index = 0; index < size; index ++) {
        Helper_TransmitData(data[index]);
    }
    Helper_StopCondition();
}
template<I2CPeripheral  I2Cx>
void I2c<I2Cx>::SlaveRead(uint8_t * data, uint8_t size) {
    Helper_StartCondition();
    for (uint8_t index = 0; index < size; index ++) {
        Helper_ReceiveData(&data[index]);
    }
    Helper_StopCondition();
}
template<I2CPeripheral  I2Cx>
void I2c<I2Cx>::DeInit(const I2cConfig & I2c) {
    i2c_reg->CR1.PE = 0;
}
template<I2CPeripheral  I2Cx>
void I2c<I2Cx>::Helper_Send_7Bit_Add(uint8_t address, Direction direction) {
    uint16_t Reading = 0;
     if (direction != kTransmitter) {
        /*Set address for read*/
        address |= (uint16_t)0x0001;
     } else {
        /*Reset*/
        address &= (uint16_t)0xFFFE;
     }
    i2c_reg->DR = address;    
    while (i2c_reg->SR1.ADDR != 1) {}
    Reading = i2c_reg->SR1.registerVal;
    Reading = i2c_reg->SR2.registerVal;
}
template<I2CPeripheral  I2Cx>
void I2c<I2Cx>::Helper_TransmitData(uint8_t data) {
    uint16_t Reading = 0;
    while (i2c_reg->SR1.TxE ==0) {}
    Reading = i2c_reg->SR1.registerVal;
    i2c_reg->DR = data;
}
template<I2CPeripheral  I2Cx>
void I2c<I2Cx>::Helper_ReceiveData(uint8_t * data) {
    uint16_t Reading = 0;
    while (i2c_reg->SR1.RxNE == 0) {}
    Reading = i2c_reg->SR1.registerVal;
    * data = (uint8_t) (i2c_reg->DR);
}
template<I2CPeripheral  I2Cx>
void I2c<I2Cx>::Helper_StartCondition() {
    uint16_t Reading = 0;
    i2c_reg->CR1.START = 1;
    /*Wait until Start Flag is set*/
    while (i2c_reg->SR1.SB == 1) {}
    Reading = i2c_reg->SR1.registerVal;
}
template<I2CPeripheral  I2Cx>
void I2c<I2Cx>::Helper_StopCondition() {
    i2c_reg->CR1.STOP = 1;
}
template<I2CPeripheral  I2Cx>
void I2c<I2Cx>::Helper_SetClk(const I2cConfig & I2c) {
    uint8_t APB1Freq = 0;
    uint8_t I2CFreq  = 0;
    uint8_t Result   = 0;
    uint16_t CR2_Reading = 0;
    /*Reset Freq Bit*/
    CR2_Reading = i2c_reg->CR2;
    CR2_Reading &= 0xFFC0;
    i2c_reg->CR2 = CR2_Reading;
    // get APB1 freq
    APB1Freq = RCC->CFGR.PPRE1;
    I2CFreq = (uint16_t)APB1Freq/1000000;
    /*Config Freq bits*/
    CR2_Reading = i2c_reg->CR2;
    CR2_Reading |= I2CFreq;
    i2c_reg->CR2 = CR2_Reading;
    if (I2c.mode == kSm) {
        /*configure TRISE with Max SCL Rasie*/
        i2c_reg->TRISE = I2CFreq +1;
		/*Sm Calculation
		 * t high = Tlow = CCR * TPCLK1*/
         Result = (uint16_t)(APB1Freq/(I2c.speed));
         /*Check Result for Allowed CCR*/
         if (Result < kMin_Sm) {
           /*Minmum CCR Value */
           Result = kMin_Sm;
         }
    } else if (I2c.mode == kFm) {
            /*config Max Raise Time for FM*/
            i2c_reg->TRISE = (uint16_t)((I2CFreq*(uint16_t)300)/(uint16_t)1000+(uint16_t)1); 
            if (I2c.dutyCycle == kduty_cycle_2) {
                i2c_reg->CCR.DUTY = kduty_cycle_2;
                /*T(L)/T(H)=2*/
                Result = (uint16_t)(APB1Freq/(I2c.speed*3));
            } else if (I2c.dutyCycle == kduty_cycle_16_9) {
                /*T(L)/T(H)=16/9*/
                Result = (uint16_t)(APB1Freq/(I2c.speed*25));
                Result |= kduty_cycle_16_9;
        }
        if (Result < kMin_Fm) {
             Result |= kMin_Fm;
        }
        /*CCR F/S set*/
        Result |=(uint16_t)0x8000;
    }
    i2c_reg->CCR = Result;
}

