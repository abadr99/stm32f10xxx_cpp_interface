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

void Spi::SpiMasterInit(const DataFrame data, const FrameFormat frame, ClkMode clk, SlaveManage slave) { // NOLINT
    // it's missed baud rate and enable
    if (clk == MODE0) {
        SPI->CR1.registerVal &= ~(0x03);
    } else if (clk == MODE1) {
        SPI->CR1.registerVal &= ~(0x03);
        SPI->CR1.registerVal |=  (0x01);
    } else if (clk == MODE2) {
        SPI->CR1.registerVal &= ~(0x03);
        SPI->CR1.registerVal |=  (0x02);
    } else if (clk == MODE3) {
        SPI->CR1.registerVal &= ~(0x03);
        SPI->CR1.registerVal |=  (0x03);
    }
    if (data == SPI_8bit) {
        SPI->CR1.DFF = 0;
    } else if (data == SPI_16bt) {
        SPI->CR1.DFF = 1;
    }
    if (frame == MSB) {
        SPI->CR1.LSBFIRST = 0;
    } else if (frame == LSB) {
        SPI->CR1.LSBFIRST = 1;
    }
    if (slave == HW) {
        SPI->CR1.SSM = 0;
    } else if (slave == SW) {
        SPI->CR1.SSM = 1;
    }
}
