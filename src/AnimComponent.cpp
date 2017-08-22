#include "AnimComponent.h"

#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

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

    if (selected_) {
        glLineWidth(3.0);
    }
    else {
        glLineWidth(1.0);
    }
    glColor4fv(color_);
    glBegin(GL_LINES);
    glVertex2d(x0_, y0_);
    glVertex2d(x1_, y1_);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glPointSize(4.0);
    glBegin(GL_POINTS);
    switch( selected_ ) {
    case 1:
        glVertex2d(x0_, y0_); break;
    case 2:
        glVertex2d(x1_, y1_); break;
    default:
        break;
    }
    glEnd();
}

void AnimComponent::Select(uint8_t value) {
    selected_ = value;
}

std::vector<uint8_t> AnimComponent::InVicinityOf(int frame, double x, double y, double vicinity) {

    std::vector<uint8_t> list;
    double dx, dy;

    list.clear();

    if (frame == frame_number_) {
        dx = (x - x0_); dy = (y - y0_);
        if ((dx*dx + dy*dy) < vicinity) {
            list.push_back(1);
        }

        dx = (x - x1_); dy = (y - y1_);
        if ((dx*dx + dy*dy) < vicinity) {
            list.push_back(2);
        }
    }

    return list;
}
