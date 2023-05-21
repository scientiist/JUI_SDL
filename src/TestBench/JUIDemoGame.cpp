#include "TestBench/JUIDemoGame.hpp"

void JUIDemoGame::Initialize() {
    SDLGame::Initialize();
    Gui = new JUI::Scene(window, renderer);

    JUI::Rect *rect = new JUI::Rect();
    rect->SetParent(Gui);
    rect->SetBackgroundColor({255, 0, 0, 0});
    rect->SetBorderColor({255, 255, 255, 0});
    rect->SetSize(JUI::UDim2{0,0, 0.5f, 0.5f});
}


void JUIDemoGame::Update(float delta) {
    SDLGame::Update(delta);

}

void JUIDemoGame::Draw() {
    SDLGame::Draw();

    Gui->Draw(renderer);
}