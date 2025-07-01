/**
 * @file HC05.h
 * @author
 * @brief 
 * @version 0.1
 * @date 2024-07-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef DEV_INC_HAL_HC05_H_
#define DEV_INC_HAL_HC05_H_

#include <string>
#include "mcal/Usart.h"

namespace stm32 {
namespace dev {
namespace mcal { namespace usart { enum UsartNum; }}
namespace hal {
namespace bluetooth {

/**
 * @class HC05
 * @brief Class to interface with the HC-05 Bluetooth module.
 * 
 * This class provides methods for Bluetooth communication using USART, 
 * including functions to send and receive data, as well as to execute AT commands 
 * for configuring the HC-05 module.
 */
class HC05 {
 public:
    /**
     * @enum DeviceRole
     * @brief Specifies the role of the Bluetooth device (Master or Slave).
     */
    enum DeviceRole { 
        kSlave,   /**< Device operates as a slave. */
        kMaster   /**< Device operates as a master. */
    };

    /**
     * @enum InquiryMode
     * @brief Specifies the inquiry mode for discovering Bluetooth devices.
     */
    enum InquiryMode { 
        kStandard,   /**< Standard inquiry mode. */
        kRssi        /**< Inquiry mode with RSSI (signal strength). */
    };

    using Usart = stm32::dev::mcal::usart::Usart;

    /**
     * @brief Constructs an HC05 object.
     * 
     * @param usart The USART instance used for Bluetooth communication.
     */
    explicit HC05(const Usart& usart);
  
    /**
     * @brief Sends a string via Bluetooth.
     * 
     * @param str A null-terminated C-string to be sent.
     */
    void Send(const char* str);

    /**
     * @brief Sends a numeric value via Bluetooth.
     * 
     * @param n The numeric data to be sent.
     */
    void Send(typename Usart::DataValType n);

    /**
     * @brief Sends a C++ string via Bluetooth.
     * 
     * @param str The string to be sent.
     */
    void Send(const std::string& str);

    /**
     * @brief Receives data via Bluetooth.
     * 
     * @return Received data as Usart::DataValType.
     */
    typename Usart::DataValType Receive();

    // ====================== Handle AT Commands ===============================

    /**
     * @brief Checks if the HC-05 module is connected.
     * Sends the "AT" command and expects an "OK" response.
     */
    void Test();

    /**
     * @brief Resets the HC-05 module.
     * Sends the "AT+RESET" command.
     */
    void Reset();

    /**
     * @brief Retrieves the firmware version of the HC-05 module.
     * Sends the "AT+VERSION?" command.
     */
    void GetFirmWareVersion();

    /**
     * @brief Sets the name of the HC-05 Bluetooth device.
     * 
     * @param name The desired device name.
     */
    void SetDeviceName(const std::string& name);

    /**
     * @brief Sets the pairing PIN code for the HC-05 module.
     * 
     * @param pin The desired PIN code for pairing.
     */
    void SetParingPin(const std::string& pin);

    /**
     * @brief Sets the role of the HC-05 device (Master or Slave).
     * 
     * @param role The device role (kMaster or kSlave).
     */
    void SetDeviceRole(DeviceRole role);

    /**
     * @brief Configures the UART settings (baud rate, stop bits, and parity).
     * 
     * @param baudRate The UART baud rate.
     * @param stopBits The number of stop bits.
     * @param parity The UART parity mode.
     */
    void SetUART(uint32_t baudRate, uint32_t stopBits, uint32_t parity);

    /**
     * @brief Configures the inquiry mode for discovering Bluetooth devices.
     * 
     * @param im The inquiry mode (kStandard or kRssi).
     * @param maxNumberOfBluetoothDevices The maximum number of devices to discover.
     * @param timeout The inquiry timeout period.
     */
    void SetInquiryMode(InquiryMode im, uint32_t maxNumberOfBluetoothDevices, uint32_t timeout);

    /**
     * @brief Binds the HC-05 module to a specific Bluetooth device by address.
     * 
     * @param address The Bluetooth address to bind to.
     */
    void SetBindToAddress(const std::string& address);

    /**
     * @brief Initiates an inquiry to discover nearby Bluetooth devices.
     */
    void InquiryBluetoothDevices();

 private:
    Usart usart_;  /**< USART instance for communication. */

    /**
     * @enum Commands
     * @brief Enumeration of AT commands for the HC-05 module.
     */
    enum Commands {
        kAT,            /**< Basic AT command */
        kAT_RESET,      /**< Reset the module */
        kAT_VERSION,    /**< Query firmware version */
        kAT_NAME,       /**< Set device name */
        kAT_PSWD,       /**< Set pairing password */
        kAT_ROLE,       /**< Set device role (master/slave) */
        kAT_UART,       /**< Set UART parameters */
        kAT_INQM,       /**< Set inquiry mode */
        kAT_BIND,       /**< Bind to a specific address */
        kAT_INQ,        /**< Inquiry command to search for devices */
        kSET_POSTFIX,   /**< Set command postfix */
        kGET_POSTFIX,   /**< Get command postfix */
        kAT_END,        /**< End of command */
        kCOMMA          /**< Command separator */
    };
};

}  // namespace bluetooth
}  // namespace hal
}  // namespace dev
}  // namespace stm32

#endif  // DEV_INC_HAL_HC05_H_
