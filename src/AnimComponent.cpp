#include "AnimComponent.h"

#include <GLFW/glfw3.h>

AnimComponent::AnimComponent(int frame)
: frame_number_(frame) {

    SetColor(1.0, 1.0, 1.0);
    SetP0(0.0, 0.0);
    SetP1(0.0, 0.0);
}

AnimComponent::~AnimComponent() {
}

void AnimComponent::SetColor(float r, float g, float b) {

    color_[0] = r;
    color_[1] = g;
    color_[2] = b;
    color_[3] = 1.0;
}

void AnimComponent::SetP0(double x, double y) {
    x0_ = x;
    y0_ = y;
}

void AnimComponent::SetP1(double x, double y) {
    x1_ = x;
    y1_ = y;
}
 
void AnimComponent::Render(int frame) {

    if (frame != frame_number_) return;

    glColor4fv(color_);
    glBegin(GL_LINES);
    glVertex2d(x0_, y0_);
    glVertex2d(x1_, y1_);
    glEnd();
}

