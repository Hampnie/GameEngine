#ifndef CAMERA_H
#define CAMERA_H

#include "common.h"
#include <glm/glm.hpp>

enum Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default values for camera
const GLfloat YAW =        -90.0f;
const GLfloat PITCH =       0.0f;
const GLfloat SPEED =       0.01f;
const GLfloat SENSITIVITY = 0.2f;

class Camera
{
public:
    Camera(glm::vec3 pos, glm::vec3 up, GLfloat yaw, GLfloat pitch);
    Camera();

    glm::mat4 getViewMatrix();

    void processKeyboard(Camera_Movement direction, GLfloat dt);
    void proccesMouse(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true);
    glm::vec3 getPosition() const;
private:
    void recalculateVectors();

    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_worldUp;

    GLfloat m_yaw;
    GLfloat m_pitch;

    GLfloat m_movementSpeed;
    GLfloat m_mouseSensitivity;


};

#endif
