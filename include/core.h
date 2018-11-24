#ifndef CORE_H
#define CORE_H

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <Box2D/Box2D.h>
#include <boost/asio.hpp>

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
    void release_resources();

    // Create new level
    void install_level(Level* level);
    // End gameloop
    void close_game();

    // Add entity to level
    void add_entity(Entity* ptr);
    // Delete entity from level
    void delete_entity(Entity* ptr);

    boost::asio::io_context* get_context();

    glm::vec2 get_window_size();
private:
    Core() {}
    ~Core() {}

    Core(Core const&) = delete;
    Core& operator= (Core const&) = delete;

    bool create_window(int width, int height, bool fullScreen);

    void draw();
    void update(float deltaSeconds);

    SDL_Window* window;
    SDL_GLContext mainContext;
    int width, height;

    Level* currentLevel;
    Level* prevLevel;

    boost::asio::io_context* context;
    std::shared_ptr<boost::asio::io_context::work> work_active;

//=================SHADER==================================
    std::shared_ptr<ShaderProgram> shader;
    GLuint default2D_VAO, default2D_VBO, default2D_EBO;
//=========================================================

    //Matrices view and projection
    glm::mat4 view;
    glm::mat4 ortho;

    bool loop;

    std::shared_ptr<b2World> physWorld;
};

#endif

