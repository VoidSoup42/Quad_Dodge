#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "Quad.h"
#include "Shader.h"
class Application;
class Game
{
public:
    Game();
    ~Game();

    void Update(float& deltaTime);

    float moveSpeed = 5.0f;

private:
    uint32_t m_vertexShader, m_fragmentShader, m_program;
    Shader shader;

    glm::mat4 m_view;
    glm::mat4 m_proj;

    Application* app_instance;
    GLFWwindow* window_instance;

    std::unique_ptr<Quad> m_player;
};