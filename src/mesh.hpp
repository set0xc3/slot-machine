#if !defined(MESH_HPP)
#define MESH_HPP

#include <cstdint>

class Mesh
{
public:
    void create();
    void destroy();

public:
    uint32_t vao = 0;
    uint32_t vbo = 0;
    uint32_t ebo = 0;
};

#endif