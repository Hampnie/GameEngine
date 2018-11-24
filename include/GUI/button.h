#ifndef BUTTON_H
#define BUTTON_H

#include <boost/signals2.hpp>
#include <glm/glm.hpp>

#include "common.h"
class ShaderProgram;

class Button
{
public:
    Button(FRect rectangle, const std::string& norm, const std::string& press, const std::string& hover);

    void update(float dt);
    void draw(std::shared_ptr<ShaderProgram> shader);

    boost::signals2::signal<void()> OnPressed;
private:
    void init(const std::string& norm, const std::string& press, const std::string& hover);

    GLuint texNormal, texHover, texPress;
    FRect rectangle;
    bool pressed;

    glm::mat4 transform;

    enum class ButtonState
    {
        STATE_NORMAL, STATE_HOVER, STATE_PRESS
    }state;
};

#endif
