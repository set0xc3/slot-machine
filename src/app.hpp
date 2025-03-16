#if !defined(APP_HPP)
#define APP_HPP

#include <SDL_main.h>

class App
{
public:
    App(const App &) = delete;
    App &operator=(const App &) = delete;
    ~App() {}

    static App &get_instance()
    {
        static App instance;
        return instance;
    }

    void init();
    void run();
    void deinit();

private:
    App()
    {
        is_running = true;
    }

    bool is_running;
};

#endif