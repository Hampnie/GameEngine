#include <string>

#include <sstream>
#include <iostream>
#include <fstream>
#include <GL/glew.h>

#include "shaderProgram.h"


ShaderProgram::ShaderProgram()
{
    m_program = glCreateProgram();
}

void ShaderProgram::add_shader_from_source_file(ShaderType type, const char *pathToFile)
{
    std::string tmpstr;
    std::ifstream shaderFile;

    shaderFile.exceptions(std::ios_base::badbit);
    try
    {
        // Open file
        shaderFile.open(pathToFile);
        std::stringstream shaderStream;
        // Read file buffer contents into stream
        shaderStream << shaderFile.rdbuf();
        // Close file handers
        shaderFile.close();
        // Convert stream into string
        tmpstr = shaderStream.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR! Shader file not successfuly read" << std::endl;
    }
    const GLchar* shaderCode = tmpstr.c_str();
    // Compile shader
    GLuint shader;
    GLint success;
    GLchar infoLog[512];

    switch(type)
    {
    case ShaderProgram::VERTEX:
        shader = glCreateShader(GL_VERTEX_SHADER);
        break;
    case ShaderProgram::FRAGMENT:
        shader = glCreateShader(GL_FRAGMENT_SHADER);
        break;
    default:
        break;
    }

    glShaderSource(shader, 1, &shaderCode, NULL);
    glCompileShader(shader);
    // Print error if any
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "Error shader compilation failed\n" << infoLog << std::endl;
    }
    // Shader program
    glAttachShader(m_program, shader);
    glDeleteShader(shader);
}

void ShaderProgram::link()
{
    glLinkProgram(m_program);
    GLint success;
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if(!success)
    {
        GLchar infolog[512];
        glGetProgramInfoLog(m_program, 512, NULL, infolog);
        std::cout << "Error shader program linking failed\n" << infolog << std::endl;
    }
}

void ShaderProgram::use_program()
{
    glUseProgram(m_program);
}

GLuint ShaderProgram::get_program() const
{
    return m_program;
}
