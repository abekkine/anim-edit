#include "AnimationManager.h"

#include <GLFW/glfw3.h>

AnimationManager::AnimationManager()
: testFlag_(true) {
}

AnimationManager::~AnimationManager() {
}

void AnimationManager::Init() {
}

void AnimationManager::Render() {
    if (testFlag_) {
        RenderTest();
    }
    else {
        // TODO
    }
}

void AnimationManager::RenderTest() {
    glTranslated(0.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2d(-30.0, 20.0);
    glVertex2d( 30.0, 20.0);
    glVertex2d(  0.0, -30.0);
    glEnd();
}

