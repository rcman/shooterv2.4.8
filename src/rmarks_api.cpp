// rmarks_api.cpp
// Project: SDL Quick Start API
// Author: Richard Marks

// C STANDARD LIBRARY
#include <cstdio>
#include <cstdlib>

// SDL
#include <SDL/SDL.h>

// API
#include "rmarks_api.h"

Keyboard* keyboard = 0;

// creates a new instance of the keyboard handler structure
// make sure you call this AFTER you init SDL and only call it once
Keyboard* keyboard_create()
{
	Keyboard* keyboard = new Keyboard;

	keyboard->key = SDL_GetKeyState(&keyboard->keycount);

	keyboard->keywaspressed = new bool [keyboard->keycount];

	for (int index = 0; index < keyboard->keycount; index++)
	{
		keyboard->keywaspressed[index] = false;
	}

	return keyboard;
}

// updates the keyboard structure for us
void keyboard_update(Keyboard* keyboard)
{
	// bail out the function if the pointer is invalid
	if (!keyboard)
	{
		return;
	}

	SDL_PumpEvents();
	keyboard->key = SDL_GetKeyState(0);
}

// destroys the keyboard handler structure
void keyboard_destroy(Keyboard* keyboard)
{
	// bail out the function if the pointer is invalid
	if (!keyboard)
	{
		return;
	}

	// clear our tracking array
	if (keyboard->keywaspressed)
	{
		delete [] keyboard->keywaspressed;
	}

	// free the pointer
	delete keyboard;

	// init to zero to prevent logic errors
	keyboard = 0;
}


