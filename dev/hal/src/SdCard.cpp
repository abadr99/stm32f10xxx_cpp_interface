/**
 * @file SdCard.cpp
 * @brief 
 * @version 0.1
 * @date 2024-08-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdint.h>
#include "mcal/inc/stm32f103xx.h"
#include "Assert.h"
#include "Pin.h"
#include "Gpio.h"
#include "Spi.h"
#include "SdCard.h"
using namespace stm32::utils::types;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::mcal::spi;
using namespace stm32::dev::hal::sdcard;

SD::SD(Pin Sdpin, Spi SdSpi) : Sdpin(Sdpin) , SdSpi(SdSpi) {
}
void SD::toggleClock(int cycles) {
    for (int i = 0; i < cycles; i++) {
         Gpio::SetPinValue(Sdpin, Gpio::kHigh);
         Gpio::SetPinValue(Sdpin, Gpio::kLow);
    }
}
void SD::Init() {
    SdSpi.MasterInit();
    Gpio::SetPinValue(Sdpin, Gpio::kHigh);
    // Send 80 clock pulses to initialize
    toggleClock(80);
    Gpio::SetPinValue(Sdpin, Gpio::kLow);
    SendCommand(CMD0, 0);  // CMD0: reset SD card
    uint8_t value = ReadResponse();
    // Initialize SD card
    uint8_t retry = 0;
    while (value != 0 && (retry != SD_TIMEOUT) && (++retry)) {
        Gpio::SetPinValue(Sdpin, Gpio::kLow);
        SendCommand(CMD55, 0);  // CMD55: indicate next command is application-specific
        ReadResponse();
        SendCommand(ACMD41, 0x40000000);  // ACMD41: initialize SD card
        value = ReadResponse();
        Gpio::SetPinValue(Sdpin, Gpio::kHigh);
    }
    STM32_ASSERT(retry != SD_TIMEOUT);
}

void SD::Transmit(uint8_t data) {
      SdSpi.Write(data);
      toggleClock(1);
}

void SD::SendCommand(SDCommand cmd, uint32_t arg) {
    Transmit(static_cast<uint8_t>(cmd) | 0x40);
    Transmit((arg >> 24) & 0xFF);
    Transmit((arg >> 16) & 0xFF);
    Transmit((arg >> 8) & 0xFF);
    Transmit(arg & 0xFF);
    Transmit(0x95);  // Dummy CRC
}
uint8_t SD::ReadResponse() {
    uint8_t response = SdSpi.Read();
    toggleClock(1);
    return response;
}

bool SD::WriteBlock(uint32_t blockAddr, const uint8_t* data) {
    Gpio::SetPinValue(Sdpin, Gpio::kLow);
    SendCommand(CMD24, blockAddr);  // CMD24: write single block
    
    if (ReadResponse() != 0x00) {
        Gpio::SetPinValue(Sdpin, Gpio::kHigh);
        return false;
    }
    
    Transmit(0xFE);  // Data token
    
    // Write 512 byte block
    for (int i = 0; i < 512; i++) {
        Transmit(data[i]);
    }
    
    // Send dummy CRC
    Transmit(0xFF);
    Transmit(0xFF);
    
    // Check if data accepted
    uint8_t response = ReadResponse();
    if ((response & 0x1F) != 0x05) {
        Gpio::SetPinValue(Sdpin, Gpio::kHigh);
        return false;
    }
    
    uint8_t retry = 0;
    // Wait for write to finish
    while (ReadResponse() == 0x00 && (retry != SD_TIMEOUT) && (++retry)) {
    }
    STM32_ASSERT(retry != SD_TIMEOUT);
    
    Gpio::SetPinValue(Sdpin, Gpio::kHigh);
    return true;
}
bool SD::ReadBlock(uint32_t blockAddr, uint8_t* data) {
    Gpio::SetPinValue(Sdpin, Gpio::kLow);
    SendCommand(SDCommand::CMD17, blockAddr);  // Read single block
    if (ReadResponse() != 0x00) {
        Gpio::SetPinValue(Sdpin, Gpio::kHigh);
        return false;
    }
    uint8_t retry = 0;
    // Wait for data token
    while (ReadResponse()!= 0xFE && (retry != SD_TIMEOUT) && (++retry)) {
    }
    STM32_ASSERT(retry != SD_TIMEOUT);
    // Read 512 byte block
    for (int i = 0; i < 512; i++) {
        data[i] = ReadResponse();
    }
    // Read CRC
    ReadResponse();
     Gpio::SetPinValue(Sdpin, Gpio::kHigh);
    return true;
}
