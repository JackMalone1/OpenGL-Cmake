#ifndef __VERTEXARRAYOBJECT_H__
#define __VERTEXARRAYOBJECT_H__

#include "glad.h"
#include "vertexBufferObject.h"

class VAO
{
public:
    GLuint ID;
    VAO();

    void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
    void Bind();
    void Unbind();
    void Delete();
};


#endif