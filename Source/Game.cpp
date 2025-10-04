#include "Game.h"
#include "Application.h"
#include <iostream>

Game::Game() : shader("../Resources/simple.vert", "../Resources/simple.frag")
{
    std::cout << "Game Created" << std::endl;
    
    app_instance = Application::Get();
    window_instance = app_instance->GetWindow();
    m_view = glm::mat4(1.0f);

    m_player = std::make_unique<Quad>();
    m_player->modelMatrix = glm::translate(m_player->modelMatrix, glm::vec3(0.0f, -4.0f, 0.0f));
    m_player->modelMatrix = glm::scale(m_player->modelMatrix, glm::vec3(1.0f, 0.1f, 1.0f));
}

Game::~Game()
{
    app_instance = nullptr;
    std::cout << "Game Destroyed" << std::endl;
}

void Game::Update(float& deltaTime)
{
    glm::vec2 frameBufferSize = app_instance->GetFrameBufferSize();
    glViewport(0, 0, frameBufferSize.x, frameBufferSize.y);
    float aspect = frameBufferSize.x / frameBufferSize.y;
    float orthoHeight = 4.5f;
    float orthoWidth = orthoHeight * aspect;
    m_proj = glm::ortho(-orthoWidth, orthoWidth, -orthoHeight, orthoHeight, -10.0f, 10.0f);

    shader.Bind();
    shader.SetUniformMatrix4fv("view", glm::value_ptr(m_view));
    shader.SetUniformMatrix4fv("proj", glm::value_ptr(m_proj));

    m_player->Draw(shader);

    float directionX = 0.0f;

    if (glfwGetKey(window_instance, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window_instance, GLFW_KEY_RIGHT) == GLFW_PRESS) directionX++;
    if (glfwGetKey(window_instance, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window_instance, GLFW_KEY_LEFT) == GLFW_PRESS)  directionX--;

    if (directionX != 0.0f)
    {
        m_player->modelMatrix = glm::translate(m_player->modelMatrix, glm::vec3(directionX * moveSpeed * deltaTime, 0.0f, 0.0f));
    }
    
}