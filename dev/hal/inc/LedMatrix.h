/**
 * @file LedMatrix.h
 * @author
 * @brief
 * @version 0.1
 * @date 2024-04-30
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef DEV_HAL_INC_LEDMATRIX_H_
#define DEV_HAL_INC_LEDMATRIX_H_

using namespace stm32::dev::mcal::pin; 
using namespace stm32::dev::mcal::gpio;

#include <array>

#include "../../mcal/inc/Pin.h"
#include "utils/inc/Font.h"

using namespace stm32::utils::font;

namespace stm32 {
namespace dev {
namespace hal {
namespace ledMatrix {

enum ConnectionType : uint8_t {
    kCommon_Row_Cathode,
    kCommon_Row_Anode,
};

template <ConnectionType connectionType>
class LedMatrix {
 public:
    using Array_t = std::array<Pin, 8>;
    LedMatrix(const Array_t rowPins, const Array_t colPins);
    void Init();
    void DrawChar(uint8_t character);
    void ClearDisblay();

 private:
    Array_t rowPins_;
    Array_t colPins_;
    Font    font_;
};
}  // namespace ledMatrix
}  // namespace hal
}  // namespace dev
}  // namespace stm32
#endif  // DEV_HAL_INC_LEDMATRIX_H_