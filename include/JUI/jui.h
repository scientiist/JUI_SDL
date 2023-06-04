/* @file       jui.h
 * @desc       Josh's User Interface Toolkit (C++/SDL2 Edition)
 * @auth       Josh O'Leary
 * @revision   1
 * @edited     2023-05-20
 * @copyright  (C) 2023 Conarium Software
 * @license    GNU Affero GPL-3
 */
#pragma once

#include <vector>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <string>

#include <JUI/Types/Font.hpp>

namespace JUI {

    //static JUI::Font debug_font;
    static void Init(SDL_Renderer* renderer)
    {
        //debug_font = Font(renderer, "fonts/FreeSans.ttf", 10);
    }



}