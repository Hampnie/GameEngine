#include "shaderProgram.h"
#include "fighter.h"
#include "input.h"
#include "resourceManager.h"
#include "core.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/compatibility.hpp>

Fighter::Fighter(FRect rectangle, b2World* physWorld) :
    Entity(rectangle, Entity::phys_body_type::DYNAMIC, "textures/Gun.png", bodyUserData::BT_PLAYER, physWorld),
    movementSpeed(100.0f),
    angle(0.0f),
    physWorld(physWorld)
{
}

void Fighter::update(float dt)
{
    GLfloat velocity = movementSpeed * dt;

    body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
    
    /*
    switch(direction)
    {
        case MOVE_DIRECTION::STOP:
            break;
        case MOVE_DIRECTION::UP:
            body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, -velocity));
            break;
        case MOVE_DIRECTION::DOWN:
            body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, velocity));
            break;
        case MOVE_DIRECTION::LEFT:
            body->SetLinearVelocity(b2Vec2(-velocity, body->GetLinearVelocity().y));
            break;
        case MOVE_DIRECTION::RIGHT:
            body->SetLinearVelocity(b2Vec2(velocity, body->GetLinearVelocity().y));
            break;
    }
    */

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

    MOVE_UP = MOVE_RIGHT = MOVE_LEFT = MOVE_DOWN = false;

    rectangle.x = body->GetPosition().x * PHYS_MULT_FACTOR - rectangle.width/2;
    rectangle.y = body->GetPosition().y * PHYS_MULT_FACTOR - rectangle.height/2;

    body->SetTransform(body->GetPosition(), angle);
}

void Fighter::draw(ShaderProgram *shader)
{
    glBindTexture(GL_TEXTURE_2D, sprite);

    glm::mat4 transform;

    transform = glm::translate(transform, glm::vec3(rectangle.width/2, rectangle.height/2, 0.0f));
    transform = glm::translate(transform, glm::vec3(rectangle.x, rectangle.y, 0.0f));
    transform = glm::scale(transform, glm::vec3(rectangle.width/2, rectangle.height/2, 0.0f));
    transform = glm::rotate(transform, angle, glm::vec3(0.0f, 0.0f, 1.0f));

    //glm::mat4 view;
    //view = glm::translate(view, glm::vec3(-(rectangle.x + rectangle.width / 2.0f) + screenX/2, -(rectangle.y + rectangle.height / 2.0f) + screenY/2, -3.0f));

    shader->setMat4("model", transform);
    //shader->setMat4("view", view);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Fighter::set_angle(float a)
{
    angle = a;
}

void Fighter::set_velocity(Fighter::MOVE_DIRECTION dir)
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

float Fighter::get_angle()
{
    return angle;
}

FRect Fighter::get_rect()
{
    return rectangle;
}
