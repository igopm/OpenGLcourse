//
// Created by Igor Maschikevich on 11/16/2017.
//
//==========================================================================================
#include <iostream>
#include <string>
#include <math.h>
#include "SOIL.h"
//==========================================================================================
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ShadersLoader.h"
//==========================================================================================
const GLuint WindowWidth = 600;
const GLuint WindowHeight = 400;
const char* setImage ="common_textures/container2.jpg";
//==========================================================================================
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
//==========================================================================================
//void drawCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint namberTirangls);
//==========================================================================================
GLfloat vertices[] = {
    //Positions              //Colors
    // body
    0.3f,     0.5f,  0.0f,   0.604f, 0.804f, 0.196f,     // 0
    -0.3f,    -0.6f,  0.0f,   0.604f, 0.804f, 0.196f,   // 1
    0.3f,    -0.6f,   0.0f,    0.686f, 0.933f, 0.933f,   // 2
    -0.3f,     0.5f,  0.0f,     0.686f, 0.933f, 0.933f,  // 3
    // left leg
    -0.25f,   -0.6f,   0.0f,   1.0f, 0.0f, 1.0f,  // 4
    -0.15f,   -0.6f,   0.0f,   1.0f, 0.0f, 1.0f,  // 5
    -0.15f,   -0.8f,   0.0f,   1.0f, 0.0f, 1.0f,  // 6
    -0.25f,   -0.8f,   0.0f,   1.0f, 0.0f, 1.0f,  // 7
    // right leg
    0.15f,   -0.6f,   0.0f,   1.0f, 1.0f, 1.0f,   // 8
    0.25f,   -0.6f,   0.0f,   1.0f, 1.0f, 1.0f,   // 9
    0.25f,   -0.8f,   0.0f,   1.0f, 1.0f, 1.0f,   // 10
    0.15f,   -0.8f,   0.0f,   1.0f, 1.0f, 1.0f,   // 11
    // left hand
    -0.3f,    0.25f,  0.0f,   0.9f, 0.7f, 0.4f,   // 12
    -0.6f,    0.25f,  0.0f,   0.9f, 0.7f, 0.4f,   // 13
    -0.6f,    0.125f, 0.0f,   0.9f, 0.7f, 0.4f,   // 14
    -0.3f,    0.125f, 0.0f,   0.9f, 0.7f, 0.4f,   // 15
    // right hand
    0.3f, 0.25f,   0.0f,   1.0f, 0.5f, 1.0f,   // 16
    0.6f,   0.25f,   0.0f,   1.0f, 0.5f, 1.0f,   // 17
    0.6f,   0.125f,  0.0f,   1.0f, 0.5f, 1.0f,   // 18
    0.3f, 0.125f,  0.0f,   1.0f, 0.5f, 1.0f,   // 19

    //head
    0.05f,  0.5f,    0.0f,   1.0f, 1.0f, 0.0f,   // 20
    -0.05f,  0.5f,    0.0f,   1.0f, 1.0f, 0.0f,   // 21
    0.0f,   0.6f,    0.0f,   1.0f, 1.0f, 0.0f,   // 22

    -0.05f,  0.7f,    0.0f,   1.0f, 1.0f, 0.0f,   // 23
    0.05f,  0.7f,    0.0f,   1.0f, 1.0f, 0.0f,   // 24

    -0.1f,   0.55f,   0.0f,   1.0f, 1.0f, 0.0f,   // 25
    -0.1f,   0.65f,   0.0f,   1.0f, 1.0f, 0.0f,   // 26

    0.1f,   0.55f,   0.0f,   1.0f, 1.0f, 0.0f,   // 27
    0.1f,   0.65f,   0.0f,   1.0f, 1.0f, 0.0f   // 28
};

unsigned int indices[] = {
    1, 2, 0,
    3, 1, 0,

    4, 7, 6,
    5, 6, 4,

    8, 11, 10,
    9, 10, 8,

    14, 15, 12,
    12, 13, 14,

    18, 17, 16,
    18, 16, 19

    //    21, 20, 22,
    //    22, 24, 23,

    //    25, 22, 26,
    //    21, 26, 27,

    //    21, 22, 25,
    //    26, 22, 23,

    //    20, 27, 22,
    //    22, 28, 24
};
GLfloat verticesBG[] = {
    1.0f, 1.0f,  0.0f,     // 0 raight up
    1.0f, -1.0f,  0.0f,  // 1 raight downstairs

    -1.0f, 1.0f,  0.0f,   // 2 left up
    -1.0f, -1.0f,  0.0f // 3 left downstairs
};
unsigned int indicesBG[] = {
    3, 1, 0,
    0, 2, 3
};
//==========================================================================================
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
//==========================================================================================
int main(){
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
    //window
    GLFWwindow* window = glfwCreateWindow(WindowWidth, WindowHeight, "OpenGL Dz2", nullptr, nullptr);
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
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    // Setup OpenGL options
    glEnable(GL_DEPTH_TEST);
    //================================================================================
    // Assembling a vertex shader
    auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
    string vertexShaderSource = shaders::loadShaderSourceFromFile("shaders/dz2.vert");
    const char* vertexShaderSourceNative = vertexShaderSource.c_str();
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
    std::string fragmentShaderSource =shaders::loadShaderSourceFromFile("shaders/dz2.frag");
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
    GLuint VBOs[2], VAOs[2], EBOs[2];
    glGenVertexArrays(2, VAOs); // we can also generate multiple VAOs or buffers at the same time
    glGenBuffers(2, VBOs);
    glGenBuffers(2, EBOs);

    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAOs[0]);
    // 2. Copy our array of vertices to the buffer for OpenGL
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. We set pointers to the vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // 4. We set colors to the vertex attributes
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // 5. Copy our array of indices to the buffer for OpenGL
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBindVertexArray(0);


    // BG
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAOs[1]);
    // 2. Copy our array of vertices to the buffer for OpenGL
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesBG), verticesBG, GL_STATIC_DRAW);
    // 3. We set pointers to the vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // 4. We set colors to the vertex attributes
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // 5. Copy our array of indices to the buffer for OpenGL
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesBG), indicesBG, GL_STATIC_DRAW);
    glBindVertexArray(0);
    //================================================================================
    // Load and create a texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // Set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load image, create texture and generate mipmaps
    //    int width, height;
    unsigned char* image = SOIL_load_image(setImage, &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
    while(!glfwWindowShouldClose(window)){
        glClearColor(0.2f, 0.6f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Use shaderProgram
        glUseProgram(shaderProgram);

        glBindVertexArray(VAOs[0]);
        glDrawElements(GL_TRIANGLES, 51, GL_UNSIGNED_INT, 0);

        //        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAOs[1]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    //================================================================================
    // Delete VAO, VBO, EBO
    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    glDeleteBuffers(2, EBOs);

    glfwTerminate();
    return 0;
}
//==========================================================================================
// Function for control. For exit press -  q;
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
//    if (key == GLFW_KEY_Q && action == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, GL_TRUE);
//}
// glEnable(GL_DEPTH_TEST);
//==========================================================================================
