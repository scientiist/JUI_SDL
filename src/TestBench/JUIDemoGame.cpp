#include "TestBench/JUIDemoGame.hpp"

void JUIDemoGame::Initialize() {
    SDLGame::Initialize();
    Gui = new JUI::Scene(window, renderer);


    JUI::Rect *rect = new JUI::Rect();
    rect->SetParent(Gui);
    rect->SetBackgroundColor({255, 0, 0, 0});
    rect->SetBorderColor({255, 255, 255, 0});
    rect->SetSize(JUI::UDim2{0,0, 0.5f, 0.5f});

    JUI::Rect *rect2 = new JUI::Rect();
    rect2->SetParent(rect);
    rect2->SetBackgroundColor({0,0,255,0});
    rect2->SetSize(JUI::UDim2{0, 0, 1.0f, 0.5f});

    // TODO: Implement Default Font

    JUI::Text *text = new JUI::Text();
    text->SetParent(rect2);
    text->Content = "42069";

}

void JUIDemoGame::Update(float delta) {
    SDLGame::Update(delta);

}

void JUIDemoGame::Draw() {
    SDLGame::Draw();

    Gui->Draw(renderer);
}