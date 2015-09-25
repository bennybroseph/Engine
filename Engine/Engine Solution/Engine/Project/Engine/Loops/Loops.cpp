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

		HWND consoleWindow = GetConsoleWindow(); // Get the current console window
		SetWindowPos(consoleWindow, 0, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER); // Move it to the Top Left and don't change its size or 'z' order

		Graphics::Init(160, 144, 5, false);
		Text::Init();
		Debug::Init();
		FPS::Init(60);

		srand((unsigned)time(0));

		MainLoop oMainLoop;

		Debug::Log("Onto Main_Loop.Run()");
		oMainLoop.Run();
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

