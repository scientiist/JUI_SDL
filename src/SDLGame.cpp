#include <SDLGame.hpp>
#include "JUI/Types/Vector2.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <chrono>
#include <thread>
#include <iostream>

Vector2 SDLGame::GetWindowSize() {
    int* x;
    int* y;
    SDL_GetWindowSize(window, x, y);
    return {*x, *y};
}
void SDLGame::SetWindowSize(int x, int y) {
    SDL_SetWindowSize(window, x, y);
}
void SDLGame::SetWindowSize(Vector2 const&v) {
    SDL_SetWindowSize(window, v.GetX(), v.GetY());
}

void SDLGame::Draw() {

}

void SDLGame::Render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    Draw();
    SDL_RenderPresent(renderer);
}
void SDLGame::Update(float delta) { }

void SDLGame::handleEvents() {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            requestQuit = true;

        if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
            Focused = false;

        if (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
            Focused = true;
    }
}

void SDLGame::Run()
{
    Gameloop();
}

void SDLGame::Gameloop() {
    while (!requestQuit) {
        RunFrame();
    }
}

void SDLGame::RunFrame()
{
    this->handleEvents(); // Include this in timing?

    auto start = std::chrono::high_resolution_clock::now();

    this->Update(frameDelta);
    this->Render();

    // TODO: Refactor time tracking to seconds, so we can actually use it in Gametick() sanely
    if (!Focused)
        std::this_thread::sleep_for(std::chrono::microseconds((62500 - 1000)));
    auto stop = std::chrono::high_resolution_clock::now();

    frameDelta = std::chrono::duration_cast<std::chrono::microseconds>(start-stop).count();
    if (frameDelta < 1000 && Focused)
        std::this_thread::sleep_for(std::chrono::microseconds(1000 - (int) frameDelta));
    frameCount++;
}

void SDLGame::Cleanup()  {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(1);
}

void SDLGame::Initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        std::cerr << "SDL_Error: " << SDL_GetError() << std::endl;


    window = SDL_CreateWindow("Re: Backyard Monsters", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1152, 864, SDL_WINDOW_SHOWN);
    SDL_SetWindowResizable(window, SDL_TRUE);
    if (window == nullptr) {
        std::cerr << "SDL_Error: " << SDL_GetError() << std::endl;
    }
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
        std::cerr << "SDL_Error: " << "Couldn't init SDL_Image." << std::endl;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderSetLogicalSize(renderer, 1152, 864);
    SDL_GL_SetSwapInterval(0);
    SDL_UpdateWindowSurface(window);
}