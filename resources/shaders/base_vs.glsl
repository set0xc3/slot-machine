#version 460 core

layout (location = 0) in vec2 a_position;
layout (location = 1) in vec2 a_texture_coord;

out vec2 texture_coord;

uniform mat4 u_projection;
uniform mat4 u_model;

void main() {
    gl_Position = u_projection * u_model * vec4(a_position, 0.0, 1.0);

    texture_coord = a_texture_coord;
}