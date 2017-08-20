#include "InputManager.h"

#include <iostream>

InputManager::InputManager()
: window_(nullptr),
  resize_width_(-1),
  resize_height_(-1)
{
}

InputManager::~InputManager()
{
}

void InputManager::SetWindow(GLFWwindow* win)
{
    window_ = win;
}

void InputManager::Resize(GLFWwindow* win, int width, int height)
{
    if (window_ == nullptr) throw;

    if (window_ == win) {
        // TODO : Handle resize event, not needed for now.
        resize_width_ = width;
        resize_height_ = height;
    }
}

void InputManager::Keyboard(GLFWwindow* win, int key, int scancode, int action, int mods)
{
    if (window_ == nullptr) throw;

    if (window_ == win) {
        if (action == GLFW_RELEASE && key == GLFW_KEY_ESCAPE) {
            // TODO : Issue [quit request event]
        } else if (action == GLFW_PRESS) {
            // TODO : Process scancode and mods, too.
            (void)scancode;
            (void)mods;
            ProcessKeys(key);
        }
    }
}

void InputManager::Button(GLFWwindow* win, int button, int action, int mods)
{
    if (window_ == nullptr) throw;

    if (window_ == win) {
        // TODO
        (void)button;
        (void)action;
        (void)mods;
    }
}

void InputManager::Cursor(GLFWwindow* win, double x, double y)
{
    if (window_ == nullptr) throw;

    if (window_ == win) {
        // TODO
        (void)x;
        (void)y;
    }
}

void InputManager::ProcessKeys(int key)
{
    // TODO : Issue [keypress event], or some complex, evaluated event.
    switch (key)
    {
        case GLFW_KEY_SPACE:
            std::cout << "SPACE BAR pressed!" << std::endl;
            break;
        default:
            break;
    }
}

