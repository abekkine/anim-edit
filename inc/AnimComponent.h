#ifndef ANIM_COMPONENT_H_
#define ANIM_COMPONENT_H_

#include <stdint.h>

#include <vector>

#include "json.hpp"
using json = nlohmann::json;

#include "Point.h"

#include <memory>

class AnimComponent {
public:
    explicit AnimComponent(int id);
    ~AnimComponent();
    void SetColor(float r, float g, float b);
    void SetP0(double x, double y);
    void SetP1(double x, double y);
    void RenderLines();
    void RenderPoints();
    void Render();
    void RenderInBetween(double ratio, std::shared_ptr<AnimComponent> ptrComp);
    void RenderAlpha(int alpha_index, int a_size);
    std::vector<std::shared_ptr<Point>> PointsInVicinity(double x, double y, double vicinity);
    json& DumpJSON();
public:
    int id_;
    std::shared_ptr<Point> p0_;
    std::shared_ptr<Point> p1_;
private:
    uint8_t selected_;
    float color_[4];
    json j_;
};

#endif  // ANIM_COMPONENT_H_

