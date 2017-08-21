#ifndef ANIMATION_MANAGER_H_
#define ANIMATION_MANAGER_H_

#include <vector>

#include "AnimComponent.h"
#include "EventInterface.h"

class AnimationManager {
public:
    AnimationManager();
    ~AnimationManager();
    void Init();
    void Render();
private:
    void RenderTest();
    void RenderScene();
private:
    void frameControlEventHandler(EventInterface* event);
private:
    const bool test_flag_;
    int number_of_frames_;
    int active_frame_;
    std::vector<AnimComponent*> components_;
};

#endif  // ANIMATION_MANAGER_H_

