#pragma once

#include "JUI/Widget.hpp"

#include <JUI/Font.hpp>

namespace JUI {

    enum TextVAlign {
        V_ALIGN_TOP, V_ALIGN_CENTER, V_ALIGN_BOTTOM
    };
    enum TextHAlign {
        H_ALIGN_LEFT, H_ALIGN_CENTER, H_ALIGN_RIGHT
    };

    // Text Widget
    // Expands to fill the size of the parent Container
    // TODO: Rich Text Support
    class Text : Widget {

        JUI::Font *Font; // Prolly want a reference?
        TextVAlign VertAlign;
        TextHAlign HorizAlign;
        std::string Text;
        SDL_Color TextColor;
        SDL_Color TextOutlineColor;
        float TextOutline;
        bool RichTextEnabled;

        // Refactor Scene to pass SLD_Renderer reference
        // to children during call to Draw();

        void Draw(SDL_Renderer *target) override {

            auto abs_pos = this->GetParent()->GetAbsolutePosition();
            FC_DrawAlign(Font->fc_font, target, abs_pos.X, abs_pos.Y, static_cast<FC_AlignEnum>(HorizAlign),
                         Text.c_str());

        }
    };
}