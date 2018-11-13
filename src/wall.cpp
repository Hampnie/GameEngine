#include "wall.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Wall::Wall(FRect rectangle, phys_body_type phys_type, b2World *physWorld) :
    Entity(rectangle, phys_type, "textures/wall.png", bodyUserData::BT_WALL, physWorld)
{

}

void Wall::draw(ShaderProgram *shader)
{
    glBindTexture(GL_TEXTURE_2D, sprite);

    glm::mat4 transform;

    transform = glm::translate(transform, glm::vec3(rectangle.width/2, rectangle.height/2, 0.0f));
    transform = glm::translate(transform, glm::vec3(rectangle.x, rectangle.y, 0.0f));
    transform = glm::scale(transform, glm::vec3(rectangle.width/2, rectangle.height/2, 0.0f));

    shader->setMat4("model", transform);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
