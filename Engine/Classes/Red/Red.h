#ifndef RED_INCLUDED
#define RED_INCLUDED

#include "../Define.h"
#include "../Layer/Layer.h"
#include "../Sprite/Sprite_Class.h"
#include "../NPC/NPC.h"

class Red_Class
{
public:
    Red_Class();
    ~Red_Class();

    void Handle(Layer_Class*,std::vector<NPC*>&);
    void Move();
    void Check_Keys();
    bool Collision();
    bool Collision_Tilemap();
    bool Collision_NPC();
    void Draw(short);
    void Load_Textures();

    void Key_Flag_Down(SDL_Keycode);
    void Key_Flag_Up(SDL_Keycode);

    Layer_Class* Mask;
    std::vector<NPC*> NPCs;

    Sprite_Class* Sprite;
    Sprite_Class* Head;

    int timer,x_speed[2],y_speed[2];
    float x,y;
    bool move_x,move_y;
    bool up_flag,down_flag,left_flag,right_flag;
};

#endif // RED_INCLUDED
