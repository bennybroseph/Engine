#include "Layer.h"

TLayer_Class::TLayer_Class(std::string tilemap_file,std::string image_file)
{
    name = tilemap_file;
    FILE* tilemap = fopen(tilemap_file.c_str(),"r");

    for(int i=0;i<COLLUM;i++)
    {
        for(int f=0;f<ROW;f++)
        {
            fscanf(tilemap,"%d:%d  ",&Tilemap[i][f].row,&Tilemap[i][f].collum);
        }
        fscanf(tilemap,"\n");
    }
    fclose(tilemap);

    Tiles = Graphics::Load_Image(image_file.c_str());
    On = Graphics::Load_Image("Images/On.png");
    Off = Graphics::Load_Image("Images/Off.png");
    Visible = On;

    on = true;
    selector_x = 0;selector_y = 0;
}

void TLayer_Class::Mouse_Click(float mouse_x,float mouse_y,int height)
{
    if(mouse_x <= 160){mouse_y = (mouse_y - height) + Tiles.h;}

    if(mouse_x < Tiles.w)
    {
        if(mouse_y < Tiles.h)
        {
            selector_x = ((int)(mouse_x/16))*16;
            selector_y = ((int)(mouse_y/16))*16;
        }
    }
    if (!frame_passed)
    {
        if((mouse_y > Tiles.h+48)&&(mouse_y < Tiles.h+64))
        {
            if((mouse_x > 72)&&(mouse_x < 88))
            {
                Move("Up");
            }
        }
        if((mouse_y > Tiles.h+64)&&(mouse_y < Tiles.h+80))
        {
            if((mouse_x > 72)&&(mouse_x < 88))
            {
                Move("Down");
            }
            if((mouse_x > 56)&&(mouse_x < 72))
            {
                Move("Left");
            }
            if((mouse_x > 88)&&(mouse_x < 104))
            {
                Move("Right");
            }
        }
        if(((mouse_x > 160)&&(mouse_x < 176))&&((mouse_y > 0)&&(mouse_y < 16)))
        {
            if(on)
            {
                on = false;
                Visible = Off;
            }
            else if(!on)
            {
                on = true;
                Visible = On;
            }
        }
    }
    if(mouse_x > 176)
    {
        Tilemap[(int)(mouse_y/16)][(int)(mouse_x/16)-11].row = ((int)(selector_y/16));
        Tilemap[(int)(mouse_y/16)][(int)(mouse_x/16)-11].collum = ((int)(selector_x/16));
    }
    frame_passed = true;
}
void TLayer_Class::Move(std::string type)
{
    int x = 0,y = 0;
    Tilemap_Struct temp[COLLUM][ROW];

    for(int i=0;i<COLLUM;i++)
    {
        for(int f=0;f<ROW;f++)
        {
            temp[i][f] = Tilemap[i][f];
        }
    }

    if(type == "Up"){y = 1;}
    if(type == "Down"){y = -1;}
    if(type == "Left"){x = 1;}
    if(type == "Right"){x = -1;}

    for(int i=0;i<COLLUM;i++)
    {
        for(int f=0;f<ROW;f++)
        {
            if(i+y > COLLUM-1){Tilemap[i][f] = temp[0][f];}
            else if(i+y < 0){Tilemap[i][f] = temp[COLLUM-1][f];}
            else if(f+x > ROW-1){Tilemap[i][f] = temp[i][0];}
            else if(f+x < 0){Tilemap[i][f] = temp[i][ROW-1];}
            else{Tilemap[i][f] = temp[i+y][f+x];}

        }
    }
}
void TLayer_Class::New(std::string filename,int collums,int rows)
{
    std::ofstream empty_map;
    empty_map.open(filename.c_str());

    for(int i=0;i<collums;i++)
    {
        for(int f=0;f<rows;f++)
        {
            empty_map << "0:9  ";
        }
        empty_map << "\n";
    }
    empty_map.close();
}
