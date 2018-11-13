#include "gamelevel.h"

#include <glm/gtc/matrix_transform.hpp>
#include <Box2D/Box2D.h>
#include <sstream>

#include "core.h"
#include "input.h"
#include "bullet.h"

GameLevel::GameLevel(std::string pathToLevel) : map(pathToLevel) 
{
    glm::vec2 windowSize = Core::instance().getWindowSize();
    screenX = windowSize.x;
    screenY = windowSize.y;
}

void GameLevel::init(b2World* physWorld)
{
    Level::init(physWorld);

    int x, y, width, height;
    std::stringstream stream(map);

    while(stream)
    {
        // Load map and add walls
        stream >> x >> y >> width >> height;
        FRect position1{x, y, width, height};
        Wall* wall = new Wall(position1, Entity::phys_body_type::STATIC, physWorld);
        addEntity(wall);
    }

    // Add player
    FRect position{512, 384, 80.0f, 84.0f};
    mainFighter = std::make_shared<Fighter>(position, physWorld);
    addEntity(mainFighter.get());
}

void GameLevel::input_handler(float dt)
{
	//mainFighter->set_velocity(Fighter::MOVE_DIRECTION::STOP);

    if(Input::keyPressed(SDLK_w))
    {
        mainFighter->set_velocity(Fighter::MOVE_DIRECTION::UP);
    }
    if(Input::keyPressed(SDLK_s))
    {        
        mainFighter->set_velocity(Fighter::MOVE_DIRECTION::DOWN);
    }
    if(Input::keyPressed(SDLK_a))
    {
        mainFighter->set_velocity(Fighter::MOVE_DIRECTION::LEFT);
    }
    if(Input::keyPressed(SDLK_d))
    {
        mainFighter->set_velocity(Fighter::MOVE_DIRECTION::RIGHT);
    }
    if(Input::buttonPressed(SDL_BUTTON_LEFT))
    {
        glm::vec2 mousePos = Input::mousePosition();
        launchBullet(glm::vec2(mousePos.x - screenX/2, mousePos.y - screenY/2));
    }

    // Calculate angle
    glm::vec2 mousePos = Input::mousePosition();
    glm::vec2 playerCenter{screenX/2, screenY/2};
    mainFighter->set_angle(atan2(playerCenter.y - mousePos.y, playerCenter.x - mousePos.x));

    cooldown += dt;
}

void GameLevel::launchBullet(glm::vec2 direction)
{
    if(cooldown >= 1.0f)
    {
        float magicAngle = mainFighter->get_angle() - 90.0f;

        FRect rectangle = mainFighter->get_rect();
        //Calculate bullet start point
        glm::vec2 playerCenter{rectangle.x + rectangle.width / 2.0f, rectangle.y + rectangle.height / 2.0f};
        glm::vec2 bullPoint(rectangle.x + rectangle.width, rectangle.y - rectangle.height / 3.0f);
        glm::vec2 point;
        point.x = playerCenter.x + (bullPoint.x - playerCenter.x) * cos(magicAngle) - (bullPoint.y - playerCenter.y) * sin(magicAngle);
        point.y = playerCenter.y + (bullPoint.y - playerCenter.y) * cos(magicAngle) + (bullPoint.x - playerCenter.x) * sin(magicAngle);

        Bullet* ptr = new Bullet(physWorld, direction, point);
        Core::instance().addEntity(ptr);
        cooldown = 0.0f;
    }
}

void GameLevel::draw(ShaderProgram *shader)
{
	glm::mat4 view;
	FRect rectangle = mainFighter->get_rect();
    view = glm::translate(view, glm::vec3(-(rectangle.x + rectangle.width / 2.0f) + screenX/2, -(rectangle.y + rectangle.height / 2.0f) + screenY/2, -3.0f));

    shader->setMat4("view", view);

	Level::draw(shader);
	
}