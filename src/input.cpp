#include "input.h"
#include "common.h"

#include <vector>
#include <algorithm>
#include <iostream>

// Структура содержит пару элементов: кнопка и ее состояние.
template <typename T>
struct InputInstance : std::pair<T, Input::InputState>
{
    typedef std::pair<T, Input::InputState> base_class;

    inline InputInstance(T value) : base_class(value, Input::InputInvalid) {}
    inline InputInstance(T value, Input::InputState state) : base_class(value, state) {}

    inline bool operator==(const InputInstance &rhs) const
    {
        return this->first == rhs.first;
    }
};

// Instance types
typedef InputInstance<SDL_Keycode> KeyInstance;
typedef InputInstance<Input::MouseButton> ButtonInstance;

// Типы контейнеров
typedef std::vector<KeyInstance> KeyContainer;
typedef std::vector<ButtonInstance> ButtonContainer;

// Globals
static KeyContainer sg_keyInstances; // Контейнер кнопок
static ButtonContainer sg_buttonInstances;
static int mouseXcurrPos, mouseYcurrPos;
static int mouseXprevPos, mouseYprevPos;
static int mouseXdelta, mouseYdelta;

/*******************************************************************************
 * Static Helper Fucntions
 ******************************************************************************/

// Ищем кнопку и ее состояние в контейнере
static inline KeyContainer::iterator FindKey(SDL_Keycode value)
{
    return std::find(sg_keyInstances.begin(), sg_keyInstances.end(), value);
}
static inline ButtonContainer::iterator FindButton(Input::MouseButton value)
{
    return std::find(sg_buttonInstances.begin(), sg_buttonInstances.end(), value);
}

template <typename TPair>
static inline void UpdateStates(TPair &instance)
{
    switch(instance.second)
    {
    case Input::InputRegistered:
        instance.second = Input::InputTriggered;
        break;
    case Input::InputTriggered:
        instance.second = Input::InputPressed;
        break;
    case Input::InputUnregistered:
        instance.second = Input::InputReleased;
        break;
    default:
        break;
    }
}

template <typename TPair>
static inline bool CheckReleased(const TPair &instance)
{
    return instance.second == Input::InputReleased;
}

template <typename Container>
static inline void Update(Container &container)
{
    typedef typename Container::iterator Iter;
    typedef typename Container::value_type TPair;

    // Remove old data
    Iter remove = std::remove_if(container.begin(), container.end(), &CheckReleased<TPair>);
    container.erase(remove, container.end());
    // Update existing data
    std::for_each(container.begin(), container.end(), &UpdateStates<TPair>);
}

//============================================================================
// Input Implementation
//============================================================================
Input::InputState Input::keyState(SDL_Keycode key)
{
    KeyContainer::iterator it = FindKey(key);
    return (it != sg_keyInstances.end()) ? it->second : InputInvalid;
}
Input::InputState Input::buttonState(MouseButton button)
{
    ButtonContainer::iterator it = FindButton(button);
    return (it != sg_buttonInstances.end()) ? it->second : InputInvalid;
}

glm::vec2 Input::mousePosition()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    return glm::vec2(x, y);
}

void Input::mouseDelta(int &x, int &y)
{
    x = mouseXdelta;
    y = mouseYdelta;
}

void Input::update(SDL_Window *window)
{
    // Update mouse delta
    // Set mouse to center window
    /*
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    SDL_WarpMouseInWindow(window, w/2, h/2);

    SDL_GetMouseState(&mouseXcurrPos, &mouseYcurrPos);
    mouseXdelta = mouseXcurrPos - w/2;
    mouseYdelta = mouseYcurrPos - h/2;
    */
    // Update keystate values
    Update(sg_keyInstances);
    Update(sg_buttonInstances);
}

void Input::registerKeyPress(SDL_Keycode key)
{
    // Сначала смотрим, не находится ли кнопка уже в контейнере
    KeyContainer::iterator it = FindKey(key);
    if(it == sg_keyInstances.end()) // и если не находится, то добавляем
    {
        sg_keyInstances.push_back(KeyInstance(key, InputRegistered));
    }
}

void Input::registerKeyRelease(SDL_Keycode key)
{
    // Cмотрим, есть ли кнопка в контейнере
    KeyContainer::iterator it = FindKey(key);
    if(it != sg_keyInstances.end()) // и если есть, то помечаем ее Unregistered
    {
        it->second = InputUnregistered;
    }
}

void Input::registerMousePress(MouseButton button)
{
    // Сначала смотрим, не находится ли кнопка уже в контейнере
    ButtonContainer::iterator it = FindButton(button);
    if(it == sg_buttonInstances.end()) // и если не находится, то добавляем
    {
        sg_buttonInstances.push_back(ButtonInstance(button, InputRegistered));
    }
}

void Input::registerMouseRelease(MouseButton button)
{
    // Cмотрим, есть ли кнопка в контейнере
    ButtonContainer::iterator it = FindButton(button);
    if(it != sg_buttonInstances.end()) // и если есть, то помечаем ее Unregistered
    {
        it->second = InputUnregistered;
    }
}

void Input::reset()
{
    sg_keyInstances.clear();
    sg_buttonInstances.clear();
}
