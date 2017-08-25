#ifndef ANIM_COMPONENT_H_
#define ANIM_COMPONENT_H_

#include <stdint.h>

#include <vector>

#include "json.hpp"
using json = nlohmann::json;

#include "Point.h"

class AnimComponent {
public:
    explicit AnimComponent(int frame);
    ~AnimComponent();
    int Frame() { return frame_number_; }
    void SetColor(float r, float g, float b);
    void SetP0(double x, double y);
    void SetP1(double x, double y);
    void MoveBackOneFrame();
    void RenderLines();
    void RenderPoints();
    void Render(int frame);
    void RenderAlpha(std::vector<int>& alpha_frames);
    json& DumpJSON();

public:
    int id_;
private:
    static int num_;
    uint8_t selected_;
    int frame_number_;
    float color_[4];
    json j_;

    Point* p0_;
    Point* p1_;
};

#endif  // ANIM_COMPONENT_H_

