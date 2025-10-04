#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "Game.h"

class Application
{
public:
    Application(uint16_t width = 1280, uint16_t height = 720, const char* title = "Window", bool vSync = true, bool fullscreen = false);
    ~Application();

    void Run();
    glm::vec2 GetFrameBufferSize();

    static inline Application* Get()
    {
        return s_Application;
    }

    static inline GLFWwindow* GetWindow()
    {
        return s_Application->m_window;
    }

private:
    GLFWwindow* m_window;
    std::unique_ptr<Game> m_game;

    static Application* s_Application;
};