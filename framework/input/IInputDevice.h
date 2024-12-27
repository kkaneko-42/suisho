#ifndef SUISHO_IINPUT_DEVICE_H_
#define SUISHO_IINPUT_DEVICE_H_

#include "math/Vec2.h"
#include <stdexcept>

namespace suisho {

class IInputDevice {
public:
    virtual ~IInputDevice() {}

    virtual bool poll() = 0;

    virtual bool isPressed(int keycode) {
        throw std::logic_error("No button-like controls");
    }

    virtual float getAxis1D(int keycode) {
        throw std::logic_error("No 1D-axial controls");
    }

    virtual Vec2 getAxis2D(int scancode) {
        throw std::logic_error("No 2D-axial controls");
    }
};

} // namespace suisho

#endif // SUISHO_IINPUT_DEVICE_H_
