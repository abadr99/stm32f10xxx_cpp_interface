/**
 * @file LCD.cpp
 * @author noura36
 * @brief 
 * @version 0.1
 * @date 2024-07-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "BitManipulation.h"

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
        LCD::SendCommand(config, LCDCommand::kFUNCTION_SET_8_BIT);
        Systick::Delay_ms(1);
        //  Display ON/OFF Control
        LCD::SendCommand(config, LCDCommand::kDISPLAY_ON_CURSOR_OFF);
        Systick::Delay_ms(1);
        //  Clear Screen
        LCD::SendCommand(config, LCDCommand::kCLEAR_SCREEN);
        Systick::Delay_ms(5);
        //  Entry mode set
        LCD::SendCommand(config, LCDCommand::kENTRY_MODE_INC_SHIFT_OFF);
        Systick::Delay_ms(1);
    }
    // TODO(@noura36): make 4bit using nibble function in gpio
}
void LCD::ClearScreen(const LCD_Config &config) {
    LCD::SendCommand(config, LCDCommand::kCLEAR_SCREEN);
    Systick::Delay_ms(1);
}
void LCD::SendChar(const LCD_Config &config, uint8_t character) {
    LCD::SendData(config, character);
}
void LCD::SendString(const LCD_Config &config, uint8_t str[]) {
    uint8_t itrator = 0;
    while (itrator != '\0') {
        LCD::SendData(config, str[itrator++]);
    }
}
