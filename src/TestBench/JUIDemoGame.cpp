#include "TestBench/JUIDemoGame.hpp"

void JUIDemoGame::Initialize() {
    SDLGame::Initialize();
    Gui = new JUI::Scene(window, renderer);

    JUI::Rect *rect = new JUI::Rect();
    rect->SetParent(Gui);
    rect->SetName("YA NOTHIN");
    rect->SetBackgroundColor({255, 0, 0, 0});
    rect->SetBorderColor({255, 255, 255, 0});
    rect->SetSize({0,0, 1, 1});
    rect->SetPosition({0, 0, 0.1, 0.3});

    JUI::Rect *rect2 = new JUI::Rect();
    rect2->SetParent(rect);
    rect2->SetName("NO TALENT");
    rect2->SetBackgroundColor({0,0,255,0});
    rect2->SetSize({0, 0, 1.0f, 0.5f});
    rect2->SetPosition({10, 10, 0, 0});

    // TODO: Implement Default Font

    Font bruh = Font(renderer, "fonts/FreeSans.ttf", 18);

    JUI::Text *text = new JUI::Text();
    text->SetParent(rect2);
    text->SetName("GO HOME AND PRACTICE");
    text->SetFont(bruh);
    text->SetTextColor({255, 255, 255, 255});
    text->SetText("HELLO WORLD");
}

void JUIDemoGame::Update(float delta) {
    SDLGame::Update(delta);

    auto text = Gui->FindFirstChild("YA NOTHIN")->FindFirstChild("NO TALENT")->FindFirstChild("GO HOME AND PRACTICE");

    if (text != nullptr)

    Gui->Update(delta);
}

void JUIDemoGame::Draw() {
    SDLGame::Draw();

    Gui->Draw(renderer);
}