#pragma once

#include <JUI/Types/Vector2.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace JUI;

class SDLGame {
public:
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