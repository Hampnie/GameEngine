#define GLEW_STATIC
#include <GL/glew.h>
#include "GUI/button.h"
#include "resourceManager.h"
#include "input.h"
#include "shaderProgram.h"
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

Button::Button(FRect rectangle, const std::string& norm, const std::string& press, const std::string& hover)
    : rectangle(rectangle)
{
    init(norm, press, hover);
}

void Button::init(const std::string& norm, const std::string& press, const std::string& hover)
{
    texNormal = ResourceManager::Instance().loadTexture(norm.c_str());
    texPress = ResourceManager::Instance().loadTexture(press.c_str());
    texHover =ResourceManager::Instance().loadTexture(hover.c_str());

    
    transform = glm::translate(transform, glm::vec3(rectangle.width/2, rectangle.height/2, 0.0f));
    transform = glm::translate(transform, glm::vec3(rectangle.x, rectangle.y, 0.0f));
    transform = glm::scale(transform, glm::vec3(rectangle.width/2, rectangle.height/2, 0.0f));
    state = STATE_NORMAL;
    pressed = false;
}

void Button::update(float dt)
{
    // Change button's state
    int x, y;
    if (Input::buttonPressed(SDL_BUTTON_LEFT) && rectangle.contains(Input::mousePosition()))
    {
        state = STATE_PRESS;
        pressed = true;
    }
    else if (rectangle.contains(Input::mousePosition()))
    {
        if (pressed)
        {
            this->OnPressed();
            return;
        }
        state = STATE_HOVER;
        pressed = false;
    }
    else
    {
        state = STATE_NORMAL;
        pressed = false;
    }
}

void Button::draw(ShaderProgram *shader)
{
    //Choose texture
    switch (state)
    {
    case STATE_NORMAL:
        glBindTexture(GL_TEXTURE_2D, texNormal);
        break;
    case STATE_HOVER:
        glBindTexture(GL_TEXTURE_2D, texHover);
        break;
    case STATE_PRESS:
        glBindTexture(GL_TEXTURE_2D, texPress);
        break;
    }
    shader->setMat4("model", transform);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

