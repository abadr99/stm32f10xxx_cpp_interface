/**
 * @file SPi.cpp
 * @author Noura & Noran
 * @version 0.1
 * @date 2024-05-1
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "mcal/stm32f103xx.h"
#include "utils/Types.h"
#include "utils/Assert.h"
#include "utils/BitManipulation.h"
#include "utils/Util.h"
#include "mcal/Spi.h"

using namespace stm32;
using namespace stm32::type;
using namespace stm32::registers::rcc; 
using namespace stm32::dev::mcal::spi;
using namespace stm32::registers::spi;

#define TO_STRING(str_)  #str_

#define SPI_CONFIG_ERROR(error_) \
    TO_STRING(Invalid Spi error_)

#define SPI__TX_TIME_OUT_ERROR  "Timeout while waiting transmitting the data."
#define SPI__RX_TIME_OUT_ERROR  "Timeout while waiting receiving the data."

#define CHECK_SPI_CONFIG() \
    STM32_ASSERT((config_.br >= kF_DIV_2 && config_.br <= kF_DIV_256), \
    SPI_CONFIG_ERROR(BaudRate)); \
    STM32_ASSERT((config_.data == kSpi_8bit || config_.data == kSpi_16bit), \
    SPI_CONFIG_ERROR(DataFrame)); \
    STM32_ASSERT((config_.clk >= kMode0 && config_.clk <= kMode3), \
    SPI_CONFIG_ERROR(ClockMode)); \
    STM32_ASSERT((config_.frame == kLSB || config_.frame == kMSB), \
    SPI_CONFIG_ERROR(FrameFormat)); \
    STM32_ASSERT((config_.slave == kSW || config_.slave == kHW), \
    SPI_CONFIG_ERROR(SlaveSelectMode));

Spi::Spi(const SpiConfig& config) :config_(config) {
    switch (config_.number) {
        case kSPI1 : spi_reg = (reinterpret_cast<volatile SpiRegDef*>
                                (Addr<Peripheral::kSPI1 >::Get())); break;
        case kSPI2 : spi_reg = (reinterpret_cast<volatile SpiRegDef*>
                                (Addr<Peripheral::kSPI2 >::Get())); break;
        default    : STM32_ASSERT(false, SPI_CONFIG_ERROR(SpiNumber)); break;
    }
}

void Spi::MasterInit() {
    // baud rate
    MasterBaudRate();
    // CPOL & CPHA
    SetClockMode();
    // DDF
    SetDataFrame();
    // LSBFIRST
    SetFrameFormat();
    // set master
    spi_reg->CR1.MSTR = 1;
    spi_reg->CR1.SPE = 1;
}

void Spi::SlaveInit() {
    // DDF
    SetDataFrame();
    // CPOL & CPHA
    SetClockMode();
    // LSBFIRST
    SetFrameFormat();
    // HW or SW slave manage
    spi_reg->CR1.SSM = (config_.slave == kSW);
    spi_reg->CR1.SSI = (config_.slave == kHW);
    // set salve
    spi_reg->CR1.MSTR = 0;
    spi_reg->CR1.SPE = 1;
}

void Spi::Write(uint8_t data) {
    spi_reg->DR = data;
    util::BusyWait<constant::TimeOut::kSpi>([&](){ return !spi_reg->SR.TXE; });
}

uint8_t Spi::Read() {
    util::BusyWait<constant::TimeOut::kSpi>([&](){ return !(spi_reg->SR.RXNE); });
    return spi_reg->DR;
}

Spinum Spi::GetSpiNum() {
    return config_.number;
}

void Spi::SetDataFrame() {
    spi_reg->CR1.DFF = (config_.data == kSpi_16bit);
}

void Spi::SetClockMode() {
    util::WriteBits<RegWidth_t, 0, 1>(spi_reg->CR1.registerVal, config_.clk);
}

void Spi::SetFrameFormat() {
    spi_reg->CR1.LSBFIRST = (config_.frame == kLSB);
}

void Spi::MasterBaudRate() {
    spi_reg->CR1.BR = static_cast<uint8_t>(config_.br);
}
