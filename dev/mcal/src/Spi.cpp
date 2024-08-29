/**
 * @file SPi.cpp
 * @author Noura & Nooran
 * @version 0.1
 * @date 2024-05-1
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "mcal/inc/stm32f103xx.h"
#include "utils/inc/Types.h"
#include "utils/inc/Assert.h"
#include "utils/inc/BitManipulation.h"
#include "mcal/inc/Spi.h"

using namespace stm32::utils::bit_manipulation;
using namespace stm32::registers::rcc; 
using namespace stm32::dev::mcal::spi;
using namespace stm32::registers::spi;


Spi::Spi(const SpiConfig& config) :config_(config) {
    switch (config_.number) {
        case kSPI1 : spi_reg = (reinterpret_cast<volatile SpiRegDef*>(SPI1)); break;
        case kSPI2 : spi_reg = (reinterpret_cast<volatile SpiRegDef*>(SPI2)); break;
        default: break;
    }
}

void Spi::MasterInit() {
    // baud rate
    Helper_MasterBaudRate();
    // CPOL & CPHA
    Helper_SetClockMode();
    // DDF
    Helper_SetDataFrame();
    // LSBFIRST
    Helper_SetFrameFormat();
    // HW or SW slave manage
    spi_reg->CR1.SSM = (config_.slave == kSW);
    spi_reg->CR1.SSI = (config_.slave == kHW);
    // set master
    spi_reg->CR1.MSTR = 1;
    spi_reg->CR1.SPE = 1;
}

void Spi::SlaveInit() {
    // DDF
    Helper_SetDataFrame();
    // CPOL & CPHA
    Helper_SetClockMode();
    // LSBFIRST
    Helper_SetFrameFormat();
    // HW or SW slave manage
    spi_reg->CR1.SSM = (config_.slave == kSW);
    spi_reg->CR1.SSI = (config_.slave == kHW);
    // set salve
    spi_reg->CR1.MSTR = 0;
    spi_reg->CR1.SPE = 1;
}

void Spi::Write(uint8_t data) {
    spi_reg->DR = data;
    uint32_t ctr = 0;
    while ((!spi_reg->SR.TXE) && (ctr != SPI_TIMEOUT) && (++ctr)) {
    }
    STM32_ASSERT(ctr != SPI_TIMEOUT);
}

uint8_t Spi::Read() {
    uint32_t ctr = 0;
    while (!(spi_reg->SR.RXNE) && (ctr != SPI_TIMEOUT) && (++ctr)) {
    }
    STM32_ASSERT(ctr != SPI_TIMEOUT);
    return spi_reg->DR;
}
Spinum Spi::GetSpiNum() {
    return config_.number;
}
inline void Spi::Helper_SetDataFrame() {
    spi_reg->CR1.DFF = (config_.data == kSpi_16bt);
}

void Spi::Helper_SetClockMode() {
    switch (config_.clk) {
        case kMode0: spi_reg->CR1.registerVal &= ~0x03; break;
        case kMode1: spi_reg->CR1.registerVal = (spi_reg->CR1.registerVal & ~0x03) | 0x01; break;
        case kMode2: spi_reg->CR1.registerVal = (spi_reg->CR1.registerVal & ~0x03) | 0x02; break;
        case kMode3: spi_reg->CR1.registerVal |= 0x03; break;
    }
}

void Spi::Helper_SetFrameFormat() {
    spi_reg->CR1.LSBFIRST = (config_.frame == kLSB);
}

void Spi::Helper_MasterBaudRate() {
    STM32_ASSERT(config_.br >= kF_DIV_2 && config_.br <= kF_DIV_256);
    spi_reg->CR1.BR = static_cast<uint8_t>(config_.br);
}
