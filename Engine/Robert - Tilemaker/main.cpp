#include "Tilemaker/Loops.h"

int main (int argc, char* argv [] )
{
    TLoops::Setup();
    Debug::Log("Onto Quit()");
    TLoops::Quit();
    Debug::Log("Exited successfully");

    return 0;
}
