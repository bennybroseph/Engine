#ifndef MAIN_LOOP_H_INCLUDED
#define MAIN_LOOP_H_INCLUDED

#include "Loop.h"

#include "Layer.h"
#include "../../Classes/Define.h"
#include "../../Engine/Graphics/Graphics.h"
#include <vector>

namespace TLoops{ class TMain_Loop_Class: public TLoop
{
    public:

        TMain_Loop_Class();
        ~TMain_Loop_Class();

        void OnKeyDown(SDL_Keycode, Uint16, SDL_Scancode);
        void OnKeyUp(SDL_Keycode, Uint16, SDL_Scancode);

        void OnMouseMove(int, int, int, int, bool, bool, bool);
        void OnLButtonDown(int, int);
        void OnLButtonUp(int, int);
        void OnRButtonDown(int, int);
        void OnResize(int, int);

        void Update();
        void Draw();
        void ReLoad_Textures();

    private:
        GLSurface Mover;
        GLSurface Switch_Layer;
        GLSurface Selector;
        GLSurface Checked;
        GLSurface Unchecked;
        GLSurface Box;

        std::vector<TLayer_Class*> Layer;

        int mouse_x ,mouse_y;
        int layer;
        bool all, lmouse_flag;
};
}

#endif // MAIN_LOOP_H_INCLUDED
