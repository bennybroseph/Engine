#ifndef NPC_H_INCLUDED
#define NPC_H_INCLUDED

#include "../Define.h"
#include "../Layer/Layer.h"
#include "../Sprite/Sprite_Class.h"

class NPC
{
    public:
        NPC(int,int);
        ~NPC();

        void Handle(Layer_Class*,float,float);
        void Move();
        void Timer();
        void Animate();
        bool Collision();
        void Draw(short);
        void Load_Textures();

        Layer_Class* Mask;

        Sprite_Class* Sprite;
        Sprite_Class* Head;

        int timer[2],x_speed[2],y_speed[2];
        float x,y,px,py;
        bool move_x,move_y,collision;
};

#endif // NPC_H_INCLUDED
