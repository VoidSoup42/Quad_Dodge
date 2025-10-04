#pragma once

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
    Shader(const char* vertexFile, const char* fragmentFile);
    ~Shader();

    void Bind();
    void Unbind();

    inline uint32_t GetId()
    {
        return m_id;
    }

    void SetUniformMatrix4fv(const char* name, float* value);
    void setUniform1i(const char* name, int value);
    void SetUniformVec4(const char* name, const glm::vec4& value);
    void SetUniformVec3(const char* name, const glm::vec3& value);

private:
    unsigned int m_id;
};