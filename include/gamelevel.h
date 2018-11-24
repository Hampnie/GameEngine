#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <string>
#include <vector>

#include "fighter.h"
#include "level.h"

class b2World;
class ShaderProgram;

class GameLevel : public Level
{
public:
    GameLevel(std::string pathToLevel);
    virtual ~GameLevel() {}

    virtual void release() override {}

    virtual void init(std::shared_ptr<b2World> physWorld);

    virtual void input_handler(float dt) override;

    virtual void draw(std::shared_ptr<ShaderProgram> shader) override;

protected:
    bool launch_bullet(glm::vec2 direction, bool isMainPlayer, glm::vec2 playerPosition = glm::vec2(0,0));

    float screenX, screenY;
    float cooldown;
    std::string map;

    std::vector<Fighter*> players;

    std::shared_ptr<Fighter> mainFighter;
};

#endif // GAMELEVEL_H
