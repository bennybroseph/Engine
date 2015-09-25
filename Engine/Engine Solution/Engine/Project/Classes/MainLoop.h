//////////////////////////////////////////////////////////////
// File: MainLoop.h
// Author: Ben Odom
// Brief: Handles all of the game objects, and the tileset.
//        Basically works as a function caller/initializer
//        for the game loop.
//////////////////////////////////////////////////////////////

#ifndef _MAINLOOP_H_
#define _MAINLOOP_H_

#include "../Engine/Loops/Loop/Loop.h"
#include "Layer/Layer.h"
#include "Red/Red.h"
#include "NPC/NPC.h"
#include "Battle/Battle.h"
#include "Define.h"
#include "../Engine/Graphics/Graphics.h"

#include <vector>

namespace Loops 
{
	class MainLoop : public Loop
	{
	public:
		// Calls all the necessary functions
		void Update();
		// Calls the necessary draw functions for each of it's member objects
		void Draw();

		// Gets called automatically by the virtual function it inherits from. Handles what to do when a key is pressed down
		void OnKeyDown(SDL_Keycode a_eSym, Uint16 a_eMod, SDL_Scancode a_eScancode);
		// Gets called automatically by the virtual function it inherits from. Handles what to do when a key is released
		void OnKeyUp(SDL_Keycode a_eSym, Uint16 a_eMod, SDL_Scancode a_eScancode);

		// Currently unused functions
		void OnMouseMove(int a_iMouseX, int a_iMouseY, int a_iXVel, int a_iYVel, bool a_bIsLeft, bool a_bIsRight, bool a_bIsMiddle);
		void OnLButtonDown(int a_iMouseX, int a_iMouseY);
		void OnRButtonDown(int a_iMouseX, int a_iMouseY);

		void OnExit();

		MainLoop();
		~MainLoop();

	private:
		GLSurface m_glSurfaceMouse; // The mouse cursor's image file
		GLSurface m_glSurfaceBG; // The background color

		std::vector<Layer_Class*> m_voTileLayer; // Holds the tile set in each layer
		std::vector<Pokemon_Class*> m_voRedPokemon; // Holds the player's Pokemon
		std::vector<Pokemon_Class*> m_voEnemyPokemon; // Holds the current enemy's Pokemon

		Red_Class m_oRed; // The player character
		std::vector<NPC*> m_voNPC; // Holds the NPCs in the current area

		int m_iMouseX, m_iMouseY; // The current mouse x and y values
	};
}

#endif // _MAINLOOP_H_
