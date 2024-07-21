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
    kDMA_Channel1,
    kDMA_Channel2,
    kDMA_Channel3,
    kDMA_Channel4,
    kDMA_Channel5,
    kDMA_Channel6,
    kDMA_Channel7,
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
enum State : uint8_t {
    kDMA_Disable,
    kDMA_Enable,
};
enum Size : uint8_t {
    k8bit,
    k16bit,
    k32bit,
};
enum Priority : uint8_t {
    kDMA_Low,
    kDMA_Medium,
    kDMA_High,
    kDMA_VeryHigh,
};
struct DMAConfig {
    Channel channel;
    Direction dir;
    Mode mode;
    uint32_t sourceBaseAddr;
    uint32_t destinationBaseAddr;
    Size bufferSize;
    State periphIncState;
    State memIncState;
    Size peripheralDataSize;
    Size memoryDataSize;
    Priority channelPriority;
    State transErrInterrupt;
    State transCompInterrupt;
};
class Dma {
 public:
static void Init(const DMAConfig& config);
static void Enable(Channel dmaChannel);
static void Disable(Channel dmaChannel);
static pFunction Helper_GetPointerToTransferCompleteISR(Channel channel);
static pFunction Helper_GetPointerToTransferErrorISR(Channel channel);
 private:
static pFunction PointerToTransferCompleteISR[7];
static pFunction PointerToTransferErrorISR[7];
static void Helper_SetPointerToTransferCompleteISR(Channel channel, pFunction func);
static void Helper_SetPointerToTransferErrorISR(Channel channel, pFunction func);
};
}   // namespace dma
}   // namespace mcal
}   // namespace dev
}   // namespace stm32
#endif  // DEV_MCAL_INC_DMA_H_
