#ifndef FPS_INCLUDED
#define FPS_INCLUDED

#include <ctime>
#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <SDL.h>

#include <iostream>

namespace FPS
{
    void Init(float,float);
    bool GFPS();
    void FPS_Cap();

    extern float Current_FPS;
    extern float Current_GFPS;
    extern float Delay;
}


#endif // FPS_INCLUDED
