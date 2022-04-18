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
#include "Texture.h"
#include "Libraries/glm/glm/glm.hpp"
#include "Libraries/glm/glm/gtc/matrix_inverse.hpp"
#include "Libraries/glm/glm/gtc/type_ptr.hpp"
#include "Camera.h"

const int width = 800;
const int height = 800;


// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width,height, "this", NULL, NULL);
    if(window == NULL)
    {
        std::cout << "Failed to create glfw window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glViewport(0, 0,width, height);

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
    

    Texture brickTex("assets/brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    brickTex.texUnit(shaderProgram, "tex0", 0);


    glEnable(GL_DEPTH_TEST);

    Camera camera(width, height, glm::vec3(.0f,.0f,2.f));

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderProgram.activate();
        camera.Inputs(window);
        camera.Matrix(45.0f,0.1f,100.0f,shaderProgram,"camMatrix");
        brickTex.Bind();
        vao1.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);

    }
    brickTex.Delete();
    vao1.Delete();
    vbo1.Delete();
    ebo.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}