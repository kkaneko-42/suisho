#ifndef SUISHO_INPUT_MOUSE_H_
#define SUISHO_INPUT_MOUSE_H_

#include "input/IInputDevice.hpp"
#include <bitset>

namespace suisho {

class Mouse : public IInputDevice {
public:
    enum Keycode {
        kLeft,
        kRight,
        kMiddle,
        kKeycodeCount
    };

    Mouse(void* win);

    bool poll() override;
    bool isPressed(int keycode) override;
    Vec2 getAxis2D(int scancode = -1) override;

private:
    void* win_;
    std::bitset<kKeycodeCount> states_;
};

} // namespace suisho

#endif // SUISHO_INPUT_MOUSE_H_
