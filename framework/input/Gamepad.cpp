#include "input/Gamepad.h"
#include <unordered_map>
#include <GLFW/glfw3.h>
#include <stdexcept>

using namespace suisho;

const std::unordered_map<int, int> kKeycodeTable = {
    { Gamepad::kLeftStick, GLFW_GAMEPAD_BUTTON_LEFT_THUMB },
    { Gamepad::kRightStick, GLFW_GAMEPAD_BUTTON_RIGHT_THUMB },
    { Gamepad::kNorth, GLFW_GAMEPAD_BUTTON_Y },
    { Gamepad::kEast, GLFW_GAMEPAD_BUTTON_B },
    { Gamepad::kSouth, GLFW_GAMEPAD_BUTTON_A },
    { Gamepad::kWest, GLFW_GAMEPAD_BUTTON_X },
    { Gamepad::kDpadUp, GLFW_GAMEPAD_BUTTON_DPAD_UP },
    { Gamepad::kDpadRight, GLFW_GAMEPAD_BUTTON_DPAD_RIGHT },
    { Gamepad::kDpadDown, GLFW_GAMEPAD_BUTTON_DPAD_DOWN },
    { Gamepad::kDpadLeft, GLFW_GAMEPAD_BUTTON_DPAD_LEFT },
    { Gamepad::kShoulderLeft, GLFW_GAMEPAD_BUTTON_LEFT_BUMPER },
    { Gamepad::kShoulderRight, GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER },
    { Gamepad::kStart, GLFW_GAMEPAD_BUTTON_START },
    { Gamepad::kBack, GLFW_GAMEPAD_BUTTON_BACK },
};

Gamepad::Gamepad(int id) : id_(id), state_(new GLFWgamepadstate())
{}

bool Gamepad::poll() {
    if (glfwGetGamepadState(id_, state_.get()) == GLFW_FALSE) {
        return false;
    }

    return true;
}

bool Gamepad::isPressed(int keycode) {
    if (kKeycodeTable.count(keycode) == 0) {
        throw std::runtime_error("Gamepad: Invalid keycode " + keycode);
    }

    return state_->buttons[kKeycodeTable.at(keycode)];
}

float Gamepad::getAxis1D(int keycode) {
    int actual_keycode = 0;
    if (keycode == kTriggerLeft) {
        actual_keycode = GLFW_GAMEPAD_AXIS_LEFT_TRIGGER;
    }
    else if (keycode == kTriggerRight) {
        actual_keycode = GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER;
    }
    else {
        throw std::runtime_error("Gamepad::getAxis1D(): Invalid keycode " + keycode);
    }

    return state_->axes[actual_keycode];
}

Vec2 Gamepad::getAxis2D(int keycode) {
    int x_keycode = 0;
    if (keycode == kLeftStick) {
        x_keycode = GLFW_GAMEPAD_AXIS_LEFT_X;
    }
    else if (keycode == kRightStick) {
        x_keycode = GLFW_GAMEPAD_AXIS_RIGHT_X;
    }
    else {
        throw std::runtime_error("Gamepad::getAxis2D(): Invalid keycode " + keycode);
    }

    return Vec2(state_->axes[x_keycode], -state_->axes[x_keycode + 1]);
}
