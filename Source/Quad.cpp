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

    // position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

    // uv attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

    glGenBuffers(1, &m_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    glNamedBufferData(m_indexBuffer, m_indices.size() * sizeof(uint32_t), m_indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void Quad::Draw(Shader& shader)
{
    shader.Bind();
    shader.SetUniformMatrix4fv("model", glm::value_ptr(modelMatrix));
    glBindVertexArray(m_vertexArray);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, 0);
}