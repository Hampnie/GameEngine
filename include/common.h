#ifndef COMMON_H
#define COMMON_H

#include <GL/glew.h>
#include <GL/gl.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

struct FRect
{
    float x;
    float y;
    float width;
    float height;

    bool contains(glm::vec2 point)
    {
        return ( (x < point.x && y < point.y) &&
                 (x + width > point.x)        &&
                 (y + height > point.y) );
    }
};

struct bodyUserData
{
    enum body_type
    {
        BT_BULLET,
        BT_WALL,
        BT_PLAYER
    };
    body_type type;
    void* self_ptr;
    bool alive = true;
};

#endif // COMMON_H
