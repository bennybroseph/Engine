#include "Red.h"

Red_Class::Red_Class()
{
    Sprite = new Sprite_Class("Images/Red.png",0,3,0,3,16,160);
    Head = new Sprite_Class("Images/Red.png",0,3,0,3,16,8,160);
    Mask = new Layer_Class();

    timer = clock();

    x_speed[0] = 1;x_speed[1] = 10;
    y_speed[0] = 1;y_speed[1] = 10;
    x = 128;
    y = 208;
    Sprite->x = x;
    Sprite->y = y-4;
    Head->x = Sprite->x;
    Head->y = Sprite->y;
    move_x = false;
    move_y = false;
    up_flag = false;
    down_flag = false;
    left_flag = false;
    right_flag = false;
}
void Red_Class::Load_Textures()
{
    Sprite->Load_Textures("Images/Red.png");
    Head->Load_Textures("Images/Red.png");
}
void Red_Class::Handle(Layer_Class* Mask_temp, std::vector<NPC*>& NPC_temp)
{
   Mask = Mask_temp;
   NPCs = NPC_temp;
   Check_Keys();
   if(move_x||move_y){Move();}
   else{timer = clock();Collision_NPC();}
}
void Red_Class::Move()
{
    if((move_y)&&(clock() - timer >= y_speed[1]))
    {
        timer = clock();
        y += y_speed[0];
        move_x = false;
    }
    if((move_x)&&(clock() - timer >= x_speed[1]))
    {
        timer = clock();
        x += x_speed[0];
        move_y = false;
    }

    if(Collision())
    {
        if(move_x){x -= x_speed[0];}
        if(move_y){y -= y_speed[0];}
    }

    Sprite->Move(x,y-4);
    Head->Move(Sprite->x,Sprite->y);
}
bool Red_Class::Collision()
{
    if(Collision_Tilemap()||Collision_NPC())
    {
        return true;
    }

    return false;
}
bool Red_Class::Collision_Tilemap()
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

    return false;
}
bool Red_Class::Collision_NPC()
{
    short i;

    for(i=0;i<NPCs.size();i++)
    {
        if(((int)(NPCs[i]->x/16) == (int)x/16)&&((int)(NPCs[i]->y/16) == (int)y/16))
        {
            return true;
        }
        if(((int)(NPCs[i]->x/16) == (int)(x+15)/16)&&((int)(NPCs[i]->y/16) == (int)(y+15)/16))
        {
            return true;
        }
        if(((int)((NPCs[i]->x+15)/16) == (int)x/16)&&((int)((NPCs[i]->y+15)/16) == (int)y/16))
        {
            return true;
        }
        if(((int)((NPCs[i]->x+15)/16) == (int)(x+15)/16)&&((int)((NPCs[i]->y+15)/16) == (int)(y+15)/16))
        {
            return true;
        }
    }
    return false;
}
void Red_Class::Check_Keys()
{
    if(((up_flag||down_flag)&&(!left_flag&&!right_flag))&&(!move_x&&!move_y))
    {
        if(up_flag)
        {
            y_speed[0] = -abs(y_speed[0]);
            Sprite->Change("Collum",2,0,true,0,3);
            Head->Change("Collum",2,0,true,0,3);
        }
        if(down_flag)
        {
            y_speed[0] = abs(y_speed[0]);
            Sprite->Change("Collum",3,0,true,0,3);
            Head->Change("Collum",3,0,true,0,3);
        }
        move_y = true;
        move_x = false;
    }
    else if((int)(y/16) != (float)y/16)
    {
        move_y = true;
    }
    else if(((up_flag&&y_speed[0] == -abs(y_speed[0]))||(down_flag&&y_speed[0] == abs(y_speed[0])))&&(move_y&&!move_x))
    {
        move_y = true;
    }
    else
    {
        move_y = false;
    }

    if(((left_flag||right_flag)&&(!up_flag&&!down_flag))&&(!move_x&&!move_y))
    {
        if(left_flag)
        {
            x_speed[0] = -abs(x_speed[0]);
            Sprite->Change("Collum",0,0,true,0,1);
            Head->Change("Collum",0,0,true,0,1);
        }
        if(right_flag)
        {
            x_speed[0] = abs(x_speed[0]);
            Sprite->Change("Collum",1,0,true,0,1);
            Head->Change("Collum",1,0,true,0,1);
        }
        move_x = true;
        move_y = false;
    }
    else if((int)(x/16) != (float)x/16)
    {
        move_x = true;
    }
    else if(((left_flag&&x_speed[0] == -abs(x_speed[0]))||(right_flag&&x_speed[0] == abs(x_speed[0])))&&(move_x&&!move_y))
    {
        move_x = true;
    }
    else
    {
        move_x = false;
    }
}
void Red_Class::Key_Flag_Up(SDL_Keycode sym)
{
    switch(sym)
    {
        case SDLK_UP: up_flag = false;
        break;

        case SDLK_DOWN: down_flag = false;
        break;

        case SDLK_LEFT: left_flag = false;
        break;

        case SDLK_RIGHT: right_flag = false;
        break;

        default:
            break;
    }
}
void Red_Class::Key_Flag_Down(SDL_Keycode sym)
{
    switch(sym)
    {
        case SDLK_UP: up_flag = true;
        break;

        case SDLK_DOWN: down_flag = true;
        break;

        case SDLK_LEFT: left_flag = true;
        break;

        case SDLK_RIGHT: right_flag = true;
        break;

        default:
            break;
    }

}
void Red_Class::Draw(short n)
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
Red_Class::~Red_Class(){}
