//////////////////////////////////////////////////////////////
// File: Debug.h
// Author: Ben Odom
// Brief: Holds a log file that can be appended to at run
//        time for debugging purposes. Has functionality to 
//        print the current program time in milliseconds
//////////////////////////////////////////////////////////////

#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <SDL.h>
#include <fstream>
#include <vector>

namespace Debug
{
    //////Functions//////

    //Initializes members of Debug and opens txt files
    void Init();

    //Writes the given text to "J_Log.txt"
    void Log(char*);
    //Writes the given text to "J_Err.txt"
    void Error(char*);

    //Frees memory used by Debug, called at program exit
    void Quit();
}

#endif // _DEBUG_H_
