#ifndef INPUT_H
#define INPUT_H

#include "SDL2/SDL.h"
#include "common.h"

class Input
{
public:
    typedef decltype(SDL_MouseButtonEvent::button) MouseButton;

    // Possible key states
    enum InputState
    {
        InputInvalid,
        InputRegistered,
        InputUnregistered,
        InputTriggered,
        InputPressed,
        InputReleased
    };


    // State checking
    static InputState keyState(SDL_Keycode key);
    static bool keyTriggered(SDL_Keycode key);
    static bool keyPressed(SDL_Keycode key);
    static bool keyReleased(SDL_Keycode key);

    static InputState buttonState(MouseButton button);
    static bool buttonTriggered(MouseButton button);
    static bool buttonPressed(MouseButton button);
    static bool buttonReleased(MouseButton button);

    static glm::vec2 mousePosition();
    static void mouseDelta(int &x, int &y);

private:

    // State updating
    static void update(SDL_Window* window);
    static void registerKeyPress(SDL_Keycode key);
    static void registerKeyRelease(SDL_Keycode key);
    static void registerMousePress(MouseButton button);
    static void registerMouseRelease(MouseButton button);
    static void reset();
    friend class Core;
};

inline bool Input::keyTriggered(SDL_Keycode key)
{
    return keyState(key) == InputTriggered;
}

inline bool Input::keyPressed(SDL_Keycode key)
{
    return keyState(key) == InputPressed;
}

inline bool Input::keyReleased(SDL_Keycode key)
{
    return keyState(key) == InputReleased;
}

inline bool Input::buttonTriggered(MouseButton button)
{
  return buttonState(button) == InputTriggered;
}

inline bool Input::buttonPressed(MouseButton button)
{
  return buttonState(button) == InputPressed;
}

inline bool Input::buttonReleased(MouseButton button)
{
  return buttonState(button) == InputReleased;
}

#endif // INPUT_H
