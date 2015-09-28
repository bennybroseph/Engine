#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#include <glut.h>
#include <stdio.h>
#include <string>

#include "../../Classes/Define.h"

#define GL_GLEXT_LEGACY

struct GLSurface
{
	GLuint Surface;
	int w, h;
	float rotation[3] = { 0,0,0 };
};

namespace Graphics
{
	bool Init(const int ac_iWidth, const int ac_iHeight, const int ac_iScale = 3, const bool ac_bFullScreen = false);

	GLSurface LoadSurface(const std::string ac_sFilename);
	GLSurface LoadSurface(const SDL_Surface *ac_psdlSurface);

	void UpdateWindowName(const char *szBuffer);
	void DrawSurface(const GLSurface &ac_glSurface, const float ac_fPosX, const float ac_fPosY);
	void DrawSurface(
		const GLSurface &ac_glSurface,
		const float ac_fPosX, const float ac_fPosY,
		const float ac_fOffsetX, const float ac_fOffsetY,
		const float ac_fWidth, const float ac_fHeight);

	void Resize(const int ac_iScale = 3, const bool ac_bFullScreen = false);
	void ToggleFullScreen();

	//Draws the given rect in the given color
	void Draw_Rect(
		const float ac_fPosX, const float ac_fPosY,
		const float ac_fWidth, const float ac_fHeight,
		const int ac_iRed, const int ac_iGreen, const int ac_iBlue);
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
#endif // _GRAPHICS_H_
