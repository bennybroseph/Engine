#include "MainLoop.h"

const unsigned int CAMERA_OFFSET_X = 64; // Helps to make the 0, 0 position of the window far enough away from the player so that he appears centered on the screen
const unsigned int CAMERA_OFFSET_Y = 64; // Helps to make the 0, 0 position of the window far enough away from the player so that he appears centered on the screen

const unsigned int TILE_WIDTH = 16;  // Size of the tiles across
const unsigned int TILE_HEIGHT = 16; // Size of the tiles up and down

namespace Loops
{
	void MainLoop::Update()
	{
		m_oRed.Handle(m_voTileLayer[2], m_voNPC);
		Camera::CameraControl.SetCamera(m_oRed.x - CAMERA_OFFSET_X, m_oRed.y - CAMERA_OFFSET_Y);

		for (int i = 0; i < m_voNPC.size(); i++)
		{
			m_voNPC[i]->Handle(m_voTileLayer[2], m_oRed.x, m_oRed.y);
		}

		//Battle_System::Handle();
	}
	void MainLoop::Draw()
	{
		Graphics::DrawSurface(m_glSurfaceBG, 0, 0);

		for (int i = 0; i < m_voTileLayer.size() - 1; i++)
		{
			for (int j = Camera::CameraControl.CameraY / TILE_HEIGHT; j < (Camera::CameraControl.CameraY / TILE_HEIGHT) + 10; j++)
			{
				for (int k = Camera::CameraControl.CameraX / TILE_WIDTH; k < (Camera::CameraControl.CameraX / TILE_WIDTH) + 10; k++)
				{
					Graphics::DrawSurface(
						m_voTileLayer[i]->Tiles,
						(k * TILE_WIDTH) - Camera::CameraControl.CameraX,
						(j * TILE_HEIGHT) - Camera::CameraControl.CameraY,
						m_voTileLayer[i]->Tilemap[j][k].collum * TILE_HEIGHT,
						m_voTileLayer[i]->Tilemap[j][k].row * TILE_WIDTH,
						TILE_WIDTH,
						TILE_HEIGHT);
				}
			}
			if (i == 0)
			{
				m_voTileLayer[2]->Animate(
					(Camera::CameraControl.CameraY / TILE_HEIGHT) - 16,
					Camera::CameraControl.CameraX / TILE_WIDTH,
					(Camera::CameraControl.CameraY / TILE_HEIGHT) + 10,
					(Camera::CameraControl.CameraX / TILE_WIDTH) + 11);
			}
			m_oRed.Draw(i);
			for (int j = 0; j < m_voNPC.size(); j++)
			{
				m_voNPC[j]->Draw(i);
			}
		}

		//Battle_System::Draw();

		//Graphics::Draw_Image(Mouse_Image,cursor_x-15/2,cursor_y-15/2);
	}

	void MainLoop::OnKeyDown(SDL_Keycode a_eSym, Uint16 a_eMod, SDL_Scancode a_eScancode)
	{
		switch (a_eSym)
		{
		case SDLK_ESCAPE: running = false; break;

		case SDLK_F1: Graphics::Resize(1); break;
		case SDLK_F2: Graphics::Resize(2); break;
		case SDLK_F3: Graphics::Resize(3); break;
		case SDLK_F4: Graphics::Resize(4); break;
		case SDLK_F5: Graphics::Resize(5); break;
		case SDLK_F11: Graphics::ToggleFullScreen(); break;

		default:
		{
			Battle_System::Key_Flag_Down(a_eSym);
			m_oRed.Key_Flag_Down(a_eSym);
			break;
		}
		}
	}
	void MainLoop::OnKeyUp(SDL_Keycode a_eSym, Uint16 a_eMod, SDL_Scancode a_eScancode)
	{
		switch (a_eSym)
		{
		default: 
		{
			Battle_System::Key_Flag_Up(a_eSym);
			m_oRed.Key_Flag_Up(a_eSym);
			break;
		}
		}
	}

	void MainLoop::OnMouseMove(int a_iMouseX, int a_iMouseY, int a_iXVel, int a_iYVel, bool a_bIsLeft, bool a_bIsRight, bool a_bIsMiddle)
	{
		m_iMouseX += a_iXVel;
		m_iMouseY += a_iYVel;
	}
	void MainLoop::OnLButtonDown(int a_iMouseX, int a_iMouseY)
	{

	}
	void MainLoop::OnRButtonDown(int a_iMouseX, int a_iMouseY)
	{

	}

	void MainLoop::OnExit()
	{
		running = false;
	}

	MainLoop::MainLoop()
	{
		m_glSurfaceBG = Graphics::LoadSurface("Images/background.png");
		m_glSurfaceMouse = Graphics::LoadSurface("Images/cursor.png"); // Unused...

		Layer_Class* oTempLayer; // Temporary pointer for the new memory being created

		oTempLayer = new Layer_Class("Maps/Pallet_Town/background.txt", "Images/Overworld.png"); // Loads the background tile set
		m_voTileLayer.push_back(oTempLayer);

		oTempLayer = new Layer_Class("Maps/Pallet_Town/overworld.txt", "Images/Overworld_Original.png"); // Loads the foreground tile set
		m_voTileLayer.push_back(oTempLayer);

		oTempLayer = new Layer_Class("Maps/Pallet_Town/mask.txt", "Images/Masks.png"); // Loads the collision mask tile set
		m_voTileLayer.push_back(oTempLayer);

		NPC* oTempNPC; // Temporary pointer for the new memory being created
		oTempNPC = new NPC(128, 224);
		m_voNPC.push_back(oTempNPC);

		Pokemon_Class* oTempPokemon; // Temporary pointer for the new memory being created
		oTempPokemon = new Pokemon_Class(1);
		m_voRedPokemon.push_back(oTempPokemon);

		oTempPokemon = new Pokemon_Class(4);
		m_voEnemyPokemon.push_back(oTempPokemon);

		Battle_System::Init(m_voRedPokemon, m_voEnemyPokemon);

		m_iMouseX = 0;
		m_iMouseY = 0;
	}
	MainLoop::~MainLoop()
	{

	}
}
