/**
 * @file CAN.h
 * @author 
 * @brief 
 * @version 0.1
 * @date 2024-11-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef DEV_INC_MCAL_CAN_H_
#define DEV_INC_MCAL_CAN_H_

namespace stm32 {
namespace dev   {
namespace mcal  {
namespace can   {

/**
 * @brief Operating modes of the CAN peripheral.
 */
enum OperatingMode : uint8_t {
    kSleep,             /**< Sleep mode */
    kInitialization,    /**< Initialization mode */
    kNormal             /**< Normal operation mode */
};

/**
 * @brief CAN test modes.
 */
enum TestMode : uint8_t {
    kSilent,        /**< Silent mode */
    kLoopBack,      /**< Loopback mode */
    kCombined       /**< Combined silent and loopback mode */
};

/**
 * @brief CAN identifier types.
 */
enum IdType : uint8_t {
    kStd,   /**< Standard identifier */
    kExt    /**< Extended identifier */
};

/**
 * @brief Remote Transmission Request (RTR) types.
 */
enum RTRType : uint8_t {
    kData,      /**< Data frame */
    kRemote     /**< Remote frame */
};

/**
 * @brief CAN transmit mailbox identifiers.
 */
enum MailBoxType : uint8_t {
    kMailBox0,  /**< Mailbox 0 */
    kMailBox1,  /**< Mailbox 1 */
    kMailBox2   /**< Mailbox 2 */
};

/**
 * @brief FIFO types for received messages.
 */
enum FifoNumber : uint8_t {
    kFIFO0,     /**< FIFO 0 */
    kFIFO1      /**< FIFO 1 */
};

/**
 * @brief Priority determination for CAN message transmission.
 */
enum FifoPriority : uint8_t {
    kID,        /**< Priority based on message ID */
    kRequest    /**< Priority based on request type */
};

/**
 * @brief Status of received FIFO.
 */
enum ReceivedFifo : uint8_t {
    kUnLocked,  /**< FIFO is unlocked */
    kLocked     /**< FIFO is locked */
};

/**
 * @brief Retransmission behavior for CAN messages.
 */
enum Retransmission : uint8_t {
    kAuto,      /**< Automatic retransmission enabled */
    kNoAuto     /**< Automatic retransmission disabled */
};

/**
 * @brief Filter modes for CAN.
 */
enum FilterMode : uint8_t {
    kMask,      /**< Mask mode */
    kList       /**< List mode */
};

/**
 * @brief Filter scale configurations.
 */
enum FilterScale : uint8_t {
    k16it,      /**< 16-bit scale */
    k32bit      /**< 32-bit scale */
};

/**
 * @brief Prescaler options for CAN communication speed.
 */
enum Prescaler : uint8_t {
    k100KBPS,   /**< 100 kbps */
    k125KBPS,   /**< 125 kbps */
    k250KBPS,   /**< 250 kbps */
    k500KBPS,   /**< 500 kbps */
    k800KBPS,   /**< 800 kbps */
    k1MBPS      /**< 1 Mbps */
};

/**
 * @brief State for enabling or disabling features.
 */
enum State : uint8_t {
    kDisable,   /**< Disabled state */
    kEnable     /**< Enabled state */
};

/**
 * @brief CAN configuration structure.
 */
struct CanConfig {
    Prescaler buadRate;        /**< CAN baud rate prescaler */
    OperatingMode opMode;      /**< Operating mode */
    TestMode mode;             /**< Test mode */
    FifoPriority priority;     /**< FIFO priority */
    uint8_t SJW;               /**< Resynchronization jump width */
    uint8_t BS1;               /**< Time segment 1 */
    uint8_t BS2;               /**< Time segment 2 */
    State TTCM;                /**< Time-triggered communication mode */
    State ABOM;                /**< Automatic bus-off management */
    State AWUM;                /**< Automatic wake-up mode */
    State NART;                /**< No automatic retransmission */
    State RFLM;                /**< Receive FIFO locked mode */
    State TXFP;                /**< Transmit FIFO priority */
};

/**
 * @brief CAN filter configuration structure.
 */
struct FilterConfig {
    uint32_t idHigh;           /**< Filter ID high */
    uint32_t idLow;            /**< Filter ID low */
    uint32_t maskIdHigh;       /**< Mask ID high */
    uint32_t maskIdLow;        /**< Mask ID low */
    FifoNumber fifoAssign;     /**< FIFO assignment */
    uint32_t bank;             /**< Filter bank number */
    FilterMode mode;           /**< Filter mode */
    FilterScale scale;         /**< Filter scale */
    State activation;          /**< Filter activation state */
};

/**
 * @brief CAN transmit message structure.
 */
struct CanTxMsg {
    uint32_t stdId;            /**< Standard ID */
    uint32_t extId;            /**< Extended ID */
    IdType ide;                /**< Identifier type */
    RTRType rtr;               /**< Remote transmission request */
    uint8_t dlc;               /**< Data length code */
    uint8_t data[8];           /**< Data field */
};

/**
 * @brief CAN receive message structure.
 */
struct CanRxMsg {
    uint32_t stdId;            /**< Standard ID */
    uint32_t extId;            /**< Extended ID */
    IdType ide;                /**< Identifier type */
    RTRType rtr;               /**< Remote transmission request */
    uint8_t dlc;               /**< Data length code */
    uint8_t data[8];           /**< Data field */
    uint8_t FMI;               /**< Filter match index */
};

/**
 * @brief CAN driver class.
 */
class Can {
 public:
    using CANRegDef = stm32::registers::can::CANRegDef;
    using can_ptr   = stm32::type::RegType<CANRegDef>::ptr;

    /**
     * @brief Initializes the CAN peripheral with the specified configuration.
     * @param conf Configuration structure for CAN initialization.
     */
    static void Init(const CanConfig &conf);

    /**
     * @brief Initializes the CAN filter with the specified configuration.
     * @param conf Filter configuration structure.
     */
    static void FilterInit(const FilterConfig& conf);

    /**
     * @brief Transmits a CAN message.
     * @param message CAN transmit message structure.
     */
    static void Transmit(CanTxMsg message);

    /**
     * @brief Cancels message transmission in the specified mailbox.
     * @param mailbox Mailbox identifier.
     */
    static void CancelTransmit(MailBoxType mailbox);

    /**
     * @brief Receives a CAN message from the specified FIFO.
     * @param message CAN receive message structure.
     * @param fifo FIFO number to receive from.
     */
    static void Receive(CanRxMsg message, FifoNumber fifo);

    /**
     * @brief Retrieves the number of pending messages in the specified FIFO.
     * @param fifo FIFO number.
     * @return Number of pending messages.
     */
    uint8_t GetPendingMessages(FifoNumber fifo);

 private:
    static can_ptr CAN;  /**< Pointer to CAN registers */

    /**
     * @brief Sets the operating mode for the CAN peripheral.
     * @param conf CAN configuration structure.
     * @param mode Operating mode.
     */
    static void SetOperatingMode(const CanConfig &conf, OperatingMode mode);
};
}   // namespace can
}   // namespace mcal
}   // namespace dev
}   // namespace stm32
#endif  // DEV_INC_MCAL_CAN_H_
