#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "Shader.h"

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
    
    glm::mat4 modelMatrix = glm::mat4(1.0f);

    void Draw(Shader& shader);

private:
    uint32_t m_vertexArray, m_vertexBuffer, m_indexBuffer;
    std::vector<Vertex> m_vertices;
    std::vector<uint32_t> m_indices;

    
};