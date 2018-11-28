#ifndef EMPTY_ENTITY_H
#define EMPTY_ENTITY_H

#include "common.h"
#include <iostream>

class ShaderProgram;

class EmptyEntity
{
public:
	enum class texture_type
	{
		Wall,
		Player,
		Bullet
	};

    EmptyEntity(FRect rectangle, texture_type type, std::string ID);


    virtual ~EmptyEntity()
    {
    }

    virtual void init() {}

    virtual void update(float dt) {}
    virtual void draw(std::shared_ptr<ShaderProgram> shader);

    void set_position(float x, float y); // Mb final?
    void set_angle(float a) {angle = a;}
    FRect get_rectangle() {return rectangle;}
    std::string get_ID() { return ID;}

protected:
    GLuint texture;
    FRect rectangle;
    float angle = 0;
    std::string ID;
};

#endif
