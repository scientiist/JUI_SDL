#pragma once

#include "JUI/Types/Vector2.hpp"
#include "JUI/Types/Event.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace JUI;



class SDLGame {
public:
    JUI::Event<float> RenderTick;
    JUI::Event<float> LogicTick;


    JUI::Event< > FocusGained;
    JUI::Event< > FocusLost;

    Event<SDL_KeyboardEvent>         KeyPressed;
    Event<SDL_KeyboardEvent>         KeyReleased;
    Event<SDL_MouseButtonEvent>      MousePressed;
    Event<SDL_MouseButtonEvent>      MouseReleased;
    Event<SDL_MouseMotionEvent>      MouseMoved;
    Event<SDL_MouseWheelEvent>       MouseWheelMoved;
    Event<SDL_ControllerButtonEvent> ButtonPressed;
    Event<SDL_ControllerButtonEvent> ButtonReleased;
    Event<SDL_ControllerAxisEvent>   ThumbstickMoved;



    virtual void Initialize();
    virtual void Cleanup();
    virtual void Update(float delta);
    virtual void Draw();

    // Starts Render & Gametic Threads
    void Run();
    void Gameloop();
    void RunFrame();
    void Render();

    bool Focused;
    bool DropFPSOnFocusLost = true;
    bool Paused;

    Vector2 GetWindowSize();
    void SetWindowSize(int x, int y);
    void SetWindowSize(Vector2 const&v);

protected:
    bool requestQuit;
    float frameDelta;
    float tickDelta;
    int frameCount;

    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;

    void handleEvents();
};