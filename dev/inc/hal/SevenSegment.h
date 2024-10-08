/**
 * @file SevenSegment.h
 * @author
 * @brief
 * @version 0.1
 * @date 2024-07-7
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef DEV_INC_HAL_SEVENSEGMENT_H_
#define DEV_INC_HAL_SEVENSEGMENT_H_

#include "mcal/Pin.h"
#include "utils/Array.h"

using namespace stm32::dev::mcal::pin;

namespace stm32 {
namespace dev {
namespace hal {
namespace ssd {

/**
 * @brief Enum representing the display values for a seven-segment display.
 * 
 * These hex codes represent the segment configurations for digits 0 through 9.
 */
enum SSdDisplay: uint8_t {
    kZero  = 0x3F,  /**< Display '0' */
    kOne   = 0x06,  /**< Display '1' */
    kTwo   = 0x5B,  /**< Display '2' */
    kThree = 0x4F,  /**< Display '3' */
    kFour  = 0x66,  /**< Display '4' */
    kFive  = 0x6D,  /**< Display '5' */
    kSix   = 0x7D,  /**< Display '6' */
    kSeven = 0x07,  /**< Display '7' */
    kEight = 0x7F,  /**< Display '8' */
    kNine  = 0x6F,  /**< Display '9' */
};

/**
 * @brief Seven-Segment display driver class.
 * 
 * This class provides methods to control a seven-segment display, including enabling/disabling the display
 * and sending a digit to be displayed.
 * 
 * @tparam connectionType The type of connection for the display (e.g., common anode or common cathode).
 */
template<stm32::type::ConnectionType connectionType>
class SevenSegment {
 public:
    /**< Type alias for an array of pins for the data segments. */
    using Array_t = stm32::util::Array<Pin, 7>;

    /**
     * @brief Constructs a Seven-Segment display object with a given data pin array and enable pin.
     * 
     * @param dataPins Array of pins for the data segments (A-G).
     * @param enablePin Pin for enabling the seven-segment display.
     */
    SevenSegment(const Array_t& dataPins, const Pin& enablePin);  

    /**
     * @brief Constructs a Seven-Segment display object with only data pins.
     * 
     * @param dataPins Array of pins for the data segments (A-G).
     */
    explicit SevenSegment(const Array_t& dataPins);  

    /**
     * @brief Initializes the Seven-Segment display.
     */
    void Init();

    /**
     * @brief Enables the Seven-Segment display.
     */
    void Enable();

    /**
     * @brief Disables the Seven-Segment display.
     */
    void Disable();

    /**
     * @brief Sends a number to be displayed on the Seven-Segment display.
     * 
     * @param num The number to be displayed (0-9).
     */
    void SendNumber(SSdDisplay num);

 private:
    Array_t dataPins_;          /**< Array of pins for the data segments. */
    Pin     enablePin_;         /**< Pin for enabling the display. */
    bool    isEnablePinUsed_;   /**< Flag indicating if the enable pin is used. */
};
}  // namespace ssd
}  // namespace hal
}  // namespace dev
}  // namespace stm32
#endif  // DEV_INC_HAL_SEVENSEGMENT_H_
