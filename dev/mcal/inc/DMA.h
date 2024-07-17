/**
 * @file EXTI.h
 * @author Noura & MRefat
 * @brief 
 * @version 0.1
 * @date 2024-07-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef DEV_MCAL_INC_DMA_H_
#define DEV_MCAL_INC_DMA_H_

namespace stm32 {
namespace dev   {
namespace mcal  {
namespace dma   {

enum Channel : uint8_t {
    kCH1,
    kCH2,
    kCH3,
    kCH4,
    kCH5,
    kCH6,
    kCH7,
};
enum Direction : uint8_t {
    kMEM2MEM,
    kMEM2PER,
    kPER2MEM,
};
/**
 * @note: The circular buffer mode cannot be used if the memory-to-memory data transfer is configured on the selected Channel
 */
enum Mode : uint8_t {
    kNoCircular,
    kCircular,
};
enum Increment : uint8_t {
    kEnable,
    kDisable,
};
enum Size : uint8_t {
    k8bit,
    k16bit,
    k32bit,
};
enum Priorty : uint8_t {
    kLow,
    kMedium,
    kHigh,
    kVeryHigh,
};
struct DMAConfig {
    Channel ch;
    Direction dir;
    Mode mode;
    Increment periInc;
    Increment memInc;
    Size perSize;
    Size memSize;
    Priorty chPriorty;
};
class Dma {
 public:
static void DMA_Init(const DMAConfig& config);
};
}   // namespace dma
}   // namespace mcal
}   // namespace dev
}   // namespace stm32
#endif  // DEV_MCAL_INC_DMA_H_
