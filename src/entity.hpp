#if !defined(ENTITY_HPP)
#define ENTITY_HPP

#include "mesh.hpp"
#include "texture.hpp"

#include <string>
#include <vector>

#include <glm/glm.hpp>

class Entity
{
public:
  Entity();
  ~Entity();

  bool is_scissor = false;
  glm::vec2 position{0.0f, 0.0f};
  glm::vec2 rotation{0.0f, 0.0f};
  glm::vec2 size{1.0f, 1.0f};
  glm::vec2 initial_position{0.0f, 0.0f};

  Mesh *mesh = nullptr;
  std::weak_ptr<Texture> texture;
  Entity *root = nullptr;
  std::vector<Entity *> childs;

  void set_texture(const std::weak_ptr<Texture>& new_texture);
};

#endif