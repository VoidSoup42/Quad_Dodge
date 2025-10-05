#include "Game.h"
#include "Application.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>

Game::Game() : shader("../Resources/simple.vert", "../Resources/simple.frag")
{
    app_instance = Application::Get();
    window_instance = app_instance->GetWindow();
    
    m_view = glm::mat4(1.0f);
    m_player = std::make_unique<Quad>();
    m_player->modelMatrix = glm::translate(m_player->modelMatrix, glm::vec3(0.0f, -4.0f, 0.0f));
    m_player->modelMatrix = glm::scale(m_player->modelMatrix, glm::vec3(1.0f, 0.1f, 1.0f));

    m_obstaclePositions = {
        { -7.0f, 8.0f },
        { -3.5f, 8.0f },
        {  0.0f, 8.0f },
        {  3.5f, 8.0f },
        {  7.0f, 8.0f }
    };
}

Game::~Game()
{
    app_instance = nullptr;
    window_instance = nullptr;
    std::cout << "Game Destroyed" << std::endl;
}

void Game::Update(float &deltaTime)
{
    float time = glfwGetTime();
    glClearColor(0.871, 0.243, 0.243, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glm::vec2 frameBufferSize = app_instance->GetFrameBufferSize();
    glViewport(0, 0, frameBufferSize.x, frameBufferSize.y);
    float aspect = frameBufferSize.x / frameBufferSize.y;
    float orthoHeight = 4.5f;
    float orthoWidth = orthoHeight * aspect;
    m_proj = glm::ortho(-orthoWidth, orthoWidth, -orthoHeight, orthoHeight, -10.0f, 10.0f);

    shader.Bind();
    shader.SetUniformMatrix4fv("view", glm::value_ptr(m_view));
    shader.SetUniformMatrix4fv("proj", glm::value_ptr(m_proj));
    shader.SetUniformVec3("color", glm::vec3(1.0f, 1.0f, 1.0f));
    m_player->Draw(shader);

    // Player Controller
    float directionX = 0.0f;
    if (glfwGetKey(window_instance, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window_instance, GLFW_KEY_RIGHT) == GLFW_PRESS) directionX++;
    if (glfwGetKey(window_instance, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window_instance, GLFW_KEY_LEFT) == GLFW_PRESS)  directionX--;

    if (directionX != 0.0f)
    {
        m_player->modelMatrix = glm::translate(m_player->modelMatrix, glm::vec3(directionX * moveSpeed * deltaTime, 0.0f, 0.0f));

        if (m_player->modelMatrix[3].x > orthoWidth - 0.5f)     m_player->modelMatrix[3].x = orthoWidth - 0.5f;
        if (m_player->modelMatrix[3].x < -orthoWidth + 0.5f)    m_player->modelMatrix[3].x = -orthoWidth + 0.5f;
    }

    // Obstacle Spawner
    static float obstacleSpawnTimer = 0.0f;
    obstacleSpawnTimer += deltaTime;
    if (obstacleSpawnTimer >= .4f)
    {
        int random = rand() % m_obstaclePositions.size();
        std::unique_ptr<Quad> obstacle = std::make_unique<Quad>();
        obstacle->modelMatrix = glm::translate(obstacle->modelMatrix, glm::vec3(m_obstaclePositions[random], 0.0f));
        obstacle->modelMatrix = glm::scale(obstacle->modelMatrix, glm::vec3(1.0, 0.7, 1.0));
        m_obstacles.push_back(std::move(obstacle));
        obstacleSpawnTimer = 0.0f;
    }

    // Obstacle Movement
    for (std::unique_ptr<Quad> &obstacle : m_obstacles)
    {
        obstacle->modelMatrix = glm::translate(obstacle->modelMatrix, glm::vec3(0.0f, -obstacleSpeed * deltaTime, 0.0f));
        shader.SetUniformVec3("color", glm::vec3(1.0, 1.0, 1.0));
        obstacle->Draw(shader);
    }

    // Collision Detection
    for (std::unique_ptr<Quad>& obstacle : m_obstacles)
    {
        float obstacleX = obstacle->modelMatrix[3].x;
        float obstacleY = obstacle->modelMatrix[3].y;
        float playerX = m_player->modelMatrix[3].x;
        float playerY = m_player->modelMatrix[3].y;

        float playerWidth = 1.0f;
        float playerHeight = 0.1f;
        float obstacleWidth = 1.0f;
        float obstacleHeight = 0.7f;

        bool collisionX = std::abs(playerX - obstacleX) < (playerWidth + obstacleWidth);
        bool collisionY = std::abs(playerY - obstacleY) < (playerHeight + obstacleHeight);

        if (collisionX && collisionY)
        {
            std::cout << "Collision Detected!" << std::endl;
            ResetGame();
            break;
        }
    }

    // Remove off-screen obstacles
    m_obstacles.erase(std::remove_if(m_obstacles.begin(), m_obstacles.end(), [](const std::unique_ptr<Quad> &obstacle) {
        float y = obstacle->modelMatrix[3].y;
        return y < -10.0f;
    }), m_obstacles.end());
}

void Game::ResetGame()
{
    m_obstacles.clear();
    m_player->modelMatrix = glm::mat4(1.0f);
    m_player->modelMatrix = glm::translate(m_player->modelMatrix, glm::vec3(0.0f, -4.0f, 0.0f));
    m_player->modelMatrix = glm::scale(m_player->modelMatrix, glm::vec3(1.0f, 0.1f, 1.0f));
}