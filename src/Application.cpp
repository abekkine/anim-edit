#include "Application.h"

#include <iostream>
#include <chrono>

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
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    // TODO : move following block into display thread.
    while (not display_.QuitRequested()) {
        display_.PreRender();

        // Sample animation rendering
        display_.WorldMode();
        animator_.Render();

        // Sample ui rendering
        display_.UiMode();
        ui_.Render();

        display_.PostRender();

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        start = end;
    }

    display_.Exit();
}

