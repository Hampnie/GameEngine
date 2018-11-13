#ifndef FIGHTER_H
#define FIGHTER_H

#include <glm/glm.hpp>
#include <iostream>

#include "entity.h"
#include "common.h"
#include "bullet.h"


class ShaderProgram;

class Fighter : public Entity
{
public:
enum MOVE_DIRECTION
    {
        LEFT,
        RIGHT,
        UP,
        DOWN,
        STOP
    };

    Fighter(FRect rectangle, b2World* physWorld);
    ~Fighter() {}

    void update(float dt);
    void draw(ShaderProgram *shader);

    void set_angle(float a);
    void set_velocity(MOVE_DIRECTION dir);

    float get_angle();
    FRect get_rect();     

private:
    void calculateAngle();
    void setViewMatrix();

    //MOVE_DIRECTION direction;
    bool MOVE_UP, MOVE_DOWN, MOVE_RIGHT, MOVE_LEFT;

    float angle;

    float movementSpeed;
    b2World* physWorld;
};

#endif // FIGHTER_H
