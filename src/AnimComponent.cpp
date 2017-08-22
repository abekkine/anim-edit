#include "AnimComponent.h"

#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "PointManager.h"

AnimComponent::AnimComponent(int frame)
: frame_number_(frame) {

    selected_ = false;
    SetColor(1.0, 1.0, 1.0);
    p0_ = POINTS.AddPoint(frame_number_, 0.0, 0.0);
    p1_ = POINTS.AddPoint(frame_number_, 0.0, 0.0);
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

    p0_->x_ = x;
    p0_->y_ = y;
}

void AnimComponent::SetP1(double x, double y) {

    p1_->x_ = x;
    p1_->y_ = y;
}
 
void AnimComponent::Render(int frame) {

    if (frame != frame_number_) return;

    if (p0_->selected_ != Point::NONE ||
        p1_->selected_ != Point::NONE) {
        glLineWidth(3.0);
    }
    else {
        glLineWidth(1.0);
    }

    glColor4fv(color_);
    glBegin(GL_LINES);
    glVertex3d(p0_->x_, p0_->y_, 0.0);
    glVertex3d(p1_->x_, p1_->y_, 0.0);
    glEnd();

    if (p0_->selected_ == Point::SELECT) {
        glPointSize(4.0);
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_POINTS);
        glVertex3d(p0_->x_, p0_->y_, -1.0);
        glEnd();
    }
    else if (p0_->selected_ == Point::MARK) {
        glPointSize(4.0);
        glColor3f(1.0, 0.0, 1.0);
        glBegin(GL_POINTS);
        glVertex3d(p0_->x_, p0_->y_, -1.0);
        glEnd();
    }

    if (p1_->selected_ == Point::SELECT) {
        glPointSize(4.0);
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_POINTS);
        glVertex3d(p1_->x_, p1_->y_, -1.0);
        glEnd();
    }
    else if (p1_->selected_ == Point::MARK) {
        glPointSize(4.0);
        glColor3f(1.0, 0.0, 1.0);
        glBegin(GL_POINTS);
        glVertex3d(p1_->x_, p1_->y_, -1.0);
        glEnd();
    }
}
