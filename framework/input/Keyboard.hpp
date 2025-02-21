#ifndef SUISHO_INPUT_KEYBOARD_H_
#define SUISHO_INPUT_KEYBOARD_H_

#include "input/IInputDevice.hpp"
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

private:
    void* win_;
    std::bitset<UCHAR_MAX> states_;
};

} // namespace suisho

#endif // SUISHO_INPUT_KEYBOARD_H_
