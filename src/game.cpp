#include "game.hpp"
#include "gfx.hpp"
#include "window.hpp"
#include <cmath>
#include <iostream>

void Game::init()
{
    textures["ellipse"] = Texture::load("resources/assets/ellipse.png");
    textures["triangle"] = Texture::load("resources/assets/triangle.png");
    textures["rectangle"] = Texture::load("resources/assets/rectangle.png");
    textures["star"] = Texture::load("resources/assets/star.png");
    textures["frame"] = Texture::load("resources/assets/frame.png");
    textures["stop"] = Texture::load("resources/assets/stop.png");
    textures["start"] = Texture::load("resources/assets/start.png");

    auto window_size = Window::get_instance().get_size();

    frame = new Entity();
    frame->is_scissor = true;
    frame->set_texture(textures["frame"]);
    frame->position = glm::vec2(
        (window_size.x / 2.0f) - frame->texture.lock()->get_size().x / 2.0f,
        (window_size.y / 2.0f) - frame->texture.lock()->get_size().y / 2.0f + 60.0f);
    entities.push_back(frame);

    int num_columns = 5;
    int num_symbols_per_column = 4;
    columns.resize(num_columns);
    column_offsets.resize(num_columns, 0.0f);

    float column_width = frame->size.x / num_columns;

    for (int col = 0; col < num_columns; col++)
    {
        columns[col].resize(num_symbols_per_column);
        for (int row = 0; row < num_symbols_per_column; row++)
        {
            auto ent = new Entity();
            ent->set_texture(textures["star"]);
            float symbol_height = ent->texture.lock()->get_size().y;
            float x = frame->position.x + col * column_width + (column_width - ent->size.x) / 2.0f;
            float y = frame->position.y + frame->size.y - row * symbol_height;
            ent->initial_position = glm::vec2(x, y);
            ent->position = ent->initial_position;
            ent->root = frame;
            frame->childs.push_back(ent);
            entities.push_back(ent);
            columns[col][row] = ent;
        }
    }

    auto start_button = new Entity();
    start_button->set_texture(textures["start"]);
    start_button->position = glm::vec2(frame->position.x, 20.0f);
    entities.push_back(start_button);

    auto stop_button = new Entity();
    stop_button->set_texture(textures["stop"]);
    stop_button->position = glm::vec2(
        frame->position.x + frame->size.x - stop_button->texture.lock()->get_size().x,
        20.0f);
    entities.push_back(stop_button);

    curr_state = GameState::Spinning;
}

void Game::update(float dt)
{
    float speed = 100.0f;

    switch (curr_state)
    {
    case GameState::Idle:
        break;
    case GameState::Spinning:
        for (size_t col = 0; col < columns.size(); col++)
        {
            for (size_t row = 0; row < columns[col].size(); row++)
            {
                Entity *ent = columns[col][row];

                // Обновляем смещение колонки
                float symbol_height = ent->texture.lock()->get_size().y;
                column_offsets[col] += speed * dt;
                column_offsets[col] = fmod(column_offsets[col], symbol_height);
                ent->position.y = ent->initial_position.y - column_offsets[col];

                // Если символ вышел за нижнюю границу фрейма, перемещаем его наверх
                if (ent->position.y + ent->size.y < frame->position.y)
                {
                    ent->position.y += symbol_height * columns[col].size();
                }
            }
        }
        break;
    case GameState::Stopping:
        break;
    case GameState::Win:
        break;
    }
}

std::vector<Entity *> Game::get_entities() const
{
    return entities;
}