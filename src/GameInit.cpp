#ifdef WIN32
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "rmarks_api.h"
#include "main.h"
#else
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include "rmarks_api.h"
#include "main.h"
#endif

SDL_Surface* screen = 0;
SDL_Surface* tileset = 0;

SDL_Surface* man = 0;
SDL_Rect* manA;

SDL_Surface* enemy = 0;
SDL_Rect* enemy1;

MyPlayer* player = 0;
Shipshots* shots = 0;
enemymotion* enemy_sine = 0;

SDL_Event* 	event = 0;
Mix_Chunk* shot1ogg = 0;
Mix_Chunk* shot2ogg = 0;

SDL_Surface* Numb = 0;
SDL_Rect* num;
    // int explosionstartx = 2 * 32;
    // int explosionstarty = 5 * 32;
int explosionstartx = 70;
int explosionstarty = 169;
int explosiondiff = 33;


Shipshots savedshots[MAX_SHOTS];
ShipshotsBehind savedshotsbehind[MAX_SHOTS];

Enemyspots savedenemy[MAX_ENEMIES];
EnemyExplosion savedexplosion[MAX_ENEMIES];
Stars savedstars[MAX_STARS];


//The event structure

bool Gameinit()
{
    // initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }
    atexit(SDL_Quit);

    // set up the screen
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_DOUBLEBUF);

	// create our keyboard handler
	keyboard = keyboard_create();

    // if there was an error in setting up the screen
    if (!screen)
    {
        return false;
    }

    if (!init_player()){ return false; };
    if (!init_enemy()){ return false; };
//    if (!TTF_Init()){ return false; };

     //Initialize SDL_ttf ***************************************************************************************

   if (TTF_Init() == -1)
	{
		fprintf(stderr, "Unable to initialize SDL_TTF!\nSDL_TTF Error: %s\n", TTF_GetError());
		return false;
	}

	font = TTF_OpenFont("bmp/BoomBox.ttf", 24);

	if (!font)
	{
		fprintf(stderr, "Unable to load \"georgia.TTF\"!\nSDL_TTF Error: %s\n", TTF_GetError());
		return false;
	}


    // init SDL_mixer

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 1, 4096))
	{
		fprintf(stderr, "SDL_Mixer Error: %s\n", Mix_GetError());
		exit(1);
	}
    Mix_AllocateChannels(64);
	// load resources

	shot1ogg = Mix_LoadWAV("snd/laser.wav");

	if (!shot1ogg)
	{
		fprintf(stderr, "SDL_mixer Error: %s\n", Mix_GetError());
	}

	shot2ogg = Mix_LoadWAV("snd/expl.wav");

	if (!shot2ogg)
	{
		fprintf(stderr, "SDL_mixer Error: %s\n", Mix_GetError());
	}

	if (!shot1ogg || !shot2ogg)
	{
		fprintf(stderr, "unable to load resources!\n");
		exit(1);
	}



    //Set the window caption
    SDL_WM_SetCaption( "Franco Gaetan's Shooter Game Demo ", 0 );

    // create the sdl event
    event = new SDL_Event;
    num = new SDL_Rect[11];

    // load the files
    if (!load_files())
    {
        return false;
    }

    // load man files
    if (!load_man())
    {
        return false;
    }

   if (!LoadNum())
    {
    return false;
    }


// Init Enemy Start for now

    enemy_sine->spx = 0;
    enemy_sine->spy = 400;
     enemy_sine->currentenemytime = 0;
     enemy_sine->enemydelay = 2;
     enemy_sine->enemycounter = 0;


    num[0].x = 0;        // this is going to load my Numbers
    num[0].y = 0;
    num[0].w = 16;
    num[0].h = 16;

    num[1].x = 16 * 1;
    num[1].y = 0;
    num[1].w = 16;
    num[1].h = 16;

    num[2].x = 16 * 2;
    num[2].y = 0;
    num[2].w = 16;
    num[2].h = 16;

    num[3].x = 16 * 3;
    num[3].y = 0;
    num[3].w = 16;
    num[3].h = 16;

    num[4].x = 16 * 4;
    num[4].y = 0;
    num[4].w = 16;
    num[4].h = 16;

    num[5].x = 16 * 5;
    num[5].y = 0;
    num[5].w = 16;
    num[5].h = 16;

    num[6].x = 16 * 6;
    num[6].y = 0;
    num[6].w = 16;
    num[6].h = 16;

    num[7].x = 16 * 7;
    num[7].y = 0;
    num[7].w = 16;
    num[7].h = 16;

    num[8].x = 16 * 8;
    num[8].y = 0;
    num[8].w = 16;
    num[8].h = 16;

    num[9].x = 16 * 9;
    num[9].y = 0;
    num[9].w = 16;
    num[9].h = 16;



    int i;



    for (i=0;i<MAX_SHOTS;i++)
    {
        savedshots[i].shotalive = false;
        savedshots[i].vely = 0;
        savedshots[i].x = 0;
        savedshots[i].velx = 0;
        savedshots[i].y = 0;
        savedshots[i].w = 16;;
        savedshots[i].h = 32;
        savedshotsbehind[i].h = 32;
        savedshotsbehind[i].w = 16;
        savedshotsbehind[i].y = 0;
        savedshotsbehind[i].velx = 0;
        savedshotsbehind[i].x = 0;
        savedshotsbehind[i].shotalive = false;
        savedshotsbehind[i].vely = 0;

    }

    for (i=0;i<MAX_ENEMIES;i++)
    {
        savedenemy[i].x = 10 + rand() % (1020 - 10 );
        savedenemy[i].y = 10 + rand() % (760 - 10 );
        savedenemy[i].h = 32;
        savedenemy[i].w = 32;
        savedenemy[i].velx = 0;
        savedenemy[i].vely = 0;
        savedenemy[i].enemyalive = true;
        savedenemy[i].collisiondetected = false;
        savedenemy[i].animnumber = 0;



};

for (i=0;i<MAX_ENEMIES;i++)
    {
        savedexplosion[i].x = 0;
        savedexplosion[i].y = 0;
        savedexplosion[i].animnumber = 1;
       //savedexplosion[i].alive = true;
    }

    // plane is 704 and 109
    // 32 * 4 on Y = 128
    // 24 * 32 = 768

    //---------------------------------------------------------------------------------------------------
    // HEALTH
    //--------------------------------------------------------------------------------------------------

   // float x = 430, y = 10;
   rect.h = 24;
   rect.w = 300;        // this will ne the health bar and will go down when you get hit
    // Draw box
   // fprintf (stderr, "Health now %d\n",HEALTH);
   //rect.x = static_cast<int>(x);
   //rect.y = static_cast<int>(y);
    rect.x = 430;
    rect.y = 10;



    manA = new SDL_Rect[18];            // Main player needs to be changed
    enemy1 = new SDL_Rect[18];          // Enemy array

    player->animnumber = 0;
    player->y = 650;
    player->x = 599;
    player->velx = 6;
    player->vely = 6;

    player->firingdelay =3;
    player->firingcounter = 0;
    player->shotsfired = 0;

    savedexplosion[0].enemyexplosioncounter = 0;
    savedexplosion[0].enemyexplosiondelay = 3;
    savedexplosion[0].currentframe = 1;
    savedexplosion[0].currentexplosions = 0;

    savedenemy[0].enemyalive =true;

    manA[0].x = 697;    // this is the main ship, my ship
    manA[0].y = 103;
    manA[0].w = 98;
    manA[0].h = 98;

    manA[1].x = 37;     // this is the shot
    manA[1].y = 169;
    manA[1].w = 16;
    manA[1].h = 32;

    enemy1[0].x = 4;  // Enemy Ship 1
    enemy1[0].y = 4;
    enemy1[0].w = 32;
    enemy1[0].h = 32;

	for (int index = 0; index < 6; index++)
	{
		int srcx = 70 + (32 * index) + (index);
		enemy1[1+index].x = srcx;
		enemy1[1+index].y = 169;
		enemy1[1+index].w = 32;
		enemy1[1+index].h = 32;
	}

    // Start of explosion is at 6th row and 3rd over
    // subtract 1 for the line I think

    // int explosionstartx = 2 * 32;
    // int explosionstarty = 5 * 32;

    enemy1[1].x = explosionstartx;  // Enemy Ship Explosion 1
    enemy1[1].y = explosionstarty;
    enemy1[1].w = 32;
    enemy1[1].h = 32;

    enemy1[2].x = explosionstartx + explosiondiff;  // Enemy Ship Explosion 2
    enemy1[2].y = explosionstarty;
    enemy1[2].w = 32;
    enemy1[2].h = 32;

    enemy1[3].x = explosionstartx + explosiondiff * 2;  // Enemy Ship Explosion 3
    enemy1[3].y = explosionstarty;
    enemy1[3].w = 32;
    enemy1[3].h = 32;

    enemy1[4].x = explosionstartx + explosiondiff * 3;   // Enemy Ship Explosion 4
    enemy1[4].y = explosionstarty;

    enemy1[4].w = 32;
    enemy1[4].h = 32;

    enemy1[5].x = explosionstartx + explosiondiff * 4;  // Enemy Ship Explosion 5
    enemy1[5].y = explosionstarty;
    enemy1[5].w = 32;
    enemy1[5].h = 32;

    enemy1[6].x = explosionstartx + explosiondiff * 5;  // Enemy Ship Explosion 6
    enemy1[6].y = explosionstarty;
    enemy1[6].w = 32;
    enemy1[6].h = 32;

    enemy1[7].x = explosionstartx + explosiondiff * 6;  // Enemy Ship Explosion 6
    enemy1[7].y = explosionstarty;
    enemy1[7].w = 32;
    enemy1[7].h = 32;


	// clear screen to black
	//SDL_FillRect(screen, 0, 0);


	return true;
}

