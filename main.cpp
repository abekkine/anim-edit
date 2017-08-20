#include <iostream>

#include "Version.h"
#include "Application.h"

void displayVersion() {
    std::cout << VERSION_STR << std::endl;
}

int main() {

    displayVersion();

    Application* app = new Application();
    
    try {
        app->Init();
        app->Run();
        app->Exit();
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}



