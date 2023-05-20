/* @file       Font.hpp
 * @desc       Class Wrapper for SDL_TTF Font and SDL_FontCache functionality
 * @auth       Josh O'Leary
 * @revision   1
 * @edited     2023-05-20
 * @copyright  (C) 2023 Conarium Software
 * @license    GNU Affero GPL-3
 */
#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_ttf.h>

#include <SDL_FontCache/SDL_FontCache.h>

#include <stdlib.h>
#include <stdio.h>
#include <string>

typedef enum
{
	TextRenderSolid,
	TextRenderShaded,
	TextRenderBlended
} TextRenderMethod;

#include <JUI/jui.h>

namespace JUI 
{
    class Font {
    public:
        Font() {}

        Font(std::string font) {
            fc_font = FC_CreateFont();
            FC_LoadFont(fc_font, JUI::getRenderer(), font, 12, {0, 0, 0, 255});
        }

        static bool TTFInitialized;

        static Font Load(std::string file, int ptsize);

    private:
        FC_Font *fc_font;
    protected:
    };
}