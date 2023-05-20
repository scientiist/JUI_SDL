#pragma once

#include "JUI/Widget.hpp"

namespace JUI {
    // Text Widget
    // Expands to fill the size of the parent Container
    // TODO: Rich Text Support
    class Text : Widget {
        std::string Text;
        SDL_Color TextColor;
        SDL_Color TextOutlineColor;
        float TextOutline;
        bool RichTextEnabled;


    };
}