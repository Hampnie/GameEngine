#ifndef WALL_H
#define WALL_H

#include "entity.h"

class Wall : public Entity
{
public:
    Wall(FRect rectangle, phys_body_type phys_type, std::shared_ptr<b2World> physWorld);

    void update(float dt) {}
    void draw(std::shared_ptr<ShaderProgram> shader);
};

#endif
