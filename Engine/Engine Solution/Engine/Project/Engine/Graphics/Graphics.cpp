#include "Graphics.h"

const unsigned int DEFAULT_WINDOW_WIDTH = 1920;
const unsigned int DEFAULT_WINDOW_HEIGHT = 1080;

namespace Graphics
{
	SDL_Window *sdlWindow = nullptr; // A pointer to the window
	SDL_DisplayMode *sdlMode = nullptr;
	SDL_GLContext glContext;

	GLSurface glSurfaceBG; // Surface that hold the background image
	bool bFullScreen;

	int iResolutionW, iResolutionH;
	int iWinWidth, iWinHeight;

	bool Init(const int ac_iWidth, const int ac_iHeight, const int ac_iScale, const bool ac_bFullScreen)
	{
		iResolutionW = ac_iWidth;
		iResolutionH = ac_iHeight;

		bFullScreen = ac_bFullScreen;

		glSurfaceBG = Graphics::LoadSurface("Images/background.png");

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

		if (SDL_GetDisplayMode(0, 0, sdlMode) != 0)
		{
			printf("SDL_Error: %s\n", SDL_GetError());
			return 1;
		}

		iWinWidth = (bFullScreen) ? sdlMode->w : iResolutionW*ac_iScale;
		iWinHeight = (bFullScreen) ? sdlMode->h : iResolutionH*ac_iScale;

		if (sdlWindow == nullptr)
		{
			printf("SDL_Error: %s\n", SDL_GetError());
			return 1;
		}

		glContext = SDL_GL_CreateContext(sdlWindow);
		SDL_GL_SetSwapInterval(1);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glViewport(200, 0, 1188, 1080);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();

		glOrtho(0.0f, iWinWidth, iWinHeight, 0.0f, -1.0f, 1.0f);
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

	void DrawSurface(const GLSurface &ac_glSurface, float a_fPosX, float a_fPosY)
	{
		//if (bFullScreen)a_fPosX += 48;
		glColor3f(1.0f, 1.0f, 1.0f);

		glBindTexture(GL_TEXTURE_2D, ac_glSurface.Surface);
		glBegin(GL_QUADS);
		//Bottom-left vertex (corner)
		glColor3b(127, 127, 127);
		glTexCoord2i(0, 0); //Position on texture to begin interpolation
		glVertex3f(a_fPosX, a_fPosY, 0.f); //Vertex Coords

		//Bottom-right vertex (corner)
		glTexCoord2i(1, 0);
		glVertex3f(a_fPosX + ac_glSurface.w, a_fPosY, 0.f);

		//Top-right vertex (corner)
		glTexCoord2i(1, 1);
		glVertex3f(a_fPosX + ac_glSurface.w, a_fPosY + ac_glSurface.h, 0.f);

		//Top-left vertex (corner)
		glTexCoord2i(0, 1);
		glVertex3f(a_fPosX, a_fPosY + ac_glSurface.h, 0.f);
		glEnd();
	}
	void DrawSurface(
		const GLSurface &ac_glSurface,
		float a_fPosX,
		float a_fPosY,
		const float ac_fOffsetX,
		const float ac_fOffsetY,
		const float ac_fWidth,
		const float ac_fHeight)
	{
		//if (bFullScreen)a_fPosX += 48;
		glColor3f(1.0f, 1.0f, 1.0f);

		glBindTexture(GL_TEXTURE_2D, ac_glSurface.Surface);

		glBegin(GL_QUADS);
		// Bottom-left vertex (corner)
		glColor3b(127, 127, 127);
		glTexCoord2f(ac_fOffsetX / ac_glSurface.w, ac_fOffsetY / ac_glSurface.h); // Position on texture to begin interpolation
		glVertex3f(a_fPosX, a_fPosY, 0.f); // Vertex Coords

		// Bottom-right vertex (corner)
		glTexCoord2f((ac_fOffsetX / ac_glSurface.w) + (ac_fWidth / ac_glSurface.w), ac_fOffsetY / ac_glSurface.h);
		glVertex3f(a_fPosX + ac_fWidth, a_fPosY, 0.f);

		// Top-right vertex (corner)
		glTexCoord2f((ac_fOffsetX / ac_glSurface.w) + (ac_fWidth / ac_glSurface.w), (ac_fOffsetY / ac_glSurface.h) + (ac_fHeight / ac_glSurface.h));
		glVertex3f(a_fPosX + ac_fWidth, a_fPosY + ac_fHeight, 0.f);

		// Top-left vertex (corner)
		glTexCoord2f(ac_fOffsetX / ac_glSurface.w, (ac_fOffsetY / ac_glSurface.h) + (ac_fHeight / ac_glSurface.h));
		glVertex3f(a_fPosX, a_fPosY + ac_fHeight, 0.f);
		glEnd();

	}

	void Resize(const int ac_iWidth, const int ac_iHeight, const int ac_iScale, const bool ac_bFullScreen)
	{
		iWinWidth = ac_iWidth;
		iWinHeight = ac_iHeight;
		bFullScreen = ac_bFullScreen;

		SDL_SetWindowSize(sdlWindow, bFullScreen*(1920) + (iWinWidth*ac_iScale)*(!bFullScreen), bFullScreen*(1080) + (iWinHeight*ac_iScale)*(!bFullScreen));
		SDL_SetWindowPosition(sdlWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

		glContext = SDL_GetWindowSurface(sdlWindow);

		glLoadIdentity();
		glOrtho(0.0f, iWinWidth + (96 * bFullScreen), iWinHeight, 0.0f, -1.0f, 1.0f);
		glViewport(0, 0, bFullScreen*(1920) + (iWinWidth*ac_iScale)*(!bFullScreen), bFullScreen*(1080) + (iWinHeight*ac_iScale)*(!bFullScreen)); //Set the viewport
		glMatrixMode(GL_MODELVIEW); //Set back to model view

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		glClear(GL_COLOR_BUFFER_BIT);
	}

	void UpdateWindowName(const char *szBuffer)
	{
		SDL_SetWindowTitle(sdlWindow, szBuffer);
	}

	void DrawBackground()
	{
		DrawSurface(glSurfaceBG, 0.0f, 0.0f);
	}

	void Draw_Rect(float x, float y, float w, float h, int r, int g, int b)
	{
		if (bFullScreen)x += 48;
		//if(boundTexture != NULL){
		glBindTexture(GL_TEXTURE_2D, NULL);// boundTexture = NULL; }
		//if(scale == 7.5)x += 48;

		glBegin(GL_QUADS);
		glColor3b(r, g, b);
		//Bottom-left vertex (corner)
		glVertex3f(x, y, 0.0f); //Vertex Coords

		//Bottom-right vertex (corner)
		glVertex3f(x + w, y, 0.f);

		//Top-right vertex (corner)
		glVertex3f(x + w, y + h, 0.f);

		//Top-left vertex (corner)
		glVertex3f(x, y + h, 0.f);

		glEnd();
	}
	void Draw_Line(float x1, float y1, float x2, float y2, int r, int g, int b)
	{
		if (bFullScreen) { x1 += 48; x2 += 48; }
		//if(boundTexture != NULL){
		glBindTexture(GL_TEXTURE_2D, NULL);// boundTexture = NULL; }
		//if(scale == 7.5)x1 += 48;

		glBegin(GL_LINES);
		glColor3b(r, g, b);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
		glEnd();
	}
	void Draw_Point(float x, float y, int r, int g, int b)
	{
		if (bFullScreen)x += 48;
		//if(boundTexture != NULL){
		glBindTexture(GL_TEXTURE_2D, NULL);// boundTexture = NULL; }
		//if(scale == 7.5)x += 48;

		glBegin(GL_POINTS);
		glColor3b(r, g, b);
		glVertex2f(x, y);
		glEnd();
	}
	void Draw_Circle(float x, float y, float R, int n, int r, int g, int b)
	{
		if (bFullScreen)x += 48;
		//if(boundTexture != NULL){
		glBindTexture(GL_TEXTURE_2D, NULL); //boundTexture = NULL; }
		//if(scale == 7.5)x += 48;

		glBegin(GL_LINE_LOOP);
		glColor3b(r, g, b);
		for (float i = 0; i < 2 * PI; i += (2 * PI) / n) {
			glVertex2f(x + cosf(i)*R, y + sinf(i)*R);
		}
		glEnd();
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
