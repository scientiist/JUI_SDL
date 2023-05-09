// Class Wrapper for SDL_TTF Font
// @auth Josh O'Leary
#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_ttf.h>


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum
{
	TextRenderSolid,
	TextRenderShaded,
	TextRenderBlended
} TextRenderMethod;



namespace JUI 
{
	class Font {
	public:
		static bool TTFInitialized;
		static Font Load(std::string&const file, int ptsize);
	private:
	protected:

	}
}