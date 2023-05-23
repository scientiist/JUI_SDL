#pragma once

#include "JUI/Widget.hpp"

#include <JUI/Font.hpp>

namespace JUI {
    enum TextAlignmentEnum { // What's the difference between this and typedef enum?
        TEXT_ALIGNMENT_LEFT, TEXT_ALIGNMENT_CENTER, TEXT_ALIGNMENT_RIGHT
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

        void SetFont(JUI::Font& font);
        JUI::Font GetFont() const;

        void SetTextAlignment(TextAlignmentEnum align);
        TextAlignmentEnum GetTextAlignment() const;


    protected:

        Vector2 GetAbsoluteSize() const override;
        Vector2 GetAbsolutePosition() const override;
    private:
        TextAlignmentEnum text_alignment = TEXT_ALIGNMENT_LEFT;
        float text_outline;
        bool rich_text_enabled;
        SDL_Color text_color;
        SDL_Color outline_color;
        std::string text;
        JUI::Font font;
    };
}