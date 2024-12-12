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
#ifndef DEV_INC_MCAL_DMA_H_
#define DEV_INC_MCAL_DMA_H_

namespace stm32 {
namespace dev   {
namespace mcal  {
namespace dma   {

/**
 * @brief Enumeration for DMA channels.
 */
enum Channel : uint8_t {
    kChannel1,  /**< DMA Channel 1. */
    kChannel2,  /**< DMA Channel 2. */
    kChannel3,  /**< DMA Channel 3. */
    kChannel4,  /**< DMA Channel 4. */
    kChannel5,  /**< DMA Channel 5. */
    kChannel6,  /**< DMA Channel 6. */
    kChannel7   /**< DMA Channel 7. */
};

/**
 * @brief Enumeration for DMA data transfer directions.
 */
enum Direction : uint8_t {
    kMem2Mem,   /**< Memory-to-memory transfer. */
    kMem2Per,   /**< Memory-to-peripheral transfer. */
    kPer2Mem    /**< Peripheral-to-memory transfer. */
};

/**
 * @brief Enumeration for DMA modes.
 * @note The circular buffer mode cannot be used if the memory-to-memory data transfer is configured on the selected channel.
 */
enum Mode : uint8_t {
    kNoCircular,    /**< Non-circular mode. */
    kCircular       /**< Circular mode. */
};

/**
 * @brief Enumeration for enabling/disabling states.
 */
enum State : uint8_t {
    kDisable,   /**< Disable the feature. */
    kEnable     /**< Enable the feature. */
};

/**
 * @brief Enumeration for DMA data sizes.
 */
enum Size : uint8_t {
    k8bit,      /**< 8-bit data size. */
    k16bit,     /**< 16-bit data size. */
    k32bit      /**< 32-bit data size. */
};

/**
 * @brief Enumeration for DMA channel priority levels.
 */
enum Priority : uint8_t {
    kLow,       /**< Low priority. */
    kMedium,    /**< Medium priority. */
    kHigh,      /**< High priority. */
    kVeryHigh   /**< Very high priority. */
};

/**
 * @brief Structure to hold the DMA configuration parameters.
 */
struct DMAConfig {
    Channel channel;                    /**< DMA channel selection. */
    Direction dir;                      /**< Direction of data transfer. */
    Mode mode;                          /**< Circular or non-circular mode. */
    uint32_t sourceBaseAddr;            /**< Source base address. */
    uint32_t destinationBaseAddr;       /**< Destination base address. */
    uint16_t bufferSize;                /**< Size of the data buffer. */
    State peripheralIncrementState;     /**< Enable or disable peripheral address increment. */
    State memIncrementState;            /**< Enable or disable memory address increment. */
    Size peripheralDataSize;            /**< Peripheral data size (8-bit, 16-bit, or 32-bit). */
    Size memoryDataSize;                /**< Memory data size (8-bit, 16-bit, or 32-bit). */
    Priority channelPriority;           /**< DMA channel priority. */
    State transErrorInterrupt;          /**< Enable or disable transfer error interrupt. */
    State transCompleteInterrupt;       /**< Enable or disable transfer complete interrupt. */
};

/**
 * @brief Class for controlling the DMA.
 */
class Dma {
 public:
    /**
     * @brief Typedef for a pointer to a function.
     */
    using pFunction = stm32::type::pFunction;
    using DmaRegDef = stm32::registers::dma::DMARegDef;
    using RegType   = stm32::type::RegType<DmaRegDef>::ptr;
    /**
     * @brief Initializes the DMA with the given configuration.
     * 
     * @param config The configuration settings for the DMA.
     */
    static void Init(const DMAConfig& config);
    static RegType GetPtr();
    /**
     * @brief Enables the specified DMA channel.
     * 
     * @param dmaChannel The DMA channel to be enabled.
     */
    static void Enable(Channel dmaChannel);

    /**
     * @brief Disables the specified DMA channel.
     * 
     * @param dmaChannel The DMA channel to be disabled.
     */
    static void Disable(Channel dmaChannel);

    /**
     * @brief Sets the pointer to the transfer complete ISR for the specified DMA channel.
     * 
     * @param channel The DMA channel.
     * @param func The function pointer to the ISR.
     */
    static void SetPointerToTransferCompleteISR(Channel channel, pFunction func);

    /**
     * @brief Sets the pointer to the transfer error ISR for the specified DMA channel.
     * 
     * @param channel The DMA channel.
     * @param func The function pointer to the ISR.
     */
    static void SetPointerToTransferErrorISR(Channel channel, pFunction func);

    /**
     * @brief Gets the pointer to the transfer complete ISR for the specified DMA channel.
     * 
     * @param channel The DMA channel.
     * @return pFunction The function pointer to the ISR.
     */
    static pFunction GetPointerToTransferCompleteISR(Channel channel);

    /**
     * @brief Gets the pointer to the transfer error ISR for the specified DMA channel.
     * 
     * @param channel The DMA channel.
     * @return pFunction The function pointer to the ISR.
     */
    static pFunction GetPointerToTransferErrorISR(Channel channel);

 private:
    static constexpr uint32_t kCallBackSiz = 7;
    /**< Pointers to transfer complete ISRs for each DMA channel. */
    static pFunction PointerToTransferCompleteISR[kCallBackSiz];
    /**< Pointers to transfer error ISRs for each DMA channel. */
    static pFunction PointerToTransferErrorISR[kCallBackSiz];
    static RegType DMA;
};

}   // namespace dma
}   // namespace mcal
}   // namespace dev
}   // namespace stm32
#endif  // DEV_INC_MCAL_DMA_H_
