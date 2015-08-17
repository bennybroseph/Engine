#include "NPC.h"
#include <iostream>

NPC::NPC(int pass_x, int pass_y)
{
    Sprite = new Sprite_Class("Images/Red.png",0,3,0,3,16,160);
    Head = new Sprite_Class("Images/Red.png",0,3,0,3,16,8,160);
    Mask = new Layer_Class();

    timer[0] = clock();
    timer[1] = clock();

    x_speed[0] = 1;x_speed[1] = 20;
    y_speed[0] = 1;y_speed[1] = 20;
    x = pass_x;
    y = pass_y;
    Sprite->x = x;
    Sprite->y = y-4;
    Head->x = Sprite->x;
    Head->y = Sprite->y;
    move_x = false;
    move_y = false;
}
void NPC::Load_Textures()
{
    Sprite->Load_Textures("Images/Red.png");
    Head->Load_Textures("Images/Red.png");
}
void NPC::Handle(Layer_Class* Mask_Temp, float temp_x, float temp_y)
{
   Mask = Mask_Temp;
   px = temp_x;py = temp_y;
   Timer();
   Move();
   Animate();
}
void NPC::Timer()
{
    if(clock() - timer[1] >= 2000)
    {
        short i = (rand()%4) + 1;

        switch(i)
        {
            case 1: move_x = true; move_y = false; x_speed[0] = abs(x_speed[0]);
                    Sprite->Change("Collum",1,0,true,0,1);
                    Head->Change("Collum",1,0,true,0,1);
            break;

            case 2: move_y = true; move_x = false; y_speed[0] = abs(y_speed[0]);
                    Sprite->Change("Collum",3,0,true,0,3);
                    Head->Change("Collum",3,0,true,0,3);
            break;

            case 3: move_x = true; move_y = false; x_speed[0] = -abs(x_speed[0]);
                    Sprite->Change("Collum",0,0,true,0,1);
                    Head->Change("Collum",0,0,true,0,1);
            break;

            case 4: move_y = true; move_x = false; y_speed[0] = -abs(y_speed[0]);
                    Sprite->Change("Collum",2,0,true,0,3);
                    Head->Change("Collum",2,0,true,0,3);
            break;

            default: break;
        }
        timer[1] = clock();
    }
    else
    {
        if(move_x||move_y)
        {
            if((int)(x/16) != (float)x/16)
            {
                move_x = true;
            }
            else if((int)(y/16) != (float)y/16)
            {
                move_y = true;
            }
            else
            {
                move_x = false;
                move_y = false;
            }
        }
    }
}
void NPC::Move()
{
    bool loop = false;

    if((move_x||move_y)&&(clock() - timer[0] >= x_speed[1])&&(clock() - timer[0] >= y_speed[1]))
    {
        do
        {
            if((move_y)&&(clock() - timer[0] >= y_speed[1]))
            {
                y += y_speed[0];
                move_x = false;
            }
            if((move_x)&&(clock() - timer[0] >= x_speed[1]))
            {
                x += x_speed[0];
                move_y = false;
            }

            if((clock() - timer[0] >= x_speed[1])&&(clock() - timer[0] >= y_speed[1]))
            {
                if((Collision()||collision)&&(move_x||move_y))
                {
                    if(move_x){x -= x_speed[0];x = ((int)(x/16))*16;}
                    if(move_y){y -= y_speed[0];y = ((int)(y/16))*16;}
                    timer[1] = clock() - 2000;
                    Timer();
                    loop = true;
                    collision = false;
                }
                else{loop = false;timer[0] = clock();}
            }
        }
        while(loop);
        Sprite->Move(x,y-4);
        Head->Move(Sprite->x,Sprite->y);
    }
}
bool NPC::Collision()
{
    int top_right,bot_left;

    top_right = Mask->Tilemap[(int)y/16][(int)x/16].collum;
    bot_left = Mask->Tilemap[(int)(y+15)/16][(int)(x+15)/16].collum;


    if(top_right == 0||top_right == 3 ||top_right == 4)
    {
        return true;
    }
    if(bot_left == 0||bot_left == 3||bot_left == 4)
    {
        return true;
    }
    if(((int)(px/16) == (int)x/16)&&((int)(py/16) == (int)y/16))
    {
        return true;
    }
    if(((int)(px/16) == (int)(x+15)/16)&&((int)(py/16) == (int)(y+15)/16))
    {
        return true;
    }
    if(((int)((px+15)/16) == (int)x/16)&&((int)((py+15)/16) == (int)y/16))
    {
        return true;
    }
    if(((int)((px+15)/16) == (int)(x+15)/16)&&((int)((py+15)/16) == (int)(y+15)/16))
    {
        return true;
    }

    return false;
}
void NPC::Animate()
{

}

void NPC::Draw(short n)
{
    if(n == 0)
    {
        if(((Sprite->a_row == 0)||(Sprite->a_row == 32))&&(!move_x&&!move_y)){Sprite->Freeze();}
        Sprite->Animate();
        Head->Change("Both",Sprite->a_row/Sprite->a_size,Sprite->a_collum/Sprite->a_size);
        Sprite->Draw();
    }
    if(n == 1)
    {
        Head->Draw();
    }
}

NPC::~NPC()
{

}
