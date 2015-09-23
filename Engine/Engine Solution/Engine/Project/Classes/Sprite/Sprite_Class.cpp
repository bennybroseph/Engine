#include "Sprite_Class.h"

Sprite_Class::Sprite_Class(std::string filename,int start,int end,int row,int collum,int size,int collum_size,int speed)
{
    Load_Textures(filename);

    row_start = start*size;
    row_end = end*size;
    a_row = start*size;
    a_collum  = collum*size;
    a_size = size;
    c_size = collum_size;
    a_speed = speed;
    a_time = clock();
    x = 0;
    y = 0;
    reverse = false;
}
Sprite_Class::Sprite_Class(std::string filename,int start,int end,int row,int collum,int size,int speed)
{
    Load_Textures(filename);

    row_start = start*size;
    row_end = end*size;
    a_row = start*size;
    a_collum  = collum*size;
    a_size = size;
    c_size = size;
    a_speed = speed;
    a_time = clock();
    x = 0;
    y = 0;
    reverse = false;
    frozen = false;
}
void Sprite_Class::Load_Textures(std::string filename)
{
    Sprite = Graphics::LoadSurface(filename.c_str());
}
void Sprite_Class::Animate(std::string Type)
{
    if(!frozen)
    {
        if(Type == "Normal")
        {
            if(a_row > row_end){a_row = row_start;}
            if(clock() - a_time > a_speed)
            {
                a_row += a_size;
                if(a_row > row_end){a_row = row_start;}
                a_time = clock();
            }
        }
        if(Type == "Reverse")
        {
            if(clock() - a_time > a_speed)
            {
                if((a_row > row_start)&&(reverse)){a_row -= a_size;a_time = clock();}
                else if(reverse){reverse = false;}
                if((a_row < row_end)&&(!reverse)){a_row += a_size;a_time = clock();}
                else if(!reverse){reverse = true;}
            }
        }
    }
    else if(frozen){frozen = false;}
}
void Sprite_Class::Move(int new_x,int new_y)
{
    x = new_x;
    y = new_y;
}
void Sprite_Class::New(std::string new_file)
{
    Sprite = Graphics::LoadSurface(new_file.c_str());
}
void Sprite_Class::Change(std::string Type,int new_index,int new_index2,bool set_change,int start,int end)
{
    if(Type == "Both")
    {
        a_row = new_index*a_size;
        a_collum = new_index2*a_size;
    }
    if(Type == "Row")
    {
        a_row = new_index*a_size;
    }
    if(Type == "Collum")
    {
        a_collum = new_index*a_size;
    }
    if(set_change)
    {
        row_start = start*a_size;
        row_end = end*a_size;
    }
}
void Sprite_Class::Freeze()
{
    a_time = clock() - a_speed;
    frozen = true;
}
void Sprite_Class::Draw()
{
   Graphics::DrawSurface(Sprite,x-Camera::CameraControl.CameraX,y-Camera::CameraControl.CameraY,a_row,a_collum,abs(a_size),abs(c_size));
}
Sprite_Class::~Sprite_Class(){}
