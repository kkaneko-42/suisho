#ifndef SUISHO_INPUT_KEYBOARD_H_
#define SUISHO_INPUT_KEYBOARD_H_

#include "input/IInputDevice.h"
#include <bitset>
#include <stdexcept>
#include <climits>

namespace suisho {

class Keyboard : public IInputDevice {
public:
    enum Keycode {
        kSpace,
        kArrowUp,
        kArrowRight,
        kArrowDown,
        kArrowLeft,
    };

    Keyboard(void* window); // FIXME
    bool poll() override;
    bool isPressed(int keycode) override;

    Vec2 getAxis2D(int scancode) override {
        throw std::logic_error("Keyboard has no 2D-axial controls");
    }

private:
    void* win_;
    std::bitset<UCHAR_MAX> states_;
};

} // namespace suisho

#endif // SUISHO_INPUT_KEYBOARD_H_
