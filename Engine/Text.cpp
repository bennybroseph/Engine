#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_opengl.h>

GLuint TextToTexture( TTF_Font* font, GLubyte r, GLubyte g, GLubyte b, const char* text, int ptsize )
{
    SDL_Color color = { r, g, b };
    SDL_Surface* msg = TTF_RenderText_Blended( font, text, color );

    // create new texture, with default filtering state (==mipmapping on)
    GLuint tex;
    glGenTextures( 1, &tex );
    glBindTexture( GL_TEXTURE_2D, tex );

    // disable mipmapping on the new texture
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, msg->w, msg->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, msg->pixels );

    SDL_FreeSurface( msg );
    return tex;
}

GLuint stringTex = 0;
void drawGLScene( int winWidth, int winHeight )
{
    glViewport(0, 0, winWidth, winHeight );

    glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective(45.0f, winWidth / (float)winHeight, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);

    // this is where the magic happens
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    glColor3ub( 255, 255, 255 );
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, stringTex );
    glBegin(GL_QUADS);
        glTexCoord2f( 0.0f, 0.0f ); glVertex2f( -1.0f, -1.0f );
        glTexCoord2f( 1.0f, 0.0f ); glVertex2f(  1.0f, -1.0f );
        glTexCoord2f( 1.0f, 1.0f ); glVertex2f(  1.0f,  1.0f );
        glTexCoord2f( 0.0f, 1.0f ); glVertex2f( -1.0f,  1.0f );
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

int main( int argc, char *argv[] )
{
    SDL_Init( SDL_INIT_EVERYTHING );
    //SDL_Surface* display = SDL_SetVideoMode( 640, 480, 32, SDL_OPENGL );
    SDL_Window* display = SDL_CreateWindow("Pokemon Red", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500,500,
                                  SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if( -1 == TTF_Init() )
        return -1;

    // http://unifoundry.com/unifont.html
    TTF_Font *font = TTF_OpenFont( "Fonts/Pokemon Retro.ttf", 8 );
    stringTex = TextToTexture( font, 200, 255, 255, "Hello!", 8 );

    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    bool running = true;
    while( running )
    {
        SDL_Event event;
        while( SDL_PollEvent( &event ) )
        {
            if( event.type == SDL_QUIT )
            {
                running = false;
                break;
            }
        }

        drawGLScene( 500, 500 );
        //SDL_GL_SwapBuffers();
        SDL_Delay( 16 );
    }

    TTF_CloseFont(font);

    TTF_Quit();
    SDL_Quit();
    return 0;
}
