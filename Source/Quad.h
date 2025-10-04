#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

struct Vertex
{
    glm::vec2 position;
    glm::vec2 uv;
};

class Quad
{
public:
    Quad();
    ~Quad() = default;
    glm::vec2 size = glm::vec2(1.0f, 1.0f);
    glm::vec2 position = glm::vec2(0.0f, 0.0f);

    void Draw(uint32_t shaderProgram);

private:
    uint32_t m_vertexArray, m_vertexBuffer, m_indexBuffer;
    std::vector<Vertex> m_vertices;
    std::vector<uint8_t> m_indices;
};