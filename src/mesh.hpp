#if !defined(MESH_HPP)
#define MESH_HPP

#include <cstdint>

class Mesh
{
public:
    Mesh();
    ~Mesh();

    const uint32_t get_id();

private:
    uint32_t vao = 0;
    uint32_t vbo = 0;
    uint32_t ebo = 0;
};

#endif