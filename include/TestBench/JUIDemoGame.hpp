#pragma once

#include <JUI/Scene.hpp>

#include "SDLGame.hpp"

class JUIDemoGame : public SDLGame
{
public:
    JUI::Scene Gui;
    void Initialize() override;
    void Draw() override;
    void Update(float delta) override;
protected:
private:
};




void JUIDemoGame::Initialize() {
    Gui = JUI::Scene();
    
}