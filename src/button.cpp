#define GLEW_STATIC
#include <GL/glew.h>
#include "GUI/button.h"
#include "resourceManager.h"
#include "input.h"
#include "shaderProgram.h"
#include <glm/gtc/matrix_transform.hpp>


Button::Button(FRect rectangle, const std::string& norm, const std::string& press, const std::string& hover)
    : rectangle(rectangle)
{
    init(norm, press, hover);
}

void Button::init(const std::string& norm, const std::string& press, const std::string& hover)
{
    texNormal = ResourceManager::Instance().load_texture(norm.c_str());
    texPress = ResourceManager::Instance().load_texture(press.c_str());
    texHover = ResourceManager::Instance().load_texture(hover.c_str());

    
    transform = glm::translate(transform, glm::vec3(rectangle.width/2, rectangle.height/2, 0.0f));
    transform = glm::translate(transform, glm::vec3(rectangle.x, rectangle.y, 0.0f));
    transform = glm::scale(transform, glm::vec3(rectangle.width/2, rectangle.height/2, 0.0f));
    state = ButtonState::STATE_NORMAL;
    pressed = false;
}

void Button::update(float dt)
{
    // Change button's state
    int x, y;
    if (Input::buttonPressed(SDL_BUTTON_LEFT) && rectangle.contains(Input::mousePosition()))
    {
        state = ButtonState::STATE_PRESS;
        pressed = true;
    }
    else if (rectangle.contains(Input::mousePosition()))
    {
        if (pressed)
        {
            this->OnPressed();
            return;
        }
        state = ButtonState::STATE_HOVER;
        pressed = false;
    }
    else
    {
        state = ButtonState::STATE_NORMAL;
        pressed = false;
    }
}

void Button::draw(std::shared_ptr<ShaderProgram> shader)
{
    //Choose texture
    switch (state)
    {
    case ButtonState::STATE_NORMAL:
        glBindTexture(GL_TEXTURE_2D, texNormal);
        break;
    case ButtonState::STATE_HOVER:
        glBindTexture(GL_TEXTURE_2D, texHover);
        break;
    case ButtonState::STATE_PRESS:
        glBindTexture(GL_TEXTURE_2D, texPress);
        break;
    }
    shader->set_mat4("model", transform);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

