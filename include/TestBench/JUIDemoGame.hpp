#pragma once

//#include <JUI/jui.h>
#include <JUI/Widgets/Widget.hpp>

#include "SDLGame.hpp"

class JUIDemoGame : public SDLGame {
public:
    JUIDemoGame() : SDLGame() {}

    ~JUIDemoGame() override {}

    JUI::Widget *Gui;

    void Initialize() override;

    void Draw() override;

    void Update(float delta) override;

protected:
private:
};

