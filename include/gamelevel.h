#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <vector>
#include <string>

#include "fighter.h"
#include "wall.h"
#include "level.h"

class b2World;
class ShaderProgram;

class GameLevel : public Level
{
public:
    GameLevel(std::string pathToLevel);
    virtual ~GameLevel() {}

    virtual void release() override {}

    virtual void init(b2World* physWorld);

    virtual void input_handler(float dt) override;

    virtual void draw(ShaderProgram *shader) override;

private:
    void launchBullet(glm::vec2 direction);

    float screenX, screenY;
    float cooldown;
    std::string map;

    std::shared_ptr<Fighter> mainFighter;
};

#endif // GAMELEVEL_H
