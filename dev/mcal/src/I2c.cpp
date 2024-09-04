/**
 * @file I2c.cpp
 * @author
 * @brief 
 * @version 0.1
 * @date 2024-07-13
 * @copyright Copyright (c) 2024
 */

// --- INCLUDES
#include <stdint.h>
#include "mcal/inc/stm32f103xx.h"
#include "utils/inc/BitSet.h"
#include "utils/inc/Assert.h"
#include "utils/inc/BitManipulation.h"
#include "mcal/inc/Rcc.h"
#include "mcal/inc/I2c.h"

// --- IMPORT USED NAMESPACE
using namespace stm32::utils::bit_manipulation;
using namespace stm32::dev::mcal::rcc;
using namespace stm32::registers::rcc;
using namespace stm32::dev::mcal::i2c;
using namespace stm32::registers::i2c;

// --- I2C LAYOUT CHECK
ASSERT_STRUCT_SIZE(I2CRegDef, (sizeof(RegWidth_t) * 9));
ASSERT_MEMBER_OFFSET(I2CRegDef, CR1, 0);
ASSERT_MEMBER_OFFSET(I2CRegDef, CR2,   sizeof(RegWidth_t) * 1);
ASSERT_MEMBER_OFFSET(I2CRegDef, OAR1,  sizeof(RegWidth_t) * 2);
ASSERT_MEMBER_OFFSET(I2CRegDef, OAR2,  sizeof(RegWidth_t) * 3);
ASSERT_MEMBER_OFFSET(I2CRegDef, DR,    sizeof(RegWidth_t) * 4);
ASSERT_MEMBER_OFFSET(I2CRegDef, SR1,   sizeof(RegWidth_t) * 5);
ASSERT_MEMBER_OFFSET(I2CRegDef, SR2,   sizeof(RegWidth_t) * 6);
ASSERT_MEMBER_OFFSET(I2CRegDef, CCR,   sizeof(RegWidth_t) * 7);
ASSERT_MEMBER_OFFSET(I2CRegDef, TRISE, sizeof(RegWidth_t) * 8);


I2c::I2c(const I2cConfig & I2c) {
    i2c_reg                   = (I2c.i2cx == kI2C1) ? I2C1 : I2C2;
    i2c_reg->CR1.PE           = 0;
    i2c_reg->CR1.ACK          = I2c.ack;
    i2c_reg->CR1.NOSTRETCH    = ~(I2c.clkStretch);
    i2c_reg->CR1.ENGC         = I2c.genCall;
    i2c_reg->CR2.FREQ         = I2c.speed; 
    i2c_reg->CR2.ITBUFEN      = I2c.buffState;
    i2c_reg->CR2.ITEVTEN      = I2c.eventState;
    i2c_reg->CR2.ITERREN      = I2c.errorState;
    i2c_reg->OAR1.registerVal = (I2c.ownAddress1 | I2c.addressLength);
    
    if (I2c.dual == kEnable) {
        i2c_reg->OAR2.registerVal = (I2c.ownAddress2 | I2c.addressLength);
    }
    
    SetClk(I2c);
    i2c_reg->CR1.PE = 1;
}

void I2c::MasterTransmit(uint16_t slave, uint8_t * data, uint8_t size) {
    StartCondition();
    Send_7Bit_Add(slave, kTransmitter);
    for (uint8_t index = 0; index < size; index++) {
        TransmitData(data[index]);
    }
    StopCondition();
}

void I2c::MasterRead(uint16_t slave, uint8_t * data, uint8_t size) {
    StartCondition();
    Send_7Bit_Add(slave, kReceiver);
    for (uint8_t index = 0; index < size; index ++) {
        ReceiveData(&data[index]);
    }
    StopCondition();
}

void I2c::SlaveTransmit(uint8_t * data, uint8_t size) {
    StartCondition();
    for (uint8_t index = 0; index < size; index ++) {
        TransmitData(data[index]);
    }
    StopCondition();
}

void I2c::SlaveRead(uint8_t * data, uint8_t size) {
    StartCondition();
    for (uint8_t index = 0; index < size; index ++) {
        ReceiveData(&data[index]);
    }
    StopCondition();
}

void I2c::DeInit(const I2cConfig & I2c) {
    i2c_reg->CR1.PE = 0;
}

void I2c::Send_7Bit_Add(uint8_t address, Direction direction) {
    uint16_t Reading = 0;
    address = direction != kTransmitter ? SetBit<uint16_t, 1>(address)     // Set address for read
                                        : ClearBit<uint16_t, 1>(address);  // Reset
    i2c_reg->DR = address;    
    while (i2c_reg->SR1.ADDR != 1) {}
    Reading = i2c_reg->SR1.registerVal;
    Reading = i2c_reg->SR2.registerVal;
}

void I2c::TransmitData(uint8_t data) {
    uint16_t Reading = 0;
    while (i2c_reg->SR1.TxE ==0) {}
    Reading = i2c_reg->SR1.registerVal;
    i2c_reg->DR = data;
}

void I2c::ReceiveData(uint8_t* data) {
    uint16_t Reading = 0;
    while (i2c_reg->SR1.RxNE == 0) {}
    Reading = i2c_reg->SR1.registerVal;
    *data = static_cast<uint8_t>(i2c_reg->DR);
}

void I2c::StartCondition() {
    uint16_t Reading = 0;
    i2c_reg->CR1.START = 1;
    while (i2c_reg->SR1.SB == 1) {}
    Reading = i2c_reg->SR1.registerVal;
}

void I2c::StopCondition() {
    i2c_reg->CR1.STOP = 1;
}

void I2c::SetClk(const I2cConfig & I2c) {
    uint32_t APB1Freq = RCC->CFGR.PPRE1;
    uint32_t I2CFreq  = static_cast<uint16_t>(APB1Freq/1000000);
    uint16_t CR2_Reading = 0;

    // RESET FREQ BIT
    CR2_Reading = ClearBits<uint16_t, 0, 5>(CR2_Reading);
    i2c_reg->CR2.registerVal = CR2_Reading;
    CR2_Reading = i2c_reg->CR2.registerVal;
    CR2_Reading |= I2CFreq;
    i2c_reg->CR2.registerVal = CR2_Reading;

    auto HandleSM = [&]() -> uint16_t {
        uint16_t result;
        // -- CONFIGURE TRISE WITH MAX SCL
        i2c_reg->TRISE = I2CFreq +1;
        // -- DO SM CALCULATION
        //    Thigh = Tlow = CCR * TPCLK1
        result = static_cast<uint16_t>(APB1Freq/(I2c.speed));
        // CHECK RESULT FOR ALLOWED CCR
        if (result < kMin_Sm) {
            return kMin_Sm;
        }
        return result;
    };
    
    auto HandleFM = [&]() -> uint16_t {
        uint16_t result;
        // -- CONFIGURE MAX RAISE TIME FOR FM
        i2c_reg->TRISE = static_cast<uint16_t>((I2CFreq * 300) / 1000 + 1);
        if (I2c.dutyCycle == kduty_cycle_2) {
            i2c_reg->CCR.DUTY = kduty_cycle_2;
            result = static_cast<uint16_t>(APB1Freq / (I2c.speed * 3));
        } else {
            result = static_cast<uint16_t>(APB1Freq / (I2c.speed * 25));
            result |= kduty_cycle_16_9;
        }
        // --- HANDLE BOUNDARY
        if (result < kMin_Fm) {
            result |= kMin_Fm;
        }
        return result | static_cast<uint16_t>(0x8000);
    };


    switch (I2c.mode) {
        case kSm: i2c_reg->CCR.registerVal = HandleSM(); break;   
        case kFm: i2c_reg->CCR.registerVal = HandleFM(); break;
    }
}

