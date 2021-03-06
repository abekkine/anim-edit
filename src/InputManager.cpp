#include "InputManager.h"

#include <iostream>
#include <string>

#include "EventService.h"
#include "QuitEvent.h"
#include "FrameControlEvent.h"
#include "WorldPositionEvent.h"
#include "EditEvent.h"
#include "FileEvent.h"
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
                LeftButtonDown(); break;
            case GLFW_RELEASE:
                LeftButtonUp(); break;
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

        UpdateWorldPosition(wx, wy);
    }
}

void InputManager::ProcessKeys(int key)
{
    // TODO : Issue [keypress event], or some complex, evaluated event.
    switch (key)
    {
        case GLFW_KEY_E:
            ToggleEditMode(); break;
        case GLFW_KEY_M:
            MarkNextPoint(); break;
        case GLFW_KEY_A:
            AddNewComponent(); break;
        case GLFW_KEY_D:
            DeleteSelectedComponent(); break;
        case GLFW_KEY_X:
            DeleteActiveFrame(); break;
        case GLFW_KEY_F:
            AddNewFrame(); break;
        case GLFW_KEY_O:
            ToggleOnionSkin(); break;
        case GLFW_KEY_RIGHT:
            GotoNextFrame(); break;
        case GLFW_KEY_LEFT:
            GotoPrevFrame(); break;
        case GLFW_KEY_UP:
            GotoFirstFrame(); break;
        case GLFW_KEY_DOWN:
            GotoLastFrame(); break;
        case GLFW_KEY_SPACE:
            TogglePlayback(); break;
        case GLFW_KEY_S:
            SaveToDisk(); break;
        case GLFW_KEY_L:
            LoadFromDisk(); break;
        default:
            std::cout << "Key press : " << key << std::endl;
            break;
    }
}

void InputManager::GotoNextFrame() {
    FrameControlEvent* event = new FrameControlEvent(FrameControlEvent::NEXT_FRAME);
    EVENTS.Publish("frame", event);
}

void InputManager::GotoPrevFrame() {
    FrameControlEvent* event = new FrameControlEvent(FrameControlEvent::PREV_FRAME);
    EVENTS.Publish("frame", event);
}

void InputManager::GotoFirstFrame() {
    FrameControlEvent* event = new FrameControlEvent(FrameControlEvent::FIRST_FRAME);
    EVENTS.Publish("frame", event);
}

void InputManager::GotoLastFrame() {
    FrameControlEvent* event = new FrameControlEvent(FrameControlEvent::LAST_FRAME);
    EVENTS.Publish("frame", event);
}

void InputManager::TogglePlayback() {
    FrameControlEvent* event = new FrameControlEvent(FrameControlEvent::TOGGLE_PLAYBACK);
    EVENTS.Publish("frame", event);
}

void InputManager::LeftButtonDown() {
    MouseButtonEvent* event = new MouseButtonEvent(MouseButtonEvent::LEFT_DOWN);
    EVENTS.Publish("button", event);
}

void InputManager::LeftButtonUp() {
    MouseButtonEvent* event = new MouseButtonEvent(MouseButtonEvent::LEFT_UP);
    EVENTS.Publish("button", event);
}

void InputManager::UpdateWorldPosition(double x, double y) {
    WorldPositionEvent* event = new WorldPositionEvent(x, y);
    EVENTS.Publish("pos", event);
}

void InputManager::ToggleEditMode() {
    EditEvent* event = new EditEvent(EditEvent::TOGGLE_EDIT);
    EVENTS.Publish("edit", event);
}

void InputManager::MarkNextPoint() {
    EditEvent* event = new EditEvent(EditEvent::MARK_NEXT);
    EVENTS.Publish("edit", event);
}

void InputManager::AddNewComponent() {
    EditEvent* event = new EditEvent(EditEvent::ADD_COMPONENT);
    EVENTS.Publish("edit", event);
}

void InputManager::AddNewFrame() {
    EditEvent* event = new EditEvent(EditEvent::ADD_FRAME);
    EVENTS.Publish("edit", event);
}

void InputManager::ToggleOnionSkin() {
    EditEvent* event = new EditEvent(EditEvent::TOGGLE_ONION_SKIN);
    EVENTS.Publish("edit", event);
}

void InputManager::DeleteSelectedComponent() {
    EditEvent* event = new EditEvent(EditEvent::DELETE_COMPONENT);
    EVENTS.Publish("edit", event);
}

void InputManager::DeleteActiveFrame() {
    EditEvent* event = new EditEvent(EditEvent::DELETE_FRAME);
    EVENTS.Publish("edit", event);
}

void InputManager::SaveToDisk() {
    FileEvent* event = new FileEvent(FileEvent::SAVE);
    EVENTS.Publish("file", event);
}

void InputManager::LoadFromDisk() {
    FileEvent* event = new FileEvent(FileEvent::LOAD);
    EVENTS.Publish("file", event);
}