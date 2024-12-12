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
#include "mcal/stm32f103xx.h"
#include "utils/BitSet.h"
#include "utils/Assert.h"
#include "utils/BitManipulation.h"
#include "utils/Util.h"
#include "mcal/Rcc.h"
#include "mcal/I2c.h"

// --- IMPORT USED NAMESPACE
using namespace stm32;
using namespace stm32::type;
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

// TODO(@ManarAbdelraouf): Check if we should use another assembly 
//                         instructions here e.g. READ

#ifndef UNIT_TEST
#define READ(reg) \
    asm volatile ( \
        "LDR R0, [%0]"  /* Load the value at the register address into R0 */ \
        :               /* No output operands */ \
        : "r" (&(reg)) /* Input operand: address of register */ \
        : "r0"          /* Clobbered register (R0 is modified) */ \
    )
#else 
#define READ(ref)
#endif
#define TO_STRING(str_)  #str_

#define I2C_CONFIG_ERROR(error_) \
    TO_STRING(Invalid I2c error_)


I2c::I2c(const I2cConfig & I2c) {
    STM32_ASSERT((I2c.i2cx == kI2C1) || (I2c.i2cx == kI2C2),
                  I2C_CONFIG_ERROR(I2C peripheral));
    STM32_ASSERT((I2c.mode == kSm) || (I2c.mode == kFm), I2C_CONFIG_ERROR(Mode));
    STM32_ASSERT((I2c.addressLength ==  k7_bit) || (I2c.addressLength ==  k10_bit),
                  I2C_CONFIG_ERROR(Address Length));
    auto I2C1 = reinterpret_cast<volatile I2CRegDef*>(Addr<Peripheral::kI2C1 >::Get());
    auto I2C2 = reinterpret_cast<volatile I2CRegDef*>(Addr<Peripheral::kI2C2 >::Get());
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

void I2c::DeInit() {
    i2c_reg->CR1.PE = 0;
}

void I2c::Send_7Bit_Add(uint8_t address, Direction direction) {
    address = direction != kTransmitter ? util::SetBit<uint16_t, 1>(address)
                                        : util::ClearBit<uint16_t, 1>(address);
    i2c_reg->DR = address;
    util::BusyWait<constant::TimeOut::kI2C>([&](){ return i2c_reg->SR1.ADDR; });
    READ(i2c_reg->SR1);
    READ(i2c_reg->SR2);
}

void I2c::TransmitData(uint8_t data) {
    util::BusyWait<constant::TimeOut::kI2C>([&](){ return i2c_reg->SR1.TxE == 0; });
    READ(i2c_reg->SR1);
    i2c_reg->DR = data;
}

void I2c::ReceiveData(uint8_t* data) {
    util::BusyWait<constant::TimeOut::kI2C>([&](){ return i2c_reg->SR1.RxNE == 0; });
    READ(i2c_reg->SR1);
    *data = static_cast<uint8_t>(i2c_reg->DR);
}

void I2c::StartCondition() {
    i2c_reg->CR1.START = 1;
    util::BusyWait<constant::TimeOut::kI2C>([&](){ return i2c_reg->SR1.SB; });
    READ(i2c_reg->SR1);
}

void I2c::StopCondition() {
    i2c_reg->CR1.STOP = 1;
}

void I2c::SetClk(const I2cConfig & I2c) {
    auto rcc_register = Rcc::GetPtr();
    uint32_t Apb1_freq = rcc_register->CFGR.PPRE1;
    uint32_t i2c_freq  = static_cast<uint16_t>(Apb1_freq / 1000000);
    uint16_t cr2 = i2c_reg->CR2.registerVal;

    // RESET FREQ BIT
    cr2 = util::ClearBits<uint16_t, 0, 5>(cr2);
    i2c_reg->CR2.registerVal = cr2;
    cr2 = i2c_reg->CR2.registerVal;
    cr2 |= i2c_freq;
    i2c_reg->CR2.registerVal = cr2;

    auto HandleSM = [&]() -> uint16_t {
        uint16_t result;
        // -- CONFIGURE TRISE WITH MAX SCL
        i2c_reg->TRISE = i2c_freq +1;
        // -- DO SM CALCULATION
        //    Thigh = Tlow = CCR * TPCLK1
        result = static_cast<uint16_t>(Apb1_freq/(I2c.speed));
        // CHECK RESULT FOR ALLOWED CCR
        if (result < kMin_Sm) {
            return kMin_Sm;
        }
        return result;
    };
    
    auto HandleFM = [&]() -> uint16_t {
        uint16_t result;
        // -- CONFIGURE MAX RAISE TIME FOR FM
        i2c_reg->TRISE = static_cast<uint16_t>((i2c_freq * 300) / 1000 + 1);
        if (I2c.dutyCycle == kduty_cycle_2) {
            // i2c_reg->CCR.DUTY = kduty_cycle_2;
            result = static_cast<uint16_t>(Apb1_freq / (I2c.speed * 3));
        } else {
            result = static_cast<uint16_t>(Apb1_freq / (I2c.speed * 25));
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

#undef READ
