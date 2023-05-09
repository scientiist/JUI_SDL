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

    static void JUI_Init()
    {
        
    }

    static void JUI_Quit()
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