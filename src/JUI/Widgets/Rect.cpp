#include <JUI/Widgets/Rect.hpp>

namespace JUI {

    Rect::Rect() : Widget() {}
    Rect::~Rect() {}

    void Rect::Draw(SDL_Renderer* target) {
        SDL_SetRenderDrawColor(target, bg_color.r, bg_color.g, bg_color.b, bg_color.a);

        Vector2 abs_pos = GetAbsolutePosition();
        Vector2 abs_size = GetAbsoluteSize();

        SDL_Rect box{(int)abs_pos.X, (int)abs_pos.Y, (int)abs_size.X, (int)abs_size.Y};
        SDL_RenderFillRect(target, &box);

        SDL_SetRenderDrawColor(target,
                               border_color.r, border_color.g, border_color.b, border_color.a);
        SDL_RenderDrawRect(target, &box);

        // TODO: You can't set the Line Width in SDL
        // So we need to render 4 smaller rectangles on each edge of the box
        // to achieve BorderWidth functionality

    }

    void Rect::Update(float delta) {

    }
}

