#include "bullet.h"
#include <glm/gtc/matrix_transform.hpp>

Bullet::Bullet(std::shared_ptr<b2World> physWorld, glm::vec2 direction, Fighter* player, std::string ID)
    : Entity::Entity(FRect{0.0f, 0.0f, 10.f, 10.0f}, ID, Entity::phys_body_type::DYNAMIC, texture_type::Bullet, bodyUserData::BT_BULLET, physWorld),
   	  direction(direction)
{
	float magicAngle = player->get_angle() - 90.0f;

    FRect playerRectangle = player->get_rectangle();
    //Calculate bullet start point
    glm::vec2 startPoint;
    glm::vec2 playerCenter{playerRectangle.x + playerRectangle.width / 2.0f, playerRectangle.y + playerRectangle.height / 2.0f};
    glm::vec2 bullPoint(playerRectangle.x + playerRectangle.width, playerRectangle.y - playerRectangle.height / 3.0f);
    startPoint.x = playerCenter.x + (bullPoint.x - playerCenter.x) * cos(magicAngle) - (bullPoint.y - playerCenter.y) * sin(magicAngle);
    startPoint.y = playerCenter.y + (bullPoint.y - playerCenter.y) * cos(magicAngle) + (bullPoint.x - playerCenter.x) * sin(magicAngle);
    rectangle.x = startPoint.x;
    rectangle.y = startPoint.y;
}

void Bullet::init()
{
    Entity::init();

    float length = std::sqrt(direction.x*direction.x + direction.y*direction.y);

    body->ApplyLinearImpulse(b2Vec2((direction.x / length) * speed, (direction.y / length) * speed), body->GetPosition(), true);;
    std::cout<< "Spawn bullet\n";
}

void Bullet::update(float dt)
{
    rectangle.x = body->GetPosition().x * PHYS_MULT_FACTOR - rectangle.width/2;
    rectangle.y = body->GetPosition().y * PHYS_MULT_FACTOR - rectangle.height/2;

    // If velocity too small - delete it
    if((std::abs(body->GetLinearVelocity().x)) + (std::abs(body->GetLinearVelocity().y)) < 4)
    {
    	Core::instance().delete_entity(static_cast<EmptyEntity*>(this));
    }
}
