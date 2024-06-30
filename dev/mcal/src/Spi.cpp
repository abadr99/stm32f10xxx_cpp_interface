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

Spi& Spi::BuildSpi1() {
    spi_reg = SPI1;
    return *this;
}
Spi& Spi::BuildSpi2() {
    spi_reg = SPI2;
    return *this;
}
void Spi::MasterInit(const SpiConfig& config) {
    // baud rate
    Helper_MasterBaudRate(config);
    // CPOL & CPHA
    Helper_SetClockMode(config);
    // DDF
    Helper_SetDataFrame(config);
    // LSBFIRST
    Helper_SetFrameFormat(config);
    // HW or SW slave manage
    if (config.slave == kHW) {
        spi_reg->CR1.SSM = 0;
    } else if (config.slave == kSW) {
        spi_reg->CR1.SSM = 1;
        spi_reg->CR1.SSI = 1;
    }
    // set master
    spi_reg->CR1.SPE = 1;
    spi_reg->CR1.MSTR = 1;
}
void Spi::SlaveInit(const SpiConfig& config) {
    // DDF
    Helper_SetDataFrame(config);
    // CPOL & CPHA
    Helper_SetClockMode(config);
    // LSBFIRST
    Helper_SetFrameFormat(config);
    // HW or SW slave manage
    if (config.slave == kHW) {
        spi_reg->CR1.SSM = 0;
    } else if (config.slave == kSW) {
        spi_reg->CR1.SSM = 1;
        spi_reg->CR1.SSI = 0;
    }
    // set salve
    spi_reg->CR1.SPE = 1;
    spi_reg->CR1.MSTR = 0;
}

void Spi::Write(uint8_t data) {
    spi_reg->DR = data;
    while (spi_reg->SR.BSY) {
    }
}
uint8_t Spi::Read() {
    while (spi_reg->SR.BSY) {
    }
    return spi_reg->DR;
}
void Spi::Helper_SetDataFrame(const SpiConfig& config) {
    if (config.data == kSPI_8bit) {
        spi_reg->CR1.DFF = 0;
    } else if (config.data == kSPI_16bt) {
        spi_reg->CR1.DFF = 1;
    }
}
void Spi::Helper_SetClockMode(const SpiConfig& config) {
    if (config.clk == kMODE0) {
        spi_reg->CR1.registerVal &= ~(0x03);
    } else if (config.clk == kMODE1) {
        spi_reg->CR1.registerVal &= ~(0x03);
        spi_reg->CR1.registerVal |=  (0x01);
    } else if (config.clk == kMODE2) {
        spi_reg->CR1.registerVal &= ~(0x03);
        spi_reg->CR1.registerVal |=  (0x02);
    } else if (config.clk == kMODE3) {
        spi_reg->CR1.registerVal &= ~(0x03);
        spi_reg->CR1.registerVal |=  (0x03);
    } 
}
void Spi::Helper_SetFrameFormat(const SpiConfig& config) {
    if (config.frame == kMSB) {
       spi_reg->CR1.LSBFIRST = 0;
    } else if (config.frame == kLSB) {
        spi_reg->CR1.LSBFIRST = 1;
    }
}
void Spi::Helper_MasterBaudRate(const SpiConfig& config) {
    STM32_ASSERT(config.br >= kF_DIV_2 && config.br <= kF_DIV_256);
    if (config.br == kF_DIV_2) {
        spi_reg->CR1.BR = 0;
    } else if (config.br == kF_DIV_4) {
        spi_reg->CR1.BR = 1;
    } else if (config.br == kF_DIV_8) {
        spi_reg->CR1.BR = 2;
    } else if (config.br == kF_DIV_16) {
        spi_reg->CR1.BR = 3;
    } else if (config.br == kF_DIV_32) {
        spi_reg->CR1.BR = 4;
    } else if (config.br == kF_DIV_64) {
        spi_reg->CR1.BR = 5;
    } else if (config.br == kF_DIV_128) {
        spi_reg->CR1.BR = 6;
    } else if (config.br == kF_DIV_256) {
        spi_reg->CR1.BR = 7;
    }
}
