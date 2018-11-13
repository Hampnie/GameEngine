#ifndef ENTITY_H
#define ENTITY_H

#include "shaderProgram.h"
#include <Box2D/Box2D.h>
#include <iostream>
#include "common.h"

class Entity
{
public:
    enum phys_body_type
    {
        STATIC,
        DYNAMIC
    };

    Entity(FRect rectangle, phys_body_type phys_type, const std::string& sprite, bodyUserData::body_type bData_type, b2World* physWorld);


    virtual ~Entity()
    {
        physWorld->DestroyBody(body);
        std::cout << "Entity was deleted\n";
    }

    virtual void init();

    virtual void update(float dt) {}
    virtual void draw(ShaderProgram *shader) {}

protected:
    b2Body *body;

    GLuint sprite;
    FRect rectangle;
    phys_body_type phys_type;
    bodyUserData::body_type bData_type;
    b2World* physWorld;

    enum {PHYS_MULT_FACTOR = 100};
};

#endif
