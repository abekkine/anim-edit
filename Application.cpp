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
        display_.WorldMode();

        // Sample animation rendering
        // TODO

        // Sample ui rendering
        // TODO

        // End

        display_.PostRender();

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        start = end;
    }

    display_.Exit();
}

