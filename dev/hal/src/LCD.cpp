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
void LCD::SetLowNibbleValue(const LCD_Config &config, uint8_t value) {
    value&=0x0F;
    for (uint8_t i =0; i< config.dataPins.Size(); i++) {
        uint8_t pinState = Gpio::GetPinValue(config.dataPins[i]);
        pinState &= (0xF0);
        pinState |= (value);
        Gpio::SetPinValue(config.dataPins[i], static_cast<State> (pinState));
    }
}
void LCD::SetHighNibbleValue(const LCD_Config &config, uint8_t value) {
    value&=0xF0;
    for (uint8_t i =0; i< config.dataPins.Size(); i++) {
        uint8_t pinState = Gpio::GetPinValue(config.dataPins[i]);
        pinState &= (0x0F);
        pinState |= (value);
        Gpio::SetPinValue(config.dataPins[i], static_cast<State> (pinState));
    }
}
void LCD::SetLowNibbleDirection(const LCD_Config &config, OutputMode mode) {
    uint8_t direction = static_cast<uint8_t> (mode);
    direction &= 0x0F;
    for (uint8_t i =0; i< config.dataPins.Size(); i++) {
        direction &= (0xF0);
        direction |= (direction);
        Gpio::SetOutputMode(config.dataPins[i], static_cast<OutputMode> (direction));
    }
}
void LCD::SetHighNibbleDirection(const LCD_Config &config, OutputMode mode) {
    uint8_t direction = static_cast<uint8_t> (mode);
    direction &= 0xF0;
    for (uint8_t i =0; i< config.dataPins.Size(); i++) {
        direction &= (0x0F);
        direction |= (direction);
        Gpio::SetOutputMode(config.dataPins[i], static_cast<OutputMode> (direction));
    }
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
    } else if (config.mode == k4_bit) {
        if (config.lcd4BitDataPin == kLowNibble) {
            SetLowNibbleValue(config, (data >> 4));
            SendFallingEdgePulse(config);
            SetLowNibbleValue(config, data);
            SendFallingEdgePulse(config);
        } else if (config.lcd4BitDataPin == kHighNibble) {
            SetHighNibbleValue(config, data);
            SendFallingEdgePulse(config);
            SetHighNibbleValue(config, (data << 4));
            SendFallingEdgePulse(config);
        }
    }
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
    } else if (config.mode == k4_bit) {
        if (config.lcd4BitDataPin == kLowNibble) {
            SetLowNibbleValue(config, (commandValue >> 4));
            SendFallingEdgePulse(config);
            SetLowNibbleValue(config, commandValue);
            SendFallingEdgePulse(config);
        } else if (config.lcd4BitDataPin == kHighNibble) {
            SetHighNibbleValue(config, commandValue);
            SendFallingEdgePulse(config);
            SetHighNibbleValue(config, (commandValue << 4));
            SendFallingEdgePulse(config);
        }
    }
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
    } else if (config.mode == k4_bit) {
        if (config.lcd4BitDataPin == kLowNibble) {
            SetLowNibbleDirection(config, OutputMode::kPushPull_2MHZ);
        } else if (config.lcd4BitDataPin == kHighNibble) {
            SetHighNibbleDirection(config, OutputMode::kPushPull_2MHZ);
        }
        SendCommand(config, LCDCommand::kRETURN_HOME);
        Systick::Delay_ms(50);
        //  Function Set
        SendCommand(config, LCDCommand::kFUNCTION_SET_4_BIT);
        Systick::Delay_ms(1);
        //  Display ON/OFF Control
        SendCommand(config, LCDCommand::kDISPLAY_ON_CURSOR_OFF);
        Systick::Delay_ms(1);
        //  Clear Screen
        SendCommand(config, LCDCommand::kCLEAR_SCREEN);
        Systick::Delay_ms(5);
        //  Entry mode set
        SendCommand(config, LCDCommand::kENTRY_MODE_INC_SHIFT_OFF);
        Systick::Delay_ms(5);
    }
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
    if (num == 0) {
        SendChar(config, '0');
        return;
    }
    bool isNegative = num < 0;
    if (isNegative) {
        num = -num;
    }
    std::string numStr = std::to_string(num);
    if (isNegative) {
        SendChar(config, '-');
    }
    for (char c : numStr) {
        SendChar(config, c);
    }
}
void LCD::SendFloat(const LCD_Config &config, double num) {
    if (num < 0) {
        SendChar(config, '-');
        num = -num;
    }
    int realPart = static_cast<int>(num);
    double fractionalPart = num - realPart;
    SendNum(config, realPart);
    SendChar(config, '.');
    // Extract and send fractional part
    fractionalPart *= 100;  // Consider two decimal places
    SendNum(config, static_cast<int>(fractionalPart));
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
