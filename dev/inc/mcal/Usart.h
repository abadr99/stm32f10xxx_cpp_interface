/**
 * @file Usart.h
 * @brief
 * @version 0.1
 * @date 2024-06-24
 *
 * @copyright Copyright (c) 2024
 *  
 */
#ifndef DEV_INC_MCAL_USART_H_
#define DEV_INC_MCAL_USART_H_

#include "mcal/stm32f103xx.h"

namespace stm32 {
namespace dev {
namespace mcal {
namespace usart {

/**
 * @enum UsartNum
 * @brief Enumeration of USART peripheral numbers.
 */
enum UsartNum : uint8_t {
    kUsart1,   /**< USART 1 */
    kUsart2,   /**< USART 2 */
    kUsart3,   /**< USART 3 */
};

/**
 * @enum UsartMode
 * @brief Enumeration for selecting USART communication modes.
 */
enum UsartMode : uint8_t {
    kRx = 0b01,   /**< Receive mode */
    kTx,          /**< Transmit mode */
    kRxTx,        /**< Both transmit and receive mode */
};

/**
 * @enum StopBitsNum
 * @brief Enumeration for selecting the number of stop bits.
 */
enum StopBitsNum : uint8_t {
    kSb_1_,     /**< 1 stop bit */
    kSb_0_5_,   /**< 0.5 stop bits */
    kSb_2_,     /**< 2 stop bits */
    kSb_1_5_,   /**< 1.5 stop bits */
};

/**
 * @enum WordLength
 * @brief Enumeration for selecting word length (number of data bits).
 */
enum WordLength : uint8_t {
    kDataBits_8_,   /**< 8 data bits */
    kDataBits_9_,   /**< 9 data bits */
};

/**
 * @enum ParityMode
 * @brief Enumeration for selecting parity mode in communication.
 */
enum ParityMode : uint8_t {
    kNo_Parity   = 0b00,  /**< No parity */
    kEven_Parity = 0b01,  /**< Even parity */
    kOdd_Parity  = 0b11,  /**< Odd parity */
};

/**
 * @enum HwFlowControl
 * @brief Enumeration for selecting hardware flow control options.
 */
enum HwFlowControl : uint8_t {
    kNone,      /**< No flow control */
    kRTS,       /**< RTS flow control */
    kCTS,       /**< CTS flow control */
    kRTS_CTS,   /**< RTS and CTS flow control */
};

/**
 * @enum ErrorType
 * @brief Enumeration representing various USART errors.
 */
enum ErrorType : uint8_t {
    kParityError,    /**< Parity error detected */
    kFrameError,     /**< Frame error detected */
    kNoiseError,     /**< Noise error detected */
    kOverRunError,   /**< Overrun error detected */
    kSuccess,        /**< No error */
};

/**
 * @struct UsartConfig
 * @brief Structure representing USART configuration settings.
 * 
 * This structure includes parameters like baud rate, word length, stop bits, parity mode, etc.
 */
struct UsartConfig {
    UsartNum number;                  /**< USART peripheral number */
    UsartMode mode;                   /**< Communication mode (Tx, Rx, or both) */
    StopBitsNum numOfSB;              /**< Number of stop bits */
    WordLength dataBits;              /**< Number of data bits */
    ParityMode parityMode;            /**< Parity mode (none, even, or odd) */
    HwFlowControl flowControlState;   /**< Hardware flow control setting */
    uint32_t baudRate;                /**< Baud rate for communication */
};

/**
 * @class Usart
 * @brief Class for configuring and controlling the USART peripheral.
 * 
 * This class provides methods for initializing the USART, transmitting and receiving data,
 * and managing error detection. It also supports interrupt-driven communication.
 */
class Usart {
 public:
    using DataValType = uint16_t;    /**< Alias for data value type */
    using pFunction = stm32::type::pFunction;   /**< Alias for a pointer to a function */

    /**
     * @brief Constructs a USART object with the specified configuration.
     * 
     * @param config Reference to a UsartConfig structure containing the configuration settings.
     */
    explicit Usart(const UsartConfig& config);

    /**
     * @brief Initializes the USART peripheral with the configuration provided in the constructor.
     */
    void Init();

    /**
     * @brief Transmits a single data value.
     * 
     * @param dataValue The value to transmit.
     */
    void Transmit(DataValType dataValue);

    /**
     * @brief Transmits a single data value with an interrupt service routine (ISR).
     * 
     * @param dataValue The value to transmit.
     * @param pISR Pointer to the ISR function to call after transmission.
     */
    void Transmit(DataValType dataValue, pFunction pISR);

    /**
     * @brief Receives a single data value.
     * 
     * @return DataValType The received data value.
     */
    DataValType Receive();

    /**
     * @brief Receives a data value using an interrupt service routine (ISR).
     * 
     * @param pData Pointer to where the received data should be stored.
     * @param pISR Pointer to the ISR function to call after reception.
     */
    void Receive(DataValType *pData, pFunction pISR);

    /**
     * @brief Returns the error type detected during USART communication.
     * 
     * @return ErrorType The type of error detected.
     */
    ErrorType RetErrorDetection();

    /**
     * @brief Retrieves the USART peripheral number.
     * 
     * @return UsartNum The USART number.
     */
    UsartNum GetUsartNum();

    /**
     * @brief Gets the ISR function for transmission complete interrupt for the specified USART number.
     * 
     * @param number The USART number.
     * @return pFunction Pointer to the transmission complete ISR function.
     */
    static pFunction Helper_GetTransmitCompleteISR(UsartNum number);

    /**
     * @brief Gets the ISR function for reception ready interrupt for the specified USART number.
     * 
     * @param number The USART number.
     * @return pFunction Pointer to the reception ready ISR function.
     */
    static pFunction Helper_GetReceiveReadyISR(UsartNum number);

    /**
     * @brief Sets the received data for the specified USART number.
     * 
     * @param number The USART number.
     * @param data The received data value.
     */
    static void Helper_SetReceivedData(UsartNum number, DataValType data);

 private:
    /**
     * @enum Flag
     * @brief Enumeration representing whether a feature is enabled or disabled.
     */
    enum Flag : uint8_t { kDisabled, kEnabled };

    const UsartConfig& config_;   /**< Reference to the USART configuration structure */
    /**< Pointer to the USART register structure */
    volatile stm32::registers::usart::UsartRegDef* usartReg;
    /**< Array of pointers to received data for each USART */
    static volatile DataValType *pReceivedData_[3];
    /**< Array of pointers to transmit complete ISR functions */
    static pFunction pTransmitCompleteFun_[3];
    /**< Array of pointers to receive ready ISR functions */
    static pFunction pReceiveReadyFun_[3];

    /**
     * @brief Sets the baud rate for the USART peripheral based on the configuration.
     */
    void _SetBaudRate();

    /**
     * @brief Sets the transmission complete ISR function for the specified USART number.
     * 
     * @param number The USART number.
     * @param pISR Pointer to the ISR function.
     */
    static void SetTransmitCompleteISR(UsartNum number, pFunction pISR);

    /**
     * @brief Sets the reception ready ISR function for the specified USART number.
     * 
     * @param number The USART number.
     * @param pISR Pointer to the ISR function.
     */
    static void SetReceiveReadyISR(UsartNum number, pFunction pISR);
};

}  // namespace usart
}  // namespace mcal
}  // namespace dev
}  // namespace stm32 // namespace stm32

#endif  //  DEV_INC_MCAL_USART_H_
