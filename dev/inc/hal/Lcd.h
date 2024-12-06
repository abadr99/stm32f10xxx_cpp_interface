/**
 * @file LCD.h
 * @author noura36
 * @brief
 * @version 0.1
 * @date 2024-07-29
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef DEV_INC_HAL_LCD_H_
#define DEV_INC_HAL_LCD_H_

#include <string>

namespace stm32 {
namespace dev {
namespace hal {
namespace lcd {

/**
 * @brief Enum representing various commands for controlling the LCD display.
 */
enum LCDCommand : uint8_t {
    kCLEAR_SCREEN               = 0x01,   /**< Clears the LCD screen. */
    kRETURN_HOME                = 0x02,   /**< Returns cursor to home position. */

    kFUNCTION_SET_8_BIT         = 0x38,   /**< Sets 8-bit mode with 2-line display. */
    kFUNCTION_SET_4_BIT         = 0x28,   /**< Sets 4-bit mode with 2-line display. */

    kDISPLAY_ON_CURSOR_ON       = 0x0E,   /**< Turns display and cursor on. */
    kDISPLAY_ON_CURSOR_OFF      = 0x0C,   /**< Turns display on and cursor off. */
    kDISPLAY_OFF_CURSOR_OFF     = 0x09,   /**< Turns both display and cursor off. */

    kBLINK_ON                   = 0x0F,   /**< Enables cursor blinking. */
    kBLINK_OFF                  = 0x0E,   /**< Disables cursor blinking. */

    kENTRY_MODE_DEC_SHIFT_OFF   = 0x04,   /**< Decrements cursor, no shift. */
    kENTRY_MODE_DEC_SHIFT_ON    = 0x05,   /**< Decrements cursor, shifts display. */
    kENTRY_MODE_INC_SHIFT_OFF   = 0x06,   /**< Increments cursor, no shift. */
    kENTRY_MODE_INC_SHIFT_ON    = 0x07,   /**< Increments cursor, shifts display. */

    kSHIFT_LEFT                 = 0x18,   /**< Shifts display left. */
    kSHIFT_RIGHT                = 0x1C,   /**< Shifts display right. */

    kINC_CURSOR                 = 0x04,   /**< Moves cursor right. */
    kDEC_CURSOR                 = 0x00,   /**< Moves cursor left. */

    kCGRAM_START                = 0x40,   /**< Sets starting address of CGRAM. */
    kDDRAM_START                = 0x80    /**< Sets starting address of DDRAM. */
};

/**
 * @brief Enum representing the mode (4-bit or 8-bit) for the LCD interface.
 */
enum LcdMode : uint8_t {
    kEightBit = 8,   /**< 8-bit communication mode. */
    kFourBit  = 4    /**< 4-bit communication mode. */
};

/**
 * @brief Structure representing the configuration for the LCD.
 * 
 * @tparam M Specifies whether 4-bit or 8-bit mode is used.
 */
template<LcdMode M>
struct LCD_Config {
    using Pin  = stm32::dev::mcal::pin::Pin;
    using Port = stm32::dev::mcal::pin::Port;
    stm32::util::Array<Pin, M> dataPins;   /**< Array of data pins. */
    Port controlPort;                      /**< Port for control signals. */
    Pin RSpin;                             /**< RS pin (Register Select). */
    Pin RWpin;                             /**< RW pin (Read/Write select). */
    Pin ENpin;                             /**< Enable pin. */
};

/**
 * @brief Class to interface with the LCD display.
 * 
 * Provides methods to interact with the LCD, including printing text, numbers, 
 * clearing the screen, and managing the cursor and display shifts.
 * 
 * @tparam M Specifies the communication mode (4-bit or 8-bit).
 */
template<LcdMode M>
class Lcd {
 public:
    using Rows_t = uint8_t;
    using cols_t = uint8_t;

    /**
     * @brief Constructs an LCD object with the specified configuration.
     * 
     * @param config_ The configuration object specifying pin connections and mode.
     */
    explicit Lcd(const LCD_Config<M> &config_);

    /**
     * @brief Clears the screen of the LCD.
     */
    void ClearScreen();

    /**
     * @brief Prints a single character to the LCD.
     * 
     * @param character The character to print.
     */
    void Print(char character);

    /**
     * @brief Prints a string to the LCD.
     * 
     * @param str The string to print.
     */
    void Print(const std::string &str);

    /**
     * @brief Prints an integer to the LCD.
     * 
     * @param num The integer to print.
     */
    void Print(int32_t num);

    /**
     * @brief Prints a floating-point number to the LCD.
     * 
     * @param num The number to print.
     */
    void Print(double num);

    /**
     * @brief Sets the cursor position on the LCD.
     * 
     * @param rowNum The row number.
     * @param colNum The column number.
     */
    void SetPosition(Rows_t rowNum, cols_t colNum);

    /**
     * @brief Enables the cursor on the LCD.
     */
    void EnableCursor();

    /**
     * @brief Disables the cursor on the LCD.
     */
    void DisableCursor();

    /**
     * @brief Shifts the display content to the left.
     */
    void ShiftLeft();

    /**
     * @brief Shifts the display content to the right.
     */
    void ShiftRight();

    /**
     * @brief Turns the display on.
     */
    void DisplayOn();

    /**
     * @brief Turns the display off.
     */
    void DisplayOff();

    /**
     * @brief Enables blinking of the cursor.
     */
    void BlinkOn();

    /**
     * @brief Disables blinking of the cursor.
     */
    void BlinkOff();

 private:
    /**
     * @brief Initializes the LCD with the specified configuration.
     */
    void Init();

    /**
     * @brief Sends a falling-edge pulse to the Enable pin to latch data.
     */
    void SendFallingEdgePulse();

    /**
     * @brief Sends a command to the LCD.
     * 
     * @param command The command to send.
     */
    void SendCommand(uint32_t command);

    /**
     * @brief Sends data to the LCD.
     * 
     * @param data The data byte to send.
     */
    void SendData(uint8_t data);

    /**
     * @brief Writes output data to the configured data pins.
     * 
     * @param value The byte value to write to the pins.
     */
    void WriteOutputPins(uint8_t value);

    LCD_Config<M> config_;   /**< LCD configuration. */
};
}   //  namespace lcd
}   //  namespace hal
}   //  namespace dev
}   //  namespace stm32
#endif  //  DEV_INC_HAL_LCD_H_
