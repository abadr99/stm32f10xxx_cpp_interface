/**
 * @file LCD.cpp
 * @author noura36
 * @brief 
 * @version 0.1
 * @date 2024-07-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "Assert.h"
#include "BitManipulation.h"
#include "string"
#include "Pin.h"
#include "Gpio.h"
#include "Systick.h"
#include "Array.h"
#include "LCD.h"

using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::mcal::systick;
using namespace stm32::dev::hal::lcd;
using namespace stm32::utils::array;
using namespace stm32::utils::bit_manipulation;

template<LcdMode M>
LCD<M>::LCD(const LCD_Config<M> &config) : config_(config) {
    // AS WE ASSUMING THE LCD IS CONNECTED TO THE SAME PORT
    // WE HAVE TO ENABLE RCC FOR THIS PORT
    // TODO(@abadr99): after merging rcc-enhancements pr
}

template<LcdMode M>
void LCD<M>::SendFallingEdgePulse() {
    Gpio::SetPinValue(config_.ENpin, kHigh);
    Systick::Delay_ms(1);
    Gpio::SetPinValue(config_.ENpin, kLow);
    Systick::Delay_ms(1);
}

template<LcdMode M>
void LCD<M>::SetLowNibbleValue(uint8_t value) {
    for (uint8_t i = 0; i< config_.dataPins.Size(); i++) {
        Gpio::SetPinValue(config_.dataPins[i], ExtractBits<uint8_t,i>(value));
    }
}

template<LcdMode M>
void LCD<M>::WriteOutputPins(uint8_t value) {
    for (uint8_t i = 0; i < config_.dataPins.Size(); ++i) {
        Gpio::SetPinValue(config_.dataPins[i], ExtractBits<uint8_t>(data, i));
    } 
}

template<LcdMode M>
void LCD<M>::SendData(uint8_t data) {
    Gpio::SetPinValue(config_.RSpin, kHigh);
    Gpio::SetPinValue(config_.RWpin, kLow);
    
    // -- 8-BIT MODE
    if constexpr (M == k8_bit) {
        WriteOutputPins(data);
        SendFallingEdgePulse();
        return;
    } 

    // -- 4-BIT MODE 
    WriteOutputPins(data);
    SendFallingEdgePulse();
    WriteOutputPins(data >> 4);
    SendFallingEdgePulse();
}

template<LcdMode M>
void LCD<M>::SendCommand(LCDCommand command) {
    Gpio::SetPinValue(config_.RSpin, kLow);
    Gpio::SetPinValue(config_.RWpin, kLow);
    
    uint8_t commandValue = static_cast<uint8_t>(command);
    
    if constexpr (M == k8_bit) {
        WriteOutputPins(command);
        SendFallingEdgePulse();
        return; 
    } 
    
    WriteOutputPins(command);
    SendFallingEdgePulse();
    SetLowNibbleValue(config_, commandValue >> 4);
    SendFallingEdgePulse(config);
}

template<LcdMode M>
void LCD<M>::Init() {
    //  DIRECTION OF CONTROL PINS SHOULD BE OUTPUT
    
    // -- FIRST CHECK DIRECTION OF GIVEN PINS
    STM32_ASSERT();
    
    Gpio::SetOutputMode(config_.RSpin, OutputMode::kPushPull_2MHZ);
    Gpio::SetOutputMode(config_.RWpin, OutputMode::kPushPull_2MHZ);
    Gpio::SetOutputMode(config_.ENpin, OutputMode::kPushPull_2MHZ);

    if (config_.mode == k8_bit) {
        for (uint8_t i =0; i< config_.dataPins.Size(); i++) {
            //  SET Direction for LCD data  pins --> OUTPUT
            Gpio::SetOutputMode(config_.dataPins[i], OutputMode::kPushPull_2MHZ);
        }
        Systick::Delay_ms(50);
        //  Function Set
        SendCommand(config_, LCDCommand::kFUNCTION_SET_8_BIT);
        Systick::Delay_ms(1);
        //  Display ON/OFF Control
        SendCommand(config_, LCDCommand::kDISPLAY_ON_CURSOR_OFF);
        Systick::Delay_ms(1);
        //  Clear Screen
        SendCommand(config_, LCDCommand::kCLEAR_SCREEN);
        Systick::Delay_ms(5);
        //  Entry mode set
        SendCommand(config_, LCDCommand::kENTRY_MODE_INC_SHIFT_OFF);
        Systick::Delay_ms(1);
    } else if (config_.mode == k4_bit) {
        if (config_.lcd4BitDataPin == kLowNibble) {
            SetLowNibbleDirection(config_, OutputMode::kPushPull_2MHZ);
        } else if (config_.lcd4BitDataPin == kHighNibble) {
            SetHighNibbleDirection(config_, OutputMode::kPushPull_2MHZ);
        }
        SendCommand(config_, LCDCommand::kRETURN_HOME);
        Systick::Delay_ms(50);
        //  Function Set
        SendCommand(config_, LCDCommand::kFUNCTION_SET_4_BIT);
        Systick::Delay_ms(1);
        //  Display ON/OFF Control
        SendCommand(config_, LCDCommand::kDISPLAY_ON_CURSOR_OFF);
        Systick::Delay_ms(1);
        //  Clear Screen
        SendCommand(config_, LCDCommand::kCLEAR_SCREEN);
        Systick::Delay_ms(5);
        //  Entry mode set
        SendCommand(config_, LCDCommand::kENTRY_MODE_INC_SHIFT_OFF);
        Systick::Delay_ms(5);
    }
}
void LCD::ClearScreen() {
    SendCommand(config_, LCDCommand::kCLEAR_SCREEN);
    Systick::Delay_ms(1);
}
void LCD::SendChar(, uint8_t character) {
    SendData(config_, character);
}
void LCD::SendString(, const std::string &str) {
    //  c hold each ccharacter in the string
    for (char c : str) {
        SendData(config_, c);
    }
}
// TODO(@noura36): sined number
void LCD::SendNum(, int num) {
    if (num == 0) {
        SendChar(config_, '0');
        return;
    }
    bool isNegative = num < 0;
    if (isNegative) {
        num = -num;
    }
    std::string numStr = std::to_string(num);
    if (isNegative) {
        SendChar(config_, '-');
    }
    for (char c : numStr) {
        SendChar(config_, c);
    }
}
void LCD::SendFloat(, double num) {
    if (num < 0) {
        SendChar(config_, '-');
        num = -num;
    }
    int realPart = static_cast<int>(num);
    double fractionalPart = num - realPart;
    SendNum(config_, realPart);
    SendChar(config_, '.');
    // Extract and send fractional part
    fractionalPart *= 100;  // Consider two decimal places
    SendNum(config_, static_cast<int>(fractionalPart));
}
void LCD::SetPosition(, LcdRows rowNum, LcdCol colNum) {
    LCDCommand command;
    /* if the user enter invalid location AC will point to
			the first place in DDRAM (0, 0 )  */
    uint8_t lcdCommand = static_cast<uint8_t>(LCDCommand::kDDRAM_START);
    if (rowNum > kRow2 || rowNum < kRow1 || colNum < kCOL1 || colNum > kCOL16) {
        command = LCDCommand::kDDRAM_START;
    } else if (rowNum == kRow1) {
        command = static_cast<LCDCommand>(lcdCommand + static_cast<uint8_t>(colNum) -1);
    } else if (rowNum == kRow2) {
        command = static_cast<LCDCommand>(lcdCommand + 64 + static_cast<uint8_t>(colNum) -1);
    }
    SendCommand(config_, command);
    Systick::Delay_ms(1);
}
void LCD::EnableCursor() {
    SendCommand(config_, LCDCommand::kDISPLAY_ON_CURSOR_ON);
}
void LCD::DisableCursor() {
    SendCommand(config_, LCDCommand::kDISPLAY_ON_CURSOR_OFF);
}
void LCD::ShiftLeft() {
    SendCommand(config_, LCDCommand::kSHIFT_LEFT);
}
void LCD::ShiftRight() {
    SendCommand(config_, LCDCommand::kSHIFT_RIGHT);
}
void LCD::DisplayOn() {
    SendCommand(config_, LCDCommand::kDISPLAY_ON_CURSOR_OFF);
}
void LCD::DisplayOff() {
    SendCommand(config_, LCDCommand::kDISPLAY_OFF_CURSOR_OFF);
}
void LCD::BlinkOn() {
    SendCommand(config_, LCDCommand::kBLINK_ON);
}
void LCD::BlinkOff() {
    SendCommand(config_, LCDCommand::kBLINK_OFF);
}
