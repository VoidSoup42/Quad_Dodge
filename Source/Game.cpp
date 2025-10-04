#include "Game.h"
#include <iostream>

Game::Game() : shader("../Resources/simple.vert", "../Resources/simple.frag")
{
    std::cout << "Game Created" << std::endl;

    // const char* vertexShader = "\n"
    //     "#version 460 core"
    //     "layout (location = 0) in vec2 aPos;"
    //     "layout (location = 1) in vec2 uv;"
    //     "void main(){"
    //     "   gl_Position = vec4(aPos, 1.0, 1.0);"
    //     "}";

    // const char* fragmentShader = "\n"
    //     "#version 460 core"
    //     "out vec4 FragColor;"
    //     "void main(){"
    //     "   FragColor = vec4(1.0, 0.5, 0.2, 1.0);"
    //     "}";

    // m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // glShaderSource(m_vertexShader, 1, &vertexShader, 0);
    // glCompileShader(m_vertexShader);
    
    // m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // glShaderSource(m_fragmentShader, 1, &fragmentShader, 0);
    // glCompileShader(m_fragmentShader);

    // m_program = glCreateProgram();

    // glAttachShader(m_program, m_vertexShader);
    // glAttachShader(m_program, m_fragmentShader);
    // glLinkProgram(m_program);

    // glDeleteShader(m_vertexShader);
    // glDeleteShader(m_fragmentShader);

        
}

void Game::Update(float& deltaTime)
{
    shader.Bind();
    testQuad.Draw(m_program);
}