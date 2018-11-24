#ifndef COMMON_H
#define COMMON_H

#include <GL/glew.h>
#include <GL/gl.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <memory>

#include <string>
#include <boost/asio.hpp>

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

struct command_struct
{
    std::string str;
    boost::asio::ip::tcp::socket* playerSocket;
    command_struct(std::string str, boost::asio::ip::tcp::socket* playerSocket) :
    str(str),
    playerSocket(playerSocket)
    { }
};

#endif // COMMON_H
