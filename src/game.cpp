#include "game.hpp"

#include "gfx.hpp"
#include "window.hpp"

void Game::init()
{
    textures["ellipse"] = GFX::get_instance().texture_load("resources/assets/ellipse.png");
    textures["triangle"] = GFX::get_instance().texture_load("resources/assets/triangle.png");
    textures["rectangle"] = GFX::get_instance().texture_load("resources/assets/rectangle.png");
    textures["star"] = GFX::get_instance().texture_load("resources/assets/star.png");
    textures["frame"] = GFX::get_instance().texture_load("resources/assets/frame.png");
    textures["stop"] = GFX::get_instance().texture_load("resources/assets/stop.png");
    textures["start"] = GFX::get_instance().texture_load("resources/assets/start.png");

    auto window_size = Window::get_instance().get_size();

    // ent->texture = textures["star"];
    // ent->position = glm::vec2(0.0f, 0.0f);
    // ent->size = ent->texture->size;
    // ent->mesh = new (Mesh);
    // ent->mesh->create();
    // entities.push_back(ent);

    frame = new (Entity);
    frame->name = "frame";
    frame->texture = textures["frame"];
    frame->position = glm::vec2((window_size.x / 2.0f) - frame->texture->size.x / 2.0f, (window_size.y / 2.0f) - (frame->texture->size.y / 2.0f) + 60.0f);
    frame->size = frame->texture->size;
    frame->mesh = new (Mesh);
    frame->mesh->create();
    entities.push_back(frame);

    for (size_t i = 0; i < 1; i += 1)
    {
        auto ent_rect = new (Entity);
        ent_rect->texture = textures["rectangle"];
        ent_rect->size = ent_rect->texture->size;

        ent_rect->position = glm::vec2(frame->position.x, (frame->position.y + frame->size.y) - ent_rect->size.y);

        ent_rect->mesh = new (Mesh);
        ent_rect->mesh->create();
        entities.push_back(ent_rect);
    }
}

void Game::update(float dt)
{
    entities[1]->position.y -= 100.0f * dt;
}

void Game::deinit()
{
}

Entity *Game::get_frame() const {
    return frame;
}

std::vector<Entity *> Game::get_entities() const
{
    return entities;
}