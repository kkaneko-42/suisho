#include "input/Keyboard.h"
#include <unordered_map>
#include <GLFW/glfw3.h>

using namespace suisho;

const std::unordered_map<int, int> kKeycodeTable = {
    { Keyboard::kSpace, GLFW_KEY_SPACE },
    { Keyboard::kArrowUp, GLFW_KEY_UP },
    { Keyboard::kArrowRight, GLFW_KEY_RIGHT },
    { Keyboard::kArrowDown, GLFW_KEY_DOWN },
    { Keyboard::kArrowLeft, GLFW_KEY_LEFT },
};

bool Keyboard::poll() {
    // Get current context
    GLFWwindow* ctx = glfwGetCurrentContext();
    if (glfwGetError(nullptr) != GLFW_NO_ERROR) {
        return false;
    }
    else if (ctx == nullptr) {
        // No window's context is current
        return true;
    }

    // Poll events
    glfwPollEvents();
    if (glfwGetError(nullptr) != GLFW_NO_ERROR) {
        return false;
    }

    // Set number keys
    for (char key = '0'; key <= '9'; ++key) {
        states_[key] = (glfwGetKey(ctx, key) == GLFW_PRESS);
    }

    // Set alphabet keys
    for (char key = 'A'; key <= 'Z'; ++key) {
        states_[key] = (glfwGetKey(ctx, key) == GLFW_PRESS);
    }

    // Set other keys
    for (auto [host, lib] : kKeycodeTable) {
        states_[host] = (glfwGetKey(ctx, lib) == GLFW_PRESS);
    }

    return true;
}

bool Keyboard::isPressed(int keycode) {
    if (keycode < 0 || keycode >= states_.size()) {
        throw std::runtime_error(std::string("Keyboard: Invalid keycode ") + (char)(keycode + '0'));
    }

    return states_[keycode];
}
