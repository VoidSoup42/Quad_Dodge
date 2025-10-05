#include "Application.h"
#include <iostream>

Application *Application::s_Application = nullptr;

Application::Application(uint16_t width, uint16_t height, const char* title, bool vSync, bool fullscreen)
{
    s_Application = this;
    if (!glfwInit())
    {
        std::cout << "Failed to initialize glfw" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_window = glfwCreateWindow(width, height, title, fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);
    if (!m_window)
    {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(vSync);

    if (!glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return;
    }

    m_game = std::make_unique<Game>();
}

Application::~Application()
{
    std::cout << "Application Destroyed" << std::endl;
    s_Application = nullptr;
}

void Application::Run()
{
    float lastFrame;
    float deltaTime;
    while (!glfwWindowShouldClose(m_window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        m_game->Update(deltaTime);

        glfwPollEvents();
        glfwSwapBuffers(m_window);
    }
}

glm::vec2 Application::GetFrameBufferSize()
{
    int x, y;
    glfwGetFramebufferSize(m_window, &x, &y);
    return glm::vec2(x, y);
}