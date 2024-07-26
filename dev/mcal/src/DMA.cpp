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
#define DMA_SET_NUMBER_OF_DATA(channel, dataNum)            (DMA->CHANNEL[channel].CNDTR = dataNum)

#define CHECK_CONFIG()\
    STM32_ASSERT(config.channel >= kDMA_Channel1 && config.channel <= kDMA_Channel7);\
    STM32_ASSERT(config.dir >= kMEM2MEM && config.dir <= kPER2MEM);\
    STM32_ASSERT(config.mode >= kNoCircular && config.mode <= kCircular);\
    STM32_ASSERT(config.periphIncState >= kDMA_Disable && config.periphIncState <= kDMA_Enable);\
    STM32_ASSERT(config.memIncState >= kDMA_Disable && config.memIncState <= kDMA_Enable);\
    STM32_ASSERT(config.memoryDataSize >= k8bit && config.memoryDataSize <= k32bit);\
    STM32_ASSERT(config.peripheralDataSize >= k8bit && config.peripheralDataSize <= k32bit);\
    STM32_ASSERT(config.channelPriority >= kDMA_Low && config.channelPriority <= kDMA_VeryHigh);


inline void helper_SetDirection(Channel dmaChannel, Direction dmaDirection) {
    switch (dmaDirection) {
        case kMEM2MEM : DMA->CHANNEL[dmaChannel].CCR.MEM2MEM = 1; break;
        case kMEM2PER : DMA->CHANNEL[dmaChannel].CCR.DIR = 1;     break;
        case kPER2MEM : DMA->CHANNEL[dmaChannel].CCR.DIR = 0;     break;
        default       : return;
    }
}

pFunction Dma::PointerToTransferCompleteISR[7] = {nullptr};
pFunction Dma::PointerToTransferErrorISR[7] = {nullptr};

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

    // Configure Src and Dest base addresses
    if (config.dir == kMEM2PER) {
        DMA->CHANNEL[config.channel].CPAR = config.sourceBaseAddr;
        DMA->CHANNEL[config.channel].CMAR = config.destinationBaseAddr;
    } else {
        DMA->CHANNEL[config.channel].CPAR = config.sourceBaseAddr;
        DMA->CHANNEL[config.channel].CMAR = config.destinationBaseAddr;
    }
}

void Dma::Enable(Channel dmaChannel) {
    STM32_ASSERT(dmaChannel >= kDMA_Channel1 && dmaChannel <= kDMA_Channel7);
    DMA_ENABLE(dmaChannel);
}

void Dma::Disable(Channel dmaChannel) {
    STM32_ASSERT(dmaChannel >= kDMA_Channel1 && dmaChannel <= kDMA_Channel7);
    DMA_DISABLE(dmaChannel);
}

void Dma::SetPointerToTransferCompleteISR(Channel channel, pFunction func) {
    if (channel >= kDMA_Channel1 && channel <= kDMA_Channel7) {
        Dma::PointerToTransferCompleteISR[channel] = func;
    }
}

void Dma::SetPointerToTransferErrorISR(Channel channel, pFunction func) {
    if (channel >= kDMA_Channel1 && channel <= kDMA_Channel7) {
        Dma::PointerToTransferErrorISR[channel] = func;
    }
}

pFunction Dma::GetPointerToTransferCompleteISR(Channel channel) {
    return Dma::PointerToTransferCompleteISR[channel];
}

pFunction Dma::GetPointerToTransferErrorISR(Channel channel) {
    return Dma::PointerToTransferErrorISR[channel];
}

extern "C" void DMA_Channel1Handler(void) {
    if (DMA->ISR.TEIF1 == 1) {
        pFunction fun = Dma::GetPointerToTransferErrorISR(kDMA_Channel1);
        if (fun != NULL) {
            fun();
            // Clear flag
            DMA->IFCR.CTEIF1 = 1;
        }
    } else if (DMA->ISR.TCIF1 == 1) {
        pFunction fun = Dma::GetPointerToTransferCompleteISR(kDMA_Channel1);
        if (fun != NULL) {
            fun();
            // Clear flag
            DMA->IFCR.CTCIF1 = 1;
        }
    }
}
extern "C" void DMA_Channel2Handler(void) {
    if (DMA->ISR.TEIF2 == 1) {
        pFunction fun = Dma::GetPointerToTransferErrorISR(kDMA_Channel2);
        if (fun != NULL) {
            fun();
            DMA->IFCR.CTEIF2 = 1;
        }
    } else if (DMA->ISR.TCIF2 == 1) {
        pFunction fun = Dma::GetPointerToTransferCompleteISR(kDMA_Channel2);
        if (fun != NULL) {
            fun();
            DMA->IFCR.CTCIF2 = 1;
        }
    }
}
extern "C" void DMA_Channel3Handler(void) {
    if (DMA->ISR.TEIF3 == 1) {
        pFunction fun = Dma::GetPointerToTransferErrorISR(kDMA_Channel3);
        if (fun != NULL) {
            fun();
            DMA->IFCR.CTEIF3 = 1;
        }
    } else if (DMA->ISR.TCIF3 == 1) {
        pFunction fun = Dma::GetPointerToTransferCompleteISR(kDMA_Channel3);
        if (fun != NULL) {
            fun();
            DMA->IFCR.CTCIF3 = 1;
        }
    }
}
extern "C" void DMA_Channel4Handler(void) {
    if (DMA->ISR.TEIF4 == 1) {
        pFunction fun = Dma::GetPointerToTransferErrorISR(kDMA_Channel4);
        if (fun != NULL) {
            fun();
            DMA->IFCR.CTEIF4 = 1;
        }
    } else if (DMA->ISR.TCIF4 == 1) {
        pFunction fun = Dma::GetPointerToTransferCompleteISR(kDMA_Channel4);
        if (fun != NULL) {
            fun();
            DMA->IFCR.CTCIF4 = 1;
        }
    }
}
extern "C" void DMA_Channel5Handler(void) {
    if (DMA->ISR.TEIF5 == 1) {
        pFunction fun = Dma::GetPointerToTransferErrorISR(kDMA_Channel5);
        if (fun != NULL) {
            fun();
            DMA->IFCR.CTEIF5 = 1;
        }
    } else if (DMA->ISR.TCIF1 == 1) {
        pFunction fun = Dma::GetPointerToTransferCompleteISR(kDMA_Channel5);
        if (fun != NULL) {
            fun();
            DMA->IFCR.CTCIF5 = 1;
        }
    }
}
extern "C" void DMA_Channel6Handler(void) {
    if (DMA->ISR.TEIF6 == 1) {
        pFunction fun = Dma::GetPointerToTransferErrorISR(kDMA_Channel6);
        if (fun != NULL) {
            fun();
            DMA->IFCR.CTEIF6 = 1;
        }
    } else if (DMA->ISR.TCIF6 == 1) {
        pFunction fun = Dma::GetPointerToTransferCompleteISR(kDMA_Channel6);
        if (fun != NULL) {
            fun();
            DMA->IFCR.CTCIF6 = 1;
        }
    }
}
extern "C" void DMA_Channel7Handler(void) {
    if (DMA->ISR.TEIF7 == 1) {
        pFunction fun = Dma::GetPointerToTransferErrorISR(kDMA_Channel7);
        if (fun != NULL) {
            fun();
            DMA->IFCR.CTEIF7 = 1;
        }
    } else if (DMA->ISR.TCIF7 == 1) {
        pFunction fun = Dma::GetPointerToTransferCompleteISR(kDMA_Channel7);
        if (fun != NULL) {
            fun();
            DMA->IFCR.CTCIF7 = 1;
        }
    }
}
