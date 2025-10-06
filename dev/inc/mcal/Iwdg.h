/**
 * @file Iwdg.h
 * @author Manar Abdelraouf
 * @brief 
 * @version 0.1
 * @date 2024-07-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef DEV_INC_MCAL_IWDG_H_
#define DEV_INC_MCAL_IWDG_H_

namespace stm32 {
namespace dev {
namespace mcal {
namespace iwdg {
/**
 * @brief Enum representing the prescaler values for the IWDG.
 */
enum Prescaler {
    kDiv4,     /**< Divide clock by 4 */
    kDiv8,     /**< Divide clock by 8 */
    kDiv16,    /**< Divide clock by 16 */
    kDiv32,    /**< Divide clock by 32 */
    kDiv64,    /**< Divide clock by 64 */
    kDiv128,   /**< Divide clock by 128 */
    kDiv256    /**< Divide clock by 256 */
};

/**
 * @brief Class to manage the Independent Watchdog (IWDG).
 * 
 * This class allows initializing the IWDG and refreshing the watchdog 
 * to prevent system reset. The prescaler and reload value must be configured 
 * at the time of initialization.
 */
class Iwdg {
 public:
    using IWDGRegDef = stm32::registers::iwdg::IWDGRegDef;
    template<typename T>
    static volatile T* GetPtr();
    /**
     * @brief Constructor to initialize the IWDG with the specified prescaler and reload value.
     * 
     * @param prescaler The prescaler value to divide the IWDG clock.
     * @param reloadVal The reload value to set the watchdog counter (max value: 4095).
     * 
     * @note The reload value determines the timeout period before the watchdog resets the system.
     */
    static void Init();
    Iwdg(Prescaler prescaler, uint16_t reloadVal);

    /**
     * @brief Refreshes the watchdog timer to prevent a reset.
     * 
     * This function must be called periodically to reset the watchdog counter 
     * and avoid a system reset.
     */
    void Refresh();
    
 private:
    static stm32::type::RegType<IWDGRegDef>::ptr IWDG;
}; 

}   //  namespace iwdg
}   //  namespace mcal
}   //  namespace dev
}   //  namespace stm32



#endif  // DEV_INC_MCAL_IWDG_H_
