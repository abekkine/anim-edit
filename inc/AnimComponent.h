#ifndef ANIM_COMPONENT_H_
#define ANIM_COMPONENT_H_

#include <stdint.h>

#include <vector>

class AnimComponent {
public:
    AnimComponent(int frame);
    ~AnimComponent();
    void SetColor(float r, float g, float b);
    void SetP0(double x, double y);
    void SetP1(double x, double y);
    void Render(int frame);
    std::vector<uint8_t> InVicinityOf(int frame, double x, double y, double vicinity=25.0);
    void Select(uint8_t value);
private:
    uint8_t selected_;
    int frame_number_;
    float color_[4];
    double x0_, y0_;
    double x1_, y1_;
};

#endif  // ANIM_COMPONENT_H_

