/**
 * @file Exti.h
 * @author
 * @brief 
 * @version 0.1
 * @date 2024-04-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef DEV_INC_MCAL_EXTI_H_
#define DEV_INC_MCAL_EXTI_H_

namespace stm32 {
namespace dev {
namespace mcal { 
namespace exti {
    
/**
 * @brief Enumeration for EXTI lines.
 */
enum Line {
    kExti0,    /**< EXTI Line 0 */
    kExti1,    /**< EXTI Line 1 */
    kExti2,    /**< EXTI Line 2 */
    kExti3,    /**< EXTI Line 3 */
    kExti4,    /**< EXTI Line 4 */
    kExti5,    /**< EXTI Line 5 */
    kExti6,    /**< EXTI Line 6 */
    kExti7,    /**< EXTI Line 7 */
    kExti8,    /**< EXTI Line 8 */
    kExti9,    /**< EXTI Line 9 */
    kExti10,   /**< EXTI Line 10 */
    kExti11,   /**< EXTI Line 11 */
    kExti12,   /**< EXTI Line 12 */
    kExti13,   /**< EXTI Line 13 */
    kExti14,   /**< EXTI Line 14 */
    kExti15,   /**< EXTI Line 15 */
    kExti16,   /**< EXTI Line 16 */
    kExti17,   /**< EXTI Line 17 */
    kExti18,   /**< EXTI Line 18 */
    kExti19    /**< EXTI Line 19 */
};

/**
 * @brief Enumeration for EXTI trigger modes.
 */
enum Trigger {
    kRising,    /**< Trigger on rising edge. */
    kFalling,   /**< Trigger on falling edge. */
    kBoth       /**< Trigger on both rising and falling edges. */
};

/**
 * @brief Structure to hold the EXTI configuration parameters.
 */
struct EXTI_Config {
    using Port = stm32::dev::mcal::pin::Port;   /**< Alias for Port type. */
    Port port;    /**< GPIO port associated with the EXTI line. */
    Line line;    /**< EXTI line to configure. */
    Trigger trigger;    /**< Trigger mode for the EXTI line. */

    void SetConfig(Port p, Line l, Trigger t) {
        port = p;
        line = l;
        trigger = t;
    }
};

/**
 * @brief EXTI management class.
 * 
 * This class provides methods to configure and manage EXTI lines for handling external interrupts.
 * @note Don't forget to enable NVIC before using EXTI.
 */
class Exti {
 public:
    /**
     * @brief Typedef for a pointer to a callback function.
     */
    using pFunction = stm32::type::pFunction;
    using EXTIRegDef = stm32::registers::exti::EXTIRegDef;
    using AfioRegDef = stm32::registers::afio::AfioRegDef;

    template<typename T>
    static volatile T* GetPtr();

    /**
     * @brief Initialize the Exti
     * 
     */
    static void Init();

    /**
     * @brief Enables the EXTI line with the provided configuration.
     * 
     * @param config The EXTI configuration structure.
     */
    static void Enable(const EXTI_Config& config);

    /**
     * @brief Disables the EXTI line with the provided configuration.
     * 
     * @param config The EXTI configuration structure.
     */
    static void Disable(const EXTI_Config& config);

    /**
     * @brief Sets the pending flag for the EXTI line.
     * 
     * @param config The EXTI configuration structure.
     */
    static void SetPendingFlag(const EXTI_Config& config);

    /**
     * @brief Clears the pending flag for the EXTI line.
     * 
     * @param config The EXTI configuration structure.
     */
    static void ClearPendingFlag(const EXTI_Config& config);

    /**
     * @brief Gets the pending flag status for the EXTI line.
     * 
     * @param config The EXTI configuration structure.
     * @return true if the pending flag is set, false otherwise.
     */
    static bool GetPendingFlag(const EXTI_Config& config);

    /**
     * @brief Sets the callback function for a specific EXTI line.
     * 
     * @param line The EXTI line.
     * @param pCallBackFun The function pointer to the callback.
     */
    static void SetpCallBackFunction(Line line, void (*pCallBackFun)(void));

    /**
     * @brief Gets the callback function for a specific EXTI line.
     * 
     * @param line The EXTI line.
     * @return pFunction The function pointer to the callback.
     */
    static pFunction GetpCallBackFunction(Line line);

 private:
    static constexpr uint32_t kCallBackSiz = 7;
    using Port       = stm32::dev::mcal::pin::Port;
    static stm32::type::RegType<EXTIRegDef>::ptr EXTI;
    static volatile AfioRegDef* AFIO;
    static pFunction pGlobalCallBackFunctions[kCallBackSiz];

    /**
     * @brief Initializes the AFIO register for the specified EXTI line and port.
     * 
     * @param line The EXTI line.
     * @param port The GPIO port.
     */
    static void InitAFIOReg(Line line, Port port);

    /**
     * @brief Sets the trigger condition for the specified EXTI line.
     * 
     * @param line The EXTI line.
     * @param trigger The trigger mode.
     */
    static void SetTrigger(Line line, Trigger trigger);

    /**
     * @brief Clears the trigger condition for the specified EXTI line.
     * 
     * @param line The EXTI line.
     * @param trigger The trigger mode.
     */
    static void ClrTrigger(Line line, Trigger trigger);

    /**
     * @brief Gets the pending bit for the specified EXTI line.
     * 
     * @param line The EXTI line.
     * @return true if the pending bit is set, false otherwise.
     */
    static bool GetPendingBit(Line line);
};

}  // namespace exti
}  // namespace mcal
}  // namespace dev
}  // namespace stm32
#endif  //  DEV_INC_MCAL_EXTI_H_
