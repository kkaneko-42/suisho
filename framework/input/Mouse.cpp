#include "input/Mouse.hpp"
#include <unordered_map>
#include <GLFW/glfw3.h>
#include <stdexcept>

using namespace suisho;

Mouse::Mouse(void* win) : win_(win)
{}

bool Mouse::poll() {
    glfwPollEvents();
    if (glfwGetError(nullptr) != GLFW_NO_ERROR) {
        return false;
    }

    GLFWwindow* ctx = reinterpret_cast<GLFWwindow*>(win_);
    for (int key = Mouse::kLeft; key < Mouse::kKeycodeCount; ++key) {
        states_[key] = (glfwGetMouseButton(ctx, key) == GLFW_PRESS);
    }

    return true;
}

bool Mouse::isPressed(int keycode) {
    if (keycode < 0 || keycode >= kKeycodeCount) {
        throw std::runtime_error(std::string("Mouse:: Invalid keycode ") + (char)(keycode + '0'));
    }

    return states_[keycode];
}

Vec2 Mouse::getAxis2D(int) {
    GLFWwindow* ctx = reinterpret_cast<GLFWwindow*>(win_);
    int win_w, win_h;
    glfwGetWindowSize(ctx, &win_w, &win_h);

    double x, y;
    glfwGetCursorPos(ctx, &x, &y);

    return Vec2(x, -y + win_h);
}
