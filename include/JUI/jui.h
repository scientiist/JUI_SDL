// Josh's UI Toolkit
// Ported to C++ / SDL
// Copyright 2023 Conarium Software LLC
#include <vector>
#include <memory>

#include <Vector2.hpp>

#pragma once

namespace JUI
{

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