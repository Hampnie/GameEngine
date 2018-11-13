#ifndef CORE_H
#define CORE_H

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <Box2D/Box2D.h>

#include <thread>


#include "common.h"
#include "entity.h"

class ShaderProgram;
class Camera;
class Level;

class Core
{
public:
    //Singleton patern
    static Core& instance()
    {
        static Core core;
        return core;
    }

    // Initialize all data
    bool init(int width, int height, bool fullScreen);
    void mainloop();
    void releaseResources();

    // Create new level
    void installLevel(Level* level);
    // End gameloop
    void closeGame();

    // Add entity to level
    void addEntity(Entity* ptr);
    // Delete entity from level
    void deleteEntity(Entity* ptr);

    glm::vec2 getWindowSize();
private:
    Core() {}
    ~Core() {}

    Core(Core const&) = delete;
    Core& operator= (Core const&) = delete;

    bool createWindow(int width, int height, bool fullScreen);

    void draw();
    void update(float deltaSeconds);

    SDL_Window* window;
    SDL_GLContext mainContext;
    int width, height;

    Level* currentLevel;
    Level* prevLevel;

//=================SHADER==================================
    ShaderProgram* shader;
    GLuint default2D_VAO, default2D_VBO, default2D_EBO;
//=========================================================

    //Matrices view and projection
    glm::mat4 view;
    glm::mat4 ortho;

    bool loop;

    b2World* physWorld;
};

#endif

