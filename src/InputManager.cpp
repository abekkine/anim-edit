#include "InputManager.h"

#include <iostream>
#include <string>

#include "EventService.h"
#include "QuitEvent.h"
#include "FrameControlEvent.h"
#include "WorldPositionEvent.h"
#include "EditEvent.h"
#include "MouseButtonEvent.h"

InputManager::InputManager()
: window_(nullptr),
  screen_width_(-1),
  screen_height_(-1)
{
}

InputManager::~InputManager()
{
}

void InputManager::SetWindow(GLFWwindow* win, int width, int height)
{
    window_ = win;
    screen_width_ = width;
    screen_height_ = height;
}

void InputManager::SetViewport(double l, double r, double b, double t)
{
    vp_left_ = l;
    vp_right_ = r;
    vp_bottom_ = b;
    vp_top_ = t;
}

void InputManager::Resize(GLFWwindow* win, int width, int height)
{
    if (window_ == nullptr) throw;

    if (window_ == win) {
        // TODO : Handle resize event, not needed for now.
        screen_width_ = width;
        screen_height_ = height;
    }
}

void InputManager::Keyboard(GLFWwindow* win, int key, int scancode, int action, int mods)
{
    if (window_ == nullptr) throw;

    if (window_ == win) {
        if (action == GLFW_RELEASE && key == GLFW_KEY_ESCAPE) {
            QuitEvent* event = new QuitEvent();
            EVENTS.Publish("quit", event);
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
        switch(button) {
        case GLFW_MOUSE_BUTTON_LEFT:
            switch (action) {
            case GLFW_PRESS:
                InvokeLeftButtonDownEvent(); break;
            case GLFW_RELEASE:
                InvokeLeftButtonUpEvent(); break;
            default:
                break;
            }
            break;
        case GLFW_MOUSE_BUTTON_RIGHT:
        case GLFW_MOUSE_BUTTON_MIDDLE:
        default:
            break;
        }

        (void)mods;
    }
}

void InputManager::Cursor(GLFWwindow* win, double x, double y)
{
    if (window_ == nullptr) throw;

    if (window_ == win) {

        double wx, wy;
        wx = vp_left_ + ((vp_right_ - vp_left_) * x / screen_width_);
        wy = vp_bottom_ + ((vp_top_ - vp_bottom_) * y / screen_height_);
        wy = -wy;

        InvokeWorldPositionEvent(wx, wy);
    }
}

void InputManager::ProcessKeys(int key)
{
    // TODO : Issue [keypress event], or some complex, evaluated event.
    switch (key)
    {
        case GLFW_KEY_E:
            InvokeToggleEditEvent(); break;
        case GLFW_KEY_M:
            InvokeMarkNextEvent(); break;
        case GLFW_KEY_A:
            InvokeAddComponentEvent(); break;
        case GLFW_KEY_SPACE:
        case GLFW_KEY_RIGHT:
        case GLFW_KEY_LEFT:
        case GLFW_KEY_UP:
        case GLFW_KEY_DOWN:
            InvokeFrameControlEvent(key); break;
        default:
            std::cout << "Key press : " << key << std::endl;
            break;
    }
}

void InputManager::InvokeFrameControlEvent(int key) {
    FrameControlEvent* event = 0;
    switch (key) {
        case GLFW_KEY_SPACE:
            event = new FrameControlEvent(FrameControlEvent::ONION_SKIN); break;
        case GLFW_KEY_RIGHT:
            event = new FrameControlEvent(FrameControlEvent::NEXT_FRAME); break;
        case GLFW_KEY_LEFT:
            event = new FrameControlEvent(FrameControlEvent::PREV_FRAME); break;
        case GLFW_KEY_UP:
            event = new FrameControlEvent(FrameControlEvent::FIRST_FRAME); break;
        case GLFW_KEY_DOWN:
            event = new FrameControlEvent(FrameControlEvent::LAST_FRAME); break;
        default:
            break;
    }

    if (event != 0) {
        EVENTS.Publish("keyboard", event);
    }
}

void InputManager::InvokeLeftButtonDownEvent() {
    MouseButtonEvent* event = new MouseButtonEvent(MouseButtonEvent::LEFT_DOWN);
    EVENTS.Publish("button", event);
}

void InputManager::InvokeLeftButtonUpEvent() {
    MouseButtonEvent* event = new MouseButtonEvent(MouseButtonEvent::LEFT_UP);
    EVENTS.Publish("button", event);
}

void InputManager::InvokeWorldPositionEvent(double x, double y) {
    WorldPositionEvent* event = new WorldPositionEvent(x, y);
    EVENTS.Publish("wpos", event);
}

void InputManager::InvokeToggleEditEvent() {
    EditEvent* event = new EditEvent(EditEvent::TOGGLE);
    EVENTS.Publish("edit", event);
}

void InputManager::InvokeMarkNextEvent() {
    EditEvent* event = new EditEvent(EditEvent::MARK_NEXT);
    EVENTS.Publish("edit", event);
}

void InputManager::InvokeAddComponentEvent() {
    EditEvent* event = new EditEvent(EditEvent::ADD_COMPONENT);
    EVENTS.Publish("edit", event);
}