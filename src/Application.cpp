#include "Application.h"

#include <iostream>

Application::Application()
: quit_requested_(false)
{
}

Application::~Application()
{
}

void Application::Init()
{
    display_.Init();
    ui_.Init();
    animator_.Init();
}

void Application::Exit()
{
}

void Application::Run()
{
    while (not display_.QuitRequested()) {
        display_.PreRender();

        // Animation rendering
        display_.WorldMode();
        animator_.Render();

        // Ui rendering
        display_.UiMode();
        ui_.Render();

        display_.PostRender();
    }

    display_.Exit();
}

