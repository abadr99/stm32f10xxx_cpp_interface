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
enum class OperatingMode : uint8_t {
    kSleep,             /**< Sleep mode */
    kInitialization,    /**< Initialization mode */
    kNormal             /**< Normal operation mode */
};

/**
 * @brief CAN test modes.
 */
enum class TestMode : uint8_t {
    kNormal   = 0b00,   /**< Silent mode */
    kSilent   = 0b10,   /**< Silent mode */
    kLoopBack = 0b01,   /**< Loopback mode */
    kCombined = 0b11    /**< Combined silent and loopback mode */
};

/**
 * @brief CAN identifier types.
 */
enum class IdType : uint8_t {
    kStId,   /**< Standard identifier */
    kExId    /**< Extended identifier */
};

/**
 * @brief Remote Transmission Request (RTR) types.
 */
enum class RemoteTxReqType : uint8_t {
    kData,      /**< Data frame */
    kRemote     /**< Remote frame */
};

/**
 * @brief CAN transmit mailbox identifiers.
 */
enum class MailBoxType : uint8_t {
    kMailBox0,  /**< Mailbox 0 */
    kMailBox1,  /**< Mailbox 1 */
    kMailBox2   /**< Mailbox 2 */
};

/**
 * @brief FIFO types for received messages.
 */
enum class FifoNumber : uint16_t {
    kFIFO0,     /**< FIFO 0 */
    kFIFO1      /**< FIFO 1 */
};

/**
 * @brief Priority determination for CAN message transmission.
 */
enum class FifoPriority : uint8_t {
    kID,        /**< Priority based on message ID */
    kRequest    /**< Priority based on request type */
};

/**
 * @brief Status of received FIFO.
 */
enum class ReceivedFifo : uint8_t {
    kUnLocked,  /**< FIFO is unlocked */
    kLocked     /**< FIFO is locked */
};

/**
 * @brief Filter modes for CAN.
 */
enum class FilterMode : uint8_t {
    kMask,      /**< Mask mode */
    kList       /**< List mode */
};

/**
 * @brief Filter scale configurations.
 */
enum class FilterScale : uint8_t {
    k16bit,      /**< 16-bit scale */
    k32bit      /**< 32-bit scale */
};

/**
 * @brief Represents time quanta values for CAN bus timing configurations.
 */
enum class TimeQuanta : uint8_t {
    kTq1,   /**< 1 Time Quanta (TQ) */
    kTq2,   /**< 2 Time Quanta (TQ) */
    kTq3,   /**< 3 Time Quanta (TQ) */
    kTq4,   /**< 4 Time Quanta (TQ) */
    kTq5,   /**< 5 Time Quanta (TQ) */
    kTq6,   /**< 6 Time Quanta (TQ) */
    kTq7,   /**< 7 Time Quanta (TQ) */
    kTq8,   /**< 8 Time Quanta (TQ) */
    kTq9,   /**< 9 Time Quanta (TQ) */
    kTq10,  /**< 10 Time Quanta (TQ) */
    kTq11,  /**< 11 Time Quanta (TQ) */
    kTq12,  /**< 12 Time Quanta (TQ) */
    kTq13,  /**< 13 Time Quanta (TQ) */
    kTq14,  /**< 14 Time Quanta (TQ) */
    kTq15,  /**< 15 Time Quanta (TQ) */
    kTq16   /**< 16 Time Quanta (TQ) */
};

enum class Interrupts : uint32_t {
    kTxMailBoxEmpty,        /**< Transmit mailbox empty */
    kFifo0MessagePending,   /**< FIFO 0 message pending */
    kFifo0Full,             /**< FIFO 0 full */
    kFifo0Overrun,          /**< FIFO 0 overrun */
    kFifo1MessagePending,   /**< FIFO 1 message pending */
    kFifo1Full,             /**< FIFO 1 full */
    kFifo1Overrun,          /**< FIFO 1 overrun */
    kErorrWarning = 8,      /**< Error warning */
    kErrorPassive,          /**< Error passive */
    kBusOff,                /**< Bus-off */
    kLastErrorCode,         /**< Last error code */
    kError = 15,            /**< Error */
    kWakeUp,                /**< Wake-up */
    kSleepAck,              /**< Sleep acknowledge */
};

enum class CallbackId : uint32_t {
    kTxMailbox0Complete,    /**< Transmit mailbox 0 complete */
    kTxMailbox1Complete,    /**< Transmit mailbox 1 complete */
    kTxMailbox2Complete,    /**< Transmit mailbox 2 complete */
    kTxMailbox0Abort,       /**< Transmit mailbox 0 abort */
    kTxMailbox1Abort,       /**< Transmit mailbox 1 abort */
    kTxMailbox2Abort,       /**< Transmit mailbox 2 abort */
    kFifo0MessagePending,   /**< FIFO 0 message pending */
    kFifo0Full,             /**< FIFO 0 full */
    kFifo1MessagePending,   /**< FIFO 1 message pending */
    kFifo1Full,             /**< FIFO 1 full */
    kSleepAck,              /**< Sleep acknowledge */
    kWakeUp,                /**< Wake-up */
    kError,                 /**< Error */
};
/**
 * @brief State for enabling or disabling features.
 */
enum class State : uint8_t {
    kDisable,   /**< Disabled state */
    kEnable     /**< Enabled state */
};
enum class CanError : uint32_t {
    kNoEr            = 0x00000000U,  /**< No error */
    kEwg             = 0x00000001U,  /**< Protocol Error Warning */
    kEpv             = 0x00000002U,  /**< Error Passive */
    kBof             = 0x00000004U,  /**< Bus-off error */
    kStf             = 0x00000008U,  /**< Stuff error */
    kFor             = 0x00000010U,  /**< Form error */
    kAck             = 0x00000020U,  /**< Acknowledgment error */
    kBr              = 0x00000040U,  /**< Bit recessive error */
    kBd              = 0x00000080U,  /**< Bit dominant error */
    kCrc             = 0x00000100U,  /**< CRC error */
    kRxFov0          = 0x00000200U,  /**< Rx FIFO0 overrun error */
    kRxFov1          = 0x00000400U,  /**< Rx FIFO1 overrun error */
    kTxAlst0         = 0x00000800U,  /**< TxMailbox 0 arbitration lost */
    kTxTerr0         = 0x00001000U,  /**< TxMailbox 0 transmit error */
    kTxAlst1         = 0x00002000U,  /**< TxMailbox 1 arbitration lost */
    kTxTerr1         = 0x00004000U,  /**< TxMailbox 1 transmit error */
    kTxAlst2         = 0x00008000U,  /**< TxMailbox 2 arbitration lost */
    kTxTerr2         = 0x00010000U,  /**< TxMailbox 2 transmit error */
    kTimeout         = 0x00020000U,  /**< Timeout error */
    kNotInitialized  = 0x00040000U,  /**< Peripheral not initialized */
    kNotReady        = 0x00080000U,  /**< Peripheral not ready */
    kNotStarted      = 0x00100000U,  /**< Peripheral not started */
    kParam           = 0x00200000U   /**< Parameter error */
};


/**
 * @brief CAN configuration structure.
 */
struct CanConfig {
    OperatingMode opMode;             /**< Operating mode */
    TestMode testMode;                /**< Test mode */
    FifoPriority priority;            /**< FIFO priority */
    ReceivedFifo receivedFifoLock;    /**< Receive FIFO locked mode */
    uint16_t baudRatePrescaler : 9;   /**< CAN baud rate prescaler */
    TimeQuanta sjw;                   /**< Resynchronization jump width between k1tq and k4tq */
    TimeQuanta bs1;                   /**< Time segment 1 between k1tq and k16tq */
    TimeQuanta bs2;                   /**< Time segment 2 between k1tq and k8tq */
    State TTCM;                       /**< Time-triggered communication mode */
    State ABOM;                       /**< Automatic bus-off management */
    State AWUM;                       /**< Automatic wake-up mode */
    State NART;                       /**< No automatic retransmission */
    CanError error = CanError::kNoEr;           /**< Error handling */
};

/**
 * @brief CAN filter configuration structure.
 */
struct FilterConfig {
    uint16_t idHigh;           /**< Filter ID high between 0x0000 and 0xFFFF */
    uint16_t idLow;            /**< Filter ID low between 0x0000 and 0xFFFF */
    uint16_t maskIdHigh;       /**< Mask ID high between 0x0000 and 0xFFFF */
    uint16_t maskIdLow;        /**< Mask ID low between 0x0000 and 0xFFFF */
    FifoNumber fifoAssign;     /**< FIFO assignment */
    uint32_t bank;             /**< Filter bank number between 0 and 13*/
    FilterMode mode;           /**< Filter mode */
    FilterScale scale;         /**< Filter scale */
    State activation;          /**< Filter activation state */
};

/**
 * @brief CAN transmit message structure.
 */
struct CanTxMsg {
    static constexpr uint8_t kDataSiz = 8;
    uint32_t stdId;            /**< Standard ID between 0 to 0x7FF */
    uint32_t extId;            /**< Extended ID between 0 to 0x1FFFFFFF */
    IdType ide;                /**< Identifier type */
    RemoteTxReqType rtr;       /**< Remote transmission request */
    uint8_t dlc;               /**< Data length code between 0 to 8 */
    uint8_t data[kDataSiz];    /**< Data field between 0 to 0xFF */
};

/**
 * @brief CAN receive message structure.
 */
struct CanRxMsg {
    static constexpr uint8_t kDataSiz = 8;
    uint32_t stdId;            /**< Standard ID between 0 to 0x7FF */
    uint32_t extId;            /**< Extended ID between 0 to 0x1FFFFFFF */
    uint32_t timeStamp;        /**< Time stamp counter value */
    IdType ide;                /**< Identifier type */
    RemoteTxReqType rtr;       /**< Remote transmission request */
    uint8_t dlc;               /**< Data length code between 0 to 8 */
    uint8_t data[kDataSiz];    /**< Data field between 0 to 0xFF */
    uint8_t FMI;               /**< Filter match index between 0 to 0xFF */
};

/**
 * @brief CAN driver class.
 */
class Can {
 public:
    using CANRegDef = stm32::registers::can::CANRegDef;
    using can_ptr   = stm32::type::RegType<CANRegDef>::ptr;
    using pFunction = stm32::type::pFunction;
    /**
     * @brief Initializes the CAN peripheral with the specified configuration.
     * @param conf Configuration structure for CAN initialization.
     */
    static void Init(const CanConfig &conf);

    /**
     * @brief Start the CAN Module.
     */
    static void Start();

    /**
     * @brief Initializes the CAN filter with the specified configuration.
     * @param conf Filter configuration structure.
     */
    static void FilterInit(const FilterConfig& conf);

    /**
     * @brief Transmits a CAN message.
     * @param message CAN transmit message structure.
     */
    static void Transmit(const CanTxMsg& message);

    static void Transmit(const CanTxMsg& message, pFunction fun);
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
    static void Receive(CanRxMsg& message, FifoNumber fifo);  //  NOLINT [runtime/references]

    /**
     * @brief Retrieves the number of pending messages in the specified FIFO.
     * @param fifo FIFO number.
     * @return Number of pending messages.
     */
    uint8_t GetPendingMessages(FifoNumber fifo);

    /**
     * @brief Enables the specified CAN interrupt.
     * @param interrupt Interrupt to enable.
     */
    static void EnableInterrupt(Interrupts interrupt);

    /**
     * @brief Disables the specified CAN interrupt.
     * @param interrupt Interrupt to disable.
     */
    static void DisableInterrupt(Interrupts interrupt);

    static void SetCallback(CallbackId id, pFunction func);
    static pFunction GetCallback(CallbackId id);
    
 private:
    static can_ptr CAN;  /**< Pointer to CAN registers */
    static constexpr uint32_t kMailboxSiz = 3;
    static constexpr uint32_t kFifoSiz = 2;
    static pFunction TxMailboxComplete[kMailboxSiz];  /**< Transmit mailbox complete callback */
    static pFunction TxMailboxAbort[kMailboxSiz];     /**< Transmit mailbox abort callback */
    static pFunction RxFifoMsgPending[kFifoSiz];       /**< Receive FIFO message pending callback */
    static pFunction RxFifoFull[kFifoSiz];             /**< Receive FIFO full callback */
    static pFunction SleepCallback;                    /**< Sleep callback */
    static pFunction WakeUpCallback;                   /**< Wake-up callback */
    static pFunction ErrorCallback;                    /**< Error callback */
    /**
     * @brief Sets the operating mode for the CAN peripheral.
     * @param conf CAN configuration structure.
     * @param mode Operating mode.
     */
    static void SetOperatingMode(OperatingMode mode);
    static uint32_t Helper_Transmit(const CanTxMsg& message);
};
}   // namespace can
}   // namespace mcal
}   // namespace dev
}   // namespace stm32
#endif  // DEV_INC_MCAL_CAN_H_
