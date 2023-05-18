#pragma once

#include "JUI/Widget.hpp"
#include "JUI/Types/Color.hpp"

namespace JUI {
    // Text Widget
    // Expands to fill the size of the parent Container
    // TODO: Rich Text Support
    class Text : Widget {
        std::string Text;
        Color TextColor;
        Color TextOutlineColor;
        float TextOutline;
        bool RichTextEnabled;


    };
}