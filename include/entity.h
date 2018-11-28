#ifndef ENTITY_H
#define ENTITY_H

#include "shaderProgram.h"
#include <Box2D/Box2D.h>
#include <iostream>
#include "common.h"
#include "emptyEntity.h"

class Entity : public EmptyEntity
{
public:
    enum class phys_body_type
    {
        STATIC,
        DYNAMIC
    };

    Entity(FRect rectangle, std::string ID, phys_body_type phys_type, texture_type type, bodyUserData::body_type bData_type, std::shared_ptr<b2World> physWorld);


    virtual ~Entity()
    {
        physWorld->DestroyBody(body);
    }

    virtual void init();

protected:
    b2Body *body;

    phys_body_type phys_type;
    bodyUserData::body_type bData_type;
    std::shared_ptr<b2World> physWorld;

    enum {PHYS_MULT_FACTOR = 100};
};

#endif
