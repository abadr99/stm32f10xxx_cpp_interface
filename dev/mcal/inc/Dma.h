/**
 * @file DMA.h
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

using namespace stm32::utils::types;
namespace stm32 {
namespace dev   {
namespace mcal  {
namespace dma   {

enum Channel : uint8_t {
    kChannel1,
    kChannel2,
    kChannel3,
    kChannel4,
    kChannel5,
    kChannel6,
    kChannel7,
};
enum Direction : uint8_t {
    kMem2Mem,
    kMem2Per,
    kPer2Mem,
};
/**
 * @note: The circular buffer mode cannot be used if the memory-to-memory data transfer is configured on the selected Channel
 */
enum Mode : uint8_t {
    kNoCircular,
    kCircular,
};
enum State : uint8_t {
    kDisable,
    kEnable,
};
enum Size : uint8_t {
    k8bit,
    k16bit,
    k32bit,
};
enum Priority : uint8_t {
    kLow,
    kMedium,
    kHigh,
    kVeryHigh,
};
struct DMAConfig {
    Channel channel;
    Direction dir;
    Mode mode;
    uint32_t sourceBaseAddr;
    uint32_t destinationBaseAddr;
    Size bufferSize;
    State peripheralIncrementState;
    State memIncrementState;
    Size peripheralDataSize;
    Size memoryDataSize;
    Priority channelPriority;
    State transErrorInterrupt;
    State transCompleteInterrupt;
};
class Dma {
 public:
    static void Init(const DMAConfig& config);
    static void Enable(Channel dmaChannel);
    static void Disable(Channel dmaChannel);
    static void SetPointerToTransferCompleteISR(Channel channel, pFunction func);
    static void SetPointerToTransferErrorISR(Channel channel, pFunction func);
    static pFunction GetPointerToTransferCompleteISR(Channel channel);
    static pFunction GetPointerToTransferErrorISR(Channel channel);
 private:
    static pFunction PointerToTransferCompleteISR[7];
    static pFunction PointerToTransferErrorISR[7];
};

}   // namespace dma
}   // namespace mcal
}   // namespace dev
}   // namespace stm32
#endif  // DEV_MCAL_INC_DMA_H_
