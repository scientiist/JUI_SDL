#include <JUI/Widgets/Text.hpp>

namespace JUI
{
    Text::Text() : Widget() {}
    Text::~Text() {}

    Vector2 Text::GetAbsoluteSize() const
    { return this->GetParent()->GetAbsoluteSize(); }

    Vector2 Text::GetAbsolutePosition() const { return this->GetParent()->GetAbsolutePosition(); }

    void Text::SetText(std::string text) { this->text = text; }

    std::string Text::GetText() const { return this->text; }

    void Text::SetTextColor(SDL_Color c) { text_color = c; }

    SDL_Color Text::GetTextColor() const { return text_color; }

    void Text::SetVerticalTextAlignment(VerticalTextAlignmentEnum align) { v_text_alignment = align; }

    VerticalTextAlignmentEnum Text::GetVerticalTextAlignment() const { return v_text_alignment; }

    void Text::SetHorizontalTextAlignment(HorizontalTextAlignmentEnum align) { h_text_alignment = align; }

    HorizontalTextAlignmentEnum Text::GetHorizontalTextAlignment() const { return h_text_alignment; }

    void Text::SetTextOutlineColor(SDL_Color c) { outline_color = c; }

    SDL_Color Text::GetTextOutlineColor() const { return outline_color; }

    void Text::SetFont(JUI::Font &f) { font = f; }

    JUI::Font Text::GetFont() const { return font; }

    // TODO: Implement Vertical Text Alignment

    void Text::Draw(SDL_Renderer *target) {
        Vector2 abs_pos = this->GetAbsolutePosition();
        Vector2 abs_size = this->GetAbsoluteSize();

        float aligned_x = abs_pos.X;
        float aligned_y = abs_pos.Y;
        FC_AlignEnum fc_align = FC_ALIGN_LEFT;

        Uint16 height = FC_GetHeight(this->font.fc_font, this->text.c_str());

        if (h_text_alignment == HTEXT_ALIGN_LEFT) {
            aligned_x = abs_pos.X;
            fc_align = FC_ALIGN_LEFT;
        }

        if (h_text_alignment == HTEXT_ALIGN_CENTER) {
            aligned_x = abs_pos.X + (abs_size.X / 2);
            fc_align = FC_ALIGN_CENTER;
        }

        if (h_text_alignment == HTEXT_ALIGN_RIGHT) {
            aligned_x = abs_pos.X + abs_size.X;
            fc_align = FC_ALIGN_RIGHT;
        }

        if (v_text_alignment == VTEXT_ALIGN_TOP) {
            aligned_y = abs_pos.Y;
        }
        if (v_text_alignment == VTEXT_ALIGN_CENTER) {
            aligned_y = abs_pos.Y + (abs_size.Y / 2) - ((float) height / 2);
        }
        if (v_text_alignment == VTEXT_ALIGN_BOTTOM) {
            aligned_y = abs_pos.Y + abs_size.Y - height;
        }
        FC_DrawAlignC(
                font.fc_font,
                target,
                aligned_x,
                aligned_y,
                fc_align,
                text_color,
                text.c_str());


        Widget::Draw(target);
    }
}