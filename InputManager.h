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
    void SetWindow(GLFWwindow* win);
    void Resize(GLFWwindow* win, int width, int height);
    void Keyboard(GLFWwindow* win, int key, int scancode, int action, int mods);
    void Button(GLFWwindow* win, int button, int action, int mods);
    void Cursor(GLFWwindow* win, double x, double y);
private:
    InputManager();
    ~InputManager();
    void ProcessKeys(int key);
private:
    GLFWwindow* window_;
    int resize_width_;
    int resize_height_;
};

#define INPUT InputManager::Instance()

#endif // INPUT_MANAGER_H_

