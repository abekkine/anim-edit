#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

#include <GLFW/glfw3.h>

class InputManager {
public:
    static InputManager& Instance() {
        static InputManager instance_;
        return instance_;
    }
public:
    void SetWindow(GLFWwindow* win, int width, int height);
    void SetViewport(double l, double r, double b, double t);
    void Resize(GLFWwindow* win, int width, int height);
    void Keyboard(GLFWwindow* win, int key, int scancode, int action, int mods);
    void Button(GLFWwindow* win, int button, int action, int mods);
    void Cursor(GLFWwindow* win, double x, double y);
    void WorldPosition(double x, double y);
private:
    InputManager();
    ~InputManager();
    void ProcessKeys(int key);
    void UpdateWorldPosition(double x, double y);
    void ToggleEditMode();
    void ToggleOnionSkin();
    void MarkNextPoint();
    void AddNewComponent();
    void DeleteSelectedComponent();
    void AddNewFrame();
    void LeftButtonDown();
    void LeftButtonUp();
    void GotoNextFrame();
    void GotoPrevFrame();
    void GotoFirstFrame();
    void GotoLastFrame();
private:
    GLFWwindow* window_;
    int screen_width_;
    int screen_height_;
    double vp_left_;
    double vp_right_;
    double vp_bottom_;
    double vp_top_;
};

#define INPUT InputManager::Instance()

#endif // INPUT_MANAGER_H_

