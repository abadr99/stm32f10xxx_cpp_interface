/**
 * @file EXTI.h
 * @author Manar
 * @brief 
 * @version 0.1
 * @date 2024-04-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef DEV_MCAL_INC_EXTI_H_
#define DEV_MCAL_INC_EXTI_H_

using namespace stm32::dev::mcal::pin;
using namespace stm32::utils::types;
namespace stm32 {
namespace dev {
namespace mcal {
namespace exti {


enum class Line {
    kEXTI0,
    kEXTI1,
    kEXTI2,
    kEXTI3,    
    kEXTI4,
    kEXTI5,
    kEXTI6,
    kEXTI7,
    kEXTI8,
    kEXTI9,
    kEXTI10,
    kEXTI11,
    kEXTI12,
    kEXTI13,
    kEXTI14,
    kEXTI15,
    kEXTI16,
    kEXTI17,
    kEXTI18,
    kEXTI19
};

enum class Trigger {
    kRising,
    kFalling,
    kBoth
};

struct EXTI_Config {
    Port port;
    Line line;
    Trigger trigger;
};
/**
 * @brief : Manage EXTIx.
 * @note  : Don't forget to Enable NVIC Befor Using EXTIx.
 */
class Exti {
 public:
    static void Enable(const EXTI_Config& config);
    static void Disable(const EXTI_Config& config);
    static void SetPendingFlag(const EXTI_Config& config);
    static void ClearPendingFlag(const EXTI_Config& config);
    uint8_t GetPendingFlag(const EXTI_Config& config);
    static void SetpCallBackFunction(Line line , void (*pCallBackFun)(void));
    static pFunction GetpCallBackFunction(Line line);
 private:
    static pFunction pGlobalCallBackFunctions[7];
    static void Helper_InitAFIOReg(Line line, Port port);
    static void Helper_SetTrigger(Line line, Trigger trigger);
    static void Helper_ClrTrigger(Line line, Trigger trigger);
    static uint8_t Helper_GetPendingBit(Line line);
};

}  // namespace exti
}  // namespace mcal
}  // namespace dev
}  // namespace stm32
#endif  //  DEV_MCAL_INC_EXTI_H_
