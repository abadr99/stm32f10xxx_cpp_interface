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
using namespace stm32::dev::mcal::spi;
using namespace stm32::registers::spi;

void Spi::SpiMasterInit(const SpiConfig& config) {
    // baud rate
    Helper_MasterBaudRate(config);
    // CPOL & CPHA
    Helper_SetClockMode(config);
    // DDF
    Helper_SetDataFrame(config);
    // LSBFIRST
    Helper_SetFrameFormat(config);
    // HW or SW slave manage
    if (config.slave == HW) {
        SPI->CR1.SSM = 0;
    } else if (config.slave == SW) {
        SPI->CR1.SSM = 1;
        SPI->CR1.SSI = 1;
    }
    // set master
    SPI->CR1.SPE = 1;
    SPI->CR1.MSTR = 1;
}
void Spi::SpiSlaveInit(const SpiConfig& config) {
    // DDF
    Helper_SetDataFrame(config);
    // CPOL & CPHA
    Helper_SetClockMode(config);
    // LSBFIRST
    Helper_SetFrameFormat(config);
    // HW or SW slave manage
    if (config.slave == HW) {
        SPI->CR1.SSM = 0;
    } else if (config.slave == SW) {
        SPI->CR1.SSM = 1;
        SPI->CR1.SSI = 0;
    }
    // set salve
    SPI->CR1.SPE = 1;
    SPI->CR1.MSTR = 0;
}
void Spi::Helper_SetDataFrame(const SpiConfig& config) {
    if (config.data == SPI_8bit) {
        SPI->CR1.DFF = 0;
    } else if (config.data == SPI_16bt) {
        SPI->CR1.DFF = 1;
    }
}
void Spi::Helper_SetClockMode(const SpiConfig& config) {
    if (config.clk == MODE0) {
        SPI->CR1.registerVal &= ~(0x03);
    } else if (config.clk == MODE1) {
        SPI->CR1.registerVal &= ~(0x03);
        SPI->CR1.registerVal |=  (0x01);
    } else if (config.clk == MODE2) {
        SPI->CR1.registerVal &= ~(0x03);
        SPI->CR1.registerVal |=  (0x02);
    } else if (config.clk == MODE3) {
        SPI->CR1.registerVal &= ~(0x03);
        SPI->CR1.registerVal |=  (0x03);
    } 
}
void Spi::Helper_SetFrameFormat(const SpiConfig& config) {
    if (config.frame == MSB) {
        SPI->CR1.LSBFIRST = 0;
    } else if (config.frame == LSB) {
        SPI->CR1.LSBFIRST = 1;
    }
}
void Spi::Helper_MasterBaudRate(const SpiConfig& config) {
    if (config.br == F_DIV_2) {
        SPI->CR1.BR = 0;
    } else if (config.br == F_DIV_4) {
        SPI->CR1.BR = 1;
    } else if (config.br == F_DIV_8) {
        SPI->CR1.BR = 2;
    } else if (config.br == F_DIV_16) {
        SPI->CR1.BR = 3;
    } else if (config.br == F_DIV_32) {
        SPI->CR1.BR = 4;
    } else if (config.br == F_DIV_64) {
        SPI->CR1.BR = 5;
    } else if (config.br == F_DIV_128) {
        SPI->CR1.BR = 6;
    } else if (config.br == F_DIV_256) {
        SPI->CR1.BR = 7;
    }
}
