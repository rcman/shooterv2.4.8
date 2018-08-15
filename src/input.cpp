// input.cpp
// Project: Shooter Demo
// Author: Franco Gaetan, Richard Marks

// C STANDARD LIBRARY
#ifdef WIN32
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <cstdio>
#include <cstdlib>
#include "main.h"
#include "rmarks_api.h"
#else
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include <cstdio>
#include <cstdlib>
#include "main.h"
#include "rmarks_api.h"
#endif


void check_input()
{
	// if A key or LEFT arrow are down
	if (keyboard->key[SDLK_LEFT] || keyboard->key[SDLK_a])
	{
		player->x -= player->velx;
	}

	// if D key or RIGHT arrow are down
	if (keyboard->key[SDLK_RIGHT] || keyboard->key[SDLK_d])
	{
		player->x +=player->velx;
	}

	// if W key or UP arrow are down
	if (keyboard->key[SDLK_UP] || keyboard->key[SDLK_w])
	{
		player->y -=player->vely;
	}

	// if S key or DOWN arrow are down
	if (keyboard->key[SDLK_DOWN] || keyboard->key[SDLK_s])
	{
		player->y +=player->vely;
	}

	// if left CTRL key is down
	if (keyboard->key[SDLK_LCTRL])
	{
		if (++player->firingcounter >= player->firingdelay)
		{
			// play audio clip
			//if (!Mix_Playing(-1))

			if (Mix_PlayChannel(-1, shot1ogg, 0) < 0)
			{
				fprintf(stderr, "SDL_mixer Error: %s\n", Mix_GetError());
			}

			for (int i = 0; i < MAX_SHOTS; i++)
			{
				if (!savedshots[i].shotalive)
				{
					// Save the Shot Record what we need to
					savedshots[i].shotalive = true;
					if (++player->shotsfired >= MAX_SHOTS)
					{
						player->shotsfired = 0;
					}

					if (player->shotsfired % 2)
					{
						savedshots[i].x = player->x;
					}
					else
					{
						savedshots[i].x = player->x + manA[0].w - manA[1].w;
					}
					savedshots[i].y = player->y + manA[0].h / 2;
					break;
				}
			}

			for (int i = 0; i < MAX_SHOTS; i++)
			{
				if (!savedshotsbehind[i].shotalive)
				{
					// Save the Shot Record what we need to
					savedshotsbehind[i].shotalive = true;

					if (player->shotsfired % 2)
					{
						savedshotsbehind[i].x = player->x + manA[0].w - manA[1].w;
					}
					else
					{
						savedshotsbehind[i].x = player->x;
					}
					savedshotsbehind[i].y = player->y + manA[0].h / 2;
					break;
				}
			}
			player->firingcounter = 0;
		}
	}
}
