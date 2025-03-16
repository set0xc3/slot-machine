#if !defined(TEXTURE_HPP)
#define TEXTURE_HPP

#include <cstdint>
#include <glm/glm.hpp>

class Texture
{
public:
    uint32_t id;
    glm::vec2 size;
};

#endif