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

#ifndef DEV_HAL_INC_HC05_H_
#define DEV_HAL_INC_HC05_H_

#include <string>

namespace stm32 {
namespace dev {
namespace mcal { namespace usart { enum UsartNum; }}
namespace hal {
namespace bluetooth {

template <stm32::dev::mcal::usart::UsartNum N>
class HC05 {
 public:
    enum DeviceRole  {kSlave, kMaster};
    enum InquiryMode {kStandard, kRssi};
    using usart_t = stm32::dev::mcal::usart::Usart<N>;
    
    explicit HC05(const usart_t& usart);
    void Send(char c);
    void Send(typename usart_t::DataValType n);
    void Send(const std::string& str);
    typename usart_t::DataValType Receive();
    
    // ====================== Handle AT Commands ===============================
    // See: https://components101.com/sites/default/files/component_datasheet/HC-05%20Datasheet.pdf
    /*
    | Command                        | Description                         | Response           |
    |--------------------------------|-------------------------------------|------------------- |
    | AT                             | Check connection                    | OK                 |
    | AT+RESET                       | Restart the module                  | OK                 |
    | AT+VERSION?                    | Check firmware version              | +VERSION:<version> |
    | AT+NAME=<name>                 | Set device name                     | OK                 |
    | AT+PSWD=<pin>                  | Set pairing PIN code                | OK                 |
    | AT+ROLE=<role>                 | Set device role (0=slave, 1=master) | OK                 |
    | AT+UART=<baud>,<stop>,<parity> | Set UART baud rate                  | OK                 |
    | AT+INQM=<parm1>,<parm2>,<parm3>| Set inquiry mode                    | OK                 |
    | AT+BIND=<address>              | Bind to specific address            | OK                 |
    | AT+INQ                         | Inquiry to available devices        | List of devices    |
    */
    void Test();
    void Reset();
    void GetFirmWareVersion();
    void SetDeviceName(const std::string& name);
    void SetParingPin(const std::string& pin);
    void SetDeviceRole(DeviceRole role);
    // TODO(@abadr99): Check if this function should be private
    void SetUART(uint32_t baudRate, uint32_t stopBits, uint32_t parity);
    void SetInquiryMode(InquiryMode im, uint32_t maxNumberOfBluetoothDevices, uint32_t timeout);
    void SetBindToAddress(const std::string& address);
    void InquiryBluetoothDevices();
    // TODO(@abadr99): Support more AT commands
 private:
    usart_t usart_;
};

}  // namespace bluetooth
}  // namespace hal
}  // namespace dev
}  // namespace stm32

#endif  // DEV_HAL_INC_HC05_H_
