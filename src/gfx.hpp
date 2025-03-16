#if !defined(GFX_HPP)
#define GFX_HPP

#include <cstdint>
#include <string>

#include "math.hpp"
#include "entity.hpp"
#include "shader.hpp"

#include <glm/glm.hpp>

class GFX
{
public:
  GFX(const GFX &) = delete;
  GFX &operator=(const GFX &) = delete;
  ~GFX() {}

  static GFX &get_instance()
  {
    static GFX instance;
    return instance;
  }

  void init();
  void deinit();
  void begin();
  void draw();
  void end();

  Shader *shader_load(const std::string vs_path, const std::string fs_path);
  void shader_mat4_set(const Shader *shader, const std::string name, const glm::mat4 matrix);

private:
  Shader *base_shader;

  GFX() {}
};

#endif