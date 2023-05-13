/////////////////////////////////////////////////////
// JUI - Josh's UI Toolkit
// Ported to C++ / SDL
// Copyright 2023 Conarium Software LLC
// @auth Joshua O'Leary

#pragma once


#include <JUI/common.hpp>
#include <JUI/Color.hpp>
#include <JUI/Vector2.hpp>
#include <JUI/Widget.hpp>
#include <JUI/Rect.hpp>
#include <JUI/Text.hpp>
#include <JUI/Scene.hpp>
#include <JUI/Texture.hpp>
#include <JUI/Slider.hpp>
#include <JUI/TextExit.hpp>
#include <JUI/VerticalLayoutContainer.hpp>
#include <JUI/HorizontalLayoutContainer.hpp>
#include <vector>
#include <memory>

namespace JUI
{
    static SDL_Renderer* renderer;
    static void Init() { }

    // Primitive Rendering Methods
    static void DrawRect(int x, int y, int w, int h) {
        SDL_Rect rect {x, y, w, h};
        SDL_RenderDrawRect(renderer, rect);
    }
    static void DrawRect(const v2d& position, const v2d& size)
    {

    }
    static void FillRect(int x, int y, int w, int h) {

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

    class ScreenCoordinates
    {
        int PixelsX;
        int PixelsY;
        float ScaleX;
        float ScaleY;
    };

    // TODO: Get sum rectangles rendering in SDL2
    class Layout  { };
    class VerticalLayoutContainer : Layout { };
    class HorizontalLayoutContainer : Layout { };
    class GridLayoutContainer : Layout { };
    class TextLabel : Widget { };
    class Slider : Widget {};
    class Checkbox : Widget {};
    class LineEdit : Widget { };
    class NineSlice : Widget { };
    class ContextButton : Widget { };
    class ScrollRect : Widget { };


}