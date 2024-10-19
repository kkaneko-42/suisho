#include "input/Gamepad.h"
#include <unordered_map>
#include <GLFW/glfw3.h>
#include <stdexcept>

using namespace suisho;

Gamepad::Gamepad(int id) : id_(id), state_(new GLFWgamepadstate())
{}

bool Gamepad::poll() {
    if (glfwGetGamepadState(id_, state_.get()) == GLFW_FALSE) {
        return false;
    }
}

bool Gamepad::isPressed(int keycode) {
    return true;
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
