#include "UiManager.h"

#include <GLFW/glfw3.h>

#include "TextManager.h"
#include "EventService.h"
#include "UiDisplayEvent.h"

UiManager::UiManager()
: testFlag_(false) {
}

UiManager::~UiManager() {
}

void UiManager::Init() {

    TextManager::Instance()->AddFont("Ubuntu", "./Ubuntu.ttf");

    EVENTS.Subscribe("ui",
        std::bind(&UiManager::handleUiDisplayEvent, this, std::placeholders::_1));
}

void UiManager::Render() {
    if (testFlag_) {
        RenderTest();
    }
    else {
        TextManager::Instance()->UseFont("Ubuntu", 20);
        glColor3f(1.0f, 1.0f, 1.0f);

        for (auto entry : text_list_) {
            auto text = entry.second;
            glRasterPos2i(text.x, text.y);
            TextManager::Instance()->Render(text.message);
        }
    }
}

void UiManager::RenderTest() {
    glTranslated(10, 10, 0);
    glColor3f(0.0, 0.0, 0.8);
    glBegin(GL_QUADS);
    glVertex2i(0, 0);
    glVertex2i(40, 0);
    glVertex2i(40, 40);
    glVertex2i(0, 40);
    glEnd();

    TextManager::Instance()->UseFont("Ubuntu", 20);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2i(10, 10);
    TextManager::Instance()->Render( "ABC" );
}

void UiManager::handleUiDisplayEvent(EventInterface* event) {
    UiDisplayEvent* e = dynamic_cast<UiDisplayEvent*>(event);

    if (e != 0) {
        UiText t;
        t.x = e->X();
        t.y = e->Y();
        t.message = e->Message();
        text_list_[e->Label()] = t;
    }
}
