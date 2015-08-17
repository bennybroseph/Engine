#ifndef BATTLE_H_INCLUDED
#define BATTLE_H_INCLUDED

#include "../Define.h"
#include "../../Engine/Text/Text.h"
#include <vector>
#include <SDL.h>

class Pokemon_Class
{
    public:
        Pokemon_Class(short);
        ~Pokemon_Class();
        void Load_Textures(short);

        float max_health,current_health;
        int index,lvl,current_xp,xp_next,xp_gained,attack_num;

        struct stat_struct
        {
            float max,temp,stage,EV,DV;
        };

        stat_struct attack,defense,special_attack,special_defense;
        stat_struct speed,accuracy;

        std::string type1,type2;
        std::string nickname,name;

        struct attack_struct
        {
            int pp_max,pp_temp;
            std::string attack_name,type;
            short stat;
            int damage,accuracy;
        };
        attack_struct attacks[4];

        GLSurface Image;
};

namespace Battle_System
{
    void Init(std::vector<Pokemon_Class*>&,std::vector<Pokemon_Class*>&);
    void Handle();
    void Check_Keys();
    void Battle_Handle();
    void Battle_Frame(Pokemon_Class*,Pokemon_Class*);
    short Enemy_AI_Wild();
    void Key_Flag_Down(SDL_Keycode);
    void Key_Flag_Up(SDL_Keycode);
	void Draw();
	void Load_Textures();

	extern GLSurface HUD;
	extern GLSurface Menu_1;
	extern GLSurface Menu_2;
	extern GLSurface Text_Box;
	extern GLSurface Selector;
	extern GLSurface Info;
};


#endif // BATTLE_H_INCLUDED
