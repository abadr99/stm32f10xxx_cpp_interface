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
#include "mcal/stm32f103xx.h"
#include "utils/Types.h"
#include "utils/Assert.h"
#include "mcal/Dma.h"

// --- IMPORT USED NAMESPACES
using namespace stm32::registers::dma;
using namespace stm32::dev::mcal::dma;
using namespace stm32::type;

#define TO_STRING(str_)  #str_

#define DMA_CONFIG_ERROR(error_) \
    TO_STRING(Invalid Dma error_)

// --- HELPER MACRO TO CHECK IF WE ARE USING CORRECT CONFIGURATIONS
#define CHECK_CONFIG()\
    STM32_ASSERT((config.channel >= kChannel1)\
              && (config.channel <= kChannel7), DMA_CONFIG_ERROR(Channel));\
    STM32_ASSERT((config.dir >= kMem2Mem)\
              && (config.dir <= kPer2Mem), DMA_CONFIG_ERROR(Direction));\
    STM32_ASSERT((config.mode >= kNoCircular)\
              && (config.mode <= kCircular), DMA_CONFIG_ERROR(Mode));\
    STM32_ASSERT((config.peripheralIncrementState >= kDisable)\
              && (config.peripheralIncrementState <= kEnable), DMA_CONFIG_ERROR(State));\
    STM32_ASSERT((config.memIncrementState >= kDisable)\
              && (config.memIncrementState <= kEnable), DMA_CONFIG_ERROR(State));\
    STM32_ASSERT((config.memoryDataSize >= k8bit)\
              && (config.memoryDataSize <= k32bit), DMA_CONFIG_ERROR(State));\
    STM32_ASSERT((config.peripheralDataSize >= k8bit)\
              && (config.peripheralDataSize <= k32bit), DMA_CONFIG_ERROR(Size));\
    STM32_ASSERT((config.channelPriority >= kLow)\
              && (config.channelPriority <= kVeryHigh), DMA_CONFIG_ERROR(Priority));

namespace helper {
    static inline void SetDirection(Channel dmaChannel, Direction dmaDirection) {
        switch (dmaDirection) {
            case kMem2Mem : 
                Dma::GetPtr()->CHANNEL[dmaChannel].CCR.MEM2MEM = 1;
                Dma::GetPtr()->CHANNEL[dmaChannel].CCR.DIR = 1;
            break;
            case kMem2Per : Dma::GetPtr()->CHANNEL[dmaChannel].CCR.DIR = 1;     break;
            case kPer2Mem : Dma::GetPtr()->CHANNEL[dmaChannel].CCR.DIR = 0;     break;
            default       : return;
        }
    }
}  // namespace helper

// --- INITIATE DMA STATIC DATA
pFunction Dma::PointerToTransferCompleteISR[7] = {nullptr};
pFunction Dma::PointerToTransferErrorISR[7] = {nullptr};
typename  Dma::RegType Dma::DMA = nullptr;

void Dma::Init(const DMAConfig& config) {
    CHECK_CONFIG();
    
    // --- 1] DISABLE DMA
    DMA->CHANNEL[config.channel].CCR.EN = 0;
    
    // --- 2] SET DIRECTION
    helper::SetDirection(config.channel, config.dir);
    
    // --- 3] SET APPROPRIATE MODE
    DMA->CHANNEL[config.channel].CCR.CIRC = config.mode;
    
    // --- 4] SET PERIPHERAL SOURCE/MEMORY INCREMENT STATE
    DMA->CHANNEL[config.channel].CCR.PINC = config.peripheralIncrementState;
    DMA->CHANNEL[config.channel].CCR.MINC = config.memIncrementState;
    
    // --- 5] SET PERIPHERAL SOURCE/MEMORY SIZE
    DMA->CHANNEL[config.channel].CCR.PSIZE = config.peripheralDataSize;
    DMA->CHANNEL[config.channel].CCR.MSIZE = config.memoryDataSize;
    
    // --- 6] SET CHANNEL PRIORITY
    DMA->CHANNEL[config.channel].CCR.PL = config.channelPriority;
    
    // --- 7] SET TRANSFER COMPLETE/ERROR INTERRUPT 
    DMA->CHANNEL[config.channel].CCR.TCIE = config.transCompleteInterrupt;
    DMA->CHANNEL[config.channel].CCR.TEIE = config.transErrorInterrupt;

    // --- 8] CONFIGURE SRC AND DST BASE ADDRESSES
    DMA->CHANNEL[config.channel].CPAR = config.dir == kMem2Per ? config.sourceBaseAddr
                                                               : config.destinationBaseAddr;
    DMA->CHANNEL[config.channel].CMAR = config.dir == kMem2Mem ? config.sourceBaseAddr
                                                               : config.destinationBaseAddr;

    // --- 9] SET SOURCE BUFFER ADDRESS
    DMA->CHANNEL[config.channel].CNDTR = config.bufferSize;
}

typename Dma::RegType Dma::GetPtr() {
    return DMA;
}

void Dma::Enable(Channel dmaChannel) {
    STM32_ASSERT((dmaChannel >= kChannel1) && (dmaChannel <= kChannel7), DMA_CONFIG_ERROR(Channel));
    DMA->CHANNEL[dmaChannel].CCR.EN = 1;
}

void Dma::Disable(Channel dmaChannel) {
    STM32_ASSERT((dmaChannel >= kChannel1) && (dmaChannel <= kChannel7), DMA_CONFIG_ERROR(Channel));
    DMA->CHANNEL[dmaChannel].CCR.EN = 0;
}

void Dma::SetPointerToTransferCompleteISR(Channel channel, pFunction func) {
    STM32_ASSERT((channel >= kChannel1) && (channel <= kChannel7), DMA_CONFIG_ERROR(Channel));
    Dma::PointerToTransferCompleteISR[channel] = func;
}

void Dma::SetPointerToTransferErrorISR(Channel channel, pFunction func) {
    STM32_ASSERT((channel >= kChannel1) && (channel <= kChannel7), DMA_CONFIG_ERROR(Channel));
    Dma::PointerToTransferErrorISR[channel] = func;
}

pFunction Dma::GetPointerToTransferCompleteISR(Channel channel) {
    return Dma::PointerToTransferCompleteISR[channel];
}

pFunction Dma::GetPointerToTransferErrorISR(Channel channel) {
    return Dma::PointerToTransferErrorISR[channel];
}

// TODO(@abadr99, @MRefat13): Check if this implementation will make debugging harder
#define DMA_CHANNEL_HANDLER(N)\
    extern "C" void DMA1_Channel##N##_IRQHandler(void) {\
        if (Dma::GetPtr()->ISR.TEIF##N == 1) {\
            pFunction fun = Dma::GetPointerToTransferErrorISR(kChannel##N);\
            if (fun != NULL) {\
                fun();\
                Dma::GetPtr()->IFCR.CTEIF##N = 1;\
            }\
        } else if (Dma::GetPtr()->ISR.TCIF##N == 1) {\
            pFunction fun = Dma::GetPointerToTransferCompleteISR(kChannel##N);\
            if (fun != NULL) {\
                fun();\
                Dma::GetPtr()->IFCR.CTCIF##N = 1;\
            }\
        }\
    }

DMA_CHANNEL_HANDLER(1)
DMA_CHANNEL_HANDLER(2)
DMA_CHANNEL_HANDLER(3)
DMA_CHANNEL_HANDLER(4)
DMA_CHANNEL_HANDLER(5)
DMA_CHANNEL_HANDLER(6)
DMA_CHANNEL_HANDLER(7)
