#include "AnimationManager.h"

#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>

#include "json.hpp"
using json = nlohmann::json;

#include "EventService.h"
#include "FrameControlEvent.h"
#include "WorldPositionEvent.h"
#include "EditEvent.h"
#include "FileEvent.h"
#include "MouseButtonEvent.h"
#include "UiDisplayEvent.h"
#include "PointManager.h"

AnimationManager::AnimationManager()
: test_flag_(false) {
    active_frame_ = 0;
    number_of_frames_ = 1;
    edit_mode_ = NONE;
    playback_mode_ = 0;
    onion_skin_mode_ = 0;
    max_onion_frames_ = 3;
    world_x_ = 0.0;
    world_y_ = 0.0;
    MarkPoint((Point*)0);
}

AnimationManager::~AnimationManager() {

    // Delete components
    for (auto c : components_) {
        delete c;
    }
}

void AnimationManager::MarkPoint(Point* mp) {

    marked_point_ = mp;
}

void AnimationManager::Init() {

    frameTimer_.Reset();

    EVENTS.Subscribe("frame",
        std::bind(&AnimationManager::frameControlEventHandler, this, std::placeholders::_1));

    EVENTS.Subscribe("pos",
        std::bind(&AnimationManager::worldPosEventHandler, this, std::placeholders::_1));

    EVENTS.Subscribe("edit",
        std::bind(&AnimationManager::editEventHandler, this, std::placeholders::_1));

    EVENTS.Subscribe("button",
        std::bind(&AnimationManager::buttonEventHandler, this, std::placeholders::_1));

    EVENTS.Subscribe("file",
        std::bind(&AnimationManager::fileEventHandler, this, std::placeholders::_1));
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

    if (playback_mode_) {

        if (frameTimer_.GetElapsed() > 0.04) {
            active_frame_++;
            if (active_frame_ == number_of_frames_) {
                active_frame_ = 0;
            }
            frameTimer_.Reset();
        }
    }

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
                active_frame_ = number_of_frames_-1; break;
            case FrameControlEvent::TOGGLE_PLAYBACK:
                TogglePlayback(); break;
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
            case EditEvent::DELETE_COMPONENT:
                DeleteComponent();
                break;
            case EditEvent::DELETE_FRAME:
                DeleteFrame();
                break;
            default:
                break;
        }
    }
}

void AnimationManager::fileEventHandler(EventInterface* event) {
    FileEvent* e = dynamic_cast<FileEvent*>(event);
    if (e != 0) {
        switch(e->GetType()) {
            case FileEvent::SAVE:
                SaveAnimation(); break;
            case FileEvent::LOAD:
                LoadAnimation(); break;
            case FileEvent::NONE:
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
    // DEBUG
    std::cout << "ClearSelections()" << std::endl;  
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

void AnimationManager::DeleteComponent() {
    std::cout << "Delete Component Event" << std::endl;

    std::lock_guard<std::mutex> lock(component_mutex_);
    CursorUpdate();
    if (marked_point_ != 0) {
        if (marked_point_->selected_ == Point::MARK) {
            std::cout << "Component to be deleted " << marked_point_->parent_ << std::endl;
            for (auto iC=components_.begin(); iC!=components_.end();) {
                if ((*iC)->id_ == marked_point_->parent_) {

                    delete (*iC);
                    components_.erase(iC);
                    break;
                }
                else {
                    ++iC;
                }
            }
        } else {
            marked_point_ = 0;
        }
    }
}

void AnimationManager::DeleteFrame() {
    if (number_of_frames_ > 1) {
        std::cout << "Delete frame(" << active_frame_ << ")" << std::endl;
        DeleteComponentsOf(active_frame_);
        MoveComponentsBackOneFrame(active_frame_);
        number_of_frames_--;
    }
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

void AnimationManager::DeleteComponentsOf(int frame) {

    for(auto iC=components_.begin(); iC!=components_.end();) {
        if (frame == (*iC)->Frame()) {
            delete (*iC);
            components_.erase(iC);
        }
        else {
            ++iC;
        }
    }
}

void AnimationManager::MoveComponentsBackOneFrame(int frame) {

    for(auto component : components_) {
        if (frame < component->Frame()) {
            component->MoveBackOneFrame();
        }
    }
}

void AnimationManager::TogglePlayback() {
    if (number_of_frames_ < 2) return;
    playback_mode_ ^= 1;
    if (playback_mode_) {
        std::cout << "Playback Mode : ON" << std::endl;
    }
    else {
        std::cout << "Playback Mode : OFF" << std::endl;
    }
}

void AnimationManager::SaveAnimation() {

    std::fstream saveFile("save.json", std::fstream::out | std::fstream::trunc);

    json j_;

    j_["active_frame"] = active_frame_;
    j_["number_of_frames"] = number_of_frames_;
    j_["components"] = {};

    for (auto c : components_) {
        j_["components"].push_back(c->DumpJSON());
    }

    saveFile << j_.dump(4);
    saveFile.close();
}

void AnimationManager::LoadAnimation() {
    // TODO
    std::cout << "Load Animation commanded" << std::endl;
}