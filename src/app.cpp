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
    const double fps_max = 60.0;
    const double period_max = 1.0 / fps_max;
    const double perf_frequency = (double)SDL_GetPerformanceFrequency();

    double time = 0.0;
    double begin_counter = 0.0;
    double end_counter = 0.0;

    while (is_running)
    {
        begin_counter = (double)SDL_GetPerformanceCounter();

        double counter_elapsed = (double)(begin_counter - end_counter);
        double dt = (double)(counter_elapsed / perf_frequency);
        double fps = (double)(perf_frequency / counter_elapsed);

        // Event
        //
        if (!Window::get_instance().event_handling())
        {
            is_running = false;
        }

        if (dt >= period_max)
        {
            // Ограничиваем dt, чтобы избежать скачков
            if (dt >= 1.0)
            {
                dt = period_max;
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

            end_counter = begin_counter;
            time += dt;

            std::cout << "Delta Time: " << dt << "s, FPS: " << fps << std::endl;
        }

        double sleep_time_ms = period_max;
        SDL_Delay((Uint32)sleep_time_ms * 1000);
    }
}

void App::deinit()
{
    GFX::get_instance().deinit();
    Window::get_instance().deinit();
}