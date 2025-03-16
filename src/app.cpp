#include "app.hpp"
#include "window.hpp"
#include "gfx.hpp"
#include "game.hpp"

#include <iostream>

void App::init()
{
    Window::get_instance().init();
    GFX::get_instance().init();
    Game::get_instance().init();
}

void App::run()
{
    Uint64 prev_time = SDL_GetPerformanceCounter();
    Uint64 freq = SDL_GetPerformanceFrequency();
    float dt = 0.0f;

    while (is_running)
    {
        Uint64 curr_time = SDL_GetPerformanceCounter();
        dt = (float)(curr_time - prev_time) / freq;
        // std::cout << "Delta Time: " << dt << "s, FPS: " << 1.0f / dt << std::endl;
        prev_time = curr_time;

        // Event
        //
        if (!Window::get_instance().event_handling())
        {
            is_running = false;
        }

        // Update
        //
        Game::get_instance().update((float)dt);

        // Renderer
        //
        GFX::get_instance().begin();
        GFX::get_instance().draw();
        GFX::get_instance().end();

        Window::get_instance().swapchain();

        SDL_Delay(1);
    }
}

void App::deinit()
{
    Game::get_instance().deinit();
    GFX::get_instance().deinit();
    Window::get_instance().deinit();
}