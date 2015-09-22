//////////////////////////////////////////////////////////////
// File: EventHandler.h
// Author: Ben Odom
// Brief: You're not meant to create an object of this class
//		  This class is created to simply be inherited by 
//        'Loop'. By making all virtual, each object of 
//        'Loops' (or its children) can redefine what 
//        happens on that event
//////////////////////////////////////////////////////////////

#ifndef _EVENTHANDLER_H_
#define _EVENTHANDLER_H_

#include <SDL.h>

class EventHandler
{
public:
	//////Constructor - Destructor//////

	EventHandler();
	//This must be virtual if any member function is virtual
	virtual ~EventHandler();

	//////Functions//////

	//Takes in the event, and then calls the appropriate function
	virtual void OnEvent(SDL_Event* Event);

	//Deals with window focus (alt-tab)
	virtual void OnInputFocus();
	virtual void OnInputBlur();

	//Takes in sym (The enum naming the key) the mod (if any, like shift), and unicode (in case of typing)
	virtual void OnKeyDown(SDL_Keycode sym, Uint16 mod, SDL_Scancode scancode);
	virtual void OnKeyUp(SDL_Keycode sym, Uint16 mod, SDL_Scancode scancode);

	//Deals with window focus (clicking in and out)
	virtual void OnMouseFocus();
	virtual void OnMouseBlur();

	//Passes                mouse_x mouse_y x_velocity y_velocity  buttonL,  buttonR,      buttonM (scroll wheel)
	virtual void OnMouseMove(int mx, int my, int xvel, int yvel, bool left, bool right, bool middle);

	//Passes which way the mouse wheel is spun
	virtual void OnMouseWheel(bool up, bool down);

	//If mouse buttons down/up
	virtual void OnLButtonDown(int mx, int my);
	virtual void OnLButtonUp(int mx, int my);
	virtual void OnRButtonDown(int mx, int my);
	virtual void OnRButtonUp(int mx, int my);
	virtual void OnMButtonDown(int mx, int my);
	virtual void OnMButtonUp(int mx, int my);

	//Checks for joystick events, but there's an SDL_Joystick object which is much better
	virtual void OnJoyAxis(Uint8 which, Uint8 axis, Sint16 value);
	virtual void OnJoyButtonDown(Uint8 which, Uint8 button);
	virtual void OnJoyButtonUp(Uint8 which, Uint8 button);
	virtual void OnJoyHat(Uint8 which, Uint8 hat, Uint8 value);
	virtual void OnJoyBall(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel);

	//Minimize and maximize of window
	virtual void OnMinimize();
	virtual void OnRestore();

	//Window resizing, not sure how to do this
	virtual void OnResize(int w, int h);

	//No clue
	virtual void OnExpose();

	//Can be different for each class that defines it
	virtual void OnExit();

	//No clue
	virtual void OnUser(Uint8 type, int code, void* data1, void* data2);
};

//Renames EventHandler as EH
//With this, instead of doing EventHandler* handle = new EventHandler,
		//You can do EH* handle = new EH
typedef EventHandler EH;

#endif // _EVENTHANDLER_H_
