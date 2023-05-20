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

