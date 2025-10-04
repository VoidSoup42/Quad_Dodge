#include "Application.h"
#include <iostream>

Application::Application(uint16_t width, uint16_t height, const char* title, bool vSync, bool fullscreen)
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize glfw" << std::endl;
        return;
    }

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
}

void Application::Run()
{
    while (!glfwWindowShouldClose(m_window))
    {
        glClearColor(0.3, 0.7, 0.8, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();
        glfwSwapBuffers(m_window);
    }
}