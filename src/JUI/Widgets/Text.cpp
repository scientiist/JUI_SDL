#include <JUI/Widgets/Text.hpp>

namespace JUI
{

    Text::Text() : Widget() {}
    Text::~Text() {}

    Vector2 Text::GetAbsoluteSize() const
    { return this->GetParent()->GetAbsoluteSize(); }

    Vector2 Text::GetAbsolutePosition() const
    { return this->GetParent()->GetAbsolutePosition(); }

    void        Text::SetText(std::string text) { this->text = text; }
    std::string Text::GetText() const           { return this->text; }

    void Text::SetTextColor(SDL_Color c) { text_color = c;    }
    SDL_Color Text::GetTextColor() const { return text_color; }

    void Text::SetTextAlignment(TextAlignmentEnum align)
    { text_alignment = align; }
    TextAlignmentEnum Text::GetTextAlignment() const { return text_alignment;}

    void Text::SetTextOutlineColor(SDL_Color c) { outline_color = c;    }
    SDL_Color Text::GetTextOutlineColor() const { return outline_color; }

    void Text::SetFont(JUI::Font& f) { font = f; }
    JUI::Font Text::GetFont() const { return font; }

    void Text::Draw(SDL_Renderer *target)
    {
        auto abs_pos = this->GetAbsolutePosition();

        FC_DrawAlignC(
                font.fc_font,
                target,
                abs_pos.X,
                abs_pos.Y,
                static_cast<FC_AlignEnum>(text_alignment),
                text_color,
                text.c_str());

        Widget::Draw(target);
    }
}