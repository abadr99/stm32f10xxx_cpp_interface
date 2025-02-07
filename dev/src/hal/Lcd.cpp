/**
 * @file Lcd.cpp
 * @author noura36
 * @brief 
 * @version 0.1
 * @date 2024-07-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <cmath>
#include <string>

#include "utils/Assert.h"
#include "utils/BitManipulation.h"
#include "utils/Util.h"

#include "mcal/Pin.h"
#include "mcal/Rcc.h"
#include "mcal/Gpio.h"
#include "mcal/Systick.h"
#include "utils/Array.h"
#include "hal/Lcd.h"

using namespace stm32;
using namespace stm32::type;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::mcal::systick;
using namespace stm32::dev::hal::lcd;
using namespace stm32::dev::mcal::rcc;

template<LcdMode M>
Lcd<M>::Lcd(const LCD_Config<M> &config) : config_(config) {
    for (uint8_t i = 0; i < config_.dataPins.Size(); ++i) {
        Peripheral p = util::MapPortToPeripheral(config_.dataPins[i].GetPort());
        Rcc::Enable(p);
    } 
    Rcc::Enable(util::MapPortToPeripheral(config_.controlPort));
    // TODO(@noura36): Should we call this function here ?
    Init();
}

template<LcdMode M>
void Lcd<M>::SendFallingEdgePulse() {
    Gpio::SetPinValue(config_.ENpin, DigitalVoltage::kHigh);
    Systick::Delay_ms(1);
    Gpio::SetPinValue(config_.ENpin, DigitalVoltage::kLow);
    Systick::Delay_ms(1);
}

template<LcdMode M>
void Lcd<M>::WriteOutputPins(uint8_t value) {
    for (uint8_t i = 0; i < config_.dataPins.Size(); ++i) {
        Gpio::SetPinValue(config_.dataPins[i], static_cast<DigitalVoltage>(util::ExtractBit<uint8_t>(value, i)));  // NOLINT [whitespace/line_length] 
    } 
}

template<LcdMode M>
void Lcd<M>::SendData(uint8_t data) {
    Gpio::SetPinValue(config_.RSpin, DigitalVoltage::kHigh);
    Gpio::SetPinValue(config_.RWpin, DigitalVoltage::kLow);
    
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
void Lcd<M>::SendCommand(uint32_t command) {
    Gpio::SetPinValue(config_.RSpin, DigitalVoltage::kLow);
    Gpio::SetPinValue(config_.RWpin, DigitalVoltage::kLow);

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
void Lcd<M>::Init() {
    //  DIRECTION OF CONTROL PINS SHOULD BE OUTPUT
    // -- FIRST CHECK DIRECTION OF GIVEN PINS
    STM32_ASSERT(config_.RSpin.IsOutput(), CONFIG_ERROR(_LCD, _CONFIG));
    STM32_ASSERT(config_.RWpin.IsOutput(), CONFIG_ERROR(_LCD, _CONFIG));
    STM32_ASSERT(config_.ENpin.IsOutput(), CONFIG_ERROR(_LCD, _CONFIG));
    
    Gpio::Set(config_.RSpin);
    Gpio::Set(config_.RWpin);
    Gpio::Set(config_.ENpin);

    for (uint8_t i = 0; i< config_.dataPins.Size(); i++) {
        Gpio::Set(config_.dataPins[i]);
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
void Lcd<M>::ClearScreen() {
    SendCommand(LCDCommand::kCLEAR_SCREEN);
    Systick::Delay_ms(1);
}

template<LcdMode M>
void Lcd<M>::Print(char character) {
    SendData(character);
}

template<LcdMode M>
void Lcd<M>::Print(const std::string &str) {
    for (char c : str) {
        SendData(c);
    }
}
// TODO(@noura36): signed number
template<LcdMode M>
void Lcd<M>::Print(int32_t num) {
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
void Lcd<M>::Print(double num) {
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
void Lcd<M>::SetPosition(Rows_t rowNum, cols_t colNum) {
    if (colNum == 0) {
        SendCommand(kDDRAM_START + rowNum);
    } else {
        SendCommand(kDDRAM_START + rowNum + 0x40);
    }
    Systick::Delay_ms(1);
}

template<LcdMode M> 
void Lcd<M>::EnableCursor() {
    SendCommand(LCDCommand::kDISPLAY_ON_CURSOR_ON);
}

template<LcdMode M> 
void Lcd<M>::DisableCursor() {
    SendCommand(LCDCommand::kDISPLAY_ON_CURSOR_OFF);
}

template<LcdMode M> 
void Lcd<M>::ShiftLeft() {
    SendCommand(LCDCommand::kSHIFT_LEFT);
}

template<LcdMode M> 
void Lcd<M>::ShiftRight() {
    SendCommand(LCDCommand::kSHIFT_RIGHT);
}

template<LcdMode M> 
void Lcd<M>::DisplayOn() {
    SendCommand(LCDCommand::kDISPLAY_ON_CURSOR_OFF);
}

template<LcdMode M> 
void Lcd<M>::DisplayOff() {
    SendCommand(LCDCommand::kDISPLAY_OFF_CURSOR_OFF);
}

template<LcdMode M> 
void Lcd<M>::BlinkOn() {
    SendCommand(LCDCommand::kBLINK_ON);
}

template<LcdMode M> 
void Lcd<M>::BlinkOff() {
    SendCommand(LCDCommand::kBLINK_OFF);
}

template class Lcd<kEightBit>;
template class Lcd<kFourBit>;
