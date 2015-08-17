#ifndef LOOP_H_INCLUDED
#define LOOP_H_INCLUDED

#include "../../Classes/Define.h"

/////////////////////////////////////////////////////////////////////////
//Class Loop
/////////////////////////////////////////////////////////////////////////
//Loop inherits the virtual event functions from EventHandler
/////////////////////////////////////////////////////////////////////////

namespace TLoops{ class TLoop: public EH
{
    public:
        ///////Constructor - Destructor//////
        TLoop();

        //Must be virtual if other functions are virtual
        virtual ~TLoop();

        //Contains a simple loop that runs the virtual event
        //Reason this is cool is because as each child of Loop redefines the event functions,
        //          it will call the redefined ones, so every child can use the same loop
        void Run();

        virtual void Update();

        //Redefined for each child, since they all draw different things
        virtual void Draw();


        //////Member Variables//////
        //Keeps the loop running
        bool running;

        //Stores events that happen during the loop
        SDL_Event event;
};
}

#endif // LOOP_H_INCLUDED
