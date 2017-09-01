#include "Display.h"

#include <iostream>

#include "InputManager.h"
#include "EventService.h"
#include "QuitEvent.h"

Display::Display()
: application_name_("example")
{
    window_ = 0;
    SetScreenSize(1280, 1280);
    SetFullscreen(false);
    SetBlending(true);
    SetSmoothing(true);
    SetViewport(-100.0, 100.0, -100.0, 100.0, -100.0, 100.0);
}

Display::~Display()
{
    Exit();
}

void Display::SetViewport(double left, double right, double bottom, double top, double near, double far)
{
    viewport_left_ = left;
    viewport_right_ = right;
    viewport_bottom_ = bottom;
    viewport_top_ = top;
    viewport_near_ = near;
    viewport_far_ = far;

    INPUT.SetViewport(left, right, bottom, top);
}

void Display::SetScreenSize(int width, int height)
{
    screen_width_ = width;
    screen_height_ = height;
}

void Display::SetFullscreen(bool value)
{
    full_screen_enabled_ = value;
}

void Display::SetBlending(bool value)
{
    blending_enabled_ = value;
}

void Display::SetSmoothing(bool value)
{
    smoothing_enabled_ = value;
}

void Display::Init()
{
    InitGraphics();
    ConfigureGraphics();

    EVENTS.Subscribe("quit", std::bind(&Display::quitEventHandler, this, std::placeholders::_1));
}

void Display::Exit()
{
    glfwTerminate();
}

void Display::InitGraphics()
{
    glfwSetErrorCallback(errorCallback);
    if (not glfwInit()) {
        std::cerr << "GLFW initialization failed!" << std::endl;
        throw;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    if (full_screen_enabled_) {
        window_ = glfwCreateWindow(
            screen_width_, screen_height_,
            application_name_.c_str(),
            glfwGetPrimaryMonitor(),
            NULL);
    }
    else {
        window_ = glfwCreateWindow(
            screen_width_, screen_height_,
            application_name_.c_str(),
            NULL,
            NULL);
    }

    if (not window_) {
        glfwTerminate();
        std::cerr << "Unable to create GLFW window!" << std::endl;
        throw;
    }
    else {
        INPUT.SetWindow(window_, screen_width_, screen_height_);
    }
}

void Display::ConfigureGraphics()
{
    // Set up callbacks.
    glfwSetKeyCallback(window_, keyCallback);
    glfwSetFramebufferSizeCallback(window_, resizeCallback);
    glfwSetCursorPosCallback(window_, cursorPositionCallback);
    glfwSetMouseButtonCallback(window_, mouseButtonCallback);

    glfwMakeContextCurrent(window_);
    glfwSwapInterval(1);

    if (blending_enabled_) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    if (smoothing_enabled_) {
        glEnable(GL_POLYGON_SMOOTH);
        glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

        glEnable(GL_LINE_SMOOTH);
        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    }
}

void Display::PreRender()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Display::PostRender()
{
    glfwSwapBuffers(window_);
    glfwPollEvents();
}

bool Display::QuitRequested()
{
    return glfwWindowShouldClose(window_);
}

void Display::ForceQuit()
{
    glfwSetWindowShouldClose(window_, GLFW_TRUE);
}

void Display::WorldMode()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(viewport_left_, viewport_right_, viewport_bottom_, viewport_top_, viewport_near_, viewport_far_);

    glMatrixMode(GL_MODELVIEW);
}

void Display::UiMode()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, screen_width_, 0, screen_height_, -1.0, 1.0);
}

void Display::quitEventHandler(EventInterface* event) {
    QuitEvent* e = dynamic_cast<QuitEvent*>(event);
    if (e != 0) {
        ForceQuit();
    }
}

void Display::errorCallback(int error, const char* description)
{
    std::cerr << "GLFW ERROR : [" << error << "] " << description << std::endl;
    throw;
}

void Display::resizeCallback(GLFWwindow* win, int width, int height)
{
    INPUT.Resize(win, width, height);
}

void Display::keyCallback(GLFWwindow* win, int key, int scancode, int action, int mods)
{
    INPUT.Keyboard(win, key, scancode, action, mods);
}

void Display::mouseButtonCallback(GLFWwindow* win, int button, int action, int mods)
{
    INPUT.Button(win, button, action, mods);
}

void Display::cursorPositionCallback(GLFWwindow* win, double x, double y)
{
    INPUT.Cursor(win, x, y);
}
