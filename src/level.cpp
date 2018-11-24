#include "level.h"

#include <algorithm>
#include <iostream>

void Level::pre_update(float dt)
{
    handle_input_data();

    if(!newEntities.empty())
    {
        for(auto const& entity: newEntities)
        {
            entity->init();
            activeEntities.push_back(entity);
        }
        newEntities.clear();
    }

}

void Level::post_update(float dt)
{
    if(!destroyEntities.empty())
    {
        for(auto const& entity: destroyEntities)
        {
            // erase-remove idiom
            activeEntities.erase( std::remove( activeEntities.begin(), activeEntities.end(), entity ), activeEntities.end() );
            delete entity;
        }
        destroyEntities.clear();
    }

    send_data();
}

void Level::update(float dt)
{
    for(auto const& entity: activeEntities)
    {
        entity->update(dt);
    }
}

void Level::draw(std::shared_ptr<ShaderProgram> shader)
{
    for(auto const& entity: activeEntities)
    {
        entity->draw(shader);
    }
}

void Level::add_entity(Entity *ptr)
{
    newEntities.push_back(ptr);
}

void Level::delete_entity(Entity *ptr)
{
    // Check if already contains
    if(std::find(destroyEntities.begin(), destroyEntities.end(), ptr) == destroyEntities.end()) 
    {
        destroyEntities.push_back(ptr);
    } 
}

void Level::send_data()
{

}

void Level::handle_input_data()
{

}
