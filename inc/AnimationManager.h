#ifndef ANIMATION_MANAGER_H_
#define ANIMATION_MANAGER_H_

#include <vector>
#include <unordered_map>

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
    void CursorUpdate();
    void SelectComponentsNearTo(double x, double y);
private:
    void frameControlEventHandler(EventInterface* event);
    void cursorEventHandler(EventInterface* event);
    void worldPosEventHandler(EventInterface* event);
    void editEventHandler(EventInterface* event);
private:
    const bool test_flag_;
    int number_of_frames_;
    int active_frame_;
    uint8_t edit_mode_;
    double cursor_x_;
    double cursor_y_;
    double world_x_;
    double world_y_;
    std::vector<AnimComponent*> components_;
    std::unordered_map<AnimComponent*, std::vector<uint8_t>> component_selection_list_;
};

#endif  // ANIMATION_MANAGER_H_

