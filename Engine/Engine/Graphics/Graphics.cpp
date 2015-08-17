#include "Graphics.h"

namespace Graphics
{
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_GLContext context;

    GLSurface Background;
    bool full_screen;

    int winH, winW;

    GLSurface Load_Image(std::string filename)
    {
        GLSurface Surface;
        SDL_Surface* image = NULL;

        image = IMG_Load(filename.c_str());
        if (image == NULL)
        {
            printf("SDL_Error: %s\n", SDL_GetError());
            return Surface;
        }

        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, image->format->BytesPerPixel, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);

        Surface.h = image->h;
        Surface.w = image->w;
        Surface.Surface = texture;

        SDL_FreeSurface(image);

        return Surface;
    }

    GLSurface Load_Image(SDL_Surface *image)
    {
        GLSurface Surface;

        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, image->format->BytesPerPixel, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);

        Surface.h = image->h;
        Surface.w = image->w;
        Surface.Surface = texture;

        SDL_FreeSurface(image);

        return Surface;
    }

    void Draw_Image(GLSurface Surface, float x, float y)
    {
        if(full_screen)x += 48;
        glColor3f(1.0f, 1.0f, 1.0f);

        glBindTexture(GL_TEXTURE_2D, Surface.Surface);
        glBegin( GL_QUADS );
            //Bottom-left vertex (corner)
            glColor3b(127,127,127);
            glTexCoord2i( 0, 0 ); //Position on texture to begin interpolation
            glVertex3f( x, y, 0.f ); //Vertex Coords

            //Bottom-right vertex (corner)
            glTexCoord2i( 1, 0 );
            glVertex3f( x+Surface.w, y, 0.f );

            //Top-right vertex (corner)
            glTexCoord2i( 1, 1 );
            glVertex3f( x+Surface.w, y+Surface.h, 0.f );

            //Top-left vertex (corner)
            glTexCoord2i( 0, 1 );
            glVertex3f( x, y+Surface.h, 0.f );
        glEnd();
    }

    void Draw_Image(GLSurface Surface, float x, float y, float dx, float dy, float w, float h)
    {
        if(full_screen)x += 48;
        glColor3f(1.0f, 1.0f, 1.0f);

        glBindTexture(GL_TEXTURE_2D, Surface.Surface);

        glBegin( GL_QUADS );
            //Bottom-left vertex (corner)
            glColor3b(127,127,127);
            glTexCoord2f( dx/Surface.w, dy/Surface.h ); //Position on texture to begin interpolation
            glVertex3f( x, y, 0.f ); //Vertex Coords

            //Bottom-right vertex (corner)
            glTexCoord2f( (dx/Surface.w)+(w/Surface.w), dy/Surface.h );
            glVertex3f( x+w, y, 0.f );

            //Top-right vertex (corner)
            glTexCoord2f( (dx/Surface.w)+(w/Surface.w), (dy/Surface.h)+(h/Surface.h) );
            glVertex3f( x+w, y+h, 0.f );

            //Top-left vertex (corner)
            glTexCoord2f( dx/Surface.w, (dy/Surface.h)+(h/Surface.h) );
            glVertex3f( x, y+h, 0.f );
        glEnd();

    }

    bool Init(int w, int h, int scale, bool is_full_screen)
    {
        winW = w;
        winH = h;
        full_screen = is_full_screen;

        Background = Graphics::Load_Image("Images/background.png");

        if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        {
            printf("SDL_Error: %s\n", SDL_GetError());
            return 0;
        }

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        window = SDL_CreateWindow("Pokemon Red", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, full_screen*(1920) + (w*scale)*(!full_screen), full_screen*(1080) + (h*scale)*(!full_screen),
                                  SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

		if (window == NULL)
        {
			printf("SDL_Error: %s\n", SDL_GetError());
            return 0;
		}

		context = SDL_GL_CreateContext(window);

		glEnable(GL_TEXTURE_2D);

		glOrtho(0.0f, w + (96 * full_screen), h, 0.0f, -1.0f, 1.0f);

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glMatrixMode( GL_MODELVIEW ); //Set back to model view

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Resize(int w, int h, int scale, bool is_full_screen)
    {
        winW = w;
        winH = h;
        full_screen = is_full_screen;


        SDL_SetWindowSize(window, full_screen*(1920) + (w*scale)*(!full_screen), full_screen*(1080) + (h*scale)*(!full_screen));
        SDL_SetWindowPosition(window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);

        context = SDL_GetWindowSurface(window);

		glLoadIdentity();
		glOrtho(0.0f, w + (96 * full_screen), h, 0.0f, -1.0f, 1.0f);
		glViewport( 0, 0, full_screen*(1920) + (w*scale)*(!full_screen), full_screen*(1080) + (h*scale)*(!full_screen)); //Set the viewport
		glMatrixMode( GL_MODELVIEW ); //Set back to model view

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Update_Window_Name(char buffer[])
    {
        SDL_SetWindowTitle(window, buffer);
    }

    void Draw_Background()
    {
        //short x = 0;
        //if(!full_screen) x -= 48;

        Draw_Image(Background,0,0);
    }

     void Draw_Rect(float x, float y, float w, float h, int r, int g, int b)
     {
        if(full_screen)x += 48;
        //if(boundTexture != NULL){
        glBindTexture( GL_TEXTURE_2D, NULL );// boundTexture = NULL; }
        //if(scale == 7.5)x += 48;

        glBegin(GL_QUADS);
            glColor3b(r,g,b);
            //Bottom-left vertex (corner)
            glVertex3f( x, y, 0.0f ); //Vertex Coords

            //Bottom-right vertex (corner)
            glVertex3f( x+w, y, 0.f );

            //Top-right vertex (corner)
            glVertex3f( x+w, y+h, 0.f );

            //Top-left vertex (corner)
            glVertex3f( x, y+h, 0.f );

        glEnd();
    }

    void Draw_Line(float x1, float y1, float x2, float y2, int r, int g, int b)
    {
        if(full_screen){x1 += 48;x2 += 48;}
        //if(boundTexture != NULL){
        glBindTexture( GL_TEXTURE_2D, NULL );// boundTexture = NULL; }
        //if(scale == 7.5)x1 += 48;

        glBegin(GL_LINES);
            glColor3b(r,g,b);
            glVertex2f( x1, y1);
            glVertex2f( x2, y2);
        glEnd();
    }

    void Draw_Point(float x, float y, int r, int g, int b)
    {
        if(full_screen)x += 48;
        //if(boundTexture != NULL){
        glBindTexture( GL_TEXTURE_2D, NULL );// boundTexture = NULL; }
        //if(scale == 7.5)x += 48;

        glBegin(GL_POINTS);
            glColor3b(r,g,b);
            glVertex2f( x, y);
        glEnd();
    }

    void Draw_Circle(float x, float y, float R, int n, int r, int g, int b)
    {
        if(full_screen)x += 48;
        //if(boundTexture != NULL){
        glBindTexture( GL_TEXTURE_2D, NULL ); //boundTexture = NULL; }
        //if(scale == 7.5)x += 48;

        glBegin(GL_LINE_LOOP);
            glColor3b(r,g,b);
        for(float i = 0; i < 2*PI; i+= (2*PI)/n){
            glVertex2f(x+cosf(i)*R, y+sinf(i)*R);
        }
        glEnd();
    }

    void Flip()
    {
        SDL_GL_SwapWindow(window);
    }

    void Quit()
    {
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
}
