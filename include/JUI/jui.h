/* @file       jui.h
 * @desc       Josh's User Interface Toolkit (C++/SDL2 Edition)
 * @auth       Josh O'Leary
 * @revision   1
 * @edited     2023-05-20
 * @copyright  (C) 2023 Conarium Software
 * @license    GNU Affero GPL-3
 */
#pragma once


#include <JUI/common.hpp>
#include "JUI/Types/Event.hpp"
//#include <JUI/Font.hpp>
#include <JUI/Types/Vector2.hpp>
#include "JUI/Widgets/Widget.hpp"
#include <JUI/Widgets/Rect.hpp>
#include <JUI/Widgets/Text.hpp>
#include <JUI/Widgets/Scene.hpp>
#include <JUI/Widgets/Texture.hpp>
#include <JUI/Widgets/Slider.hpp>
#include <JUI/Widgets/TextEdit.hpp>
#include <JUI/Widgets/VerticalLayoutContainer.hpp>
#include <JUI/Widgets/HorizontalLayoutContainer.hpp>
#include <vector>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

namespace JUI {


    static SDL_Renderer *renderer;

    static SDL_Renderer *getRenderer() { return renderer; }

    static void Init() {}

    // Primitive Rendering Methods
    static void DrawRect(int x, int y, int w, int h) {
        SDL_Rect rect{x, y, w, h};
        SDL_RenderDrawRect(renderer, &rect);
    }

    static void DrawRect(const Vector2 &position, const Vector2 &size) {
        SDL_Rect rect{
                static_cast<int>(position.X),
                static_cast<int>(position.Y),
                static_cast<int>(size.X),
                static_cast<int>(size.Y)};
        SDL_RenderDrawRect(renderer, &rect);
    }

    static void FillRect(int x, int y, int w, int h) {
        SDL_Rect rect{x, y, w, h};
        SDL_RenderFillRect(renderer, &rect);
    }

    static void DrawPolygon() {}

    static void FillPolygon() {}

    static void DrawLine() {}

    static void DrawLines() {}
    static void DrawPoint() {}
    static void DrawPoints() {}
    static void DrawCurve() {}
    static void DrawString() {}
    static void DrawTexture() {}
    static void DrawCanvas() {}


    static void Quit()
    {
        SDL_Quit();
        exit(0);
    }

}