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

template<uint8_t row, uint8_t coloumn>
class Keypad {
 public:
      void KeypadInit();
 private:
      Pin KeypadRow[row];
      pin KeypadCol[coloumn];
};
#endif  //  DEV_HAL_INC_KEYPAD_H_
