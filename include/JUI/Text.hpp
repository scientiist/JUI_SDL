#pragma once

#include <JUI/Widget.hpp>
#include <JUI/Color.hpp>

namespace JUI
{
    // Text Widget
    // Morphs to the size of the parent Container
    // TODO: Rich Text Support
    class Text : Widget {
        std::string Text;
        Color TextColor;
        Color TextOutlineColor;
        float TextOutline;
        bool RichTextEnabled;


    };
}