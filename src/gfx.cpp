#include "gfx.hpp"
#include "window.hpp"

#include <fstream>
#include <string>
#include <iterator>
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "game.hpp"

void GFX::init()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    base_shader = GFX::get_instance().shader_load("resources/shaders/base_vs.glsl", "resources/shaders/base_fs.glsl");
}

void GFX::deinit()
{
}

void GFX::begin()
{
    glm::vec2 window_size = Window::get_instance().get_size();
    glViewport(0, 0, (GLsizei)window_size.x, (GLsizei)window_size.y);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void GFX::draw()
{
    glm::vec2 window_size = Window::get_instance().get_size();
    glm::mat4 projection = glm::ortho(
        0.0f, window_size.x,
        0.0f, window_size.y,
        -1.0f, 1.0f);
    glUseProgram(base_shader->id);
    shader_mat4_set(base_shader, "u_projection", projection);

    for (Entity *entity : Game::get_instance().get_entities())
    {
        if (entity->is_scissor)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(entity->position, 0.0f));
            model = glm::scale(model, glm::vec3(entity->size, 1.0f));
            shader_mat4_set(base_shader, "u_model", model);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, entity->texture.lock()->get_id());
            glBindVertexArray(entity->mesh->get_id());
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            glEnable(GL_SCISSOR_TEST);
            glScissor(
                (GLint)entity->position.x,
                (GLint)entity->position.y,
                (GLsizei)entity->size.x,
                (GLsizei)entity->size.y);

            for (Entity *child : entity->childs)
            {
                model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(child->position, 0.0f));
                model = glm::scale(model, glm::vec3(child->size, 1.0f));
                shader_mat4_set(base_shader, "u_model", model);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, child->texture.lock()->get_id());
                glBindVertexArray(child->mesh->get_id());
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            }
            glDisable(GL_SCISSOR_TEST);
        }
    }

    for (Entity *entity : Game::get_instance().get_entities())
    {
        if (entity->is_scissor || entity->root != nullptr)
            continue;

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(entity->position, 0.0f));
        model = glm::scale(model, glm::vec3(entity->size, 1.0f));
        shader_mat4_set(base_shader, "u_model", model);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, entity->texture.lock()->get_id());
        glBindVertexArray(entity->mesh->get_id());
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}

void GFX::end()
{
}

Shader *GFX::shader_load(const std::string vs_path, const std::string fs_path)
{
    auto *result = new (Shader);

    std::string vs_source, fs_source;

    if (std::ifstream ifs{vs_path})
    {
        vs_source.assign(
            std::istreambuf_iterator<char>(ifs),
            std::istreambuf_iterator<char>());
    }
    else
    {
        throw std::runtime_error("Failed to open vertex shader: " + vs_path);
    }

    if (std::ifstream ifs{fs_path})
    {
        fs_source.assign(
            std::istreambuf_iterator<char>(ifs),
            std::istreambuf_iterator<char>());
    }
    else
    {
        throw std::runtime_error("Failed to open fragment shader: " + fs_path);
    }

    const char *vs_source_ptr = vs_source.c_str();
    const char *fs_source_ptr = fs_source.c_str();

    uint32_t vs_id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs_id, 1, &vs_source_ptr, nullptr);
    glCompileShader(vs_id);

    uint32_t fs_id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs_id, 1, &fs_source_ptr, nullptr);
    glCompileShader(fs_id);

    auto check_compile_errors = [](GLuint shader, const char *type)
    {
        GLint success;
        GLchar info_log[1024] = {0};

        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            GLsizei log_length = 0;
            glGetShaderInfoLog(shader, sizeof(info_log), &log_length, info_log);

            std::string error_msg = "SHADER_COMPILATION_ERROR (" + std::string(type) + "):\n";
            error_msg += std::string(info_log, log_length);

            std::cerr << error_msg << std::endl;
            throw std::runtime_error(error_msg);
        }
    };

    check_compile_errors(vs_id, "VERTEX");
    check_compile_errors(fs_id, "FRAGMENT");

    const GLuint program = glCreateProgram();
    glAttachShader(program, vs_id);
    glAttachShader(program, fs_id);
    glLinkProgram(program);

    GLint link_success;
    glGetProgramiv(program, GL_LINK_STATUS, &link_success);
    if (!link_success)
    {
        GLchar info_log[1024];
        glGetProgramInfoLog(program, sizeof(info_log), nullptr, info_log);
        throw std::runtime_error("PROGRAM_LINKING_ERROR:\n" + std::string(info_log));
    }

    glUseProgram(0);

    glDeleteShader(vs_id);
    glDeleteShader(fs_id);

    result = new (Shader);
    result->id = program;
    return result;
}

void GFX::shader_mat4_set(const Shader *shader, const std::string name, const glm::mat4 matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(shader->id, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}