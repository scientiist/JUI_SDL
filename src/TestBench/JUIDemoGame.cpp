#include "TestBench/JUIDemoGame.hpp"
#include <JUI/Widgets/VerticalLayoutContainer.hpp>
#include <JUI/Widgets/Scene.hpp>
#include <JUI/Widgets/Rect.hpp>
#include <JUI/Types/Font.hpp>
#include <JUI/Widgets/Text.hpp>
#include <SDL2/SDL_platform.h>

//#include <JUI/jui.h>

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
    rect2->SetBackgroundColor({0, 0, 255, 0});
    rect2->SetSize({0, 0, 1.0f, 0.5f});
    rect2->SetPosition({10, 10, 0, 0});

    // TODO: Implement Default Font

    JUI::VerticalListLayout *layout = new JUI::VerticalListLayout();
    layout->SetParent(rect2);

    Font bruh = Font(renderer, "fonts/FreeSans.ttf", 18);

    // Textbox 1
    JUI::Rect *tb1 = new JUI::Rect();
    tb1->SetParent(layout);
    tb1->SetSize({0, 50, 1.0f, 0.0f});
    tb1->SetBackgroundColor({0, 255, 0, 0});

    JUI::Text *lb1 = new JUI::Text();
    lb1->SetParent(tb1);
    lb1->SetHorizontalTextAlignment(JUI::HTEXT_ALIGN_CENTER);
    lb1->SetVerticalTextAlignment(JUI::VTEXT_ALIGN_CENTER);
    lb1->SetTextColor({255, 255, 255, 255});
    lb1->SetFont(bruh);

    JUI::Rect *tb2 = new JUI::Rect();
    tb2->SetParent(layout);
    tb2->SetSize({0, 50, 1.0f, 0.0f});
    tb2->SetBackgroundColor({0, 255, 255, 0});

    JUI::Text *lb2 = new JUI::Text();
    lb2->SetParent(tb2);
    lb2->SetHorizontalTextAlignment(JUI::HTEXT_ALIGN_CENTER);
    lb2->SetVerticalTextAlignment(JUI::VTEXT_ALIGN_CENTER);
    lb2->SetTextColor({255, 255, 255, 255});
    lb2->SetFont(bruh);

    /*JUI::Text *text = new JUI::Text();
    text->SetParent(rect2);
    text->SetHorizontalTextAlignment(JUI::HTEXT_ALIGN_CENTER);
    text->SetVerticalTextAlignment(JUI::VTEXT_ALIGN_CENTER);
    text->SetName("GO HOME AND PRACTICE");
    text->SetFont(bruh);
    text->SetTextColor({255, 255, 255, 255});
    text->SetText("HELLO WORLD");*/
}

void JUIDemoGame::Update(float delta) {
    SDLGame::Update(delta);

    Widget *thingy = Gui->FindFirstChild("YA NOTHIN")->FindFirstChild("NO TALENT")->FindFirstChild(
            "GO HOME AND PRACTICE");
    Text *text = dynamic_cast<Text *>(thingy);


    if (text != nullptr) {
        auto tekkxt = std::string(SDL_GetPlatform());
        text->SetText(tekkxt);
    }


    Gui->Update(delta);
}

void JUIDemoGame::Draw() {
    SDLGame::Draw();

    Gui->Draw(renderer);
}