#include "Text.h"

namespace Text
{
    GLuint shader_program_text;
    Font_Type Pokemon_Normal;

    void Init()
    {
        TTF_Init();

        Pokemon_Normal.color = {0, 0, 0, 0};
    }

    void Print(Font_Type Font, int x, int y, bool align, const char* text)
    {
        SDL_Surface* image;

        Pokemon_Normal.font = TTF_OpenFont("Fonts/PokemonRed.ttf", 16);
        if(Pokemon_Normal.font == NULL)
            printf("failure to load");

        // Write text to surface
        image = TTF_RenderText_Blended(Pokemon_Normal.font, text, Pokemon_Normal.color);Debug::Log("Surface Complete");

        Pokemon_Normal.Surface = Graphics::Load_Image(image);Debug::Log("Load Complete");

        //SDL_FreeSurface(image);Debug::Log("Free Complete");
        TTF_CloseFont(Pokemon_Normal.font);Debug::Log("Render Complete");

        Graphics::Draw_Image(Pokemon_Normal.Surface, x - (align)*(Pokemon_Normal.Surface.w), y - (Pokemon_Normal.Surface.h - 2));
    }

    void Print(Font_Type Font, int x, int y, bool align, int text)
    {
        char buffer[256];

        sprintf_s(buffer,"%d",text);Debug::Log("Buffer Complete");
        Print(Font, x, y, align, buffer);
    }

    void Quit()
    {

    }
}
