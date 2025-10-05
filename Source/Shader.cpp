#include "Shader.h"

std::string ReadFile(const char* filename)
{
    std::ifstream in(filename, std::ios::binary);
    if (in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return contents;
    }
    std::string msg = std::string("Failed to open file: ") + filename;
    std::cerr << msg << std::endl;
    throw std::runtime_error(msg);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
    std::string vertexCode = ReadFile(vertexFile);
    std::string fragmentCode = ReadFile(fragmentFile);

    const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    m_id = glCreateProgram();
    glAttachShader(m_id, vertexShader);
    glAttachShader(m_id, fragmentShader);

    glLinkProgram(m_id);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(m_id);
}

void Shader::Bind()
{
    glUseProgram(m_id);
}

void Shader::Unbind()
{
    glUseProgram(0);

}

void Shader::SetUniformMatrix4fv(const char* name, float* value)
{
    glUniformMatrix4fv(glGetUniformLocation(m_id, name), 1, GL_FALSE, value);
}

void Shader::SetUniformVec3(const char* name, glm::vec3 value)
{
    glUniform3fv(glGetUniformLocation(m_id, name), 1, glm::value_ptr(value));
}