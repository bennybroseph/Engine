#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include <SDL_ttf.h>
#include "../../Classes/Define.h"
#include "../Graphics/Graphics.h"

namespace Text
{
    struct Font_Type
    {
        TTF_Font* font;
        SDL_Color color;

        GLSurface Surface;

		struct Glyph
		{
			int minx, maxx, miny, maxy, advance;
		};

		Glyph Char[256];
    };

    void Init();
    void Quit();

    void Print(Font_Type, int, int, bool, int);
    void Print(Font_Type, int, int, bool, const char*);

    extern Font_Type Pokemon_Normal;
}

#endif  //TEXT_H_INCLUDED
