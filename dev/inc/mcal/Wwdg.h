/**
 * @file Wwdg.h
 * @brief 
 * @version 0.1
 * @date 2024-05-1
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef DEV_INC_MCAL_WWDG_H_
#define DEV_INC_MCAL_WWDG_H_

namespace stm32 {
namespace dev   {
namespace mcal  {
namespace wwdg  {

/**
 * @enum Prescaler
 * @brief Enumeration for the WWDG prescaler values.
 * 
 * These prescaler values determine the division factor for the WWDG clock.
 */
enum Prescaler {
    kDiv2,   /**< Divide clock by 2 */
    kDiv4,   /**< Divide clock by 4 */
    kDiv6,   /**< Divide clock by 6 */
    kDiv8    /**< Divide clock by 8 */
};

/**
 * @struct Config
 * @brief Structure representing the WWDG configuration settings.
 * 
 * This structure contains parameters for the window value, counter value, and prescaler.
 */
struct Config {
    uint8_t windowValue;   /**< Window value for WWDG */
    uint8_t counterValue;  /**< Counter value for WWDG */
    Prescaler prescaler;   /**< Prescaler value for WWDG clock division */
};

/**
 * @class Wwdg
 * @brief Class for configuring and controlling the Window Watchdog (WWDG) peripheral.
 * 
 * This class provides methods for initializing the WWDG with a configuration structure,
 * enabling and disabling interrupts, and managing the early wakeup flag.
 */
class Wwdg {
 public:
    /**
     * @brief Constructs a WWDG object with the specified configuration.
     * 
     * @param config Reference to a Config structure containing the configuration settings.
     */
    explicit Wwdg(const Config& config);

    /**
     * @brief Enables the WWDG early wakeup interrupt.
     */
    void EnableInterrupt();

    /**
     * @brief Disables the WWDG early wakeup interrupt.
     */
    void DisableInterrupt();

    /**
     * @brief Checks if the early wakeup flag is set.
     * 
     * @return true if the early wakeup flag is set, false otherwise.
     */
    bool IsEarlyWakeupFlagSet();

    /**
     * @brief Clears the early wakeup flag.
     */
    void ClearEarlyWakeupFlag();

  private:
    static volatile stm32::registers::wwdg:: WWDGRegDef* WWDG;
    Config config_;  /**< Configuration settings for the WWDG peripheral */

    /**
     * @brief Initializes the WWDG peripheral with the provided configuration.
     */
    void Init();
};

}   //  namespace wwdg
}   //  namespace mcal
}   //  namespace dev
}   //  namespace stm32

#endif  // DEV_INC_MCAL_WWDG_H_ 
