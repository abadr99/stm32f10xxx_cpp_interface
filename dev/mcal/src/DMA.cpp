/**
 * @file DMA.cpp
 * @author Noura & MRefat
 * @brief 
 * @version 0.1
 * @date 2024-07-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "mcal/inc/stm32f103xx.h"
#include "utils/inc/Types.h"
#include "Assert.h"
#include "DMA.h"

using namespace stm32::registers::dma;
using namespace stm32::dev::mcal::dma;


#define DMA_ENABLE(channel)                                 (DMA->CHANNEL[channel].CCR.EN = 1)
#define DMA_DISABLE(channel)                                (DMA->CHANNEL[channel].CCR.EN = 0)
#define DMA_SET_MODE(channel, mode)                         (DMA->CHANNEL[channel].CCR.CIRC = mode)
#define DMA_SET_PERIPHERAL_SIZE(channel, size)              (DMA->CHANNEL[channel].CCR.PSIZE = size)
#define DMA_SET_MEMORY_SIZE(channel, size)                  (DMA->CHANNEL[channel].CCR.MSIZE = size)
#define DMA_SET_PERIPHERAL_SRC_INC_STATE(channel, state)    (DMA->CHANNEL[channel].CCR.PINC = state)
#define DMA_SET_MEMORY_SRC_INC_STATE(channel, state)        (DMA->CHANNEL[channel].CCR.MINC = state)
#define DMA_SET_CHANNEL_PRIORITY(channel, priority)         (DMA->CHANNEL[channel].CCR.PL = priority)   //  NOLINT
#define DMA_SET_TRANSFER_ERROR_INT_STATE(channel, state)    (DMA->CHANNEL[channel].CCR.TEIE = state)
#define DMA_SET_TRANSFER_COMPLETE_INT_STATE(channel, state) (DMA->CHANNEL[channel].CCR.TCIE = state)

#define CHECK_CONFIG()\
    STM32_ASSERT(config.channel >= kCH1 && config.channel <= kCH7);\
    STM32_ASSERT(config.dir >= kMEM2MEM && config.dir <= kPER2MEM);\
    STM32_ASSERT(config.mode >= kNoCircular && config.mode <= kCircular);\
    STM32_ASSERT(config.periphIncState >= kDisable && config.periphIncState <= kEnable);\
    STM32_ASSERT(config.memIncState >= kDisable && config.memIncState <= kEnable);\
    STM32_ASSERT(config.memoryDataSize >= k8bit && config.memoryDataSize <= k32bit);\
    STM32_ASSERT(config.peripheralDataSize >= k8bit && config.peripheralDataSize <= k32bit);\
    STM32_ASSERT(config.channelPriority >= kLow && config.channelPriority <= kVeryHigh);


inline void helper_SetDirection(Channel dmaChannel, Direction dmaDirection) {
    switch (dmaDirection) {
        case kMEM2MEM : DMA->CHANNEL[dmaChannel].CCR.MEM2MEM = 1; break;
        case kMEM2PER : DMA->CHANNEL[dmaChannel].CCR.DIR = 1;     break;
        case kPER2MEM : DMA->CHANNEL[dmaChannel].CCR.DIR = 0;     break;
        default       : return;
    }
}

void Dma::Init(const DMAConfig& config) {
    CHECK_CONFIG();

    DMA_DISABLE(config.channel);

    helper_SetDirection(config.channel, config.dir);

    DMA_SET_MODE(config.channel, config.mode);
    
    DMA_SET_PERIPHERAL_SRC_INC_STATE(config.channel, config.periphIncState);
    
    DMA_SET_MEMORY_SRC_INC_STATE(config.channel, config.memIncState);

    DMA_SET_PERIPHERAL_SIZE(config.channel, config.peripheralDataSize);
    
    DMA_SET_PERIPHERAL_SIZE(config.channel, config.memoryDataSize);

    DMA_SET_CHANNEL_PRIORITY(config.channel, config.channelPriority);

    DMA_SET_TRANSFER_COMPLETE_INT_STATE(config.channel, config.transCompInterrupt);

    DMA_SET_TRANSFER_ERROR_INT_STATE(config.channel,    config.transErrInterrupt);
}
void Dma::Transfer(const DMAConfig& config, const uint32_t &srcAdd, const uint32_t &disAdd, uint16_t numOfData) {    //NOLINT
    if (config.dir == kMEM2PER) {
        DMA->CHANNEL[config.channel].CMAR = srcAdd;
        DMA->CHANNEL[config.channel].CPAR = disAdd;
    } else {
        DMA->CHANNEL[config.channel].CPAR = srcAdd;
        DMA->CHANNEL[config.channel].CMAR = disAdd;
    }
    DMA->CHANNEL[config.channel].CNDTR = numOfData;
    DMA->CHANNEL[config.channel].CCR.EN = 0;
}

void Dma::Enable(Channel dmaChannel) {
    STM32_ASSERT(dmaChannel >= kCH1 && dmaChannel <= kCH7);
    DMA_ENABLE(dmaChannel);
}

void Dma::Disable(Channel dmaChannel) {
    STM32_ASSERT(dmaChannel >= kCH1 && dmaChannel <= kCH7);
    DMA_DISABLE(dmaChannel);
}
