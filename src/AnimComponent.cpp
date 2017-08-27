#include "AnimComponent.h"

#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <algorithm>

#include "PointManager.h"

#define MAX_ONION_ALPHA 0.5
#define MIN_ONION_ALPHA 0.1

AnimComponent::AnimComponent(int id) : id_(id) {

    selected_ = false;
    SetColor(1.0, 1.0, 1.0);
    p0_ = POINTS.Add(id_, 0.0, 0.0);
    p1_ = POINTS.Add(id_, 0.0, 0.0);
}

AnimComponent::~AnimComponent() {

    POINTS.Delete(p0_->id_);
    POINTS.Delete(p1_->id_);
    p0_.reset();
    p1_.reset();
    std::cout << "~AnimComponent(" << id_ << ")" << std::endl;
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

void AnimComponent::RenderAlpha(int alpha_index, int alpha_size) {

    float alpha = (MAX_ONION_ALPHA - MIN_ONION_ALPHA) * (alpha_size - alpha_index) / (float)alpha_size;
    float a = color_[3];

    color_[3] = MIN_ONION_ALPHA + alpha;
    glLineWidth(1.0);
    RenderLines();

    color_[3] = a;
}

void AnimComponent::Render() {

    if (p0_->selected_ == Point::MARK ||
        p1_->selected_ == Point::MARK) {
        glLineWidth(3.0);
    }
    else {
        glLineWidth(1.0);
    }

    color_[3] = 1.0;
    RenderLines();

    RenderPoints();
}

void AnimComponent::RenderLines() {

    glColor4fv(color_);
    glBegin(GL_LINES);
    glVertex3d(p0_->x_, p0_->y_, 0.0);
    glVertex3d(p1_->x_, p1_->y_, 0.0);
    glEnd();
}

void AnimComponent::RenderPoints() {
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

std::vector<std::shared_ptr<Point>> AnimComponent::PointsInVicinity(double x, double y, double vicinity) {

    std::vector<std::shared_ptr<Point>> plist;
    double dx, dy;
    dx = x - p0_->x_;
    dy = y - p0_->y_;
    if ((dx * dx + dy * dy) < vicinity) {
        if (p0_->selected_ == Point::NONE) {
            p0_->selected_ = Point::SELECT;
        }
        plist.push_back(p0_);
    }
    else {
        p0_->selected_ = Point::NONE;
    }
    dx = x - p1_->x_;
    dy = y - p1_->y_;
    if ((dx * dx + dy * dy) < vicinity) {
        if (p1_->selected_ == Point::NONE) {
            p1_->selected_ = Point::SELECT;
        }
        plist.push_back(p1_);
    }
    else {
        p1_->selected_ = Point::NONE;
    }
    return plist;
}

json& AnimComponent::DumpJSON() {

    j_["p0"]["x"] = p0_->x_;
    j_["p0"]["y"] = p0_->y_;
    j_["p1"]["x"] = p1_->x_;
    j_["p1"]["y"] = p1_->y_;

    return j_;
}
