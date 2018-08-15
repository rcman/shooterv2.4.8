// Main.h

// this makes sure that this file is never included multiple times
// and is something that is VERY important!
#ifndef __MAIN_H__
#define __MAIN_H__

struct _TTF_Font;

// constants
const int SCREEN_WIDTH 	= 1024;
const int SCREEN_HEIGHT = 768;
const int SCREEN_BPP 	= 32;
//The frames per second
const int FRAMES_PER_SECOND = 20;
const int MAPWIDTH 		= 32;
const int MAPHEIGHT 	= 24;
const int MAX_STARS     = 100;

const int MAX_SHOTS = 30;
const int MAX_ENEMIES = 5;

const int TILEHEIGHT 	= 32;
const int TILEWIDTH 	= 32;
const int GRAVITY       = 1;

extern _TTF_Font*    font;

// SINE

struct Rectangle
{
      int x, y, w, h;
};




struct enemymotion{
        float spx;
        float spy;
        float opx;
        float opy;
        float swav;
        int currentenemytime;
        int enemydelay;
        int enemycounter;


};


extern int bx,by;
extern int explodex, explodey;

struct MyPlayer{
		int x, y;			//x, y coordinate (top left of the player rectangle)
		int h, w;			//height, width
		int velx, vely;		//velocity on x, y axis
		bool faceright;		//player facing right? -> graphics
		bool lockjump;		//may the player jump
		bool jumping;
		bool moving;
		bool ismoving;
        int animnumber;
        int speed;
        int firingcounter;
        int firingdelay;
        int shotsfired;

};


struct Shipshots
{
        int x,y;
        int h,w;
        int velx,vely;

        bool shotalive;
};

extern Shipshots savedshots[MAX_SHOTS];


struct ShipshotsBehind
{
        int x,y;
        int h,w;
        int velx,vely;

        bool shotalive;
};

extern ShipshotsBehind savedshotsbehind[MAX_SHOTS];









struct Enemyspots
{
        int x,y;
        int h,w;
        int velx,vely;
        bool collisiondetected;
        bool enemyalive;
        int animnumber;
};
extern Enemyspots savedenemy[MAX_ENEMIES];

struct EnemyExplosion
{
      int x,y;
      int animnumber;
      int currentframe;
      int currentexplosions;
      bool alive;
      int enemyexplosioncounter;
      int enemyexplosiondelay;

};
extern EnemyExplosion savedexplosion[MAX_ENEMIES];

struct Stars
{
    int x,y;
};
extern Stars savedstars[MAX_STARS];

  // forward declare the SDL stuff that we need to create pointers to
struct SDL_Surface;
struct SDL_Rect;
union SDL_Event;


extern MyPlayer* player;

extern enemymotion* enemy_sine;
extern SDL_Surface* bgmapsurface;
// Game Score
extern int Score;

// My Numbers

extern SDL_Surface*     Numb;
extern SDL_Rect*        num;



extern SDL_Surface*		screen;
//tileset = load_image("bmp/Sewers.bmp", 255, 0, 255);
extern SDL_Surface*		tileset;
//man
extern SDL_Surface*		man;
extern SDL_Rect*        manA;
extern SDL_Rect rect;
extern SDL_Surface*      enemy;
extern SDL_Rect*        enemy1;

extern SDL_Event* 		event;
extern int Map[];

struct Mix_Chunk;
extern Mix_Chunk* shot1ogg;
extern Mix_Chunk* shot2ogg;

extern bool init_player();
extern bool init_enemy();
extern void destroy_player();
extern bool Gameinit();
extern bool load_files();
extern bool load_man();
extern SDL_Surface* load_image(const char* filename, unsigned char r, unsigned char g, unsigned char b);
extern void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = 0);
extern void InitMap();
extern void RenderMap();
void moveplayer();
void DrawMainMap();
void check_input();
void collision2();
 //The sides of the rectangles
extern void movebullets();

extern bool check_collision();
extern void enemyexplodecheck();
extern void drawenemies();
void showexplosions();
void testexplosion(int bx,int by);
void testexplosion2(int bx, int by);
void starsinit();
void movestars();
void testsine();
void animate_explosions();
void render_explosions();
extern void spawn_explosion(int x, int y);
extern void playsound();
extern void soundinit();
extern bool LoadNum();
extern void checkscore();
extern int digitAtPosition(int,int);
extern void spawn_new_random_enemy();
extern void drawrectangle();
extern void checkmainshipcollision();
extern void shootingenemy();
extern inline void LineTo(SDL_Surface *scr , int x1 , int y1 , int x2 , int y2 );

// we MUST close the #ifndef fr;om above
#endif


