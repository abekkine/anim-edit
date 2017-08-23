#include "AnimationManager.h"

#include <GLFW/glfw3.h>

#include <iostream>

#include "EventService.h"
#include "FrameControlEvent.h"
#include "WorldPositionEvent.h"
#include "EditEvent.h"
#include "MouseButtonEvent.h"
#include "UiDisplayEvent.h"
#include "PointManager.h"

AnimationManager::AnimationManager()
: test_flag_(false) {
    active_frame_ = 0;
    number_of_frames_ = 2;
    edit_mode_ = NONE;
    onion_skin_mode_ = 0;
    max_onion_frames_ = 3;
    world_x_ = 0.0;
    world_y_ = 0.0;
    MarkPoint((Point*)0);
}

AnimationManager::~AnimationManager() {
}

void AnimationManager::MarkPoint(Point* mp) {

    marked_point_ = mp;
}

void AnimationManager::Init() {

    EVENTS.Subscribe("frame",
        std::bind(&AnimationManager::frameControlEventHandler, this, std::placeholders::_1));

    EVENTS.Subscribe("pos",
        std::bind(&AnimationManager::worldPosEventHandler, this, std::placeholders::_1));

    EVENTS.Subscribe("edit",
        std::bind(&AnimationManager::editEventHandler, this, std::placeholders::_1));

    EVENTS.Subscribe("button",
        std::bind(&AnimationManager::buttonEventHandler, this, std::placeholders::_1));

    // TEST : add some components
    AnimComponent* c1 = new AnimComponent(0);
    c1->SetColor(1.0, 0.0, 0.0);
    c1->SetP0(3.0, 0.0);
    c1->SetP1(40.0, 90.0);

    AnimComponent* c2 = new AnimComponent(0);
    c2->SetColor(0.0, 1.0, 0.0);
    c2->SetP0(0.0, 2.0);
    c2->SetP1(30.0, -50.0);

    AnimComponent* c3 = new AnimComponent(1);
    c3->SetColor(0.0, 0.0, 1.0);
    c3->SetP0(0.0, 0.0);
    c3->SetP1(-40.0, 60.0);
    
    components_.push_back(c1);
    components_.push_back(c2);
    components_.push_back(c3);
}

void AnimationManager::Render() {
    if (test_flag_) {
        RenderTest();
    }
    else {
        RenderScene();
    }
}

void AnimationManager::RenderScene() {

    for(auto component : components_) {
        component->Render(active_frame_);
        if (onion_skin_mode_) {
            component->RenderAlpha(alpha_frames_);
        }
    }
}

void AnimationManager::RenderTest() {
    glTranslated(0.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2d(-30.0, 20.0);
    glVertex2d( 30.0, 20.0);
    glVertex2d(  0.0, -30.0);
    glEnd();
}

void AnimationManager::frameControlEventHandler(EventInterface* event) {
    FrameControlEvent* e = dynamic_cast<FrameControlEvent*>(event);
    if (e != 0) {
        switch(e->GetType()) {
            case FrameControlEvent::NEXT_FRAME:
                if (active_frame_ < (number_of_frames_-1))
                    active_frame_++;
                break;
            case FrameControlEvent::PREV_FRAME:
                if (active_frame_ > 0) {
                    active_frame_--;
                }
                break;
            case FrameControlEvent::FIRST_FRAME:
                active_frame_ = 0; break;
            case FrameControlEvent::LAST_FRAME:
                active_frame_ = number_of_frames_-1;
            default:
                break;
        }

        CalculateAlphaFrames();
        {
            UiDisplayEvent* event = new UiDisplayEvent(
                "frame", 10, 10, std::to_string(active_frame_));
            EVENTS.Publish("ui", event);
        }
    }
}

void AnimationManager::worldPosEventHandler(EventInterface* event) {
    WorldPositionEvent* e = dynamic_cast<WorldPositionEvent*>(event);
    if (e != 0) {
        e->GetPosition(world_x_, world_y_);
        CursorUpdate();
    }
}

void AnimationManager::editEventHandler(EventInterface* event) {
    EditEvent* e = dynamic_cast<EditEvent*>(event);
    if (e != 0) {
        switch(e->GetType()) {
            case EditEvent::TOGGLE_EDIT:
                ToggleEditMode();
                break;
            case EditEvent::MARK_NEXT:
                UpdatePointSelection();
                break;
            case EditEvent::ADD_COMPONENT:
                AddComponent();
                break;
            case EditEvent::ADD_FRAME:
                AddFrame();
                break;
            case EditEvent::TOGGLE_ONION_SKIN:
                ToggleOnionSkin();
                break;
            default:
                break;
        }
    }
}

void AnimationManager::buttonEventHandler(EventInterface* event) {
    MouseButtonEvent* e = dynamic_cast<MouseButtonEvent*>(event);
    if (e != 0) {
        switch (e->GetType()) {
            case MouseButtonEvent::LEFT_DOWN:
                std::cout << "Left Button Down" << std::endl;
                if (marked_point_ != 0) {
                    edit_mode_ = MOVE;
                    ClearSelections();
                }
                break;
            case MouseButtonEvent::LEFT_UP:
                std::cout << "Left Button Up" << std::endl;
                edit_mode_ = SELECT;
                MarkPoint((Point*)0);
                break;
            default:
                break;
        }
    }
}

void AnimationManager::ToggleEditMode() {

    if (edit_mode_ == NONE) {
        edit_mode_ = SELECT;
        std::cout << "Edit Mode : SELECT" << std::endl;
    } else {
        edit_mode_ = NONE;
        std::cout << "Edit Mode : NONE" << std::endl;
        ClearSelections();
    }
}

void AnimationManager::ClearSelections() {
    for (auto point : point_selection_list_) {
        point->Select(Point::NONE);
    }
    point_selection_list_.clear();
}

void AnimationManager::UpdatePointSelection() {

    if (point_selection_list_.empty()) return;

    MarkPoint((Point*)0);
    bool mark_found = false;
    for (auto iPoint = point_selection_list_.begin(); iPoint != point_selection_list_.end(); ++iPoint)
    {
        if ((*iPoint)->selected_ == Point::MARK) {
            (*iPoint)->Select(Point::SELECT);
            if ((iPoint + 1) != point_selection_list_.end()) {
                iPoint++;
            } else {
                iPoint = point_selection_list_.begin();
            }
            MarkPoint(*iPoint);
            marked_point_->Select(Point::MARK);
            mark_found = true;
            break;
        }
    }

    if (! mark_found) {
        MarkPoint(point_selection_list_[0]);
        marked_point_->Select(Point::MARK);
    }
}

void AnimationManager::CursorUpdate() {

    if (edit_mode_ == SELECT) {
        point_selection_list_ = POINTS.GetPointsNearOf(active_frame_, world_x_, world_y_);
    } else if (edit_mode_ == MOVE) {
        if (marked_point_ != 0) {
            std::lock_guard<std::mutex> lock(world_pos_mutex_);
            marked_point_->x_ = world_x_;
            marked_point_->y_ = world_y_;
        }
    }
}

void AnimationManager::AddComponent() {
    std::cout << "Add Component Event" << std::endl;

    AnimComponent* c = new AnimComponent(active_frame_);
    c->SetColor(0.8, 0.8, 0.8);
    c->SetP0(world_x_, world_y_);
    c->SetP1(world_x_+10.0, world_y_);

    components_.push_back(c);
}

void AnimationManager::AddFrame() {

    number_of_frames_++;
}

void AnimationManager::ToggleOnionSkin() {

    onion_skin_mode_ ^= 1;

    if (onion_skin_mode_) {
        std::cout << "Onion Skin : ON" << std::endl;
        CalculateAlphaFrames();
    } else {
        std::cout << "Onion Skin : OFF" << std::endl;
    }
}

void AnimationManager::CalculateAlphaFrames() {
    // calculate alpha frames, based on current frame.
    if (max_onion_frames_ > number_of_frames_) {
        for (int i=0 ; i < (max_onion_frames_ - number_of_frames_); i++) {
            AddFrame();
        }
    }

    alpha_frames_.clear();
    int alpha_frame;
    for (int i=1; i<=max_onion_frames_; i++) {
        alpha_frame = active_frame_ - i;
        if (alpha_frame < 0) {
            alpha_frame += number_of_frames_;
        }
        alpha_frames_.push_back(alpha_frame);
    }
}
