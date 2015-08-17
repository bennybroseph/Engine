#include "Main Loop.h"
#include <windows.h>

namespace Loops{ Main_Loop_Class::Main_Loop_Class()
{

    Background = Graphics::Load_Image("Images/background.png");
    Mouse_Image = Graphics::Load_Image("Images/cursor.png");

    Layer_Class* layer_temp;

    layer_temp = new Layer_Class("Maps/Pallet_Town/background.txt","Images/Overworld.png");
    Layer.push_back(layer_temp);
    layer_temp = new Layer_Class("Maps/Pallet_Town/overworld.txt","Images/Overworld.png");
    Layer.push_back(layer_temp);
    layer_temp = new Layer_Class("Maps/Pallet_Town/mask.txt","Images/Masks.png");
    Layer.push_back(layer_temp);

    NPC* NPC_temp;
    NPC_temp = new NPC(128,224);
    Dude.push_back(NPC_temp);
//    NPC_temp = new NPC(144,224);
//    Dude.push_back(NPC_temp);
//    NPC_temp = new NPC(160,224);
//    Dude.push_back(NPC_temp);
//    NPC_temp = new NPC(176,224);
//    Dude.push_back(NPC_temp);
//    NPC_temp = new NPC(128,240);
//    Dude.push_back(NPC_temp);
//    NPC_temp = new NPC(144,240);
//    Dude.push_back(NPC_temp);
//    NPC_temp = new NPC(160,240);
//    Dude.push_back(NPC_temp);

    Pokemon_Class* Pokemon_Temp;
    Pokemon_Temp = new Pokemon_Class(1);
    Red_Pokemon.push_back(Pokemon_Temp);

    Pokemon_Temp = new Pokemon_Class(4);
    Enemy_Pokemon.push_back(Pokemon_Temp);

    Battle_System::Init(Red_Pokemon,Enemy_Pokemon);

    cursor_x = 0;
    cursor_y = 0;
}

void Main_Loop_Class::ReLoad_Textures()
{
    Text::Quit();
    Text::Init();

    //Background = Graphics::Load_Image("Images/background.png");
    Mouse_Image = Graphics::Load_Image("Images/cursor.png");

    Layer[0]->Load_Textures("Images/Overworld.png");
    Layer[1]->Load_Textures("Images/Overworld.png");
    Layer[2]->Load_Textures("Images/Masks.png");

    Red.Load_Textures();
    for(int i=0;i<Dude.size();i++)
    {
        Dude[i]->Load_Textures();
    }

    Battle_System::Load_Textures();

    for(int i=0;i<Red_Pokemon.size();i++)
    {
        Red_Pokemon[i]->Load_Textures(Red_Pokemon[i]->index);
    }
    for(int i=0;i<Enemy_Pokemon.size();i++)
    {
        Enemy_Pokemon[i]->Load_Textures(Enemy_Pokemon[i]->index);
    }
}

void Main_Loop_Class::Update()
{
    Red.Handle(Layer[2],Dude);
    Camera::CameraControl.SetCamera(Red.x-64,Red.y-64);

    for(int i=0;i<Dude.size();i++)
    {
        Dude[i]->Handle(Layer[2],Red.x,Red.y);
    }

    //Battle_System::Handle();
}

void Main_Loop_Class::Draw()
{
    Graphics::Draw_Image(Background,-48,0);

    for(short n=0;n<Layer.size()-1;n++)
    {
        for(short i=Camera::CameraControl.CameraY/16;i<(Camera::CameraControl.CameraY/16)+10;i++)
        {
            for(short f=Camera::CameraControl.CameraX/16;f<(Camera::CameraControl.CameraX/16)+10;f++)
            {
                    Graphics::Draw_Image(Layer[n]->Tiles,(f*16)-Camera::CameraControl.CameraX,(i*16)-Camera::CameraControl.CameraY,Layer[n]->Tilemap[i][f].collum*16,Layer[n]->Tilemap[i][f].row*16,16,16);
            }
        }
        if(n==0){Layer[2]->Animate(Camera::CameraControl.CameraY/16-16,Camera::CameraControl.CameraX/16,(Camera::CameraControl.CameraY/16)+10,(Camera::CameraControl.CameraX/16)+11);}
        Red.Draw(n);
        for(int i=0;i<Dude.size();i++)
        {
            Dude[i]->Draw(n);
        }
    }

//    Battle_System::Draw();

    //Graphics::Draw_Image(Mouse_Image,cursor_x-15/2,cursor_y-15/2);
}

void Main_Loop_Class::OnKeyDown(SDL_Keycode sym, Uint16 mod, SDL_Scancode scancode)
{
    switch(sym)
    {
        case SDLK_ESCAPE: running = false;
        break;

        case SDLK_F1:
            Graphics::Resize(160,144, 1);
        break;
        case SDLK_F2:
            Graphics::Resize(160,144, 2);
        break;
        case SDLK_F3:
            Graphics::Resize(160,144, 3);
        break;
        case SDLK_F4:
            Graphics::Resize(160,144, 4);
        break;
        case SDLK_F11:
            Graphics::Resize(160,144, 1, true);Debug::Log("Full Screen Enabled");
        break;

        default: Battle_System::Key_Flag_Down(sym);Red.Key_Flag_Down(sym);
            break;
    }
}
void Main_Loop_Class::OnKeyUp(SDL_Keycode sym, Uint16 mod, SDL_Scancode scancode)
{
    switch(sym)
    {
        default: Battle_System::Key_Flag_Up(sym);Red.Key_Flag_Up(sym);
            break;
    }
}

void Main_Loop_Class::OnMouseMove(int mx, int my, int xvel, int yvel, bool left, bool right, bool middle)
{
    cursor_x += xvel;
    cursor_y += yvel;
}
void Main_Loop_Class::OnLButtonDown(int mx, int my)
{

}
void Main_Loop_Class::OnRButtonDown(int mx, int my)
{

}
void Main_Loop_Class::OnResize(int w, int h)
{
    Graphics::Resize(w,h);
}

Main_Loop_Class::~Main_Loop_Class()
{

}
}
