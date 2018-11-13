#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <vector>
#include "level.h"
#include <string>

class b2World;
class ShaderProgram;

class GameLevel : public Level
{
public:
    GameLevel() {}
    virtual ~GameLevel() {}

    virtual void release() override {}

    virtual void init(b2World* physWorld, std::string pathToLevel) override;

    virtual void input_handler(float dt) override;

    virtual void draw(ShaderProgram *shader) override;

private:
    void launchBullet(glm::vec2 direction);

    float screenX, screenY;
    float cooldown;

    std::shared_ptr<Fighter> mainFighter;
};

#endif // GAMELEVEL_H
