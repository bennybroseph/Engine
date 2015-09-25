#include "Graphics.h"



namespace Graphics
{
	SDL_Window *sdlWindow = nullptr; // A pointer to the window
	SDL_DisplayMode sdlMode;
	SDL_GLContext glContext;

	int iResolutionW, iResolutionH;
	int iWinWidth, iWinHeight, iWinScale;

	bool bFullScreen;

	bool Init(const int ac_iWidth, const int ac_iHeight, const int ac_iScale, const bool ac_bFullScreen)
	{
		iResolutionW = ac_iWidth;
		iResolutionH = ac_iHeight;

		bFullScreen = ac_bFullScreen;

		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			printf("SDL_Error: %s\n", SDL_GetError());
			return 1;
		}

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		sdlWindow = SDL_CreateWindow(
			"Pokemon Red",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			ac_iWidth*ac_iScale,
			ac_iHeight*ac_iScale,
			SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP*bFullScreen | SDL_WINDOW_OPENGL);

		if (sdlWindow == nullptr)
		{
			printf("SDL_Error: %s\n", SDL_GetError());
			return 1;
		}

		if (SDL_GetDisplayMode(0, 0, &sdlMode) != 0)
		{
			printf("SDL_Error: %s\n", SDL_GetError());
			return 1;
		}

		iWinWidth = (bFullScreen) ? sdlMode.w : iResolutionW*ac_iScale;
		iWinHeight = (bFullScreen) ? sdlMode.h : iResolutionH*ac_iScale;
		iWinScale = ac_iScale;

		int iViewportW = iWinHeight * (float(iResolutionW) / float(iResolutionH));
		int iViewportOffset = (iWinWidth / 2) - (iViewportW / 2);

		glContext = SDL_GL_CreateContext(sdlWindow);
		SDL_GL_SetSwapInterval(1);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glViewport(iViewportOffset, 0, iViewportW, iWinHeight);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();

		glOrtho(0.0f, ac_iWidth, ac_iHeight, 0.0f, -1.0f, 1.0f);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return 0;
	}

	GLSurface LoadSurface(const std::string ac_sFilename)
	{
		GLSurface glSurface;
		SDL_Surface* sdlSurface;

		sdlSurface = IMG_Load(ac_sFilename.c_str());
		if (sdlSurface == NULL)
		{
			printf("SDL_Error: %s\n", SDL_GetError());
			return glSurface;
		}

		GLuint glTexture;
		glGenTextures(1, &glTexture);
		glBindTexture(GL_TEXTURE_2D, glTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, sdlSurface->format->BytesPerPixel, sdlSurface->w, sdlSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdlSurface->pixels);

		glSurface.h = sdlSurface->h;
		glSurface.w = sdlSurface->w;
		glSurface.Surface = glTexture;

		SDL_FreeSurface(sdlSurface);

		return glSurface;
	}
	GLSurface LoadSurface(const SDL_Surface *ac_psdlSurface)
	{
		GLSurface glSurface;

		GLuint glTexture;
		glGenTextures(1, &glTexture);
		glBindTexture(GL_TEXTURE_2D, glTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, ac_psdlSurface->format->BytesPerPixel, ac_psdlSurface->w, ac_psdlSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, ac_psdlSurface->pixels);

		glSurface.h = ac_psdlSurface->h;
		glSurface.w = ac_psdlSurface->w;
		glSurface.Surface = glTexture;

		return glSurface;
	}

	void DrawSurface(const GLSurface &ac_glSurface, const float ac_fPosX, const float ac_fPosY)
	{
		glColor3f(1.0f, 1.0f, 1.0f);

		glBindTexture(GL_TEXTURE_2D, ac_glSurface.Surface);
		glBegin(GL_QUADS);
		//Bottom-left vertex (corner)
		glColor3b(127, 127, 127);
		glTexCoord2i(0, 0); //Position on texture to begin interpolation
		glVertex3f(ac_fPosX, ac_fPosY, 0.f); //Vertex Coords

		//Bottom-right vertex (corner)
		glTexCoord2i(1, 0);
		glVertex3f(ac_fPosX + ac_glSurface.w, ac_fPosY, 0.f);

		//Top-right vertex (corner)
		glTexCoord2i(1, 1);
		glVertex3f(ac_fPosX + ac_glSurface.w, ac_fPosY + ac_glSurface.h, 0.f);

		//Top-left vertex (corner)
		glTexCoord2i(0, 1);
		glVertex3f(ac_fPosX, ac_fPosY + ac_glSurface.h, 0.f);
		glEnd();
	}
	void DrawSurface(
		const GLSurface &ac_glSurface,
		const float ac_fPosX, const float ac_fPosY,
		const float ac_fOffsetX, const float ac_fOffsetY,
		const float ac_fWidth, const float ac_fHeight)
	{
		glColor3f(1.0f, 1.0f, 1.0f);

		glBindTexture(GL_TEXTURE_2D, ac_glSurface.Surface);

		glBegin(GL_QUADS);
		// Bottom-left vertex (corner)
		glColor3b(127, 127, 127);
		glTexCoord2f(ac_fOffsetX / ac_glSurface.w, ac_fOffsetY / ac_glSurface.h); // Position on texture to begin interpolation
		glVertex3f(ac_fPosX, ac_fPosY, 0.f); // Vertex Coords

		// Bottom-right vertex (corner)
		glTexCoord2f((ac_fOffsetX / ac_glSurface.w) + (ac_fWidth / ac_glSurface.w), ac_fOffsetY / ac_glSurface.h);
		glVertex3f(ac_fPosX + ac_fWidth, ac_fPosY, 0.f);

		// Top-right vertex (corner)
		glTexCoord2f((ac_fOffsetX / ac_glSurface.w) + (ac_fWidth / ac_glSurface.w), (ac_fOffsetY / ac_glSurface.h) + (ac_fHeight / ac_glSurface.h));
		glVertex3f(ac_fPosX + ac_fWidth, ac_fPosY + ac_fHeight, 0.f);

		// Top-left vertex (corner)
		glTexCoord2f(ac_fOffsetX / ac_glSurface.w, (ac_fOffsetY / ac_glSurface.h) + (ac_fHeight / ac_glSurface.h));
		glVertex3f(ac_fPosX, ac_fPosY + ac_fHeight, 0.f);
		glEnd();

	}

	void Resize(const int ac_iScale, const bool ac_bFullScreen)
	{
		bFullScreen = ac_bFullScreen;

		SDL_SetWindowSize(sdlWindow, iResolutionW * ac_iScale, iResolutionH * ac_iScale);
		SDL_SetWindowFullscreen(sdlWindow, SDL_WINDOW_FULLSCREEN_DESKTOP * bFullScreen);

		SDL_SetWindowPosition(sdlWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

		if (SDL_GetDisplayMode(0, 0, &sdlMode) != 0)
		{
			printf("SDL_Error: %s\n", SDL_GetError());
		}

		iWinWidth = (bFullScreen) ? sdlMode.w : iResolutionW*ac_iScale;
		iWinHeight = (bFullScreen) ? sdlMode.h : iResolutionH*ac_iScale;
		iWinScale = ac_iScale;

		int iViewportW = iWinHeight * (float(iResolutionW) / float(iResolutionH));
		int iViewportOffset = (iWinWidth / 2) - (iViewportW / 2);

		glViewport(iViewportOffset, 0, iViewportW, iWinHeight);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();

		glOrtho(0.0f, iResolutionW, iResolutionH, 0.0f, -1.0f, 1.0f);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
	}
	void ToggleFullScreen()
	{
		Resize(iWinScale, !bFullScreen);
	}

	void Draw_Rect(
		const float ac_fPosX, const float ac_fPosY,
		const float ac_fWidth, const float ac_fHeight,
		const int ac_iRed, const int ac_iGreen, const int ac_iBlue)
	{
		glBindTexture(GL_TEXTURE_2D, NULL);// boundTexture = NULL; }

		glBegin(GL_QUADS);
		glColor3b(ac_iRed, ac_iGreen, ac_iBlue);
		//Bottom-left vertex (corner)
		glVertex3f(ac_fPosX, ac_fPosY, 0.0f); //Vertex Coords

		//Bottom-right vertex (corner)
		glVertex3f(ac_fPosX + ac_fWidth, ac_fPosY, 0.f);

		//Top-right vertex (corner)
		glVertex3f(ac_fPosX + ac_fWidth, ac_fPosY + ac_fHeight, 0.f);

		//Top-left vertex (corner)
		glVertex3f(ac_fPosX, ac_fPosY + ac_fHeight, 0.f);

		glEnd();
	}
	void Draw_Line(float x1, float y1, float x2, float y2, int r, int g, int b)
	{
		glBindTexture(GL_TEXTURE_2D, NULL);

		glBegin(GL_LINES);
		glColor3b(r, g, b);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
		glEnd();
	}
	void Draw_Point(float x, float y, int r, int g, int b)
	{
		glBindTexture(GL_TEXTURE_2D, NULL);

		glBegin(GL_POINTS);
		glColor3b(r, g, b);
		glVertex2f(x, y);
		glEnd();
	}
	void Draw_Circle(float x, float y, float R, int n, int r, int g, int b)
	{
		glBindTexture(GL_TEXTURE_2D, NULL);

		glBegin(GL_LINE_LOOP);
		glColor3b(r, g, b);
		for (float i = 0; i < 2 * PI; i += (2 * PI) / n) {
			glVertex2f(x + cosf(i)*R, y + sinf(i)*R);
		}
		glEnd();
	}

	void UpdateWindowName(const char *szBuffer)
	{
		SDL_SetWindowTitle(sdlWindow, szBuffer);
	}

	void Flip()
	{
		SDL_GL_SwapWindow(sdlWindow);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Quit()
	{
		SDL_GL_DeleteContext(glContext);
		SDL_DestroyWindow(sdlWindow);
		SDL_Quit();
		Debug::Log("Graphics Quit");
	}
}
