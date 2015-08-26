#ifndef MAIN_LOOP_H_INCLUDED
#define MAIN_LOOP_H_INCLUDED

#include "../Engine/Loops/Loop/Loop.h"

#include "Layer/Layer.h"
#include "Red/Red.h"
#include "NPC/NPC.h"
#include "Battle/Battle.h"
#include "Define.h"
#include "../Engine/Graphics/Graphics.h"
#include <vector>

namespace Loops {
	class Main_Loop_Class : public Loop
	{
	public:

		Main_Loop_Class();
		~Main_Loop_Class();

		void OnKeyDown(SDL_Keycode, Uint16, SDL_Scancode);
		void OnKeyUp(SDL_Keycode, Uint16, SDL_Scancode);

		void OnMouseMove(int, int, int, int, bool, bool, bool);
		void OnLButtonDown(int, int);
		void OnRButtonDown(int, int);
		void OnResize(int, int);

		void Update();
		void Draw();
		void ReLoad_Textures();

	private:

		GLSurface Mouse_Image;
		GLSurface Background;

		std::vector<Layer_Class*> Layer;
		std::vector<Pokemon_Class*> Red_Pokemon;
		std::vector<Pokemon_Class*> Enemy_Pokemon;

		Red_Class Red;
		std::vector<NPC*> Dude;

		int cursor_x, cursor_y;
	};
}

#endif // MAIN_LOOP_H_INCLUDED
