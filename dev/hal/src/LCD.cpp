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

void LCD::SendFallingEdgePulse(const LCD_Config &config) {
    Gpio::SetPinValue(config.ENpin, kHigh);
    Systick::Delay_ms(1);
    Gpio::SetPinValue(config.ENpin, kLow);
    Systick::Delay_ms(1);
}
void LCD::SendData(const LCD_Config &config, uint8_t data) {
    Gpio::SetPinValue(config.RSpin, kHigh);
    Gpio::SetPinValue(config.RWpin, kLow);
    if (config.mode == k8_bit) {
        for (uint8_t i =0; i< config.dataPins.Size(); i++) {
            State pinState = (data &(1 << i)) ? kHigh : kLow;
            Gpio::SetPinValue(config.dataPins[i], pinState);
        }
        LCD::SendFallingEdgePulse(config); 
    }
    // TODO(@noura36): make 4bit using nibble function in gpio
}
void LCD::SendCommand(const LCD_Config &config, LCDCommand command) {
    Gpio::SetPinValue(config.RSpin, kLow);
    Gpio::SetPinValue(config.RWpin, kLow);
    uint8_t commandValue = static_cast<uint8_t>(command);
    if (config.mode == k8_bit) {
        for (uint8_t i =0; i< config.dataPins.Size(); i++) {
            State pinState = (commandValue &(1 << i)) ? kHigh : kLow;
            Gpio::SetPinValue(config.dataPins[i], pinState);
        }
        LCD::SendFallingEdgePulse(config);  
    }
    // TODO(@noura36): make 4bit using nibble function in gpio
}
void LCD::Init(const LCD_Config &config) {
    //  SET Direction for LCD control  pins --> OUTPUT 
    Gpio::SetOutputMode(config.RSpin, OutputMode::kPushPull_2MHZ);
    Gpio::SetOutputMode(config.RWpin, OutputMode::kPushPull_2MHZ);
    Gpio::SetOutputMode(config.ENpin, OutputMode::kPushPull_2MHZ);

    if (config.mode == k8_bit) {
        for (uint8_t i =0; i< config.dataPins.Size(); i++) {
            //  SET Direction for LCD data  pins --> OUTPUT
            Gpio::SetOutputMode(config.dataPins[i], OutputMode::kPushPull_2MHZ);
        }
        Systick::Delay_ms(50);
        //  Function Set
        SendCommand(config, LCDCommand::kFUNCTION_SET_8_BIT);
        Systick::Delay_ms(1);
        //  Display ON/OFF Control
        SendCommand(config, LCDCommand::kDISPLAY_ON_CURSOR_OFF);
        Systick::Delay_ms(1);
        //  Clear Screen
        SendCommand(config, LCDCommand::kCLEAR_SCREEN);
        Systick::Delay_ms(5);
        //  Entry mode set
        SendCommand(config, LCDCommand::kENTRY_MODE_INC_SHIFT_OFF);
        Systick::Delay_ms(1);
    }
    // TODO(@noura36): make 4bit using nibble function in gpio
}
void LCD::ClearScreen(const LCD_Config &config) {
    SendCommand(config, LCDCommand::kCLEAR_SCREEN);
    Systick::Delay_ms(1);
}
void LCD::SendChar(const LCD_Config &config, uint8_t character) {
    SendData(config, character);
}
void LCD::SendString(const LCD_Config &config, const std::string &str) {
    //  c hold each ccharacter in the string
    for (char c : str) {
        SendData(config, c);
    }
}
// TODO(@noura36): sined number
void LCD::SendNum(const LCD_Config &config, int num) {
    uint16_t temp = num;
    uint8_t itrator1 = 0;
    uint8_t itrator2 = 0;
    uint8_t negativeFlag = 0;
    std::string numArr = 0;
    /*Store Number in numArr as a string
			but the number will be stored in reverse order in the array
				so we need to reverse this array again*/
    if (num == 0) {
        SendChar(config, '0');
    } 
    if (num < 0) {
        num = num *(-1);
        negativeFlag = 1;
    } while (num != 0) {
        temp = num % 10;
        numArr[itrator1++] = (temp + '0');
        num = num / 10;
    } for (itrator2 = 0; itrator2 < itrator1/2; itrator2++) {
        uint8_t ch = numArr[itrator2];
        numArr[itrator2] = numArr[itrator1 - itrator2 - 1];
        numArr[itrator1 - itrator2 - 1] = ch;
    } for (itrator2 = 0; itrator2 < itrator1; itrator2++) {
        if (negativeFlag == 1) {
            SendChar(config, '-');
            negativeFlag = 0;
        }
        SendChar(config, numArr[itrator2]);
    }
}
void LCD::SendFloat(const LCD_Config &config, double num) {
    uint16_t realPart = static_cast<uint16_t> (num);
    uint16_t fractionPart = static_cast<uint16_t> ((num - realPart)*100);
    if (num < 0) {
        fractionPart *= -1;
        realPart *= -1;
        SendChar(config, '-');
    }
    SendNum(config, realPart);
    SendChar(config, '.');
    SendNum(config, fractionPart);
}
void LCD::SetPosition(const LCD_Config &config, LcdRows rowNum, LcdCol colNum) {
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
    SendCommand(config, command);
    Systick::Delay_ms(1);
}
void LCD::EnableCursor(const LCD_Config &config) {
    SendCommand(config, LCDCommand::kDISPLAY_ON_CURSOR_ON);
}
void LCD::DisableCursor(const LCD_Config &config) {
    SendCommand(config, LCDCommand::kDISPLAY_ON_CURSOR_OFF);
}
void LCD::ShiftLeft(const LCD_Config &config) {
    SendCommand(config, LCDCommand::kSHIFT_LEFT);
}
void LCD::ShiftRight(const LCD_Config &config) {
    SendCommand(config, LCDCommand::kSHIFT_RIGHT);
}
void LCD::DisplayOn(const LCD_Config &config) {
    SendCommand(config, LCDCommand::kDISPLAY_ON_CURSOR_OFF);
}
void LCD::DisplayOff(const LCD_Config &config) {
    SendCommand(config, LCDCommand::kDISPLAY_OFF_CURSOR_OFF);
}
void LCD::BlinkOn(const LCD_Config &config) {
    SendCommand(config, LCDCommand::kBLINK_ON);
}
void LCD::BlinkOff(const LCD_Config &config) {
    SendCommand(config, LCDCommand::kBLINK_OFF);
}
