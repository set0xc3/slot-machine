#include "window.hpp"

#include <glad/glad.h>

#include <string>

void Window::init()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,
                        SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

    sdl_window =
        SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED, (int)size.x, (int)size.y, SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);

    gl_context = SDL_GL_CreateContext(sdl_window);
    SDL_GL_MakeCurrent(sdl_window, gl_context);

    gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

    SDL_ShowWindow(sdl_window);
}

bool Window::event_handling()
{

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
        {
            return false;
        }
        case SDL_KEYDOWN:
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                return false;
            }
            break;
        }
        case SDL_WINDOWEVENT:
        {
            switch (event.window.event)
            {
            case SDL_WINDOWEVENT_CLOSE:
                return false;
            case SDL_WINDOWEVENT_RESIZED:
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                size = glm::vec2(event.window.data1, event.window.data2);
                break;
            }
            break;
        }
        case SDL_MOUSEMOTION:
        {
            mouse_position = glm::vec2(event.motion.x, event.motion.y);
            break;
        }
        }
    };

    return true;
}

void Window::swapchain()
{
    SDL_GL_SwapWindow(sdl_window);
}

void Window::deinit()
{
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}

const glm::vec2 Window::get_position() const
{
    return position;
}
const glm::vec2 Window::get_size() const
{
    return size;
}

const glm::vec2 Window::get_mouse_position() const
{
    return mouse_position;
}