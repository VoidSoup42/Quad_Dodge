#version 460 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 uv;

out vec2 vUV;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
    vUV = uv;
    gl_Position = proj * view * model * vec4(position, 0.0, 1.0);
}