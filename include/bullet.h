#ifndef BULLET_H
#define BULLET_H

#include "entity.h"
#include "fighter.h"
#include <iostream>

class Bullet : public Entity
{
public:
    Bullet(std::shared_ptr<b2World> physWorld, glm::vec2 direction, Fighter* player, std::string ID);

    void init();

    void update(float dt);

private:
    glm::vec2 direction;
    float speed = 0.1f;;
};

#endif // BULLET_H
