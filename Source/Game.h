#pragma once

#include "Quad.h"
#include "Shader.h"

class Game
{
public:
    Game();
    ~Game() = default;

    void Update(float& deltaTime);

    Quad testQuad;

private:
    uint32_t m_vertexShader, m_fragmentShader, m_program;
    Shader shader;
};