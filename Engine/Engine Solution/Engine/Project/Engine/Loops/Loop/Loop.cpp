#include "Loop.h"

namespace Loops{ Loop::Loop()
{
    running = true;
}

Loop::~Loop()
{
}

void Loop::Run()
{
    Debug::Log("Enter loop");
    char buffer[64];

    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            //Calls the redefined event function for the class
            OnEvent(&event);
        }
        Update();

        //Calls the redefined Draw function for the class
        Draw(); 
		Graphics::Flip();
		
		FPS::Update();
		FPS::GetFPS();
        //CPU saver
        //SDL_Delay(FPS::Delay);
        //FPS::FPS_Cap();
    }

    Debug::Log("Exit Loop");
}

//Empty because it is virtual
void Loop::Update()
{
}

//Empty because it is virtual
void Loop::Draw()
{
}
}
