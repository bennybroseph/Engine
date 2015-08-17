#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <glu.h>
#include <glext.h>
#include <stdio.h>
#include <string>

#include "../../Classes/Define.h"

#define GL_GLEXT_LEGACY

struct GLSurface
{
    GLuint Surface;
    int w,h;
    float rotation[3] = {0,0,0};
};

namespace Graphics
{
    bool Init(int, int, int = 3, bool = false);
    void Resize(int, int, int = 3, bool = false);

    GLSurface Load_Image(std::string);
    GLSurface Load_Image(SDL_Surface*);

    void Update_Window_Name(char[]);
    void Draw_Image(GLSurface, float, float);
    void Draw_Image(GLSurface, float, float, float, float, float, float);
    void Draw_Background();
    //Draws the given rect in the given color
    void Draw_Rect(float, float, float, float, int, int, int);
    //Draws the given line in the given color
    void Draw_Line(float, float, float, float, int, int, int);
    //Draws the given point in the given color
    void Draw_Point(float, float, int, int, int);
    //Draws the given Circle in the Given color
    void Draw_Circle(float, float, float, int, int, int, int);

    void Flip();

    void Quit();

    extern int winH, winW;
}
#endif // GRAPHICS_H_INCLUDED
