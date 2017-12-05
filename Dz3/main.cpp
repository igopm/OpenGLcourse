//
// Created by Igor Maschikevich on 12/03/2017.
//
//==========================================================================================
#include <iostream>
//#include <string>
//#include <math.h>
//#include <thread>
//==========================================================================================
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//==========================================================================================
#include "MotokoGL.h"
#include "Shader.h"
#include "MyCamera.h"
//==========================================================================================
const GLuint WindowWidth = 800;
const GLuint WindowHeight = 600;
const char* DefaultNameWindow = "Dz3";
////==========================================================================================
const char* setVertexBG ="shaders/bg.vert";
const char* setFragmentBG ="shaders/bg.frag";

const char* setVertexCube ="shaders/cube.vert";
const char* setFragmentCube ="shaders/cube.frag";
MyCamera camera;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//==========================================================================================
GLfloat verticesCube[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
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
int main(){
    using namespace std;
    using namespace MotokoGL;
    // Initialization GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //    // turn on/off resizable window
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    // for Mac OS X
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //    //window
    GLFWwindow* window = glfwCreateWindow(WindowWidth, WindowHeight, DefaultNameWindow, nullptr, nullptr);
    if (window == nullptr){
        cout <<"Failed to create GLEW window" << endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    //================================================================================
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //================================================================================
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK){
        cout << "Faild to initialize GLEW" << endl;
        return -1;
    }
    //    Shader
    //================================================================================
    Shader bgShader(setVertexBG, setFragmentBG);
    Shader cubeShader(setVertexCube, setFragmentCube);
    //================================================================================
    //    VAO
    //================================================================================
    Vao vaoBg = Vao({2, 0, 2}, verticesBG, sizeof(verticesBG), indicesBG, sizeof(indicesBG));
    Vao vaoCube = Vao({3, 0, 2}, verticesCube, sizeof(verticesCube));
    //================================================================================
    Tex texBG = Tex::fromFile("common_textures/wall.jpg");
    Tex texCube = Tex::fromFile("common_textures/container2.jpg");
    //===============================================================================
    // Setup OpenGL options
    glEnable(GL_DEPTH_TEST);

    //==============================================================================================
    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();

        float currentFrame = glfwGetTime();
        camera.deltaTime = currentFrame - camera.lastFrame;
        camera.lastFrame = currentFrame;

        camera.processInput(window);

        glClearColor(0.2f, 0.6f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //=======================================================================
        bgShader.Use();
        texBG.bind(0);
        glDepthMask(GL_FALSE);
        vaoBg.draw();
        //=======================================================================
        glDepthMask(GL_TRUE);
        //=======================================================================
        cubeShader.Use();
        //=======================================================================
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;


        projection = glm::perspective(glm::radians(camera.fov), (float)WindowWidth/
                                      (float)WindowHeight, 0.1f, 5.0f);

        view = glm::lookAt(camera.cameraPos, camera.cameraPos + camera.cameraFront, camera.cameraUp);

        model = glm::rotate(camera.model, (GLfloat)glfwGetTime() * 1.0f, glm::vec3(0.5f, 1.0f, 0.0f));


        // Get their uniform locationq
        GLint modelLoc = glGetUniformLocation(cubeShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(cubeShader.Program, "view");
        GLint projLoc = glGetUniformLocation(cubeShader.Program, "projection");
        // Pass them to the shaders
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        //=======================================================================
        texCube.bind(0);
        // Draw container
        vaoCube.draw();
        //=======================================================================
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    camera.camera_mouse( window, xpos,  ypos);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.camera_scroll(window, xoffset, yoffset);
}
