#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <GLFW/glfw3.h>

#include <string>

#include "EventInterface.h"

class Display {
public:
    Display();
    ~Display();
    void SetViewport(double left, double right, double top, double bottom, double near=-1.0, double far=1.0);
    void SetScreenSize(int width, int height);
    void SetFullscreen(bool value);
    void SetBlending(bool value);
    void SetSmoothing(bool value);
    void Init();
    void Exit();
    void PreRender();
    void PostRender();
    bool QuitRequested();
    void WorldMode();
    void UiMode();
private:
    void InitGraphics();
    void ConfigureGraphics();
    void ForceQuit();
private:
    void quitEventHandler(EventInterface* event);
private:
    static void errorCallback(int error, const char* description);
    static void resizeCallback(GLFWwindow* win, int width, int height);
    static void keyCallback(GLFWwindow* win, int key, int scancode, int action, int mods);
    static void mouseButtonCallback(GLFWwindow* win, int button, int action, int mods);
    static void cursorPositionCallback(GLFWwindow* win, double x, double y);
private:
    bool full_screen_enabled_;
    bool blending_enabled_;
    bool smoothing_enabled_;
    int screen_width_;
    int screen_height_;
    // viewport (for ortho)
    double viewport_left_;
    double viewport_right_;
    double viewport_top_;
    double viewport_bottom_;
    double viewport_near_;
    double viewport_far_;
    const std::string application_name_;

    GLFWwindow* window_;
};

#define DISPLAY Display::Instance()

#endif // DISPLAY_H_

