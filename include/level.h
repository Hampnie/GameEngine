#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "entity.h"

class b2World;
class ShaderProgram;

class Level
{
public:
    Level() {}
    virtual ~Level() {}

    virtual void init(b2World* physWorld)
    {
        this->physWorld = physWorld;
    }
    virtual void draw(ShaderProgram *shader);

    void preUpdate(float dt);
    virtual void update(float dt);
    void postUpdate(float dt);

    virtual void input_handler(float dt) {}

    void addEntity(Entity* ptr);
    void deleteEntity(Entity* ptr);
    
    virtual void release() = 0;

protected:
    virtual void send_data();
    virtual void handle_input_data();

    b2World* physWorld;    

    std::vector<Entity*> activeEntities;
    std::vector<Entity*> destroyEntities;
    std::vector<Entity*> newEntities;
};

#endif
