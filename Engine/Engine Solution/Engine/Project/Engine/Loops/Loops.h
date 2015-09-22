#ifndef LOOPS_H_INCLUDED
#define LOOPS_H_INCLUDED

#include <SDL.h>
//#include <SDL_mixer.h>
#include <ctime>

#include "../Debug/Debug.h"
#include "../Sound/Sound.h"
#include "../Text/Text.h"
#include "../TextIn/TextIn.h"
#include "../Graphics/Graphics.h"
#include "../FPS/FPS.h"
#include "../../Classes/MainLoop.h"

/////////////////////////////////////////////////////////////////////////////
//Namespace Loops
/////////////////////////////////////////////////////////////////////////////
//Meant to contain all "while(running)" loops
//To use, create a member function called something appropriate, and
//      copy the shell loop into the function.
//Meant to work by calling functions of all other namespaces
//You should create a member function for each loop you would run
//  Ex: Loop for menu, then loop for single-player, loop for options, etc.
/////////////////////////////////////////////////////////////////////////////

namespace Loops
{
    class  Main_Loop_Class;

    extern Main_Loop_Class Main_Loop;

    //Inits all other namespaces of the engine
    void Setup();

    //The main draw loop, you will probably replace this when Loops is customized
    //  for your project

    //Calls the Quit() functions of all other namespaces and frees memory before program exit
    void Quit();
}

#endif // LOOPS_H_INCLUDED
