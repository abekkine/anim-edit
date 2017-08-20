#include "UiManager.h"

#include <GLFW/glfw3.h>

UiManager::UiManager()
: testFlag_(true) {
}

UiManager::~UiManager() {
}

void UiManager::Init() {
}

void UiManager::Render() {
    if (testFlag_) {
        RenderTest();
    }
    else {
        // TODO
    }
}

void UiManager::RenderTest() {
    glTranslated(10, 10, 0);
    glColor3f(0.0, 0.0, 0.8);
    glBegin(GL_QUADS);
    glVertex2i(0, 0);
    glVertex2i(40, 0);
    glVertex2i(40, 40);
    glVertex2i(0, 40);
    glEnd();
}

