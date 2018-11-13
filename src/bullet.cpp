#include "bullet.h"
#include <glm/gtc/matrix_transform.hpp>

Bullet::Bullet(b2World *physWorld, glm::vec2 direction, glm::vec2 position)
    : Entity(FRect{position.x, position.y, 10.f, 10.0f}, Entity::phys_body_type::DYNAMIC, "textures/projectile.png", bodyUserData::BT_BULLET, physWorld),
      direction(direction),
      speed(1000.0f)
{

}

void Bullet::init()
{
    Entity::init();
    body->ApplyLinearImpulse(b2Vec2(direction.x * speed, direction.y * speed), body->GetPosition(), true);
    //body->SetLinearVelocity(b2Vec2(direction.x * speed, direction.y * speed));
    std::cout<< "Spawn bullet\n";
}

void Bullet::update(float dt)
{
    rectangle.x = body->GetPosition().x * PHYS_MULT_FACTOR - rectangle.width/2;
    rectangle.y = body->GetPosition().y * PHYS_MULT_FACTOR - rectangle.height/2;
}

void Bullet::draw(ShaderProgram *shader)
{
    glBindTexture(GL_TEXTURE_2D, sprite);

    glm::mat4 transform;

    transform = glm::translate(transform, glm::vec3(rectangle.width/2, rectangle.height/2, 0.0f));
    transform = glm::translate(transform, glm::vec3(rectangle.x, rectangle.y, 0.0f));
    transform = glm::scale(transform, glm::vec3(rectangle.width/2, rectangle.height/2, 0.0f));

    shader->setMat4("model", transform);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
