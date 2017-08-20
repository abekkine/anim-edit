#ifndef ANIMATION_MANAGER_H_
#define ANIMATION_MANAGER_H_

class AnimationManager {
public:
    AnimationManager();
    ~AnimationManager();
    void Init();
    void Render();
private:
    void RenderTest();
private:
    const bool testFlag_;
};

#endif  // ANIMATION_MANAGER_H_

