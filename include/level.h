#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "emptyEntity.h"

class b2World;
class ShaderProgram;

class Level
{
public:
    Level() {}
    virtual ~Level() {}

    virtual void init(std::shared_ptr<b2World> physWorld)
    {
        this->physWorld = physWorld;
    }
    virtual void draw(std::shared_ptr<ShaderProgram> shader);

    void pre_update(float dt);
    virtual void update(float dt);
    void post_update(float dt);

    virtual void input_handler(float dt) {}

    void add_entity(EmptyEntity* ptr);
    void delete_entity(EmptyEntity* ptr);

protected:
    virtual void send_data();
    virtual void handle_input_data();

    std::shared_ptr<b2World> physWorld;    

    std::vector<EmptyEntity*> activeEntities;
    std::vector<EmptyEntity*> destroyEntities;
    std::vector<EmptyEntity*> newEntities;
};

#endif
