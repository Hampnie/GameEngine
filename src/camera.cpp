#include "camera.h"

#define GLM_FORCE_RADIANS
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>

Camera::Camera(glm::vec3 pos, glm::vec3 up, GLfloat yaw, GLfloat pitch) :
    m_position(pos),
    m_worldUp(up),
    m_yaw(yaw),
    m_pitch(pitch),
    m_front(glm::vec3(0.0f, 0.0f, -1.0f)),
    m_movementSpeed(SPEED),
    m_mouseSensitivity(SENSITIVITY)
{
    recalculateVectors();
}

Camera::Camera() :
    m_position(glm::vec3(0.0f, 0.0f, 0.0f)),
    m_worldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
    m_yaw(YAW),
    m_pitch(PITCH),
    m_front(glm::vec3(0.0f, 0.0f, -1.0f)),
    m_movementSpeed(SPEED),
    m_mouseSensitivity(SENSITIVITY)
{
    recalculateVectors();
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::processKeyboard(Camera_Movement direction, GLfloat dt)
{
    GLfloat velocity = m_movementSpeed * dt;
    /*
    switch(direction)
    {
    case FORWARD:
        m_position += m_front * velocity;
        break;
    case BACKWARD:
        m_position -= m_front * velocity;
        break;
    case LEFT:
        m_position -= m_right * velocity;
        break;
    case RIGHT:
        m_position += m_right * velocity;
        break;
    }
    */
    glm::vec3 XZdir(m_front.x, m_position.y, m_front.z); // front vector without Y axis

    float tmp = 1 / glm::length(XZdir); // Число, на которое нам нужно увеличить наш вектор, чтобы его длинна была = 1
    glm::vec3 unitXZvec(m_front.x * tmp, m_position.y, m_front.z * tmp); // Unit vector directional
    switch(direction)
    {
    case FORWARD:
        m_position += unitXZvec * velocity;
        break;
    case BACKWARD:
        m_position -= unitXZvec * velocity;
        break;
    case LEFT:
        m_position -= m_right * velocity; // m_right vector already is an unit vector
        break;
    case RIGHT:
        m_position += m_right * velocity;
        break;
    }
    //std::cout << glm::length(tmpvec) << std::endl;
}

void Camera::proccesMouse(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch)
{
    xoffset *= m_mouseSensitivity;
    yoffset *= m_mouseSensitivity;

    m_yaw += xoffset;
    m_pitch += yoffset;

    if(constrainPitch)
    {
        if(m_pitch > 89.0f)
            m_pitch = 89.0f;
        if(m_pitch < -89.0f)
            m_pitch = -89.0f;
    }
    recalculateVectors();
}

void Camera::recalculateVectors()
{
    // Calculate the new Front vector;
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

    m_front = glm::normalize(front);
    // recalculate right and up vector
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}

glm::vec3 Camera::getPosition() const
{
    return m_position;
}
