#pragma once

#include "Widget.hpp"
#include <SDL2/SDL_pixels.h>
#include "JUI/Types/UDim2.hpp"

namespace JUI {
    class Rect : public Widget {
    public:

        Rect();
        ~Rect() override;
        void Draw(SDL_Renderer* target) override;
        void Update(float delta) override;

        SDL_Color GetBackgroundColor() const;
        void SetBackgroundColor(SDL_Color c);

        SDL_Color GetBorderColor() const;
        void SetBorderColor(SDL_Color c);

        float GetBorderWidth() const;
        void SetBorderWidth(float pixels);

        bool GetClipsDescendants() const;
        void SetClipsDescendants(bool ye);

        // Are these necessary? SDL_Color contains an alpha channel
        float GetTransparency() const { return this->transparency; }
        void SetTransparency(float alpha) { transparency = alpha; }

        bool IsVisible() const;

        void SetVisible(bool);

    protected:
        float border_width = 1.0f;
        SDL_Color bg_color;
        SDL_Color border_color;
        float transparency;
        bool clips_descendants;
    private:
    };



}
