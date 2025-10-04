#include "Game.h"
#include "Application.h"
#include <iostream>

Game::Game() : shader("../Resources/simple.vert", "../Resources/simple.frag")
{
    std::cout << "Game Created" << std::endl;
    
    app_instance = Application::Get();
    proj = glm::ortho(-8.0f, 8.0f, -4.5f, 4.5f, -10.0f, 10.0f);
    view = glm::mat4(1.0f);
}

void Game::Update(float& deltaTime)
{
    glm::vec2 frameBufferSize = app_instance->GetFrameBufferSize();
    glViewport(0, 0, frameBufferSize.x, frameBufferSize.y);
    float aspect = frameBufferSize.x / frameBufferSize.y;
    float orthoHeight = 4.5f;
    float orthoWidth = orthoHeight * aspect;
    proj = glm::ortho(-orthoWidth, orthoWidth, -orthoHeight, orthoHeight, -10.0f, 10.0f);


    shader.Bind();
    shader.SetUniformMatrix4fv("view", glm::value_ptr(view));
    shader.SetUniformMatrix4fv("proj", glm::value_ptr(proj));

    testQuad.Draw(shader);
}