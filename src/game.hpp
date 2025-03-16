#if !defined(GAME_HPP)
#define GAME_HPP

#include <vector>
#include <map>
#include <memory>

#include "entity.hpp"

enum GameState
{
    Idle,
    Spinning,
    Stopping,
    Win
};

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

    std::vector<Entity *> get_entities() const;

private:
    Game() {}

    Entity *frame;
    std::vector<std::vector<Entity *>> columns;
    std::vector<Entity *> entities;
    std::vector<float> column_offsets;

    GameState curr_state = GameState::Idle;

    std::map<std::string, std::shared_ptr<Texture>> textures;
};

#endif