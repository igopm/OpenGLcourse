//
// Created by Igor Maschikevich on 11/16/2017.
//
//==========================================================================================
#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include "SOIL.h"
#include "MotokoGL.h"
#include "./vaofactory.h"
//==========================================================================================
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
//==========================================================================================
const GLuint WindowWidth = 800;
const GLuint WindowHeight = 600;
const char* DefaultNameWindow = "Dz2";
//==========================================================================================
const char* setVertexHuman ="shaders/dz1.vert";
const char* setFragmentHuman ="shaders/dz1.frag";
const char* setVertexBG ="shaders/bg.vert";
const char* setFragmentBG ="shaders/bg.frag";
//==========================================================================================
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
//==========================================================================================

GLfloat vertices[] = {
    //Positions              //Colors
    // left leg
    -0.3f,   -0.6f,   0.0f,   1.0f, 0.0f, 1.0f,  // 0
    -0.2f,   -0.6f,   0.0f,   1.0f, 0.0f, 1.0f,  // 1
    -0.2f,   -0.8f,   0.0f,   1.0f, 0.0f, 1.0f,  // 2
    -0.3f,   -0.8f,   0.0f,   1.0f, 0.0f, 1.0f,  // 3
    // right leg
    0.2f,   -0.6f,   0.0f,   0.5f, 0.0f, 1.0f,   // 4
    0.3f,   -0.6f,   0.0f,   0.5f, 0.0f, 1.0f,   // 5
    0.3f,   -0.8f,   0.0f,   0.5f, 0.0f, 1.0f,   // 6
    0.2f,   -0.8f,   0.0f,   0.5f, 0.0f, 1.0f,   // 7
    // left hand
    -0.3f,    0.5f,  0.0f,   0.9f, 0.7f, 0.4f,   // 8
    -0.6f,    0.5f,  0.0f,   0.9f, 0.7f, 0.4f,   // 9
    -0.6f,    0.4f, 0.0f,   0.9f, 0.7f, 0.4f,   // 10
    -0.3f,    0.4f, 0.0f,   0.9f, 0.7f, 0.4f,   // 11
    // right hand
    0.3f, 0.5f,   0.0f,   1.0f, 1.f, 1.0f,   // 12
    0.6f,   0.5f,   0.0f,   1.0f, 1.0f, 1.0f,   // 13
    0.6f,   0.4f,  0.0f,   1.0f, 1.0f, 1.0f,   // 14
    0.3f, 0.4f,  0.0f,   1.0f, 1.0f, 1.0f   // 15
};

unsigned int indices[] = {
    1, 2, 0,
    3, 0, 2,

    4, 7, 6,
    5, 6, 4,

    8, 11, 10,
    9, 10, 8,

    14, 15, 12,
    12, 13, 14
};



GLfloat verticesHead[] = {
    0.2f, 0.9f,   1.0f, 1.0f, // Top Right
    0.2f, 0.5f, 1.0f, 0.0f, // Bottom Right
    -0.2f, 0.9f, 0.0f, 1.0f,  // Top Left
    -0.2f,  0.5f, 0.0f, 0.0f // Bottom Left
};
unsigned int indicesHead[] = {
    0, 2, 3,
    1, 3, 0
};
GLfloat verticesBody[] = {
    //Positions              //Colors
    // body
    0.3f, 0.5f,   1.0f, 1.0f, // Top Right
    0.3f,  -0.6f, 1.0f, 0.0f, // Bottom Right
    -0.3f, -0.6f, 0.0f, 0.0f, // Bottom Left
    -0.3f,  0.5f, 0.0f, 1.0f  // Top Left
};
unsigned int indicesBody[] = {
    0, 2, 3,
    1, 2, 0
};
GLfloat verticesBG[] = {
    // Positions    // Texture Coords
    1.0f, 1.0f,      1.0f, 1.0f, // Top Right
    1.0f, -1.0f,     1.0f, 0.0f, // Bottom Right
    -1.0f, -1.0f,    0.0f, 0.0f, // Bottom Left
    -1.0f,  1.0f,    0.0f, 1.0f  // Top Left
};
unsigned int indicesBG[] = {
    0, 2, 3,
    1, 2, 0
};
////==========================================================================================
////void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
////==========================================================================================
int main(){
    using namespace std;
    using namespace MotokoGL;
    // Initialization GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // turn on/off resizable window
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    // for Mac OS X
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //window
    GLFWwindow* window = glfwCreateWindow(WindowWidth, WindowHeight, DefaultNameWindow, nullptr, nullptr);
    if (window == nullptr){
        cout <<"Failed to create GLEW window" << endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    //================================================================================
    // glfwSetKeyCallback(window, key_callback);
    //================================================================================
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK){
        cout << "Faild to initialize GLEW" << endl;
        return -1;
    }
    //================================================================================
    // Setup OpenGL options
    glEnable(GL_DEPTH_TEST);
    //================================================================================
    //    Shader
    //================================================================================
    Shader humanShader(setVertexHuman, setFragmentHuman);
    Shader bgShader(setVertexBG, setFragmentBG);
    //================================================================================
    //    VAO
    //================================================================================
    Vao vHead = createRPoly(0, 0.65, 0.17*3/4, 0.15, 50);
    Vao vaoHuman = Vao({3, 3, 0}, vertices, sizeof(vertices), indices, sizeof(indices));
    Vao vaoBody = Vao({2, 0, 2}, verticesBody, sizeof(verticesBody), indicesBody, sizeof(indicesBody));
    Vao vaoBg = Vao({2, 0, 2}, verticesBG, sizeof(verticesBG), indicesBG, sizeof(indicesBG));
    Vao vaoHead = Vao({2, 0, 2}, verticesHead, sizeof(verticesHead), indicesHead, sizeof(indicesHead));
    //================================================================================
    //    GLint uColor = glGetUniformLocation (humanShader.Program, "uColor");
    Tex texBG = Tex::fromFile("common_textures/wall.jpg");
    Tex texBody = Tex::fromFile("common_textures/container2.jpg");
    //    Tex texFase = Tex::fromFile("common_textures/awesomeface.png");
    //===============================================================================
    //==============================================================================================
    while(!glfwWindowShouldClose(window)){
        glClearColor(0.2f, 0.6f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //=======================================================================
        vHead.draw();
        // Use shaderProgram
        humanShader.Use();
        vaoHuman.draw();
        //=======================================================================
        bgShader.Use();
        //==================================

        //==================================
        texBody.bind(0);
        vaoBody.draw();
        //==================================
        //        texFase.bind(0);
        //        vaoHead.draw();
        //==================================
        texBG.bind(0);
        vaoBg.draw();
        //=======================================================================
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    //================================================================================
    glfwTerminate();
    return 0;
}
//==========================================================================================

