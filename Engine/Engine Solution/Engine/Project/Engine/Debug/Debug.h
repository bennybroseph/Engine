#ifndef DEBUG_H_INCLUDED
#define DEBUG_H_INCLUDED

#include <SDL.h>
#include <fstream>
#include <vector>

//#include "../Text/Text.h"

//////////////////////////////////////////////////////////////////////////////
//Namespace Debug
//////////////////////////////////////////////////////////////////////////////
//Outfiles any errors that occur
//Outfiles a log, showing tasks accomplished (landmarks throughout program)
//////////////////////////////////////////////////////////////////////////////

namespace Debug
{
    //////Enums//////
    enum Location
    {
        T_RIGHT,
        B_RIGHT,
        B_LEFT,
        T_LEFT
    };


    //////Functions//////

    //Initializes members of Debug and opens txt files
    void Init();

    //Writes the given text to "J_Log.txt"
    void Log(char*);

    //Writes the given text to "J_Err.txt"
    void Error(char*);

    //Adds the given data to the vectors
    void Data(std::string, int);

    //Draws the data stored in the vectors
    void DrawData(int);

    //Frees memory used by Debug, called at program exit
    void Quit();


    //////Data Structures//////

    //Stores the data Given by void Data(string, int)
    extern std::vector<std::string> vNames;
    extern std::vector<int> vNums;


    //////Member Variables//////

    //Each opens a txt file in Logs folder
    extern std::ofstream outlog;
    extern std::ofstream outerr;

    //Stores the square image used to tile the debug window background
    extern SDL_Surface* bg;
}

#endif // DEBUG_H_INCLUDED
