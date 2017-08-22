#include "AnimationManager.h"

#include <GLFW/glfw3.h>

#include <iostream>

#include "EventService.h"
#include "FrameControlEvent.h"
#include "WorldPositionEvent.h"
#include "EditEvent.h"
#include "PointManager.h"

AnimationManager::AnimationManager()
: test_flag_(false) {
    active_frame_ = 0;
    number_of_frames_ = 2;
    edit_mode_ = 0;
    world_x_ = 0.0;
    world_y_ = 0.0;
}

AnimationManager::~AnimationManager() {
}

void AnimationManager::Init() {

    EVENTS.Subscribe("keyboard",
        std::bind(&AnimationManager::frameControlEventHandler, this, std::placeholders::_1));

    EVENTS.Subscribe("wpos",
        std::bind(&AnimationManager::worldPosEventHandler, this, std::placeholders::_1));

    EVENTS.Subscribe("edit",
        std::bind(&AnimationManager::editEventHandler, this, std::placeholders::_1));

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
            case FrameControlEvent::ONION_SKIN:
                std::cout << "Onion Skin" << std::endl; break;
            case FrameControlEvent::NEXT_FRAME:
                if (active_frame_ < (number_of_frames_-1))
                    active_frame_++;
                break;
            case FrameControlEvent::PREV_FRAME:
                if (active_frame_ > 0) {
                    active_frame_--;
                }
            case FrameControlEvent::FIRST_FRAME:
                active_frame_ = 0; break;
            case FrameControlEvent::LAST_FRAME:
                active_frame_ = number_of_frames_-1;
            default:
                break;
        }
        std::cout << "Frame " << 1+active_frame_ << "/" << number_of_frames_ << std::endl;
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
            case EditEvent::TOGGLE:
                ToggleEditMode();
                break;
            case EditEvent::MARK_NEXT:
                UpdatePointSelection();
                break;
            default:
                break;
        }
    }
}

void AnimationManager::ToggleEditMode() {

    edit_mode_ ^= 1;
    if (edit_mode_) {
        std::cout << "Edit Mode On" << std::endl;
    } else {
        std::cout << "Edit Mode Off" << std::endl;
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
            (*iPoint)->Select(Point::MARK);
            mark_found = true;
            break;
        }
    }

    if (! mark_found) {
        point_selection_list_[0]->Select(Point::MARK);
    }
}

void AnimationManager::CursorUpdate() {

    if (edit_mode_) {
        point_selection_list_ = POINTS.GetPointsNearOf(active_frame_, world_x_, world_y_);
    }
}
