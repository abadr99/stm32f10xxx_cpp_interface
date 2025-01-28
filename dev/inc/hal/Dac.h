/**
 * @file DAC.h
 * @author noura36
 * @brief
 * @version 0.1
 * @date 2024-07-25
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef DEV_INC_HAL_DAC_H_
#define DEV_INC_HAL_DAC_H_

using namespace stm32::dev::mcal::pin; 
using namespace stm32::util;
using namespace stm32::dev::mcal::systick;
using namespace stm32::type;
namespace stm32 {
namespace dev {
namespace hal {
namespace dac {

/**
 * @class Dac
 * @brief Class for configuring and controlling the DAC peripheral.
 */
class Dac {
 public:
    /**
     * @brief Constructs a DAC object and initializes the DAC pins and clock source.
     *
     * @param dacPins An array of pins used by the DAC.
     * @param clock The clock source used for DAC operations.
     */
    Dac(const util::Array<Pin, 8>& dacPins, CLKSource clock);
    /**
     * @brief Plays audio data through the DAC.
     *
     * @param songRaw A pointer to the raw audio data.
     * @param songLength The length of the audio data array.
     */
    void DAC_Play(uint32_t* songRaw, uint32_t songLength);

 private:
    Array<Pin, 8> dacPins_;   /**< Array of DAC pins */
    CLKSource clock_;         /**< DAC clock source */  
    /**
     * @brief Initializes the pins used by the DAC.
     */
    void InitializePins();
};
}   // namespace dac
}   // namespace hal
}   // namespace dev
}   // namespace stm32
#endif  // DEV_INC_HAL_DAC_H_
