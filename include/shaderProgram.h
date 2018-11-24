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

    void add_shader_from_source_file(ShaderType type, const char* pathToFile);
    void use_program();
    void link();
    GLuint get_program() const;

    // Uniform functions
    inline void set_bool(const std::string &name, bool value) const;
    inline void set_float(const std::string &name, float value) const;
    inline void set_int(const std::string &name, int value) const;
    inline void set_vec2(const std::string &name, const glm::vec2 &value) const;
    inline void set_vec2(const std::string &name, float x, float y) const;
    inline void set_vec3(const std::string &name, const glm::vec3 &value) const;
    inline void set_vec3(const std::string &name, float x, float y, float z) const;
    inline void set_vec4(const std::string &name, const glm::vec4 &value) const;
    inline void set_vec4(const std::string &name, float x, float y, float z, float w) const;
    inline void set_mat2(const std::string &name, const glm::mat2 &mat) const;
    inline void set_mat3(const std::string &name, const glm::mat3 &mat) const;
    inline void set_mat4(const std::string &name, const glm::mat4 &mat) const;

private:

    GLuint m_program;
};

inline void ShaderProgram::set_bool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(m_program, name.c_str()), value);
}

inline void ShaderProgram::set_float(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(m_program, name.c_str()), value);
}

inline void ShaderProgram::set_int(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(m_program, name.c_str()), value);
}

inline void ShaderProgram::set_vec2(const std::string &name, const glm::vec2 &value) const
{
    glUniform2fv(glGetUniformLocation(m_program, name.c_str()), 1, &value[0]);
}

inline void ShaderProgram::set_vec2(const std::string &name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(m_program, name.c_str()), x, y);
}

inline void ShaderProgram::set_vec3(const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(m_program, name.c_str()), 1, &value[0]);
}

inline void ShaderProgram::set_vec3(const std::string &name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(m_program, name.c_str()), x, y, z);
}

inline void ShaderProgram::set_vec4(const std::string &name, const glm::vec4 &value) const
{
    glUniform4fv(glGetUniformLocation(m_program, name.c_str()), 1, &value[0]);
}

inline void ShaderProgram::set_vec4(const std::string &name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(m_program, name.c_str()), x, y, z, w);
}

inline void ShaderProgram::set_mat2(const std::string &name, const glm::mat2 &mat) const
{
     glUniformMatrix2fv(glGetUniformLocation(m_program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

inline void ShaderProgram::set_mat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(m_program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

inline void ShaderProgram::set_mat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

#endif
