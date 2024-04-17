/**
 * @file Nvic.h
 * @brief
 * @version 0.1
 * @date 2024-04-17
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef DEV_MCAL_INC_NVIC_H_
#define DEV_MCAL_INC_NVIC_H_
namespace stm32 {
namespace dev   {
namespace mcal  {
namespace nvic   {
class nvic {
 public:
static void EnableInterrupt(uint8_t interruptID);
static void DisableInterrupt(uint8_t interruptID);
static void SetPendingFlag(uint8_t interruptID);
static void ClearPendingFlag(uint8_t interruptID);
static uint8_t GetActiveFlag(uint8_t interruptID);
};
}   // namespace nvic
}   // namespace mcal
}   // namespace dev
}   // namespace stm32
#endif   // DEV_MCAL_INC_NVIC_H_
