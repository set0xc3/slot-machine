#if !defined(ENTITY_HPP)
#define ENTITY_HPP

#include "mesh.hpp"
#include "texture.hpp"

#include <string>

#include <glm/glm.hpp>

class Entity
{
public:
  std::string name;

  glm::vec2 position;
  glm::vec2 rotation;
  glm::vec2 size;

  Mesh *mesh;
  Texture *texture;
};

#endif