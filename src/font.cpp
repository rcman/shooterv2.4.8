#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>
#include <cctype>
#include <cstdarg>

// STL
#include <vector>
#include <string>
#include <map>
#include <algorithm>

// SDL
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "font.h"
#include "main.h"


SDL_Surface *message = NULL;
SDL_Color HealthColor = { 130, 0, 0 };
int HEALTH = 300;

void editor_printf(int x, int y, unsigned int color, const char* format, ...)
{

       char textbuffer[0x100];
       va_list args;
       va_start(args, format);
       vsprintf(textbuffer, format, args);
       SDL_Color c;
       Uint8 r, g, b;
       SDL_GetRGB(color, screen->format, &r, &g, &b);
      //  fprintf (stderr, "Score now %d\n",Score);
       c.r = r;
       c.g = g;
       c.b = b;
       SDL_Surface* textsurface = TTF_RenderText_Solid(font, textbuffer, c);
       if (textsurface)
       {

        SDL_Rect dst;
        dst.x = x;
        dst.y = y;
        SDL_BlitSurface(textsurface, 0, screen, &dst);
        SDL_FreeSurface(textsurface);
       }

       va_end(args);
}


void drawrectangle()
{

    message = TTF_RenderText_Solid( font, "Health:", HealthColor );
    apply_surface( 300, 10, message, screen );


   SDL_FillRect(screen, &rect,SDL_MapRGB(screen->format, 130,0,0));


}
