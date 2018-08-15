// rmarks_api.h
// Project: SDL Quick Start API
// Author: Richard Marks

#ifndef __RMARKS_API_H__
#define __RMARKS_API_H__

// a useful keyboard handler structure to simplify SDL keyboard control
struct Keyboard
{
	// this holds the number of keys
	int keycount;

	// this holds the state of every key
	unsigned char* key;

	// this is used to create non-repeating key presses
	bool* keywaspressed;
};

extern Keyboard* keyboard;

// creates a new instance of the keyboard handler structure
// make sure you call this AFTER you init SDL and only call it once
extern Keyboard* keyboard_create();

// updates the keyboard structure for us
extern void keyboard_update(Keyboard* keyboard);

// destroys the keyboard handler structure
extern void keyboard_destroy(Keyboard* keyboard);

#endif







