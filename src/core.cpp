#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#include <thread>
#include <chrono>

#include "core.h"
#include "shaderProgram.h"
#include "resourceManager.h"
#include "input.h"
#include "camera.h"
#include "level.h"
#include "mycontactlistener.h"

bool Core::createWindow(int width, int height, bool fullScreen)
{
    //=====================================================================
    // Init SDL and glew
    //=====================================================================
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false; // FAIL
    }

    this->width = width;
    this->height = height;

    window = SDL_CreateWindow("MyEngine", 1920, 100, width, height, SDL_WINDOW_OPENGL);
    if(window == nullptr)
    {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false; // FAIL
    }

    mainContext = SDL_GL_CreateContext(window);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    //SDL_ShowCursor(SDL_DISABLE);

    glewExperimental = GL_TRUE;
    glewInit();

    glViewport(0, 0, width, height);

    return true; // SUCCESS
}

bool Core::init(int width, int height, bool fullScreen)
{
    if(!createWindow(width, height, fullScreen))
    {
       return false; // FAIL
    }

    currentLevel = nullptr;
    prevLevel = nullptr;

    ResourceManager::Instance(); // Create instance of ResourceManager

    //mainCamera = new Camera();

    shader = new ShaderProgram();
    shader->addShaderFromSourceFile(ShaderProgram::VERTEX, "shaders/2DSprite.vert");
    shader->addShaderFromSourceFile(ShaderProgram::FRAGMENT, "shaders/2DSprite.frag");
    shader->link();
    shader->useProgram();

    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    ortho = glm::ortho(0.0f, float(width), (float)height, 0.0f, 0.0f, 100.0f);

    shader->setMat4("view", view);
    shader->setMat4("ortho", ortho);

    glEnable(GL_DEPTH_TEST);

    // Set up vertex data (and buffer(s)) and attribute pointers
    GLfloat vertices[] = {
       // Positions          // Texture Coords
        1.0f,  1.0f, 0.0f,    1.0f, 1.0f, // Top Right
        1.0f, -1.0f, 0.0f,    1.0f, 0.0f, // Bottom Right
       -1.0f, -1.0f, 0.0f,    0.0f, 0.0f, // Bottom Left
       -1.0f,  1.0f, 0.0f,    0.0f, 1.0f  // Top Left
    };
    GLuint indices[] = {  // Note that we start from 0!
       0, 1, 3, // First Triangle
       1, 2, 3  // Second Triangle
    };

    glGenVertexArrays(1, &default2D_VAO);
    glGenBuffers(1, &default2D_VBO);
    glGenBuffers(1, &default2D_EBO);

    glBindVertexArray(default2D_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, default2D_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, default2D_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // TexCoord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // Unbind VAO

    b2Vec2 gravity(0.0f, 0.0f);
    physWorld = new b2World(gravity);

    return true; // SUCCESS
}

void Core::mainloop()
{
    // Set collision listener
    MyContactListener myContactListenerInstance;
    physWorld->SetContactListener(&myContactListenerInstance);

    float currentFrame;
    float lastFrame = 0;
    float deltaTime;

    const float maxFPS = 60.0f;
    const float maxPeriod = 1.0f / maxFPS;

    loop = true;
    while(loop)
    {
        // Set frame time
        currentFrame = SDL_GetTicks() / 1000.0f;
        deltaTime = currentFrame - lastFrame;

        if(deltaTime >= maxPeriod)
        {
            lastFrame = currentFrame;

            // Check events
            SDL_Event event;
            while(SDL_PollEvent(&event))
            {
                // Input Handler
                if(event.type == SDL_KEYUP)
                    Input::registerKeyRelease(event.key.keysym.sym);
                if(event.type == SDL_KEYDOWN)
                    Input::registerKeyPress(event.key.keysym.sym);
                if(event.type == SDL_MOUSEBUTTONDOWN)
                    Input::registerMousePress(event.button.button);
                if(event.type == SDL_MOUSEBUTTONUP)
                    Input::registerMouseRelease(event.button.button);
                //User requests quit
                if(event.type == SDL_QUIT )
                    loop = false;
            }

            update(deltaTime);

            draw();

            physWorld->Step(maxPeriod, 8, 3);

            if(prevLevel)
            {
                delete prevLevel;
                prevLevel = nullptr;
                std::cout << "Delete prevlevel\n";
            }
        }
    }
}

void Core::update(GLfloat dt)
{
    Input::update(window);

    currentLevel->preUpdate(dt);
    currentLevel->update(dt);
    currentLevel->postUpdate(dt);

    currentLevel->input_handler(dt);
}

void Core::draw()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->useProgram();

    glBindVertexArray(default2D_VAO);
    currentLevel->draw(shader);    
    glBindVertexArray(0);

    SDL_GL_SwapWindow(window);
}

void Core::installLevel(Level *level)
{

    if(currentLevel != nullptr)
    {
        currentLevel->release();
        prevLevel = currentLevel;
    }
    currentLevel = level;
    currentLevel->init(physWorld);
}

void Core::releaseResources()
{
    ResourceManager::Instance().releaseAllResources();
    SDL_GL_DeleteContext(mainContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

glm::vec2 Core::getWindowSize()
{
    int x, y;
    SDL_GetWindowSize(window, &x, &y);
    return  glm::vec2(x, y);
}

void Core::closeGame()
{
    loop = false;
}

void Core::addEntity(Entity *ptr)
{
    currentLevel->addEntity(ptr);
}

void Core::deleteEntity(Entity *ptr)
{
    currentLevel->deleteEntity(ptr);
}

boost::asio::io_context& Core::get_context()
{
    return context;
}
