/**
 * @file Esp.h
 * @author Mohamed Refat
 * @brief 
 * @version 0.1
 * @date 2024-08-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef DEV_INC_HAL_ESP_H_
#define DEV_INC_HAL_ESP_H_

using namespace stm32::dev::mcal::usart;
namespace stm32 {
namespace dev {
namespace hal {
namespace esp {


/**
 * @enum EspMode
 * @brief Modes of operation for the ESP module.
 */
enum class EspMode {
    kSTA = 1,    /**< Station Mode */
    kAP,         /**< Access Point Mode */
    kSTA_Ap      /**< Station and Access Point Mode */
};

/**
 * @enum EchoState
 * @brief Echo state for AT commands.
 */
enum class EchoState {
    kOff,        /**< Disable command echo */
    kOn          /**< Enable command echo */
};

/**
 * @class Esp
 * @brief Class to interface with the ESP module for Wi-Fi communication.
 * 
 * This class provides methods for sending data, setting up communication modes,
 * managing Wi-Fi and server connections, and controlling the echo state.
 */
class Esp {
 public:
    /**
     * @brief Constructs an Esp object.
     * 
     * @param usartNum The USART peripheral number to use for communication.
     */
    explicit Esp(const UsartNum &usartNum);

    /**
     * @brief Initializes the ESP module by setting up the USART peripheral.
     */
    void Init();

    /**
     * @brief Sends a string via the ESP module.
     * 
     * @param str A null-terminated C-string to be sent.
     */
    void Send(const char *str);

    /**
     * @brief Sends a numeric value via the ESP module.
     * 
     * @param n The numeric data to be sent.
     */
    void Send(Usart::DataValType n);

    /**
     * @brief Sets the operation mode of the ESP module.
     * 
     * @param mode The mode of operation (Station, Access Point, or both).
     */
    void SetMode(const EspMode &mode);

    /**
     * @brief Enables or disables echo of AT commands.
     * 
     * @param state The echo state (On or Off).
     */
    void SetEchoState(const EchoState &state);

    /**
     * @brief Connects the ESP module to a Wi-Fi network.
     * 
     * @param username The Wi-Fi network SSID.
     * @param pswd The Wi-Fi network password.
     */
    void WiFiConnect(const char* username, const char* pswd);

    /**
     * @brief Connects the ESP module to a server.
     * 
     * @param protocol The communication protocol (TCP/UDP).
     * @param ip The server IP address.
     * @param port The server port number.
     */
    void ServerConnect(const char* protocol, const char* ip, uint16_t port);

 private:
    /**
     * @enum Commands
     * @brief Enumeration of ESP AT commands.
     */
    enum Commands {
        kAT,            /**< Basic AT command */
        kAT_RST,        /**< Reset the ESP module */
        ATE,            /**< Enable/disable echo */
        AT_CWMODE,      /**< Set Wi-Fi mode */
        AT_CWJAP_CUR,   /**< Connect to Wi-Fi */
        AT_CIPSTART,    /**< Connect to a server */
        kSET_POSTFIX,   /**< Set command postfix */
        kGET_POSTFIX,   /**< Get command postfix */
        kAT_END,        /**< End command */
        kCOMMA          /**< Command separator */
    };

    UsartConfig usartConfig_;   /**< USART configuration for communication */
    Usart usart_;               /**< USART instance for data transmission */
};

}   //  namespace esp
}   //  namespace hal
}   //  namespace dev
}   //  namespace stm32
#endif  //  DEV_INC_HAL_ESP_H_
