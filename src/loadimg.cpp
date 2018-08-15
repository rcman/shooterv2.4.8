
#include "main.h"
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

bool load_files()
{
    //Load the tile set
    tileset = load_image("1945.bmp", 255, 0, 255);
    if (!tileset)
	{
		return false;
	}

    //If eveything loaded fine
    return true;
}

// 6 x 32
// 24 * 32
bool load_man()
{
    //Load the tile set
    man = load_image("1945.bmp", 0, 67, 171);
	if (!man)
	{
		return false;
	}

    //If eveything loaded fine
    return true;
}


bool LoadNum()
{

    Numb = load_image("bmp/image4.bmp", 0, 0, 0);
	if (!Numb)
	{
		return false;
	}

    //If eveything loaded fine
    return true;
}


SDL_Surface *load_image( const char* filename , unsigned char r, unsigned char g, unsigned char b)
{
    //The image that's loaded
    SDL_Surface* loadedImage = 0;

    //The optimized surface that will be used=
    SDL_Surface* optimizedImage = 0;

    //Load the image
    loadedImage = IMG_Load( filename );

    //If the image loaded
    if( loadedImage != 0 )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old surface
        SDL_FreeSurface( loadedImage );

        //If the surface was optimized
        if( optimizedImage != 0 )
        {
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, r, g, b ) );
        }
    }

    //Return the optimized surface
    return optimizedImage;
}

