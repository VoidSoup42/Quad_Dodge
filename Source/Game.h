#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Quad.h"
#include "Shader.h"

class Application;
class Game
{
public:
    Game();
    ~Game() = default;

    void Update(float& deltaTime);

    Quad testQuad;

private:
    uint32_t m_vertexShader, m_fragmentShader, m_program;
    Shader shader;

    glm::mat4 view;
    glm::mat4 proj;

    Application* app_instance;
};