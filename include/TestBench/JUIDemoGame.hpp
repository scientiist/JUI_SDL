#pragma once

#include <JUI/jui.h>

#include "SDLGame.hpp"

class JUIDemoGame : public SDLGame {
public:
    JUI::Widget *Gui;

    void Initialize() override;

    void Draw() override;

    void Update(float delta) override;

protected:
private:
};

void JUIDemoGame::Initialize() {
    Gui = new JUI::Scene();

    JUI::Rect *rect = new JUI::Rect();
    rect->SetParent(Gui);
    rect->SetColor();
}

void JUIDemoGame::Draw() {

}

void JUIDemoGame::Update(float delta) {

}