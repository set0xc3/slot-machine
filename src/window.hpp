#if !defined(WINDOW_HPP)
#define WINDOW_HPP

#include <SDL.h>
#include <glm/glm.hpp>

class Window
{
public:
    Window(const Window &) = delete;
    Window &operator=(const Window &) = delete;
    ~Window() {}

    static Window &get_instance()
    {
        static Window instance;
        return instance;
    }

    void init();
    bool event_handling();
    void swapchain();
    void deinit();

    const glm::vec2 get_position() const;
    const glm::vec2 get_size() const;
    const glm::vec2 get_mouse_position() const;

private:
    glm::vec2 position;
    glm::vec2 size;
    glm::vec2 mouse_position;

    SDL_Window *sdl_window;
    SDL_GLContext gl_context;

    Window()
    {
        size = glm::vec2(800.0, 600.0f);
    }
};

#endif