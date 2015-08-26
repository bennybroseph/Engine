#include "Text.h"

namespace Text
{
    GLuint shader_program_text;
    Font_Type Pokemon_Normal;

    void Init()
    {
        TTF_Init();

        Pokemon_Normal.color = {0, 0, 0, 0};

		Pokemon_Normal.font = TTF_OpenFont("Fonts/PokemonRed.ttf", 16);
		if (Pokemon_Normal.font == NULL)
			printf("failure to load");

		int i;
		for (i = 0; i < 256; i++)
		{
			if (TTF_GlyphMetrics(Pokemon_Normal.font, i,
				&Pokemon_Normal.Char[i].minx, &Pokemon_Normal.Char[i].maxx, &Pokemon_Normal.Char[i].miny, &Pokemon_Normal.Char[i].maxy,
				&Pokemon_Normal.Char[i].advance) == -1)
				printf("%s\n", TTF_GetError());
		}
    }

    void Print(Font_Type Font, int x, int y, bool align, const char* text)
    {
        SDL_Surface* image;
		std::vector<std::string> lines;

		char hold[256];
		strcpy_s(hold, "");

		const char* i;
		if ((i = strchr(text, 10)) !=NULL)
		{
			strncat_s(hold, text, int(i - text));
			lines.push_back(hold);
			strcpy_s(hold, i + 1);
			lines.push_back(hold);
		}
		else
		{
			lines.push_back(text);
		}

        // Write text to surface
		int j;
		for (j = 0; j < lines.size(); j++)
		{
			image = TTF_RenderText_Blended(Pokemon_Normal.font, lines[j].c_str(), Pokemon_Normal.color);

			Pokemon_Normal.Surface = Graphics::Load_Image(image);

			Graphics::Draw_Image(Pokemon_Normal.Surface, x - (align)*(Pokemon_Normal.Surface.w), (y+(j*15)) - (Pokemon_Normal.Surface.h - 2));
		}
    }

    void Print(Font_Type Font, int x, int y, bool align, int text)
    {
        char buffer[256];

        sprintf_s(buffer,"%d",text);Debug::Log("Buffer Complete");
        Print(Font, x, y, align, buffer);
    }

    void Quit()
    {
		//SDL_FreeSurface(image);Debug::Log("Free Complete");
		TTF_CloseFont(Pokemon_Normal.font); Debug::Log("Render Complete");
    }
}
