#include "glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <streambuf>
#include "stb_image.h"
#include "shader.h"
#include "EBO.h"
#include "vertexArrayObject.h"
#include "vertexBufferObject.h"



// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
	-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
	 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
	 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
};

// Indices for vertices order
GLuint indices[] =
{
	0, 2, 1, // Upper triangle
	0, 3, 2 // Lower triangle
};


int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800,800, "this", NULL, NULL);
    if(window == NULL)
    {
        std::cout << "Failed to create glfw window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glViewport(0, 0,800, 800);

    Shader shaderProgram("vertex_shader", "fragment_shader");
    VAO vao1;
    vao1.Bind();
    VBO vbo1(vertices, sizeof(vertices));
    EBO ebo(indices, sizeof(indices));
    vao1.LinkAttrib(vbo1, 0, 3, GL_FLOAT, sizeof(float) * 8, (void*)0);
    vao1.LinkAttrib(vbo1, 1, 3, GL_FLOAT, sizeof(float) * 8, (void*)(sizeof(float) * 3));
    vao1.LinkAttrib(vbo1, 2, 2, GL_FLOAT, sizeof(float) * 8, (void*)(sizeof(float) * 6));
    vao1.Unbind();
    vao1.Unbind();
    ebo.Unbind();
    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

    int widthImg, heightImg, numColCh;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load("assets/pop_cat.png", &widthImg, &heightImg, &numColCh, 0);

    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);

    GLuint tex0Uni = glGetUniformLocation(shaderProgram.ID, "tex0");
    shaderProgram.activate();
    glUniform1ui(tex0Uni, 0);

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.activate();
        glUniform1f(uniID, 0.5f);
        glBindTexture(GL_TEXTURE_2D, texture);
        vao1.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);

    }
    glDeleteTextures(1, &texture);
    vao1.Delete();
    vbo1.Delete();
    ebo.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}