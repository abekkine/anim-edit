#ifndef ANIM_COMPONENT_H_
#define ANIM_COMPONENT_H_

class AnimComponent {
public:
    AnimComponent(int frame);
    ~AnimComponent();
    void SetColor(float r, float g, float b);
    void SetP0(double x, double y);
    void SetP1(double x, double y);
    void Render(int frame);
private:
    int frame_number_;
    float color_[4];
    double x0_, y0_;
    double x1_, y1_;
};

#endif  // ANIM_COMPONENT_H_

