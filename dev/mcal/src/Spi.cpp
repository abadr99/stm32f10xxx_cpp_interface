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

template<SpiPeripheral  SPI_NUM>
Spi<SPI_NUM>::Spi() {
    spi_reg=(SPI_NUM == kSPI1) ? SPI1 : SPI2;
}
template<SpiPeripheral  SPI_NUM>
void Spi<SPI_NUM>::MasterInit(const SpiConfig& config) {
    // baud rate
    Helper_MasterBaudRate(config);
    // CPOL & CPHA
    Helper_SetClockMode(config);
    // DDF
    Helper_SetDataFrame(config);
    // LSBFIRST
    Helper_SetFrameFormat(config);
    // HW or SW slave manage
    spi_reg->CR1.SSM = (config.slave == kSW);
    spi_reg->CR1.SSI = (config.slave == kHW);
    // set master
    spi_reg->CR1.MSTR = 1;
    spi_reg->CR1.SPE = 1;
}
template<SpiPeripheral  SPI_NUM>
void Spi<SPI_NUM>::SlaveInit(const SpiConfig& config) {
    // DDF
    Helper_SetDataFrame(config);
    // CPOL & CPHA
    Helper_SetClockMode(config);
    // LSBFIRST
    Helper_SetFrameFormat(config);
    // HW or SW slave manage
    spi_reg->CR1.SSM = (config.slave == kSW);
    spi_reg->CR1.SSI = (config.slave == kHW);
    // set salve
    spi_reg->CR1.MSTR = 0;
    spi_reg->CR1.SPE = 1;
}
template<SpiPeripheral  SPI_NUM>
void Spi<SPI_NUM>::Write(uint8_t data) {
    spi_reg->DR = data;
    while (!(spi_reg->SR.TXE)) {
    }
}
template<SpiPeripheral  SPI_NUM>
uint8_t Spi<SPI_NUM>::Read() {
    while (!(spi_reg->SR.RXNE)) {
    }
    return spi_reg->DR;
}
template<SpiPeripheral  SPI_NUM>
inline void Spi<SPI_NUM>::Helper_SetDataFrame(const SpiConfig& config) {
    spi_reg->CR1.DFF = (config.data == kSPI_16bt);
}
template<SpiPeripheral  SPI_NUM>
void Spi<SPI_NUM>::Helper_SetClockMode(const SpiConfig& config) {
    switch (config.clk) {
        case kMODE0: spi_reg->CR1.registerVal &= ~0x03; break;
        case kMODE1: spi_reg->CR1.registerVal = (spi_reg->CR1.registerVal & ~0x03) | 0x01; break;
        case kMODE2: spi_reg->CR1.registerVal = (spi_reg->CR1.registerVal & ~0x03) | 0x02; break;
        case kMODE3: spi_reg->CR1.registerVal |= 0x03; break;
    }
}
template<SpiPeripheral  SPI_NUM>
void Spi<SPI_NUM>::Helper_SetFrameFormat(const SpiConfig& config) {
    spi_reg->CR1.LSBFIRST = (config.frame == kLSB);
}
template<SpiPeripheral  SPI_NUM>
void Spi<SPI_NUM>::Helper_MasterBaudRate(const SpiConfig& config) {
    STM32_ASSERT(config.br >= kF_DIV_2 && config.br <= kF_DIV_256);
    spi_reg->CR1.BR = static_cast<uint8_t>(config.br);
}
template class Spi<kSPI1>;
template class Spi<kSPI2>;
