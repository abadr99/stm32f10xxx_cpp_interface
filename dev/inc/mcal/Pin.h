/**
 * @file Pin.h
 * @brief
 * @version 0.1
 * @date 2024-03-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef DEV_INC_MCAL_PIN_H_
#define DEV_INC_MCAL_PIN_H_
#include "utils/BitSet.h"
namespace stm32 {
namespace dev   {
namespace mcal  {
namespace pin   {
    
/**
 * @enum PinMode
 * @brief Specifies different modes for GPIO pins.
 * 
 * This enum defines the possible modes for a pin, including input, output, 
 * and analog modes with different configurations such as push-pull, open-drain, 
 * and alternative function.
 */
enum class PinMode : uint8_t {
    kAnalog,                            /**< Pin conf. as Analog input/output. */
    kOutputPushPull_10MHz,              /**< Pin conf. as Output push-pull, 10 MHz. */
    kOutputPushPull_2MHz,               /**< Pin conf. as Output push-pull, 2 MHz. */
    kOutputPushPull_50MHz,              /**< Pin conf. as Output push-pull, 50 MHz. */
    kInputFloat,                        /**< Pin conf. as Input floating. */
    kOutputOpenDrain_10MHz,             /**< Pin conf. as Output open-drain, 10 MHz. */
    kOutputOpenDrain_2MHz,              /**< Pin conf. as Output open-drain, 2 MHz. */
    kOutputOpenDrain_50MHz,             /**< Pin conf. as Output open-drain, 50 MHz. */
    kInputPullUp,                       /**< Pin conf. as Input with pull-up. */
    kAlternativePushPull_10MHz,         /**< Pin conf. as Alternate function push-pull, 10 MHz. */
    kAlternativePushPull_2MHz,          /**< Pin conf. as Alternate function push-pull, 2 MHz. */
    kAlternativePushPull_50MHz,         /**< Pin conf. as Alternate function push-pull, 50 MHz. */
    kAlternativeOpenDrain_10MHz = 13,   /**< Pin conf. as Alternate function open-drain, 10 MHz. */
    kAlternativeOpenDrain_2MHz,         /**< Pin conf. as Alternate function open-drain, 2 MHz. */
    kAlternativeOpenDrain_50MHz,        /**< Pin conf. as Alternate function open-drain, 50 MHz. */
    kInputPullDown = 20                 /**< Pin conf. as Input with pull-down. */
};

/**
 * @enum PinNumber
 * @brief Specifies the pin numbers available on a port.
 */
enum PinNumber : uint8_t {
    kPin0,    /**< Pin 0. */
    kPin1,    /**< Pin 1. */
    kPin2,    /**< Pin 2. */
    kPin3,    /**< Pin 3. */
    kPin4,    /**< Pin 4. */
    kPin5,    /**< Pin 5. */
    kPin6,    /**< Pin 6. */
    kPin7,    /**< Pin 7. */
    kPin8,    /**< Pin 8. */
    kPin9,    /**< Pin 9. */
    kPin10,   /**< Pin 10. */
    kPin11,   /**< Pin 11. */
    kPin12,   /**< Pin 12. */
    kPin13,   /**< Pin 13. */
    kPin14,   /**< Pin 14. */
    kPin15    /**< Pin 15. */
};

/**
 * @enum Port
 * @brief Defines the available GPIO ports.
 * 
 * Each port contains multiple pins (usually 16 pins). This enum allows 
 * selecting between different GPIO ports (A, B, C).
 */
enum Port : uint8_t {
    kPortA,   /**< GPIO Port A. */
    kPortB,   /**< GPIO Port B. */
    kPortC    /**< GPIO Port C. */
};

/**
 * @class Pin
 * @brief Provides an abstraction for handling GPIO pin configuration.
 * 
 * The Pin class encapsulates the configuration of a GPIO pin, including its 
 * port, pin number, and mode. It provides methods for setting and getting 
 * these configurations, as well as for checking the mode type (input, output, etc.).
 */
class Pin {
 public:
    /**
     * @brief Default constructor for Pin.
     * 
     * Initializes the Pin object with no specific configuration.
     */
    Pin() : data_(0) {}

    /**
     * @brief Parameterized constructor to initialize a Pin with specific configuration.
     * 
     * @param port The port to which the pin belongs (Port A, B, C).
     * @param pinNumber The pin number within the port (0-15).
     * @param pinMode The mode in which the pin is configured.
     */
    Pin(Port port, PinNumber pinNumber, PinMode pinMode);

    /**
     * @brief Sets the port for the Pin.
     * 
     * @param port The port to be set (Port A, B, C).
     */
    void SetPort(Port port);

    /**
     * @brief Sets the pin number for the Pin.
     * 
     * @param pinNumber The pin number to be set (0-15).
     */
    void SetPinNumber(PinNumber pinNumber);

    /**
     * @brief Sets the mode for the Pin.
     * 
     * @param pinMode The mode to be set for the pin (e.g., input, output, analog).
     */
    void SetPinMode(PinMode pinMode);

    /**
     * @brief Retrieves the port of the Pin.
     * 
     * @return The current port of the Pin (Port A, B, C).
     */
    Port GetPort();

    /**
     * @brief Retrieves the port of the Pin (const version).
     * 
     * @return The current port of the Pin (Port A, B, C).
     */
    Port GetPort() const;

    /**
     * @brief Retrieves the pin number of the Pin.
     * 
     * @return The current pin number (0-15).
     */
    PinNumber GetPinNumber();

    /**
     * @brief Retrieves the pin number of the Pin (const version).
     * 
     * @return The current pin number (0-15).
     */
    PinNumber GetPinNumber() const;

    /**
     * @brief Retrieves the mode of the Pin.
     * 
     * @return The current mode of the Pin (e.g., input, output, analog).
     */
    PinMode GetPinMode();

    /**
     * @brief Retrieves the mode of the Pin (const version).
     * 
     * @return The current mode of the Pin (e.g., input, output, analog).
     */
    PinMode GetPinMode() const;

    /**
     * @brief Checks if the pin is configured as input.
     * 
     * @return True if the pin is in input mode, false otherwise.
     */
    bool IsInput();

    /**
     * @brief Checks if the pin is configured as input (const version).
     * 
     * @return True if the pin is in input mode, false otherwise.
     */
    bool IsInput() const;

    /**
     * @brief Checks if the pin is configured as output.
     * 
     * @return True if the pin is in output mode, false otherwise.
     */
    bool IsOutput();

    /**
     * @brief Checks if the pin is configured as output (const version).
     * 
     * @return True if the pin is in output mode, false otherwise.
     */
    bool IsOutput() const;

    /**
     * @brief Checks if the pin is configured as an alternative function.
     * 
     * @return True if the pin is in an alternative function mode, false otherwise.
     */
    bool IsAlternative();

    /**
     * @brief Checks if the pin is configured as an alternative function (const version).
     * 
     * @return True if the pin is in an alternative function mode, false otherwise.
     */
    bool IsAlternative() const;

    /**
     * @brief Checks if the pin is configured as analog.
     * 
     * @return True if the pin is in analog mode, false otherwise.
     */
    bool IsAnalog();

    /**
     * @brief Checks if the pin is configured as analog (const version).
     * 
     * @return True if the pin is in analog mode, false otherwise.
     */
    bool IsAnalog() const;

 private:
    /**
     * @brief Holds the pin configuration data.
     * 
     * This data contains information about the port, pin number, and mode:
     *   - Bits 0-1: Port
     *   - Bits 2-5: Pin number
     *   - Bits 6-9: Pin mode
     */
    using DataType = stm32::util::BitSet<uint16_t>;
    DataType data_;
};

}   // namespace pin
}   // namespace mcal
}   // namespace dev
}   // namespace stm32

#endif   // DEV_INC_MCAL_PIN_H_
