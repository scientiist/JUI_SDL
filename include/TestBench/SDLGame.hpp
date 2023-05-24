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

    Event<SDL_QuitEvent>             Quitting;
    Event<SDL_WindowEvent>           WindowChanged;
    Event<SDL_WindowEvent>           FocusGained;
    Event<SDL_WindowEvent>           FocusLost;
    Event<SDL_WindowEvent>           MouseEntered;
    Event<SDL_WindowEvent>           MouseLeft;
    Event<SDL_KeyboardEvent>         KeyPressed;
    Event<SDL_KeyboardEvent>         KeyReleased;
    Event<SDL_MouseButtonEvent>      MousePressed;
    Event<SDL_MouseButtonEvent>      MouseReleased;
    Event<SDL_MouseMotionEvent>      MouseMoved;
    Event<SDL_MouseWheelEvent>       MouseWheelMoved;
    Event<SDL_ControllerButtonEvent> ButtonPressed;
    Event<SDL_ControllerButtonEvent> ButtonReleased;
    Event<SDL_ControllerAxisEvent>   ThumbstickMoved;
    Event<SDL_JoyButtonEvent>        JoyPressed;
    Event<SDL_JoyButtonEvent>        JoyReleased;
    Event<SDL_TouchFingerEvent>      TouchGesture;
    Event<SDL_TouchFingerEvent>      TouchPressed;
    Event<SDL_TouchFingerEvent>      TouchReleased;
    Event<SDL_DisplayEvent>          DisplayChanged;
    Event<SDL_DisplayEvent>          DisplayConnected;
    Event<SDL_DisplayEvent>          DisplayDisconnected;
    Event<SDL_DisplayEvent>          DisplayOrientationChanged;



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