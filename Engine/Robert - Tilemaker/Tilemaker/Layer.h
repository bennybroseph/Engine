#ifndef LAYER_INCLUDED
#define LAYER_INCLUDED

#include "../../Classes/Define.h"

class TLayer_Class
{
public:
    TLayer_Class(std::string,std::string);
    ~TLayer_Class();

    void Mouse_Click(float,float,int);
    void Move(std::string);
    void New(std::string,int,int);

    bool on, frame_passed;
    int selector_x,selector_y;

    std::string name;

    struct Tilemap_Struct
    {
        int row,collum;
    };

    Tilemap_Struct Tilemap[COLLUM][ROW];

    GLSurface Visible;
    GLSurface On;
    GLSurface Off;
    GLSurface Tiles;
};

#endif // LAYER_INCLUDED
