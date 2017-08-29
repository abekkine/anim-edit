#ifndef ANIMATION_MANAGER_H_
#define ANIMATION_MANAGER_H_

#include <vector>
#include <memory>
#include <unordered_map>
#include <mutex>

#include "AnimComponent.h"
#include "EventInterface.h"
#include "Point.h"
#include "Timer.h"

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
    void MarkPoint(std::shared_ptr<Point> mp);
    void Init();
    void Render();
private:
    void RenderTest();
    void RenderScene();
    void ToggleEditMode();
    void ToggleOnionSkin();
    void TogglePlayback();
    void AddComponent();
    void DeleteComponent();
    void DeleteFrame();
    void SetActiveFrame(int frame);
    void DeleteAll();
    void AddFrame();
    void CursorUpdate();
    void UpdatePointSelection();
    void ClearSelections();
    void CalculateAlphaFrames();
    void DeleteComponentsOf(int frame);
    void MoveComponentsBackOneFrame(int frame);
    void LoadAnimation();
    void SaveAnimation();
    std::vector<std::shared_ptr<Point>> GetPointsNearOf(double x, double y);
private:
    void frameControlEventHandler(EventInterface* event);
    void worldPosEventHandler(EventInterface* event);
    void editEventHandler(EventInterface* event);
    void buttonEventHandler(EventInterface* event);
    void fileEventHandler(EventInterface* event);
private:
    const bool test_flag_;
    int id_counter_;
    int number_of_frames_;
    int active_frame_;
    EditType edit_mode_;
    uint8_t playback_mode_;
    uint8_t onion_skin_mode_;
    int max_onion_frames_;
    double world_x_;
    double world_y_;
    std::vector<std::vector<std::shared_ptr<AnimComponent>>> frames_;
    std::vector<std::shared_ptr<Point>> point_selection_list_;
    std::shared_ptr<Point> marked_point_;
    std::mutex world_pos_mutex_;
    std::mutex component_mutex_;
    std::vector<int> alpha_frames_;
    Timer frameTimer_;
};

#endif  // ANIMATION_MANAGER_H_

