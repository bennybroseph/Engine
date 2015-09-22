#include "Text.h"

namespace Text
{
	Font_Type Pokemon_Normal;

	void Init()
	{
		TTF_Init();

		Pokemon_Normal.m_sdlColor = { 0, 0, 0, 0 };

		Pokemon_Normal.m_ttfFont = TTF_OpenFont("Fonts/PokemonRed.ttf", 16);
		if (Pokemon_Normal.m_ttfFont == NULL)
			printf("Failure to load\n");

		int i;
		for (i = 0; i < 256; i++)
		{
			if (TTF_GlyphMetrics(Pokemon_Normal.m_ttfFont, i,
				&Pokemon_Normal.m_aoChar[i].iMinX, &Pokemon_Normal.m_aoChar[i].iMaxX, &Pokemon_Normal.m_aoChar[i].iMinY, &Pokemon_Normal.m_aoChar[i].iMaxY,
				&Pokemon_Normal.m_aoChar[i].iAdvance) == -1)
				printf("%s\n", TTF_GetError());
		}
	}

	void Print(Font_Type Font, int x, int y, bool align, const char* text)
	{
		SDL_Surface* sdlSurface;
		std::vector<std::string> vsLines;

		char szHold[256];
		strcpy_s(szHold, "");

		const char* i;
		if ((i = strchr(text, 10)) != NULL)
		{
			strncat_s(szHold, text, int(i - text));
			vsLines.push_back(szHold);
			strcpy_s(szHold, i + 1);
			vsLines.push_back(szHold);
		}
		else
		{
			vsLines.push_back(text);
		}

		// Write text to surface
		int j;
		for (j = 0; j < vsLines.size(); j++)
		{
			sdlSurface = TTF_RenderText_Blended(Pokemon_Normal.m_ttfFont, vsLines[j].c_str(), Pokemon_Normal.m_sdlColor);

			Pokemon_Normal.m_glSurface = Graphics::Load_Image(sdlSurface);

			Graphics::Draw_Image(Pokemon_Normal.m_glSurface, x - (align)*(Pokemon_Normal.m_glSurface.w), (y + (j * 15)) - (Pokemon_Normal.m_glSurface.h - 2));
		}
	}

	void Print(Font_Type Font, int x, int y, bool align, int text)
	{
		char buffer[256];

		sprintf_s(buffer, "%d", text);
		Print(Font, x, y, align, buffer);
	}

	void Quit()
	{
		TTF_CloseFont(Pokemon_Normal.m_ttfFont); Debug::Log("Text Quit");
	}
}
