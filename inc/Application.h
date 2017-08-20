#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "Display.h"
#include "AnimationManager.h"
#include "UiManager.h"

class Application {
public:
    Application();
    ~Application();
    void Init();
    void Run();
    void Exit();
private:
    bool quit_requested_;
    Display display_;
    AnimationManager animator_;
    UiManager ui_;
};

#endif // APPLICATION_H_

