#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Application
{
public:
    Application(uint16_t width, uint16_t height, const char* title, bool vSync, bool fullscreen);
    ~Application() {};

    void Run();

private:
    void Update(float& deltaTime);

    GLFWwindow* m_window;
};