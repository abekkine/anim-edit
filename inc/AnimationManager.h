#ifndef ANIMATION_MANAGER_H_
#define ANIMATION_MANAGER_H_

#include <vector>

#include "AnimComponent.h"
#include "EventInterface.h"
#include "Point.h"

class AnimationManager {
public:
    AnimationManager();
    ~AnimationManager();
    void Init();
    void Render();
private:
    void RenderTest();
    void RenderScene();
    void CursorUpdate();
private:
    void frameControlEventHandler(EventInterface* event);
    void worldPosEventHandler(EventInterface* event);
    void editEventHandler(EventInterface* event);
private:
    const bool test_flag_;
    int number_of_frames_;
    int active_frame_;
    uint8_t edit_mode_;
    double world_x_;
    double world_y_;
    std::vector<AnimComponent*> components_;
    std::vector<Point*> point_selection_list_;
};

#endif  // ANIMATION_MANAGER_H_
