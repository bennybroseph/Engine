#include "Debug.h"

namespace Debug
{
    std::ofstream outlog;
    std::ofstream outerr;

    std::vector<std::string> vNames;
    std::vector<int> vNums;

    SDL_Surface* bg;

    void Init()
    {
        outlog.open("Logs/D_Log.txt");
        outerr.open("Logs/D_Err.txt");
    }


    void Log(char* message)
    {
        outlog << SDL_GetTicks() << " -- " << message << std::endl;
    }

    void Error(char* message)
    {
        outerr << SDL_GetTicks() << " -- " << message << std::endl;
    }

    void Data(std::string str, int num)
    {
        vNames.push_back(str);
        vNums.push_back(num);
    }

//    void DrawData(int locn)
//    {
//        if(vNames.size() > 0)
//        {
//            int max_w = 0, pos_x = 0, pos_y = 0, y_offset = 0;
//            std::string total;
//            char buffer[33];
//
//            //Loop goes through vector to find the max width among the surfaces
//            for(int x = 0; x<vNames.size(); x++)
//            {
//                if(Text::GetSize(vNames[x], 12, vNums[x]).w > max_w)
//                {
//                    max_w = Text::GetSize(vNames[x], 12, vNums[x]).w;
//                }
//            }
//
//            switch(locn)
//            {
//                case T_RIGHT: pos_x = Graphics::win_width;
//                              pos_y = 0;
//                              y_offset = 0;
//                              break;
//
//                case T_LEFT: pos_x = max_w;
//                             pos_y = 0;
//                             y_offset = 0;
//                             break;
//
//                case B_RIGHT: pos_x = Graphics::win_width;
//                              pos_y = (Graphics::win_height - (vNames.size() * 15)) / bg->h;
//                              y_offset = Graphics::win_height - bg->h;
//                              break;
//
//                case B_LEFT: pos_x = max_w;
//                             pos_y = (Graphics::win_height - (vNames.size() * 15)) / bg->h;
//                             y_offset = Graphics::win_height - bg->h;
//                             break;
//
//                default: Debug::Log("Location not defined"); break;
//            }
//
//            //Draws the bg tile an amount corresponding to the max_w and the amount of data messages
//            /*for(int x = pos_y; x<=y_offset + (vNames.size() * 15) / bg->w; x++)
//            {
//                for(int y = 1; y<=max_w / bg->w + 1; y++)
//                {
//                    Graphics::Draw_Image(bg, pos_x - (bg->w*y), bg->w*x);
//                }
//            }*/
//            if((locn == B_RIGHT) || (locn == B_LEFT))
//            {
//                pos_y = pos_y * bg->h / 15 + 1;
//            }
//            int y = pos_y;
//            //Draws the data on top of the bg window created above
//            for(int x = 0; x<vNames.size(); x++)
//            {
//                total = vNames[x] + itoa(vNums[x], buffer, 10);
//                Text::Draw(total, 12, pos_x - max_w, y*15, Text::BLACK);
//                y++;
//            }
//
//            //Clear the vectors so the data can be reloaded
//            vNames.clear();
//            vNums.clear();
//        }
//    }

    void Quit()
    {
        outlog.close();
        outerr.close();
        SDL_FreeSurface(bg);
    }
}
