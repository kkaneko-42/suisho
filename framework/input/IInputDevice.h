#ifndef SUISHO_IINPUT_DEVICE_H_
#define SUISHO_IINPUT_DEVICE_H_

#include "math/Vec2.h"

namespace suisho {

class IInputDevice {
public:
    virtual ~IInputDevice() {}

    virtual bool poll() = 0;
    virtual bool isPressed(int keycode) = 0;
    virtual Vec2 getAxis2D(int scancode) = 0;
};

} // namespace suisho

#endif // SUISHO_IINPUT_DEVICE_H_
