#include <JUI/Widgets/Rect.hpp>

#include <JUI/Types/Font.hpp>
#include "JUI/jui.h"

namespace JUI {

    Rect::Rect() : Widget() {}
    Rect::~Rect() {}

    void Rect::Draw(SDL_Renderer* target) {

        Vector2 abs_pos = GetAbsolutePosition();
        Vector2 abs_size = GetAbsoluteSize();

        SDL_Rect box{(int)abs_pos.X, (int)abs_pos.Y, (int)abs_size.X, (int)abs_size.Y};

        // Draw Inner Box
        SDL_SetRenderDrawColor(target, bg_color.r, bg_color.g, bg_color.b, bg_color.a);
        SDL_RenderFillRect(target, &box);

        // Draw Outline
        SDL_SetRenderDrawColor(target, border_color.r, border_color.g, border_color.b, border_color.a);

        // You can't set the Line Width in SDL
        // So we need to render 4 smaller rectangles on each edge of the box
        // to achieve BorderWidth functionality

        // Left Border
        auto left_border_topleft = abs_pos - Vector2{border_width/2, border_width/2};
        auto left_border_size = Vector2{0, abs_size.Y} + Vector2{border_width, border_width};
        SDL_Rect left_border_box{
            (int)left_border_topleft.X,
            (int)left_border_topleft.Y,
            (int)left_border_size.X,
            (int)left_border_size.Y};
        SDL_RenderFillRect(target, &left_border_box);

        // Right border
        auto right_border_topleft = abs_pos + Vector2{abs_size.X, 0};
        auto right_border_size = left_border_size;
        SDL_Rect right_border_box{
            (int)right_border_topleft.X,
            (int)right_border_topleft.Y,
            (int)right_border_size.X,
            (int)right_border_size.Y};
        SDL_RenderFillRect(target, &right_border_box);

        // Top border
        auto top_border_topleft = abs_pos - Vector2{border_width/2, border_width/2};
        auto top_border_size = Vector2{abs_size.X, 0} + Vector2{border_width, border_width};
        SDL_Rect top_border_box{
            (int)top_border_topleft.X,
            (int)top_border_topleft.Y,
            (int)top_border_size.X,
            (int)top_border_size.Y};
        SDL_RenderFillRect(target, &top_border_box);

        // Bottom border
        auto bottom_border_topleft = abs_pos + Vector2{0, abs_size.Y};
        auto bottom_border_size = top_border_size;
        SDL_Rect bottom_border_box{
            (int)bottom_border_topleft.X,
            (int)bottom_border_topleft.Y,
            (int)bottom_border_size.X,
            (int)bottom_border_size.Y};
        SDL_RenderFillRect(target, &bottom_border_box);

        //SDL_RenderDrawRect(target, &box);


        // Debug Draw

        std::string data = abs_pos.ToString();
        //FC_DrawAlign(JUI::debug_font.fc_font, target, abs_pos.X, abs_pos.Y, FC_ALIGN_LEFT, data.c_str());
        data = "";
        //FC_DrawAlign(JUI::debug_font.fc_font, target, abs_pos.X, abs_pos.Y, FC_ALIGN_LEFT, data.c_str());



        Widget::Draw(target);
    }

    void Rect::Update(float delta) {
        Widget::Update(delta);
    }

    SDL_Color Rect::GetBackgroundColor() const
    { return bg_color;}

    void Rect::SetBackgroundColor(SDL_Color c)
    { bg_color = c;}

    SDL_Color Rect::GetBorderColor() const
    { return border_color;}

    void Rect::SetBorderColor(SDL_Color c)
    { border_color = c;}

    float Rect::GetBorderWidth() const
    { return border_width; }

    void Rect::SetBorderWidth(float pixels)
    { border_width = pixels; }

    bool Rect::GetClipsDescendants() const
    { return clips_descendants; }

    void Rect::SetClipsDescendants(bool ye)
    { clips_descendants = ye;}

}