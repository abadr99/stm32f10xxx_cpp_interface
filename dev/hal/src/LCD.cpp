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
#include <cmath>
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
void LCD<M>::WriteOutputPins(uint8_t value) {
    for (uint8_t i = 0; i < config_.dataPins.Size(); ++i) {
        Gpio::SetPinValue(config_.dataPins[i], ExtractBits<uint8_t>(value, i));
    } 
}

template<LcdMode M>
void LCD<M>::SendData(uint8_t data) {
    Gpio::SetPinValue(config_.RSpin, kHigh);
    Gpio::SetPinValue(config_.RWpin, kLow);
    
    // -- 8-BIT MODE
    if constexpr (M == kEightBit) {
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

    if constexpr (M == kEightBit) {
        WriteOutputPins(command);
        SendFallingEdgePulse();
        return; 
    } 
    
    WriteOutputPins(command);
    SendFallingEdgePulse();
    WriteOutputPins(command >> 4);
    SendFallingEdgePulse();
}

template<LcdMode M>
void LCD<M>::Init() {
    //  DIRECTION OF CONTROL PINS SHOULD BE OUTPUT
    // -- FIRST CHECK DIRECTION OF GIVEN PINS
    STM32_ASSERT(config_.RSpin.IsOutput());
    STM32_ASSERT(config_.RWpin.IsOutput());
    STM32_ASSERT(config_.ENpin.IsOutput());
    
    Gpio::SetOutputMode(config_.RSpin, config_.RSpin.GetPinMode());
    Gpio::SetOutputMode(config_.RWpin, config_.RWpin.GetPinMode());
    Gpio::SetOutputMode(config_.ENpin, config_.ENpin.GetPinMode());

    for (uint8_t i = 0; i< config_.dataPins.Size(); i++) {
        Gpio::SetOutputMode(config_.dataPins[i], config_.dataPins[i].GetPinMode());
    }
    Systick::Delay_ms(50);
   
    //  Function Set
    LCDCommand cmd = M == LcdMode::kEightBit ? kFUNCTION_SET_8_BIT : kFUNCTION_SET_4_BIT;
    SendCommand(cmd);
    Systick::Delay_ms(1);
   
    //  Display ON/OFF Control
    SendCommand(LCDCommand::kDISPLAY_ON_CURSOR_OFF);
    Systick::Delay_ms(1);
   
    //  Clear Screen
    SendCommand(LCDCommand::kCLEAR_SCREEN);
    Systick::Delay_ms(5);
   
    //  Entry mode set
    SendCommand(LCDCommand::kENTRY_MODE_INC_SHIFT_OFF);
    Systick::Delay_ms(1);
}

template<LcdMode M>
void LCD<M>::ClearScreen() {
    SendCommand(LCDCommand::kCLEAR_SCREEN);
    Systick::Delay_ms(1);
}

template<LcdMode M>
void LCD<M>::Print(char character) {
    SendData(character);
}

template<LcdMode M>
void LCD<M>::Print(const std::string &str) {
    for (char c : str) {
        SendData(c);
    }
}
// TODO(@noura36): signed number
template<LcdMode M>
void LCD<M>::Print(int32_t num) {
    if (num == 0) {
        SendData('0');
        return;
    }

    bool isNegative = num < 0;
    
    if (isNegative) {
        num = -num;
        SendData('-');
    }

    std::string numStr = std::to_string(num);
    for (char c : numStr) {
        SendData(c);
    }
}

// TODO(@abadr99): Support Nans, inf and +/- zeros
template<LcdMode M>
void LCD<M>::Print(double num) {
    auto PrintStr = [&](const std::string& str) {
        for (auto ch : str) {
            SendData(ch);
        }
    };

    // HANDLE SOME SPECIAL CASES
    if (std::isnan(num)) {
        PrintStr("NAN");
        return;
    }

    if (std::isinf(num)) {
        PrintStr("INF");
        return;
    }

    if (num < 0) {
        SendData('-');
        num = -num;
    }
    
    int realPart = static_cast<int>(num);
    double fractionalPart = num - realPart;
    fractionalPart *= 100;  // Consider two decimal places
    
    std::string realPartStr       = std::to_string(realPart);
    std::string fractionalPartStr = std::to_string(fractionalPart);

    PrintStr(realPartStr);
    SendData('.');
    PrintStr(fractionalPartStr);
}

template<LcdMode M> 
void LCD<M>::SetPosition(Rows_t rowNum, cols_t colNum) {
    if (colNum == 0) {
        SendCommand(kDDRAM_START + rowNum);
    } else {
        SendCommand(kDDRAM_START + rowNum + 0X40);
    }
    Systick::Delay_ms(1);
}

template<LcdMode M> 
void LCD<M>::EnableCursor() {
    SendCommand(LCDCommand::kDISPLAY_ON_CURSOR_ON);
}

template<LcdMode M> 
void LCD<M>::DisableCursor() {
    SendCommand(LCDCommand::kDISPLAY_ON_CURSOR_OFF);
}

template<LcdMode M> 
void LCD<M>::ShiftLeft() {
    SendCommand(LCDCommand::kSHIFT_LEFT);
}

template<LcdMode M> 
void LCD<M>::ShiftRight() {
    SendCommand(LCDCommand::kSHIFT_RIGHT);
}

template<LcdMode M> 
void LCD<M>::DisplayOn() {
    SendCommand(LCDCommand::kDISPLAY_ON_CURSOR_OFF);
}

template<LcdMode M> 
void LCD<M>::DisplayOff() {
    SendCommand(LCDCommand::kDISPLAY_OFF_CURSOR_OFF);
}

template<LcdMode M> 
void LCD<M>::BlinkOn() {
    SendCommand(LCDCommand::kBLINK_ON);
}

template<LcdMode M> 
void LCD<M>::BlinkOff() {
    SendCommand(LCDCommand::kBLINK_OFF);
}

template class LCD<kEightBit>;
template class LCD<kFourBit>;
