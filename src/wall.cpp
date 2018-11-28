#include "wall.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Wall::Wall(FRect rectangle, phys_body_type phys_type, std::shared_ptr<b2World> physWorld, std::string ID) :
    Entity(rectangle, ID, phys_type, texture_type::Wall, bodyUserData::BT_WALL, physWorld)
{

}
