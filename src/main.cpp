#include "app.hpp"

int main(int argc, char *argv[])
{
    App *app = &App::get_instance();
    app->init();
    app->run();
    app->deinit();
    return 0;
}