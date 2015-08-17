///////////////////////////////////////////////////////
//SDL Engine 1.0
///////////////////////////////////////////////////////
//Developed by Ben Privat
//Erik Istre "of Doom"
//Nick Clardy
//Tobey "Green Goblin" Osborne
//
//Spring 2009
//
//Edited and Upgraded to SDL 2.0/OpenGL by Ben Odom 
//////////////////////////////////////////////////////

#include "Engine/Loops/Loops.h"

int main(int argc, char *argv[])
{
    Loops::Setup();
    Debug::Log("Onto Quit()");
    Loops::Quit();
    Debug::Log("Exited successfully");

    return 0;

} //End of Main
