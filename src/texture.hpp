#include <memory>
#include <cstdint>
#include <string>
#include <glm/glm.hpp>

class Texture
{
public:
    Texture(uint32_t id, glm::vec2 size);
    ~Texture();

    static std::shared_ptr<Texture> load(const std::string& path);

    uint32_t get_id() const;
    glm::vec2 get_size() const;

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

private:
    uint32_t id;
    glm::vec2 size;
};