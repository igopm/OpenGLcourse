//
// Created by Igor Maschikevich on 11/15/2017.
//
//================================================================================
#include <iostream>
#include <string>
//================================================================================
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ShadersLoader.h"
//================================================================================
const GLuint WindowWidth = 600;
const GLuint WindowHeight = 400;
const char* DefaultNameWindow = "OpenGL 15.11.2017";
//================================================================================
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
//================================================================================
// Coordinates of the triangle
GLfloat vertices[] = {
    0.0f,  0.5f, // 1.0
    -0.5f, -0.5f, // 1.1
    0.5f, -0.5f  // 1.2
};
unsigned int indices[] = {
    1, 2, 0
};
//================================================================================
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
//================================================================================
int main()
{
    using namespace std;
    // Initialization GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // turn on/off resizable window
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    // for Mac OS X
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //объект окна
    GLFWwindow* window = glfwCreateWindow(WindowWidth, WindowHeight, DefaultNameWindow, nullptr, nullptr);
    if (window == nullptr){
        cout <<"Failed to create GLEW window" << endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    //================================================================================
    //    glfwSetKeyCallback(window, key_callback);
    //================================================================================
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK){
        cout << "Faild to initialize GLEW" << endl;
        return -1;
    }
    //================================================================================
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    //================================================================================
    // Assembling a vertex shader
    auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
    std::string vertexShaderSource =shaders::loadShaderSourceFromFile("shaders/text.vert");
    const char* vertexShaderSourceNative =vertexShaderSource.c_str();
    glShaderSource (vertexShader, 1, &vertexShaderSourceNative, NULL);
    glCompileShader(vertexShader);

    // Check assembling vertex shader
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
    }
    //================================================================================
    // Assembling a fragment shader
    auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragmentShaderSource =shaders::loadShaderSourceFromFile("shaders/text.frag");
    const char* fragmentShaderSourceNative =fragmentShaderSource.c_str();
    glShaderSource (fragmentShader, 1, &fragmentShaderSourceNative, NULL);
    glCompileShader(fragmentShader);

    // Check assembling fragment shader
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
    }
    //================================================================================
    // Shader program
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // Check for successful linking with a shader program
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        cout << "ERROR::SHADER::PROGRRAM::LINKING_FAILED\n" << infoLog << endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    //================================================================================
    // Initialization VBO, VAO, EBO;
    GLuint VBO, VAO, EBO;
    // 1. Bind VAO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);
    // 2. Copy our array of vertices to the buffer for OpenGL
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. We set pointers to the vertex attributes
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBindVertexArray(0);
    //================================================================================
    while (!glfwWindowShouldClose(window)){
        glClearColor(0.2f, 0.6f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    //================================================================================
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}
//================================================================================
// Function for control. For exit press -  q;
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
//    if (key == GLFW_KEY_Q && action == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, GL_TRUE);
//}
//================================================================================
