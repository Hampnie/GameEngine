#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "common.h"
#include <string>
#include <glm/glm.hpp>

class ShaderProgram
{
public:
    enum ShaderType
    {
        VERTEX,
        FRAGMENT
    };

    ShaderProgram();

    void addShaderFromSourceFile(ShaderType type, const char* pathToFile);
    void useProgram();
    void link();
    GLuint getProgram() const;

    // Uniform functions
    inline void setBool(const std::string &name, bool value) const;
    inline void setFloat(const std::string &name, float value) const;
    inline void setInt(const std::string &name, int value) const;
    inline void setVec2(const std::string &name, const glm::vec2 &value) const;
    inline void setVec2(const std::string &name, float x, float y) const;
    inline void setVec3(const std::string &name, const glm::vec3 &value) const;
    inline void setVec3(const std::string &name, float x, float y, float z) const;
    inline void setVec4(const std::string &name, const glm::vec4 &value) const;
    inline void setVec4(const std::string &name, float x, float y, float z, float w) const;
    inline void setMat2(const std::string &name, const glm::mat2 &mat) const;
    inline void setMat3(const std::string &name, const glm::mat3 &mat) const;
    inline void setMat4(const std::string &name, const glm::mat4 &mat) const;

private:

    GLuint m_program;
};

inline void ShaderProgram::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(m_program, name.c_str()), value);
}

inline void ShaderProgram::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(m_program, name.c_str()), value);
}

inline void ShaderProgram::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(m_program, name.c_str()), value);
}

inline void ShaderProgram::setVec2(const std::string &name, const glm::vec2 &value) const
{
    glUniform2fv(glGetUniformLocation(m_program, name.c_str()), 1, &value[0]);
}

inline void ShaderProgram::setVec2(const std::string &name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(m_program, name.c_str()), x, y);
}

inline void ShaderProgram::setVec3(const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(m_program, name.c_str()), 1, &value[0]);
}

inline void ShaderProgram::setVec3(const std::string &name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(m_program, name.c_str()), x, y, z);
}

inline void ShaderProgram::setVec4(const std::string &name, const glm::vec4 &value) const
{
    glUniform4fv(glGetUniformLocation(m_program, name.c_str()), 1, &value[0]);
}

inline void ShaderProgram::setVec4(const std::string &name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(m_program, name.c_str()), x, y, z, w);
}

inline void ShaderProgram::setMat2(const std::string &name, const glm::mat2 &mat) const
{
     glUniformMatrix2fv(glGetUniformLocation(m_program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

inline void ShaderProgram::setMat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(m_program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

inline void ShaderProgram::setMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

#endif
