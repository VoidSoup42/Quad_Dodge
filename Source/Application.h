#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "Game.h"

class Application
{
public:
    Application(uint16_t width, uint16_t height, const char* title, bool vSync, bool fullscreen);
    ~Application() {};

    void Run();

private:
    GLFWwindow* m_window;
    std::unique_ptr<Game> m_game;
};