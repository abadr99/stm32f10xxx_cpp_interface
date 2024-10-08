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
#ifndef DEV_INC_HAL_KEYPAD_H_
#define DEV_INC_HAL_KEYPAD_H_
using namespace stm32::dev::mcal::pin; 
using namespace stm32::dev::mcal::gpio;
namespace stm32 {
namespace dev {
namespace hal {
namespace keypad {

/**
 * @class Keypad
 * @brief Class to interface with a keypad matrix.
 * 
 * This class provides methods for initializing the rows and columns of the 
 * keypad, setting up the pins, and detecting which key is pressed.
 */
class Keypad {
 public:
    /**
     * @brief Constructs a Keypad object with the specified number of rows and columns.
     * 
     * @param numRows The number of rows in the keypad matrix.
     * @param numCols The number of columns in the keypad matrix.
     */
    Keypad(uint8_t numRows, uint8_t numCols);

    /**
     * @brief Destructor for the Keypad object.
     */
    ~Keypad();

    /**
     * @brief Sets the array of pins for the keypad rows.
     * 
     * @param rows Pointer to an array of Pin objects representing the row pins.
     */
    void SetRowArr(const Pin* rows);

    /**
     * @brief Sets the array of pins for the keypad columns.
     * 
     * @param cols Pointer to an array of Pin objects representing the column pins.
     */
    void setColArr(const Pin* cols);

    /**
     * @brief Initializes the keypad, configuring the row and column pins.
     */
    void Init();

    /**
     * @brief Detects and returns the pressed key on the keypad.
     * 
     * @param keypadButtons A pointer to a 2D array of button values representing the keypad layout.
     * @return The value of the pressed key, or 0 if no key is pressed.
     */
    uint8_t GetPressed(const uint8_t* const* keypadButtons);

 private:
    uint8_t rowsNum;   /**< Number of rows in the keypad matrix. */
    uint8_t colNum;    /**< Number of columns in the keypad matrix. */
    Pin* KeypadRow;    /**< Pointer to an array of Pin objects for the rows. */
    Pin* KeypadCol;    /**< Pointer to an array of Pin objects for the columns. */
};
}  // namespace keypad
}  // namespace hal
}  // namespace dev
}  // namespace stm32
#endif  //  DEV_INC_HAL_KEYPAD_H_
