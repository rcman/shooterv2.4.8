/*This source code copyrighted by Lazy Foo' Productions (2004-2009) and may not
be redestributed without written permission.*/

//The headers
#ifdef WIN32
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "main.h"
#include "rmarks_api.h"
#else
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include "main.h"
#include "font.h"
#include "rmarks_api.h"
#endif

SDL_Color textColor = { 255, 255, 225 };
_TTF_Font *font = NULL;



void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

void clean_up()
{
    // free the memory we allocated in Gameinit()

    if (tileset) { SDL_FreeSurface(tileset); }

    // man
    if (man) { SDL_FreeSurface(man); }
     if (Numb) { SDL_FreeSurface(Numb); }

	keyboard_destroy(keyboard);

    // event is not an array, so we do not use the array-form of the delete operator:
    if (event) { delete event; }
    // Delete Player
       TTF_CloseFont( font );

}

int main( int argc, char* args[] )
{
    //Quit flag
    bool quit = false;
    int startticks = SDL_GetTicks();

    //Initialize
    if (!Gameinit())
    {
        return 1;
    }

    starsinit();

    //While the user hasn't quit
    while(!quit)
    {
        //While there's events to handle
        while( SDL_PollEvent( event ) )
        {
            //If the user has Xed out the window
            if( event->type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
		}

		// update our keyboard handler
		keyboard_update(keyboard);

		// start timing our code
		startticks = SDL_GetTicks();

		// check for our controls

		// ESC and Q quits
		if (keyboard->key[SDLK_ESCAPE] || keyboard->key[SDLK_q])
		{
			quit = true;
		}
        SDL_FillRect(screen, 0, 0);
     //   DrawMainMap();
        check_input();
        movebullets();
        collision2();
        checkmainshipcollision();
      drawenemies();
        movestars();
        moveplayer();
    //    testsine();
        animate_explosions();
        render_explosions();
        drawrectangle();
        editor_printf(10, 10, 255, "SCORE: %07d", Score);

		SDL_Flip(screen);
		// lock our framerate to roughly 30 FPS

    	// lock our framerate to roughly 30 FPS
    	int tickdiff = SDL_GetTicks() - startticks;
		if (tickdiff < 16)
		{
			SDL_Delay(16 - tickdiff);
		}


}

    //Free the images and quit SDL
    clean_up();

    return 0;
}
