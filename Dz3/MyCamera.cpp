//
// Created by Igor Maschikevich on 12/05/2017.
//
//================================================================================
#include <iostream>
#include "MyCamera.h"


void MyCamera::setView(const glm::mat4 &value)
{
    view = value;
}

void MyCamera::setProjection(const glm::mat4 &value)
{
    projection = value;
}

void MyCamera::setModel(const glm::mat4 &value)
{
    model = value;
}
//void MyCamera::glUM4(Shader sheder){
//    // Get their uniform locationq
//    GLint modelLoc = glGetUniformLocation(sheder.Program, "model");
//    GLint viewLoc = glGetUniformLocation(sheder.Program, "view");
//    GLint projLoc = glGetUniformLocation(sheder.Program, "projection");
//    // Pass them to the shaders
//    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
//    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
//}
