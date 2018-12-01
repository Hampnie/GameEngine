#include "emptyEntity.h"
#include "shaderProgram.h"

#include "resourceManager.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/compatibility.hpp>

EmptyEntity::EmptyEntity(FRect rectangle, texture_type type, std::string ID)
    : rectangle(rectangle),
      ID(ID)
{
    switch(type)
    {
        case texture_type::Wall:
            texture = ResourceManager::Instance().load_texture("textures/wall.png");
        break;
        case texture_type::Player:
            texture = ResourceManager::Instance().load_texture("textures/Gun.png");
        break;
        case texture_type::Bullet:
            texture = ResourceManager::Instance().load_texture("textures/projectile.png");
        break;
    }
}

void EmptyEntity::draw(std::shared_ptr<ShaderProgram> shader)
{
    glBindTexture(GL_TEXTURE_2D, texture);

    glm::mat4 transform;

    transform = glm::translate(transform, glm::vec3(rectangle.width/2, rectangle.height/2, 0.0f));
    transform = glm::translate(transform, glm::vec3(rectangle.x, rectangle.y, 0.0f));
    transform = glm::scale(transform, glm::vec3(rectangle.width/2, rectangle.height/2, 0.0f));
    transform = glm::rotate(transform, angle, glm::vec3(0.0f, 0.0f, 1.0f));

    shader->set_mat4("model", transform);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void EmptyEntity::set_position(float x, float y)
{
    rectangle.x = x;
    rectangle.y = y;
}

