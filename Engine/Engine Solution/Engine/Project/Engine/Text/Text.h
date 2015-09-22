#ifndef _TEXT_H_
#define _TEXT_H_

#include <SDL_ttf.h>
#include "../../Classes/Define.h"
#include "../Graphics/Graphics.h"

namespace Text
{
    struct Font_Type
    {
        TTF_Font* m_ttfFont;
        SDL_Color m_sdlColor;

        GLSurface m_glSurface;

		struct Glyph
		{
			int iMinX, iMaxX;
			int iMinY, iMaxY;
			int iAdvance;
		};

		Glyph m_aoChar[256];
    };

    void Init();
    void Quit();

    void Print(Font_Type, int, int, bool, int);
    void Print(Font_Type, int, int, bool, const char*);

    extern Font_Type Pokemon_Normal;
}

#endif  //_TEXT_H_
