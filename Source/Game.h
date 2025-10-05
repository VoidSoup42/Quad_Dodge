#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <vector>
#include "Quad.h"
#include "Shader.h"

class Application;
class Game
{
public:
    Game();
    ~Game();

    void Update(float& deltaTime);

    float moveSpeed = 8.0f;
    float obstacleSpeed = 8.0f;

private:
    uint32_t m_vertexShader, m_fragmentShader, m_program;
    Shader shader;

    glm::mat4 m_view;
    glm::mat4 m_proj;

    Application* app_instance;
    GLFWwindow* window_instance;

    std::unique_ptr<Quad> m_player;

    std::vector<glm::vec2> m_obstaclePositions;
    std::vector<std::unique_ptr<Quad>> m_obstacles;

    void ResetGame();
};