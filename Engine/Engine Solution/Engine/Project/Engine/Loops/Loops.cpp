#include "Loops.h"

namespace Loops
{
    void Setup()
    {
        //Inits all aspects of SDL and calls the appropriate SDL kill functions at exit
        SDL_Init(SDL_INIT_EVERYTHING);
        atexit(SDL_Quit);

		FILE* stream;
		freopen_s(&stream, "CON", "w", stdout);
		freopen_s(&stream, "CON", "w", stderr);

        Graphics::Init(160,144,3,false);
        Text::Init();
        Debug::Init();
        FPS::Init(120,40);

        srand((unsigned)time(0));

        Main_Loop_Class Main_Loop;

        Debug::Log("Onto Main_Loop.Run()");
        Main_Loop.Run();
    }

    void Quit()
    {
        Graphics::Quit();
        Debug::Log("Graphics::Quit() successful");
        Sound::Quit();
        Debug::Log("Sound::Quit() successful");
        Text::Quit();
        Debug::Log("Text::Quit() successful");
    }
}

