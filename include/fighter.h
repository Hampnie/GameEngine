#ifndef FIGHTER_H
#define FIGHTER_H

#include <iostream>
#include <boost/asio.hpp>

#include "entity.h"
#include "common.h"
#include "core.h"

class ShaderProgram;

class Fighter : public Entity
{
public:
enum class MOVE_DIRECTION
    {
        LEFT,
        RIGHT,
        UP,
        DOWN,
        STOP
    };

    Fighter(FRect rectangle, std::string ID, std::shared_ptr<b2World> physWorld, boost::asio::ip::tcp::socket* socket = new boost::asio::ip::tcp::socket(*Core::instance().get_context()));
    ~Fighter() {}

    void update(float dt);

    void set_true_velocity(MOVE_DIRECTION dir);
    void set_false_velocity(MOVE_DIRECTION dir);

    boost::asio::ip::tcp::socket* get_socket();
    std::string get_ID() {return ID;}
    void set_ID(std::string newID) {ID = newID;}

    void get_direction(bool& up, bool& down, bool& right, bool& left);
    void set_direction(bool up, bool down, bool right, bool left);

    float get_angle();   

private:
    bool MOVE_UP = false;
    bool MOVE_DOWN = false;
    bool MOVE_RIGHT = false;
    bool MOVE_LEFT = false;

    float movementSpeed;

    std::shared_ptr<b2World> physWorld;

    boost::asio::ip::tcp::socket* socket;
};

#endif // FIGHTER_H
