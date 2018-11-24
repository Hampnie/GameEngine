#ifndef BULLET_H
#define BULLET_H

#include "entity.h"
#include <iostream>

class Bullet : public Entity
{
public:
    Bullet(std::shared_ptr<b2World> physWorld, glm::vec2 direction, glm::vec2 position);

    void init();

    void update(float dt);
    void draw(std::shared_ptr<ShaderProgram> shader);

private:
    glm::vec2 direction;
    float speed;
};

#endif // BULLET_H
