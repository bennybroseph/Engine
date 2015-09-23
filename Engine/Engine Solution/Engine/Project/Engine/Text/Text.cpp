#include "Text.h"

namespace Text
{
	FontData PokemonNormal;

	bool Init()
	{
		TTF_Init();

		PokemonNormal.sdlColor = { 0, 0, 0, 0 };

		PokemonNormal.ttfFont = TTF_OpenFont("Fonts/PokemonRed.ttf", 16);
		if (PokemonNormal.ttfFont == NULL)
		{
			printf("Failure to load\n");
			return 1;
		}

		int i;
		for (i = 0; i < 256; i++)
		{
			if (TTF_GlyphMetrics(PokemonNormal.ttfFont, i,
				&PokemonNormal.aoChar[i].iMinX, &PokemonNormal.aoChar[i].iMaxX, &PokemonNormal.aoChar[i].iMinY, &PokemonNormal.aoChar[i].iMaxY,
				&PokemonNormal.aoChar[i].iAdvance) == -1)
			{
				printf("%s\n", TTF_GetError());
				return 1;
			}
		}

		return 0;
	}

	void Print(const FontData &ac_ttfFont, const int ac_iPosX, const int ac_iPosY, const bool ac_bAlign, const char* ac_szText)
	{
		std::vector<std::string> vsLines;

		char szHold[256];
		strcpy_s(szHold, "");

		const char* i;
		if ((i = strchr(ac_szText, 10)) != NULL)
		{
			strncat_s(szHold, ac_szText, int(i - ac_szText));
			vsLines.push_back(szHold);

			strcpy_s(szHold, i + 1);
			vsLines.push_back(szHold);
		}
		else
		{
			vsLines.push_back(ac_szText);
		}

		SDL_Surface* sdlSurface;
		GLSurface glSurface;
		// Write text to surface
		for (int j = 0; j < vsLines.size(); ++j)
		{
			sdlSurface = TTF_RenderText_Blended(ac_ttfFont.ttfFont, vsLines[j].c_str(), ac_ttfFont.sdlColor);

			glSurface = Graphics::LoadSurface(sdlSurface);

			Graphics::DrawSurface(glSurface, ac_iPosX - (ac_bAlign)*(glSurface.w), (ac_iPosY + (j * 15)) - (glSurface.h - 2));
		}

		SDL_FreeSurface(sdlSurface);
	}

	void Print(const FontData &ac_ttfFont, const int ac_iPosX, const int ac_iPosY, const bool ac_bAlign, const int ac_iText)
	{
		char szBuffer[256];

		sprintf_s(szBuffer, "%d", ac_iText);
		Print(ac_ttfFont, ac_iPosX, ac_iPosY, ac_bAlign, szBuffer);
	}

	void Quit()
	{
		TTF_CloseFont(PokemonNormal.ttfFont); Debug::Log("Text Quit");
	}
}
