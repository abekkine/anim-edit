#ifndef ANIMATION_MANAGER_H_
#define ANIMATION_MANAGER_H_

#include <vector>
#include <mutex>

#include "AnimComponent.h"
#include "EventInterface.h"
#include "Point.h"

class AnimationManager {
public:
    enum EditType {
        NONE,
        SELECT,
        MARK,
        MOVE
    };
public:
    AnimationManager();
    ~AnimationManager();
    void MarkPoint(Point* mp);
    void Init();
    void Render();
private:
    void RenderTest();
    void RenderScene();
    void ToggleEditMode();
    void AddComponent();
    void CursorUpdate();
    void UpdatePointSelection();
    void ClearSelections();
private:
    void frameControlEventHandler(EventInterface* event);
    void worldPosEventHandler(EventInterface* event);
    void editEventHandler(EventInterface* event);
    void buttonEventHandler(EventInterface* event);
private:
    const bool test_flag_;
    int number_of_frames_;
    int active_frame_;
    EditType edit_mode_;
    double world_x_;
    double world_y_;
    std::vector<AnimComponent*> components_;
    std::vector<Point*> point_selection_list_;
    Point* marked_point_;
    std::mutex world_pos_mutex_;
};

#endif  // ANIMATION_MANAGER_H_

