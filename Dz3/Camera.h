//
// Created by Igor Maschikevich on 12/05/2017.
//
//================================================================================
#pragma one

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class MyCamera
{
public:
    //    Camera(){
    //    }


    void processInput(GLFWwindow *window);
    //{
    //        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    //            glfwSetWindowShouldClose(window, true);

    //        float cameraSpeed = 2.5 * deltaTime;
    //        if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    //            cameraPos += cameraSpeed * cameraFront;
    //        if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    //            cameraPos -= cameraSpeed * cameraFront;
    //        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    //            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    //        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    //            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    //    }
    void initMVP();
    //private:
    // camera
    glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

    bool firstMouse = true;
    float yaw   = -90.0f;
    float pitch =  0.0f;
    float lastX =  800.0f / 2.0;
    float lastY =  600.0f / 2.0;
    float fov   =  45.0f;

    //// timing
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

};
