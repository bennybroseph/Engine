/////////////////////////////////////////////////////////////
// File: Text.h
// Author: Ben Odom
// Brief: Holds functionality for drawing text to the screen
//        using SDL_TTF. Can draw text string and integers.
//////////////////////////////////////////////////////////////

#ifndef _TEXT_H_
#define _TEXT_H_

#include <SDL_ttf.h>
#include "../../Classes/Define.h"
#include "../Graphics/Graphics.h"

namespace Text
{
    struct FontData
    {
        TTF_Font* ttfFont;
        SDL_Color sdlColor;

		struct Glyph
		{
			int iMinX, iMaxX;
			int iMinY, iMaxY;
			int iAdvance;
		};

		Glyph aoChar[256];
    };

    bool Init();
    
	void Print(const FontData &ac_ttfFont, const int ac_iPosX, const int ac_iPosY, const bool ac_bAlign, const char* ac_szText);
    void Print(const FontData &ac_ttfFont, const int ac_iPosX, const int ac_iPosY, const bool ac_bAlign, const int ac_iText);    

	void Quit();

    extern FontData PokemonNormal;
}

#endif  //_TEXT_H_
