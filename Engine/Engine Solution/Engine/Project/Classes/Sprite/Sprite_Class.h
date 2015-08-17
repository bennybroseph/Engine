#ifndef SPRITE_CLASS_INCLUDED
#define SPRITE_CLASS_INCLUDED

#include "../Define.h"

class Sprite_Class
{
public:
    Sprite_Class(std::string,int,int,int,int,int,int,int);
    Sprite_Class(std::string,int,int,int,int,int,int);
    ~Sprite_Class();

    void Animate(std::string = "Normal");
    void Freeze();
    void New(std::string);
    void Change(std::string,int,int = 0,bool = false,int = 0,int = 0);
    void Move(int,int);
    void Draw();
    void Load_Textures(std::string);

    int row_start,row_end,a_row,a_collum,a_size,c_size,a_speed,a_time;
    int x,y;
    bool reverse,frozen;

    GLSurface Sprite;
};

#endif // SPRITE_CLASS_INCLUDED
