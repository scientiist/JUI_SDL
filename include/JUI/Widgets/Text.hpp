#pragma once

#include "JUI/Widget.hpp"

#include <JUI/Font.hpp>

namespace JUI {


    enum TextAlignmentEnum { // What's the difference between this and typedef enum?
        TEXT_ALIGNMENT_LEFT, TEXT_ALIGNMENT_CENTER, TEXT_ALIGNMENT_RIGHT
    };


    // Text Widget
    // Expands to fill the size of the parent Container
    // TODO: Rich Text Support
    class Text : Widget {

        JUI::Font *Font; // Prolly want a reference?
        TextAlignmentEnum TextAlignment = TEXT_ALIGNMENT_LEFT;
        std::string Text;
        SDL_Color TextColor;
        SDL_Color TextOutlineColor;
        float TextOutline;
        bool RichTextEnabled;


        void Draw(SDL_Renderer *target) override {

            auto abs_pos = this->GetParent()->GetAbsolutePosition();
            FC_DrawAlignC(
                    Font->fc_font,
                    target,
                    abs_pos.X,
                    abs_pos.Y,
                    static_cast<FC_AlignEnum>(TextAlignment),
                    TextColor,
                    Text.c_str());

        }
    };
}