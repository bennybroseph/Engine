#include "Battle.h"

Pokemon_Class::Pokemon_Class(short Index)
{
    switch(Index)
    {
        case 1: index = Index;
        max_health = 18;current_health = max_health;
        lvl = 5;
        current_xp = 0;xp_next = 100;xp_gained = 0;

        attack.DV = 1+rand()%10;attack.EV = 0;
        attack.max = (lvl*attack.DV)+2;attack.temp = attack.max;attack.stage = 0;

        defense.DV = 1+rand()%10;defense.EV = 0;
        defense.max = (lvl*defense.DV)+2;defense.temp = defense.max;defense.stage = 0;

        special_attack.DV = 1+rand()%10;special_attack.EV = 0;
        special_attack.max = (lvl*special_attack.DV)+2;special_attack.temp = special_attack.max;special_attack.stage = 0;

        special_defense.DV = 1+rand()%10;special_defense.EV = 0;
        special_defense.max = (lvl*special_defense.DV)+2;special_defense.temp = special_defense.max;special_defense.stage = 0;

        speed.DV = 1+rand()%10;speed.EV = 0;
        speed.max = (lvl*speed.DV)+2;speed.temp = speed.max;speed.stage = 0;

        accuracy.DV = 1+rand()%10;accuracy.EV = 0;
        accuracy.max = (lvl*accuracy.DV)+2;accuracy.temp = accuracy.max;accuracy.stage = 0;

        type1 = "Fire";type2 = "None";
        name = "CHARMANDER";nickname = "CHARMANDER";

        Image = Graphics::Load_Image("Images/Charmander.png");

        attack_num = 0;

//        ------------------------------------------------------
///            1 - Basic Physical Attack
///            2 - Basic Special Attack
///            3 - Lower Attack
///            4 - Lower Defense
///            5 - Lower Special Attack
///            6 - Lower Special Defense
//        ------------------------------------------------------

        attacks[0].attack_name = "SCRATCH";
        attacks[0].pp_max = 35;attacks[0].pp_temp = attacks[0].pp_max;
        attacks[0].type = "NORMAL";
        attacks[0].stat = 1;
        attacks[0].damage = 35;
        attacks[0].accuracy = 100;

        attacks[1].attack_name = "GROWL";
        attacks[1].pp_max = 40;attacks[1].pp_temp = attacks[1].pp_max;
        attacks[1].type = "NORMAL";
        attacks[1].stat = 3;
        attacks[1].damage = 1;
        attacks[1].accuracy = 100;

        attacks[2].attack_name = "-";
        attacks[3].attack_name = "-";

        break;

        case 4: index = Index;
        max_health = 12;current_health = max_health;
        lvl = 5;
        current_xp = 0;xp_next = 100;xp_gained = 0;

        attack.DV = 1+rand()%10;attack.EV = 0;
        attack.max = (lvl*attack.DV)+2;attack.temp = attack.max;attack.stage = 0;

        defense.DV = 1+rand()%10;defense.EV = 0;
        defense.max = (lvl*defense.DV)+2;defense.temp = defense.max;defense.stage = 0;

        special_attack.DV = 1+rand()%10;special_attack.EV = 0;
        special_attack.max = (lvl*special_attack.DV)+2;special_attack.temp = special_attack.max;special_attack.stage = 0;

        special_defense.DV = 1+rand()%10;special_defense.EV = 0;
        special_defense.max = (lvl*special_defense.DV)+2;special_defense.temp = special_defense.max;special_defense.stage = 0;

        speed.DV = 1+rand()%10;speed.EV = 0;
        speed.max = (lvl*speed.DV)+2;speed.temp = speed.max;speed.stage = 0;

        accuracy.DV = 1+rand()%10;accuracy.EV = 0;
        accuracy.max = (lvl*accuracy.DV)+2;accuracy.temp = accuracy.max;accuracy.stage = 0;

        type1 = "Water";type2 = "None";
        name = "SQUIRTLE";nickname = "SQUIRTLE";

        Image = Graphics::Load_Image("Images/Squirtle.png");

        attacks[0].attack_name = "TACKLE";
        attacks[0].pp_max = 35;attacks[0].pp_temp = attacks[0].pp_max;
        attacks[0].type = "NORMAL";
        attacks[0].stat = 1;
        attacks[0].damage = 35;
        attacks[0].accuracy = 100;

        attacks[1].attack_name = "TAIL-WHIP";
        attacks[1].pp_max = 40;attacks[1].pp_temp = attacks[1].pp_max;
        attacks[1].type = "NORMAL";
        attacks[1].stat = 4;
        attacks[1].damage = 0;
        attacks[1].accuracy = 100;

        attacks[2].attack_name = "-";attacks[2].stat = 0;
        attacks[3].attack_name = "-";attacks[3].stat = 0;

        break;

        default:
        break;
    }
}
void Pokemon_Class::Load_Textures(short Index)
{
    switch(Index)
    {
        case 1: Image = Graphics::Load_Image("Images/Charmander.png");
        break;

        case 4: Image = Graphics::Load_Image("Images/Squirtle.png");
        break;

        default:
        break;
    }
}

namespace Battle_System
{
    int x = 73, y = 112;
    short menu_num = 1, selection_num = 0, skip = 1,i;

    bool up_flag, down_flag, left_flag, right_flag;
    bool z_flag, x_flag, i_flag;
    bool first;

    char buffer[255];

    std::vector<Pokemon_Class*> Player;
	std::vector<Pokemon_Class*> Enemy;

    GLSurface HUD;
    GLSurface Menu_1;
    GLSurface Menu_2;
    GLSurface Text_Box;
    GLSurface Selector;
    GLSurface Info;

    void Init(std::vector<Pokemon_Class*>& Player_Pass,std::vector<Pokemon_Class*>& Enemy_Pass)
    {
        Load_Textures();

        Player = Player_Pass;
        Enemy = Enemy_Pass;

        for(i=0;i<3;i++)
        {
            if(Player[0]->attacks[i].attack_name != "-")Player[0]->attack_num++;
        }

        menu_num = 1;
    }

    void Handle()
    {
        Check_Keys();
        z_flag = false;
    }

    void Battle_Handle()
    {
        if(z_flag)
        {
            short enemy_selection_num; skip = 1;
            switch(menu_num)
            {
                case 3: first = false; if((Player[0]->speed.temp > Enemy[0]->speed.temp)||((Player[0]->speed.temp == Enemy[0]->speed.temp)&&(rand()%2)))first = true;

                    if(first)
                    {
                        Battle_Frame(Player[0],Enemy[0]);
                    }
                    else
                    {
                        enemy_selection_num = Enemy_AI_Wild();
                        Battle_Frame(Enemy[0],Player[0]);
                    }
                break;

                case 5:
                    if(Player[0]->current_health == 0)
                    {
                        sprintf_s(buffer,"%s has fainted!",Player[0]->nickname.c_str());
                        skip = 4;
                    }

                    else if(Enemy[0]->current_health == 0)
                    {
                        sprintf_s(buffer,"%s has fainted!",Enemy[0]->nickname.c_str());
                        skip = 4;
                    }

                    else if(first)
                    {
                        enemy_selection_num = Enemy_AI_Wild();
                        Battle_Frame(Enemy[0],Player[0]);
                    }
                    else
                    {
                        Battle_Frame(Player[0],Enemy[0]);
                    }
                break;

                case 7:
                    if(Player[0]->current_health == 0)
                    {
                        sprintf_s(buffer,"%s has fainted!",Player[0]->nickname.c_str());
                    }

                    else if(Enemy[0]->current_health == 0)
                    {
                        sprintf_s(buffer,"%s has fainted!",Enemy[0]->nickname.c_str());
                    }
                break;

                default: sprintf_s(buffer,"%s","Coming soon...");
                    break;
            }
            if(Player[0]->current_health < 0)Player[0]->current_health = 0;
            if(Enemy[0]->current_health < 0)Enemy[0]->current_health = 0;
        }
    }

    void Battle_Frame(Pokemon_Class* Main, Pokemon_Class* Other)
    {
        sprintf_s(buffer,"%s used %s.",Main->nickname.c_str(),Main->attacks[selection_num].attack_name.c_str());
        switch(Main->attacks[selection_num].stat)
        {
            case 1:
                Other->current_health -= (Main->attack.temp*(float(Main->attacks[selection_num].damage)/100));
                skip = 2;

            break;

            default: skip = 2;
                break;
        }
    }

    short Enemy_AI_Wild()
    {
        short AI_reduce[5] = {NULL, NULL, NULL, NULL, NULL},AI_attack[5] = {NULL, NULL, NULL, NULL, NULL};

        for(i=0;i<=3;i++)
        {
            if(Enemy[0]->attacks[i].stat > 2)
            {
                AI_reduce[4]++;AI_reduce[AI_reduce[4]] = i;
            }
            if((Enemy[0]->attacks[i].stat == 1)||(Enemy[0]->attacks[i].stat == 2))
            {
                AI_attack[4]++;AI_attack[AI_attack[4]] = i;
            }
        }

        if(Enemy[0]->current_health == Enemy[0]->max_health)
        {
            if(rand()%10 <= 8)
            {
                return AI_reduce[(rand()%AI_reduce[4]) +1];
            }
            else
            {
                return AI_attack[(rand()%AI_attack[4]) +1];
            }
        }
        else if (Player[0]->lvl > Enemy[0]->lvl)
        {
            if(rand()%10 <= 8)
            {
                return AI_attack[(rand()%AI_attack[4]) +1];
            }
            else
            {
                return AI_reduce[(rand()%AI_reduce[4]) +1];
            }
        }
        else
        {
            if(rand()%10 <= 9)
            {
                return AI_attack[(rand()%AI_attack[4]) +1];
            }
            else
            {
                return AI_reduce[(rand()%AI_reduce[4]) +1];
            }
        }
    }

    void Check_Keys()
    {
        if((up_flag)||(down_flag))
        {
            if(menu_num == 1)
            {
                if(y == 112){y = 128;}
                else if(y == 128){y = 112;}
                up_flag = false;down_flag = false;
            }
            if(menu_num == 2)
            {
                if(down_flag){selection_num++;}
                if(up_flag){selection_num--;}

                if(selection_num < 0){selection_num = Player[0]->attack_num-1;}
                else if(selection_num > Player[0]->attack_num-1){selection_num = 0;}

                up_flag = false;down_flag = false;
            }
        }
        if((left_flag)||(right_flag))
        {
            if(menu_num == 1)
            {
                if(x == 120){x = 73;}
                else if(x == 73){x = 120;}
                left_flag = false;right_flag = false;
            }
        }

        if(z_flag)
        {
            menu_num += skip;
            if(menu_num > 7)menu_num = 1;

            switch(menu_num)
            {
                case 1: x = 73;y = 112;Selector.rotation[2] = 0;
                break;

                case 2: x = 41;y = 104;Selector.rotation[2] = 0;
                break;

                default: x = 130;y = -150;Selector.rotation[2] = 90;
                    break;
            }
        }

        switch(menu_num)
        {
            case 1:
            break;

            case 2:
                switch(selection_num)
                {
                    case 0: y = 104;
                    break;

                    case 1: y = 112;
                    break;

                    case 2: y = 120;
                    break;

                    case 3: y = 128;
                    break;

                    default: Debug::Error("'selection_num' is equal to a number that is invalid and unexpected.");
                        break;
                }
            break;

            default: Battle_Handle();
                break;
        }
    }

    void Key_Flag_Down(SDL_Keycode sym)
    {
        switch(sym)
        {
            case SDLK_z: z_flag = true;
            break;

            case SDLK_x: x_flag = true;
            break;

            case SDLK_i: i_flag = true;
            break;

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

    void Key_Flag_Up(SDL_Keycode sym)
    {
        switch(sym)
        {
            case SDLK_i: i_flag = false;
            break;

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

    void Draw()
    {
        Graphics::Draw_Rect(96,74,48*(Player[0]->current_health/Player[0]->max_health),4,96/2,96/2,96/2);
        Graphics::Draw_Rect(32,18,48*(Enemy[0]->current_health/Enemy[0]->max_health),4,96/2,96/2,96/2);

        Graphics::Draw_Image(HUD,0,0);

        Text::Print(Text::Pokemon_Normal,80,63,false,Player[0]->nickname.c_str());

        Text::Print(Text::Pokemon_Normal,120,71,false,Player[0]->lvl);
        Text::Print(Text::Pokemon_Normal,120,87,false,Player[0]->max_health);
        Text::Print(Text::Pokemon_Normal,113,87,true,Player[0]->current_health);



        Text::Print(Text::Pokemon_Normal,8,8,false,Enemy[0]->nickname.c_str());
        Text::Print(Text::Pokemon_Normal,40,15,false,Enemy[0]->lvl);

        Graphics::Draw_Image(Player[0]->Image,6,36);
        Graphics::Draw_Image(Enemy[0]->Image,96,0);
        switch(menu_num)
        {
            case 1: Graphics::Draw_Image(Menu_1,0,0);
            break;

            case 2: Graphics::Draw_Image(Menu_2,0,0);

                    Text::Print(Text::Pokemon_Normal,48,111,false,Player[0]->attacks[0].attack_name.c_str());
                    Text::Print(Text::Pokemon_Normal,48,119,false,Player[0]->attacks[1].attack_name.c_str());
                    Text::Print(Text::Pokemon_Normal,48,127,false,Player[0]->attacks[2].attack_name.c_str());
                    Text::Print(Text::Pokemon_Normal,48,135,false,Player[0]->attacks[3].attack_name.c_str());

                    Text::Print(Text::Pokemon_Normal,16,87,false,Player[0]->attacks[selection_num].type.c_str());

                    Text::Print(Text::Pokemon_Normal,56,95,true,Player[0]->attacks[selection_num].pp_max);
                    Text::Print(Text::Pokemon_Normal,64,95,false,Player[0]->attacks[selection_num].pp_temp);
            break;

            default: Graphics::Draw_Image(Text_Box,0,0);
                     Text::Print(Text::Pokemon_Normal,10,117,false,buffer);
                break;
        }
        Graphics::Draw_Image(Selector,x,y);

        if(i_flag)
        {
            char temp[255];
            sprintf_s(temp,"%s",buffer);

            Graphics::Draw_Image(Info,0,0);
            sprintf_s(buffer,"Attack: %d / %d",int(Player[0]->attack.temp),int(Player[0]->attack.max));
            Text::Print(Text::Pokemon_Normal,10,15,false,buffer);
            sprintf_s(buffer,"Defense: %d / %d",int(Player[0]->defense.temp),int(Player[0]->defense.max));
            Text::Print(Text::Pokemon_Normal,10,24,false,buffer);
            sprintf_s(buffer,"Enemy HP: %d / %d",int(Enemy[0]->current_health),int(Enemy[0]->max_health));
            Text::Print(Text::Pokemon_Normal,10,33,false,buffer);

            sprintf_s(buffer,"%s",temp);
        }
    }

    void Load_Textures()
    {
        HUD = Graphics::Load_Image("Images/HUD.png");
        Menu_1 = Graphics::Load_Image("Images/Battle_1.png");
        Menu_2 = Graphics::Load_Image("Images/Battle_2.png");
        Text_Box = Graphics::Load_Image("Images/Text_Box.png");
        Selector = Graphics::Load_Image("Images/Selector.png");
        Info = Graphics::Load_Image("Images/Info_BG.png");
    }
}
