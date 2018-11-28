#include "shaderProgram.h"
#include "fighter.h"
#include "input.h"
#include "resourceManager.h"
#include "core.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/compatibility.hpp>

Fighter::Fighter(FRect rectangle, std::string ID, std::shared_ptr<b2World> physWorld, boost::asio::ip::tcp::socket* socket) :
    Entity(rectangle, ID, Entity::phys_body_type::DYNAMIC, texture_type::Player, bodyUserData::BT_PLAYER, physWorld),
    movementSpeed(100.0f),
    physWorld(physWorld),
    socket(socket)
{
}

void Fighter::update(float dt)
{
    GLfloat velocity = movementSpeed * dt;

    body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));

    if(MOVE_UP)
    {
        body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, -velocity));
    }
    if(MOVE_DOWN)
    {
        body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, velocity));
    }
    if(MOVE_LEFT)
    {
        body->SetLinearVelocity(b2Vec2(-velocity, body->GetLinearVelocity().y));
    }
    if(MOVE_RIGHT)
    {
        body->SetLinearVelocity(b2Vec2(velocity, body->GetLinearVelocity().y));
    }

    rectangle.x = body->GetPosition().x * PHYS_MULT_FACTOR - rectangle.width/2;
    rectangle.y = body->GetPosition().y * PHYS_MULT_FACTOR - rectangle.height/2;

    body->SetTransform(body->GetPosition(), angle);
}

void Fighter::set_true_velocity(Fighter::MOVE_DIRECTION dir)
{
    //direction = dir;  
    switch(dir)
    {
        case MOVE_DIRECTION::UP:
            MOVE_UP = true;
            break;
        case MOVE_DIRECTION::DOWN:
            MOVE_DOWN = true;
            break;
        case MOVE_DIRECTION::LEFT:
            MOVE_LEFT = true;
            break;
        case MOVE_DIRECTION::RIGHT:
            MOVE_RIGHT = true;
            break; 
    }

}

void Fighter::set_false_velocity(MOVE_DIRECTION dir)
{
    switch(dir)
    {
        case MOVE_DIRECTION::UP:
            MOVE_UP = false;
            break;
        case MOVE_DIRECTION::DOWN:
            MOVE_DOWN = false;
            break;
        case MOVE_DIRECTION::LEFT:
            MOVE_LEFT = false;
            break;
        case MOVE_DIRECTION::RIGHT:
            MOVE_RIGHT = false;
            break; 
    }
}

float Fighter::get_angle()
{
    return angle;
}

boost::asio::ip::tcp::socket* Fighter::get_socket()
{
    return socket;
}

void Fighter::get_direction(bool& up, bool& down, bool& right, bool& left)
{
    up = MOVE_UP;
    down = MOVE_DOWN;
    right = MOVE_RIGHT;
    left = MOVE_LEFT;
}

void Fighter::set_direction(bool up, bool down, bool right, bool left)
{
    this->MOVE_UP = up;
    this->MOVE_DOWN = down;
    this->MOVE_RIGHT = right;
    this->MOVE_LEFT = left;
}
