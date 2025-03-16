#include "texture.hpp"

#include <stdexcept>

#include <SDL_image.h>
#include <glad/glad.h>


Texture::Texture(uint32_t id, glm::vec2 size) : id(id), size(size) {}

Texture::~Texture()
{
    glDeleteTextures(1, &id);
}

std::shared_ptr<Texture> Texture::load(const std::string& path)
{
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) {
        return nullptr; // Или throw std::runtime_error("Failed to load image");
    }

    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    GLenum format = (surface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
    int width = surface->w;
    int height = surface->h;

    glTexImage2D(
        GL_TEXTURE_2D, 0, format, width, height, 0,
        format, GL_UNSIGNED_BYTE, surface->pixels
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    SDL_FreeSurface(surface);

    return std::make_shared<Texture>(texture_id, glm::vec2(width, height));
}

uint32_t Texture::get_id() const
{
    return id;
}

glm::vec2 Texture::get_size() const
{
    return size;
}