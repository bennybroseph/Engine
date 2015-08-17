#include "Main Loop.h"

namespace TLoops{ TMain_Loop_Class::TMain_Loop_Class()
{
    Mover = Graphics::Load_Image("Images/Mover.png");
    Switch_Layer = Graphics::Load_Image("Images/Layer Switch.png");
    Selector = Graphics::Load_Image("Images/Selector.png");
    Unchecked = Graphics::Load_Image("Images/Check_Box.png");
    Checked = Graphics::Load_Image("Images/Checked_Box.png");
    Box = Unchecked;

    layer = 1;
    mouse_x = 0,mouse_y = 0;
    all = false;
    lmouse_flag = false;

    std::ifstream layers;
    int layer_size;
    TLayer_Class* temp;

    layers.open("layers.txt");
    layers >> layer_size;

    std::string files[layer_size];
    std::string image[layer_size];
    for(int i=0;i<layer_size;i++)
    {
        layers >> files[i] >> image[i];
        temp = new TLayer_Class(files[i],image[i]);
        Layer.push_back(temp);
    }
    layers.close();
}

void TMain_Loop_Class::ReLoad_Textures()
{

}

void TMain_Loop_Class::Update()
{
    if(lmouse_flag)
    {
        if(all)
        {
            for(short n=0;n<Layer.size();n++)
            {
                Layer[n]->Mouse_Click(mouse_x,mouse_y,Layer[layer-1]->Tiles.h);
            }
        }
        else{Layer[layer-1]->Mouse_Click(mouse_x,mouse_y,Layer[layer-1]->Tiles.h);}
    }
    else
    {
        for(short n=0;n<Layer.size();n++)
        {
            Layer[n]->frame_passed = false;
        }
    }
}

void TMain_Loop_Class::Draw()
{
    char buffer[64];

    Graphics::Draw_Background();
    Graphics::Draw_Image(Layer[layer-1]->Visible,160,0);
    Graphics::Draw_Image(Mover,56,Layer[layer-1]->Tiles.h+48);
    Graphics::Draw_Image(Box,0,Layer[layer-1]->Tiles.h+80);
    //Text::Print(Text,16,Layer[layer-1]->Tiles.h+82);
    Graphics::Draw_Image(Layer[layer-1]->Tiles,0,0);
    Graphics::Draw_Image(Switch_Layer,0,Layer[layer-1]->Tiles.h+16);
    Graphics::Draw_Image(Selector,Layer[layer-1]->selector_x,Layer[layer-1]->selector_y);

    for(int l=0;l<Layer.size();l++)
    {
        if(Layer[l]->on)
        {
            for(short i=0;i<COLLUM;i++)
            {
                for(short f=0;f<ROW;f++)
                {
                    Graphics::Draw_Image(Layer[l]->Tiles,(f*16)+176,(i*16),Layer[l]->Tilemap[i][f].collum*16,Layer[l]->Tilemap[i][f].row*16,16,16);
                }
            }
        }
    }
    if (all)
    {
        sprintf(buffer,"Tilemaker - ALL");
    }
    else sprintf(buffer,"Tilemaker - %s",Layer[layer-1]->name.c_str());
    Graphics::Update_Window_Name(buffer);
}

void TMain_Loop_Class::OnKeyDown(SDL_Keycode sym, Uint16 mod, SDL_Scancode scancode)
{
    switch(sym)
    {
        case SDLK_ESCAPE: running = false;
            break;

        case SDLK_UP: if(Layer[layer-1]->selector_y > 0){Layer[layer-1]->selector_y -= 16;}
            break;
        case SDLK_DOWN: if(Layer[layer-1]->selector_y < Layer[layer-1]->Tiles.h-16){Layer[layer-1]->selector_y += 16;}
            break;

        case SDLK_LEFT: if(Layer[layer-1]->selector_x > 0){Layer[layer-1]->selector_x -= 16;}
            break;

        case SDLK_RIGHT: if(Layer[layer-1]->selector_x < Layer[layer-1]->Tiles.w-16){Layer[layer-1]->selector_x += 16;}
            break;

        case SDLK_F1:
            Graphics::Resize(656,576, 1);
            break;
        case SDLK_F2:
            Graphics::Resize(656,576, 2);
            break;
        case SDLK_F3:
            Graphics::Resize(656,576, 3);
            break;
        case SDLK_F4:
            Graphics::Resize(656,576, 4);
            break;
        case SDLK_F11:
            Graphics::Resize(656,576, 1, true);
            break;

        default:
            break;
    }
}
void TMain_Loop_Class::OnKeyUp(SDL_Keycode sym, Uint16 mod, SDL_Scancode scancode)
{

}

void TMain_Loop_Class::OnMouseMove(int mx, int my, int xvel, int yvel, bool left, bool right, bool middle)
{
    mouse_x = xvel;
    mouse_y = yvel;

    mouse_x = mx;
    mouse_y = my;
}
void TMain_Loop_Class::OnLButtonDown(int mx, int my)
{
    mouse_x = mx;
    mouse_y = my;

    lmouse_flag = true;

    if((mouse_x < 160)&&((mouse_y > Layer[layer-1]->Tiles.h+16)&&(mouse_y < Layer[layer-1]->Tiles.h+48)))
    {
        if(mouse_y < 224)
        {
            layer++;
            if (layer > Layer.size()){layer = 1;}
        }
    }
    else if((mouse_x < 16)&&((mouse_y > Layer[layer-1]->Tiles.h+80)&&(mouse_y < Layer[layer-1]->Tiles.h+96)))
    {
        if(all)
        {
            all = false;
            Box = Unchecked;
        }
        else if(!all)
        {
            all = true;
            Box = Checked;
        }
    }
}
void TMain_Loop_Class::OnLButtonUp(int mx, int my)
{
    mouse_x = mx;
    mouse_y = my;

    lmouse_flag = false;
}
void TMain_Loop_Class::OnRButtonDown(int mx, int my)
{

}
void TMain_Loop_Class::OnResize(int w, int h)
{
    Graphics::Resize(w,h);
}

TMain_Loop_Class::~TMain_Loop_Class()
{
    std::ifstream layers;
    int layer_size;

    layers.open("layers.txt");
    layers >> layer_size;

    std::string files[layer_size];
    std::string dummy[layer_size];
    for(int i=0;i<layer_size;i++)
    {
        layers >> files[i] >> dummy[i];
    }
    layers.close();

    std::ofstream create_map;
    for(int l=0;l<layer_size;l++)
    {
        create_map.open(files[l].c_str());
        for(int i=0;i<COLLUM;i++)
            {
                for(int f=0;f<ROW;f++)
                {
                    create_map << Layer[l]->Tilemap[i][f].row << ":" << Layer[l]->Tilemap[i][f].collum << "  ";
                }
                create_map << "\n";
            }
        create_map.close();
    }
}}
