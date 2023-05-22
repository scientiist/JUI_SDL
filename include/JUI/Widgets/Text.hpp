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

        void SetTextColor()

        void SetFont(JUI::Font& font);
        JUI::Font GetFont() const;

        void SetTextAlignment(TextAlignmentEnum align);
        TextAlignmentEnum GetTextAlignment() const;


        std::string Content;
    private:
    protected:
        JUI::Font *Font; // Prolly want a reference?
        TextAlignmentEnum TextAlignment = TEXT_ALIGNMENT_LEFT;

        SDL_Color TextColor;
        SDL_Color TextOutlineColor;
        float TextOutline;
        bool RichTextEnabled;

        Vector2 GetAbsoluteSize() const override;
        Vector2 GetAbsolutePosition() const override;


    };
}