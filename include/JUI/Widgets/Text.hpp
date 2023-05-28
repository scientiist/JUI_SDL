#pragma once

#include "Widget.hpp"

#include "JUI/Types/Font.hpp"

namespace JUI {
    enum HorizontalTextAlignmentEnum { // What's the difference between this and typedef enum?
        HTEXT_ALIGN_LEFT,
        HTEXT_ALIGN_CENTER,
        HTEXT_ALIGN_RIGHT
    };
    enum VerticalTextAlignmentEnum {
        VTEXT_ALIGN_TOP,
        VTEXT_ALIGN_CENTER,
        VTEXT_ALIGN_BOTTOM
    };

    // Text Widget -  Expands to fill the size of the parent Container
    // TODO: Rich Text Support
    class Text : public Widget {
    public:
        Text();

        ~Text() override;

        void Draw(SDL_Renderer *target) override;

        void Update(float delta) override {
            Widget::Update(delta);
        };

        void SetText(std::string text);
        std::string GetText() const;

        void SetTextColor(SDL_Color c);

        SDL_Color GetTextColor() const;

        void SetTextOutlineColor(SDL_Color c);

        SDL_Color GetTextOutlineColor() const;

        void SetFont(JUI::Font &font);

        JUI::Font GetFont() const;

        void SetVerticalTextAlignment(VerticalTextAlignmentEnum align);

        VerticalTextAlignmentEnum GetVerticalTextAlignment() const;

        void SetHorizontalTextAlignment(HorizontalTextAlignmentEnum align);

        HorizontalTextAlignmentEnum GetHorizontalTextAlignment() const;

    protected:

        Vector2 GetAbsoluteSize() const override;

        Vector2 GetAbsolutePosition() const override;

    private:
        HorizontalTextAlignmentEnum h_text_alignment = HTEXT_ALIGN_LEFT;
        VerticalTextAlignmentEnum v_text_alignment = VTEXT_ALIGN_TOP;
        float text_outline;
        bool rich_text_enabled;
        SDL_Color text_color;
        SDL_Color outline_color;
        std::string text = "Sample Text";
        JUI::Font font;
    };
}