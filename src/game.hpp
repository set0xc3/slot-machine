#if !defined(GAME_HPP)
#define GAME_HPP

#include <vector>
#include <map>

#include "entity.hpp"

class Game
{
public:
    Game(const Game &) = delete;
    Game &operator=(const Game &) = delete;
    ~Game() {}

    static Game &get_instance()
    {
        static Game instance;
        return instance;
    }

    void init();
    void update(float dt);
    void deinit();

    Entity *get_frame() const;
    std::vector<Entity *> get_entities() const;

private:
    Entity *frame;
    std::vector<Entity *> entities;

    std::map<std::string, Texture *> textures;

    Game() {}
};

#endif