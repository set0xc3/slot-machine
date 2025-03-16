#include "entity.hpp"

Entity::Entity() {
    mesh = new(Mesh);
}

Entity::~Entity() {
}

void Entity::set_texture(const std::weak_ptr<Texture>& new_texture) {
    texture = new_texture;
    size = new_texture.lock()->get_size();
}