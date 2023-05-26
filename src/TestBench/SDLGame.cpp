#include "TestBench/SDLGame.hpp"
#include "JUI/Types/Vector2.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <chrono>
#include <thread>
#include <iostream>


void SDLGame::Draw() {}

void SDLGame::Update(float) {}

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
    if(renderer == nullptr) {
        std::cerr << "SDL_Error: " << "Couldn't init SDL_Renderer." << std::endl;
    }
    SDL_RenderSetLogicalSize(renderer, 1152, 864);
    SDL_GL_SetSwapInterval(0);
    SDL_UpdateWindowSurface(window);
}



Vector2 SDLGame::GetWindowSize() {
    int *x = nullptr;
    int *y = nullptr;
    SDL_GetWindowSize(window, x, y);
    return {(float) *x, (float) *y};
}
void SDLGame::SetWindowSize(int x, int y) {
    SDL_SetWindowSize(window, x, y);
}
void SDLGame::SetWindowSize(Vector2 const&v) {
    SDL_SetWindowSize(window, v.GetX(), v.GetY());
}



void SDLGame::Render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    Draw();
    SDL_RenderPresent(renderer);
}


void SDLGame::handleEvents() {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            requestQuit = true;
            Quitting(event.quit);
        }


        if (event.type == SDL_WINDOWEVENT)
        {
            WindowChanged(event.window);
            if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
            {
                Focused = false;
                FocusLost(event.window);
            }

            if (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) {
                Focused = true;
                FocusGained(event.window);
            }
        }

        if (event.type == SDL_DISPLAYEVENT)
        {
            DisplayChanged(event.display);
            if (event.display.event == SDL_DISPLAYEVENT_CONNECTED)
                DisplayConnected(event.display);

            if (event.display.event == SDL_DISPLAYEVENT_DISCONNECTED)
                DisplayDisconnected(event.display);

            if (event.display.event == SDL_DISPLAYEVENT_ORIENTATION)
                DisplayOrientationChanged(event.display);
        }


        if (event.type == SDL_KEYDOWN)
            KeyPressed(event.key);

        if (event.type == SDL_KEYUP)
            KeyReleased(event.key);

        if (event.type == SDL_MOUSEBUTTONDOWN)
            MousePressed(event.button);

        if (event.type == SDL_MOUSEBUTTONUP)
            MouseReleased(event.button);

        if (event.type == SDL_MOUSEMOTION)
            MouseMoved(event.motion);

        if (event.type == SDL_MOUSEWHEEL)
            MouseWheelMoved(event.wheel);

        if (event.type == SDL_CONTROLLERBUTTONDOWN)
            ButtonPressed(event.cbutton);

        if (event.type == SDL_CONTROLLERBUTTONUP)
            ButtonReleased(event.cbutton);

        if (event.type == SDL_FINGERMOTION)
            TouchGesture(event.tfinger);

        if (event.type == SDL_FINGERDOWN)
            TouchPressed(event.tfinger);

        if (event.type == SDL_FINGERUP)
            TouchPressed(event.tfinger);

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

    if (!Focused && DropFPSOnFocusLost)
        std::this_thread::sleep_for(std::chrono::microseconds(48000));
    else
        std::this_thread::sleep_for(std::chrono::microseconds(16000));

    auto stop = std::chrono::high_resolution_clock::now();

    float frame_delta_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count();

    frameDelta = frame_delta_microseconds / (1000 * 1000);
    frames_per_second = 1 / frameDelta;

    frameCount++;
}

void SDLGame::Cleanup()  {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(1);
}


