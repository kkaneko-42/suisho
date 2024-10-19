#ifndef SUISHO_INPUT_GAMEPAD_H_
#define SUISHO_INPUT_GAMEPAD_H_

#include "input/IInputDevice.h"
#include <memory>

struct GLFWgamepadstate;

namespace suisho {
    class Gamepad : public IInputDevice {
    public:
        enum Keycode {
            kLeftStick,
            kRightStick,
            kNorth,
            kEast,
            kSouth,
            kWest,
            kDpadUp,
            kDpadRight,
            kDpadDown,
            kDpadLeft,
            kShoulderLeft,
            kShoulderRight,
            kTriggerLeft,
            kTriggerRight,
            kStart,
            kKeycodeCount,
        };

        Gamepad(int device_id = -1);

        bool poll() override;
        bool isPressed(int keycode) override;
        Vec2 getAxis2D(int scancode) override;

    private:
        int id_;
        std::unique_ptr<GLFWgamepadstate> state_;
    };
}

#endif // SUISHO_INPUT_GAMEPAD_H_