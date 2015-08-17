#include "Loop.h"

namespace TLoops{ TLoop::TLoop()
{
    running = true;
}

TLoop::~TLoop()
{
}

void TLoop::Run()
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
        if(FPS::GFPS()){Draw(); Graphics::Flip();}
        //Draw(); Graphics::Flip();

        //sprintf(buffer,"%f:%f",);

        //std::cout << buffer << "\n";

        //CPU saver
        SDL_Delay(FPS::Delay);
        FPS::FPS_Cap();
    }

    Debug::Log("Exit Loop");
}

//Empty because it is virtual
void TLoop::Update()
{
}

//Empty because it is virtual
void TLoop::Draw()
{
}
}
