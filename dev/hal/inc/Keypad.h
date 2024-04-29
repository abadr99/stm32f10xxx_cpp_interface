/**
 * @file Keypad.h
 * @author
 * @brief
 * @version 0.1
 * @date 2024-04-29
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef DEV_HAL_INC_KEYPAD_H_
#define DEV_HAL_INC_KEYPAD_H_
using namespace stm32::dev::mcal::pin; 
using namespace stm32::dev::mcal::gpio;
template<uint8_t Rows, uint8_t Columns>
class Keypad {
 public:
      void SetRowArr(Pin rows[Rows]);
      void setColArr(Pin cols[Columns]);
      void KeypadInit();
      uint8_t GetPressed(uint8_t keypadButtons[Rows][Columns]);
 private:
      Pin KeypadRow[Rows];
      Pin KeypadCol[Columns];
};
#endif  //  DEV_HAL_INC_KEYPAD_H_
