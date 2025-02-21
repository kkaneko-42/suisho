#ifndef SUISHO_INPUT_GAMEPAD_H_
#define SUISHO_INPUT_GAMEPAD_H_

#include "input/IInputDevice.hpp"
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
            kBack,
        };

        Gamepad(int device_id);

        bool poll() override;
        bool isPressed(int keycode) override;
        float getAxis1D(int scancode) override;
        Vec2 getAxis2D(int scancode) override;

    private:
        int id_;
        std::unique_ptr<GLFWgamepadstate> state_;
    };
}

#endif // SUISHO_INPUT_GAMEPAD_H_
