#ifndef WALL_H
#define WALL_H

#include "entity.h"

class Wall : public Entity
{
public:
    Wall(FRect rectangle, phys_body_type phys_type, std::shared_ptr<b2World> physWorld, std::string ID);

    void update(float dt) {}
};

#endif
