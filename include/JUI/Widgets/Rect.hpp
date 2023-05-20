#pragma once

#include <JUI/Widget.hpp>
#include <SDL2/SDL_pixels.h>
#include "JUI/Types/UDim2.hpp"

namespace JUI {
    class Rect : public Widget {
    public:

        void Draw() override;

        void Update(float delta) override;


        UDim2 GetSize() { return size; }

        void SetSize(UDim2 s) { size = s; }

        UDim2 GetPosition() { return position; }

        void SetPosition(UDim2 pos) { position = pos; }

        SDL_Color GetBackgroundColor() { return bg_color; }

        void SetBackgroundColor(SDL_Color c) { bg_color = c; }

        SDL_Color GetBorderColor() { return border_color; }

        void SetBorderColor(SDL_Color c) { border_color = c; }

        float GetBorderWidth() { return border_width; }

        void SetBorderWidth(float pixels) { border_width = pixels; }

        bool GetClipsDescendants() { return clips_descendants; }

        void SetClipsDescendants(bool ye) { clips_descendants = ye; }

        // Are these necessary? SDL_Color contains an alpha channel
        float GetTransparency() { return this->transparency; }

        void SetTransparency(float alpha) { transparency = alpha; }


        float GetRotation() { return rotation; }

        void SetRotation(float rot) { rotation = rot; }

        bool IsVisible();

        void SetVisible(bool);

    protected:
    private:
        float border_width = 1.0f;
        SDL_Color bg_color;
        SDL_Color border_color;
        float transparency;
        bool clips_descendants;
        UDim2 position;
        UDim2 size;
        Vector2 absolute_size;
        Vector2 absolute_position;
        float rotation;
        float absolute_rotation;
    };


    void Rect::Draw() {

    }

    void Rect::Update(float delta) {

    }
}
