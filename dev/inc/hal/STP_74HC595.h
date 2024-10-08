/**
 * @file STP_74HC595.h
 * @author 
 * @brief 
 * @version 0.1
 * @date 2024-07-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef DEV_INC_HAL_STP_74HC595_H_
#define DEV_INC_HAL_STP_74HC595_H_

namespace stm32 {
namespace dev {
namespace hal {
namespace shift_register {
/**
 * @brief Shift register driver for the STP 74HC595.
 * 
 * This class provides methods to control a 74HC595 shift register, allowing
 * data to be shifted out to control multiple output pins using fewer GPIO pins.
 * 
 * @note This class requires initializing the SysTick peripheral.
 * @todo Support for multiple shift registers.
 */
class STP_74HC595 {
 public:
    /**< Type alias for Pin used in the driver. */
    using Pin = stm32::dev::mcal::pin::Pin;
    /**< Type alias for the width of the shift register value. */
    using ShiftRegisterWidth = uint8_t;
    
    /**
     * @brief Constructs an STP_74HC595 object with specified control pins.
     * 
     * @param serialInputPin Pin used for serial data input.
     * @param shiftClkPin Pin used for the shift clock.
     * @param storageClk Pin used for the storage clock.
     */
    STP_74HC595(const Pin& serialInputPin, 
                const Pin& shiftClkPin, 
                const Pin& storageClk);

    /**
     * @brief Writes a value to the shift register.
     * 
     * @param val The value to be shifted out to the register.
     */
    void Write(ShiftRegisterWidth val);

 private:
    struct Pins {
        Pin serialInputPin;   /**< Pin for serial data input. */
        Pin shiftClkPin;      /**< Pin for shift clock. */
        Pin storageClkPin;    /**< Pin for storage clock. */
    };
    
    Pins pins_;               /**< Structure holding pin configurations. */
    void Pulse();             /**< Sends a pulse to the shift register. */
    void InitializePins();    /**< Initializes the pins for the shift register. */
};


}  // namespace shift_register
}  // namespace hal
}  // namespace dev
}  // namespace stm32

#endif  // DEV_INC_HAL_STP_74HC595_H_

