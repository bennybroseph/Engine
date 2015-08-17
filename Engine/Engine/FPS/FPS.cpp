#include "FPS.h"

namespace FPS
{
    float Delay = 0;
    float SpeedFactor = 0;

    float Current_FPS;
    float Current_GFPS;

    int FPS_Max;
    int GFPS_Max;

    int Old_Time = clock();
    int Old_GTime = clock();

    int Last_Frame = clock();
    int Last_GFrame = clock();

    short counter[2];

    void Init(float FPS_Max_Pass,float GFPS_Max_Pass)
    {
        FPS_Max = FPS_Max_Pass;
        GFPS_Max = GFPS_Max_Pass;
    }

    bool GFPS()
    {
        if(((clock() - Last_Frame) + Delay <= 1000/FPS_Max)&&((clock() - Last_GFrame) + Delay >= 1000/GFPS_Max))
        {
            if (clock() - Old_GTime >= 1000)
            {
                Current_GFPS = counter[1]+(((1000 + Old_GTime) - Last_GFrame)/(clock() - Last_GFrame))-1;
                Old_GTime = clock();

                counter[1] = 0;
            }
            else counter[1] ++;

            Last_GFrame = clock();
            return 1;
        }

        return 0;
    }

    void FPS_Cap()
    {
        if (clock() - Old_Time >= 1000)
        {
            Current_FPS = counter[0]+(((1000 + Old_Time) - Last_Frame)/(clock() - Last_Frame))-1;
            Old_Time = clock();

            counter[0] = 0;
        }
        else counter[0] ++;

        SpeedFactor = (clock() - Last_Frame)*FPS_Max;

        Delay += (1000/FPS_Max)-(SpeedFactor/FPS_Max);

        if(Delay < 0)Delay = 0;

        Last_Frame = clock();

        //std::cout << Current_FPS << "/" << Current_GFPS << std::endl;
    }
}

