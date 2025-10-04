#include "Quad.h"

Quad::Quad()
{
    m_vertices = {
        { {-1.0f, -1.0f}, {0.0f, 0.0f} }, // 0: bottom-left
        { { 1.0f, -1.0f}, {1.0f, 0.0f} }, // 1: bottom-right
        { { 1.0f,  1.0f}, {1.0f, 1.0f} }, // 2: top-right
        { {-1.0f,  1.0f}, {0.0f, 1.0f} }, // 3: top-left
    };

    m_indices = {
        0, 1, 2,
        2, 3, 0
    };

    glGenVertexArrays(1, &m_vertexArray);
    glBindVertexArray(m_vertexArray);

    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glNamedBufferData(m_vertexBuffer, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, 0, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, 0, sizeof(Vertex), (void*)offsetof(Vertex, uv));
    glEnableVertexAttribArray(1);
    
    glGenBuffers(1, &m_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    glNamedBufferData(m_indexBuffer, m_indices.size() * sizeof(uint8_t), m_indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void Quad::Draw(uint32_t shaderProgram)
{
    // glUseProgram(shaderProgram);
    glBindVertexArray(m_vertexArray);
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_BYTE, 0);

}