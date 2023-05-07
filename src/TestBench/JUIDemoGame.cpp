#include "TestBench/JUIDemoGame.hpp"

void JUIDemoGame::Initialize() {
    SDLGame::Initialize();
    Gui = JUI::Scene();
}


void JUIDemoGame::Update(float delta) {
    SDLGame::Update(delta);
}

void JUIDemoGame::Draw() {
    SDLGame::Draw();

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect urAFuckingNi{0,0,40,40};
    SDL_RenderFillRect(renderer, &urAFuckingNi);
}