//////////////////////////////////////////////////////////////
// File: FPS.h
// Author: Ben Odom
// Brief: Gets an accurate read on FPS based on the past 
//        'MAX_PREV_FPS' seconds of run time. More 
//        functionality could be added later on for 
//        multi-threading purposes.
//////////////////////////////////////////////////////////////

#ifndef _FPS_H_
#define _FPS_H_

#include "..\Text\Text.h"

#include <ctime>
#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <SDL.h>

#include <iostream>
#include <list>

namespace FPS
{
    void Init(const int ac_iMaxFPS);

	void Update();

	float GetFPS();
	void PrintFPS();

	void Quit();
}


#endif // _FPS_H_
