#ifndef SHADER_H
#define SHADER_H

#include "glad.h"
#include <string>
#include <fstream>
#include <iostream>
#include <cerrno>

std::string read_shader(std::string file_name);


class Shader
{
public:
    GLuint ID;
    Shader(const char* vertexFile, const char* fragmentFile);
    ~Shader();
    void activate();
    void deactivate();
private:
    void compileErrors(unsigned int shader, const char* type);
};

#endif