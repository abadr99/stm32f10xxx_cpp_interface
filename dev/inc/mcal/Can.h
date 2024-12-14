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
 * @brief CAN peripheral identifiers.
 */
enum CanNum : uint8_t {
    kCAN1,      /**< CAN1 peripheral */
    kCAN2       /**< CAN2 peripheral */
};

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
 * @brief Status of CAN operations.
 */
enum Status : uint8_t {
    kFail,      /**< Operation failed */
    kSuccess    /**< Operation succeeded */
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
enum PriorityBased : uint8_t {
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
enum FilterMode : uint8_t {
    kMask,
    kList
};
enum FilterScale : uint8_t {
    k16it,
    k32bit
};
enum State : uint8_t {
    kDisable,
    kEnable
};
struct CanConfig {
    uint16_t prescaler;
    OperatingMode mode;
    State TTCM;
    State ABOM;
    State AWUM;
    State NART;
    State RFLM;
    State TXFP;
};
struct CanMsg {
    uint32_t stdId;
    uint32_t extId;
    IdType id;
    RTRType rtr;
    uint8_t dlc;
    uint8_t data[8];
};
class Can {
 public:
    static void Init(const CanConfig &conf);
    static void SetOperatingMode(const CanConfig &conf, OperatingMode mode);
    static void SetTestMode(TestMode mode);
    static void Transmit(CanMsg message);
    static void CancelTransmit(MailBoxType mailbox);
    static void Receive(CanMsg message, uint8_t FMI, FifoNumber fifo);
 private:
    using CANRegDef = stm32::registers::can::CANRegDef;
    static stm32::type::RegType<CANRegDef>::ptr CAN;
};
}   // namespace can
}   // namespace mcal
}   // namespace dev
}   // namespace stm32
#endif  // DEV_INC_MCAL_CAN_H_
