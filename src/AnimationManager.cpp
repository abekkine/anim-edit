#include "AnimationManager.h"

#include <GLFW/glfw3.h>

#include <iostream>

#include "EventService.h"
#include "FrameControlEvent.h"

AnimationManager::AnimationManager()
: test_flag_(false) {
    active_frame_ = 0;
    number_of_frames_ = 1;
}

AnimationManager::~AnimationManager() {
}

void AnimationManager::Init() {

    EVENTS.Subscribe("keyboard",
        std::bind(&AnimationManager::frameControlEventHandler, this, std::placeholders::_1));

    // TEST : add some components
    AnimComponent* c1 = new AnimComponent(0);
    c1->SetColor(1.0, 0.0, 0.0);
    c1->SetP0(0.0, 0.0);
    c1->SetP1(40.0, 90.0);

    AnimComponent* c2 = new AnimComponent(0);
    c2->SetColor(0.0, 1.0, 0.0);
    c2->SetP0(0.0, 0.0);
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
                std::cout << "Next Frame" << std::endl; break;
            case FrameControlEvent::PREV_FRAME:
                std::cout << "Prev Frame" << std::endl; break;
            case FrameControlEvent::FIRST_FRAME:
                std::cout << "First Frame" << std::endl; break;
            case FrameControlEvent::LAST_FRAME:
                std::cout << "Last Frame" << std::endl; break;
            default:
                break;
        }
    }
}

