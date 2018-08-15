#ifdef WIN32
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <string>
#include <math.h>
#include "main.h"
#include "font.h"
#else
#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include <math.h>
#include "main.h"
#include "font.h"
#endif

int explodex, explodey;
int Score;
SDL_Rect rect;
bool init_player()
{
        if (!player) {player = new MyPlayer; return true;}
        return false;
}

bool init_enemy()
{
        if (!enemy_sine) {enemy_sine = new enemymotion; return true;}
        return false;
}

void moveplayer()
{

    if (player->x > 930)
    {
        player->x = 930;
    }
    if (player->x <10)
    {
        player->x = 10;
    }
    if (player->y > 700)
    {
        player->y = 700;
    }
    if (player->y <10)
    {
        player->y = 10;
    }



    apply_surface( player->x, player->y, man, screen, &manA[player->animnumber]);

}


void movebullets()
{
	for (int i = 0; i < MAX_SHOTS; i++)
	{
		if (savedshots[i].shotalive)
		{
			// Move the Saved Shot
			savedshots[i].y = savedshots[i].y - 24;
			apply_surface( savedshots[i].x, savedshots[i].y, man, screen, &manA[1]);
			if (savedshots[i].y < 1 ) // Shot is dead
			{
				savedshots[i].shotalive = false;
			}
		}

		if (savedshotsbehind[i].shotalive)
		{
			savedshotsbehind[i].y = savedshotsbehind[i].y + 24;
			apply_surface( savedshotsbehind[i].x, savedshotsbehind[i].y, man, screen, &manA[1]);
			if (savedshotsbehind[i].y > 768 ) // Shot is dead
			{
				savedshotsbehind[i].shotalive = false;
			}
		}
	}
}


void DrawMainMap()
{
    // clear screen to black
	SDL_FillRect(screen, 0, 0);

}

void drawenemies()
{

    int c,t=1,delay;
    for (c = 0;c < MAX_ENEMIES; c++)
    {
       if (savedenemy[c].enemyalive)
       {
           if (savedenemy[c].collisiondetected && delay < 5)
            {
                apply_surface(savedenemy[c].x,savedenemy[c].y, man, screen, &enemy1[savedenemy[t].animnumber]);

                delay +=1;

                if (delay ==2)
                    {
                        t = t + 1;
                        delay = 0;
                    }
                    if (savedenemy[c].animnumber > 5 )
                        {
                            savedenemy[c].enemyalive = false;
                            savedenemy[c].animnumber = 0;

                        }

             }

       savedenemy[c].y +=4;
        apply_surface(savedenemy[c].x,savedenemy[c].y, man, screen, &enemy1[0] );
       if (savedenemy[c].y > 768)
       {
            savedenemy[c].y = 0;

       }
       }
       // if dead respawn

        if (!savedenemy[c].enemyalive)
       { savedenemy[c].x = 10 + rand() % (1020 - 10 );
             //savedenemy[index].y = 10 + rand() % (760 - 10 );
          savedenemy[c].y = 0;
          savedenemy[c].enemyalive = true;
          savedenemy[c].collisiondetected = false;
           savedenemy[c].animnumber = 0;
       }


   }


}

void spawn_new_random_enemy()
{
	// STEP #1 - find a dead enemy
	// STEP #2 - make it alive
	// STEP #3 - position it
	// STEP #4 - exit this function
	for (int e = 0; e < MAX_ENEMIES; e++)
	{
		// skip enemies that are alive
		if (savedenemy[e].enemyalive)
		{
			continue;
		}

		// make it alive
		savedenemy[e].enemyalive = true;

		// position randomly in the top 1/4 of the screen

		int rx = savedenemy[e].w + rand() % (SCREEN_WIDTH - (savedenemy[e].w * 2));
		//int ry = savedenemy[e].w + rand() % ((SCREEN_HEIGHT / 4) - (savedenemy[e].w * 2));

		savedenemy[e].x = rx;
		savedenemy[e].y = 0;

		// exit the function
		return;
	}
}

void collision2()
{

	for (int e = 0; e < MAX_ENEMIES; e++)
	{
		// skip enemies that are not alive
		if (!savedenemy[e].enemyalive)
		{
			continue;
		}

		int leftA	= savedenemy[e].x;
		int topA	= savedenemy[e].y;
		int rightA	= savedenemy[e].x + savedenemy[e].w;
		int bottomA = savedenemy[e].y + savedenemy[e].h;

		for (int i = 0; i < MAX_SHOTS; i++)
		{
			// skip bullets that are not alive
			if (!savedshots[i].shotalive)
			{
				continue;
			}

			// get the point of the bullet that we will collide with
			int bx = savedshots[i].x;
			int by = savedshots[i].y;
			int bx1 = savedshots[i].x + savedshots[i].w;
			int by1 = savedshots[i].y + savedshots[i].h;;


			int cx = savedshotsbehind[i].x;
			int cy = savedshotsbehind[i].y;
			int cx1 = savedshotsbehind[i].x + savedshotsbehind[i].w;
			int cy1 = savedshotsbehind[i].y + savedshotsbehind[i].h;;


//        bool IsCollision( Rectangle A, Rectangle
//{
 //     if ( A.x          <     B.x + B.w
 //           A.x + A.w   >     B.x
 //           A.y         <     B.y + B.h
 //           A.y + A.h   >     B.y )
 //     {
 //           return true;
 //     }
 //     return false;
//}



			//int bx = savedshots[i].x;
			//int by = savedshots[i].y;
		//	int bx1 = savedshotsbehind[i].x + savedenemy[i].w;
	//		int by1 = savedshotsbehind[i].y + savedenemy[i].h;

			// we are going to test the shots from the front and the back turrets
			// we store the collision boolean in these two variables to make it easy to read the
			// following code

			bool checkFront = (leftA < bx1 && rightA > bx && topA < by1 && bottomA > by);
			bool checkBack = (leftA < cx1 && rightA > cx && topA < cy1 && bottomA > cy);

	//		bool checkFront = (bx >= leftA && bx <= rightA && by >= topA && by <= bottomA);
	//		bool checkBack = (bx1 >= leftA && bx1 <= rightA && by1 >= topA && by1 <= bottomA);

			// test for any collisions of bullets and the current enemy ship
			if (checkFront || checkBack)
			{
				// there was a collision, so we kill the bullet depending on if it was from the
				// front or rear turret
				if (checkFront)
				{
				    savedshots[i].shotalive = false;
				}
				else
				{
					savedshotsbehind[i].shotalive = false;
				}

				// kill the enemy ship
				savedenemy[e].enemyalive = false;

				// TODO: spawn a new enemy
				// do not set the position of this dead enemy ship.
				// use the enemy spawning routine to spawn a new enemy!
				spawn_new_random_enemy();

				// play a sound
				if (Mix_PlayChannel(-1, shot2ogg, 0) < 0)
				{
					fprintf(stderr, "SDL_mixer Error: %s\n", Mix_GetError());
				}

				// increase the score
				Score = Score + 10;
				//fprintf (stderr, "Score %d\n",Score);


                // make a nice explosion at the collision location
				if (checkFront)
				{
					spawn_explosion(bx, by);
				}
				else
				{
					spawn_explosion(cx, cy);
				}
			}
		}
	}
}


void starsinit()
{

    int i;
    for (i =0;i<MAX_STARS;i++)
    {
        savedstars[i].x = 10 + rand() % (1020 - 10);
        savedstars[i].y = 10 + rand() % (760 - 10);
    }




}

void movestars()
{
    int i;
    unsigned int starcolor = SDL_MapRGB(screen->format, 131, 131, 131);
    for (i = 0; i < MAX_STARS; i++)
    {
    SDL_Rect star;
    star.x = savedstars[i].x;
    star.y = savedstars[i].y;
    star.w = 1;
    star.h = 1;
    SDL_FillRect(screen, &star, starcolor);
    if(++savedstars[i].y > 760)
    {
        savedstars[i].y = 0;
    }
}



}


void testsine()
{

    //if (++enemy_sine->enemycounter >= enemy_sine->enemydelay)
//	{

            // int shipX = shipWidth + rand() % (screenWidth - (shipWidth * 2));
            //enemy_sine->swav = tan((enemy_sine->spy *(3.14159267 /140))*5+1000);
            enemy_sine->swav = sin((enemy_sine->spy *(3.14159267 /180))*10+300); // Original
            //             enemy_sine->swav = tan((enemy_sine->spy *(3.14159267 /180))*5+100);  One I like
            //enemy_sine->swav = enemy_sine->swav *60+100;    //original
        enemy_sine->swav = enemy_sine->swav *160+300;
            //apply_surface(100,100, man, screen, &enemy1[4]);

            // apply_surface(enemy_sine->spx,enemy_sine->swav, man, screen, &enemy1[4]); // original

            //apply_surface(enemy_sine->swav,enemy_sine->spx, man, screen, &enemy1[0]);  // original
            fprintf(stderr, "enemy->swav %0d \n", enemy_sine->swav);
            //apply_surface(enemy_sine->swav,enemy_sine->spx, man, screen, &enemy1[0]);
            enemy_sine->spy += .2;
            enemy_sine->spx += 2;
            savedenemy[3].x = enemy_sine->swav;
            savedenemy[3].y = enemy_sine->spx;
            enemy_sine->enemycounter = 0;
            if (enemy_sine->spx > 768)
            {
                enemy_sine->spx =0;
            }
	//}

}


void animate_explosions()
{


        for (int index = 0; index < MAX_ENEMIES; index++)

        {


                // grab a reference to the explosion array element for this index

               EnemyExplosion& explosion = savedexplosion[index];



                // if this explosion is not "alive"

                if (!explosion.alive)

                {

                        // then we skip it

                        continue;

                }



                // we animate the explosion if its alive (this code doesn't execute if its not alive)



                // increment the counter, and test if we've reached the delay for changing the frame

                if (++explosion.enemyexplosioncounter >= explosion.enemyexplosiondelay)

                {

                        // reset counter

                        explosion.enemyexplosioncounter = 0;



                        // increment the frame, and test if we've run out of frames

                        if (++explosion.currentframe >= 5)

                        {

                                // we've reached the last frame, so we kill the explosion
                                // We Can Respawn enemies here if we want
                                explosion.alive = false;

                        }

                }

        }

}


void render_explosions()
{

        for (int index = 0; index < MAX_ENEMIES; index++)

        {

                // grab a reference to the explosion array element for this index

                EnemyExplosion& explosion = savedexplosion[index];



                // if this explosion is not "alive"

                if (!explosion.alive)

                {

                        // then we skip it

                        continue;

                }



                // we render the explosion if its alive (this code doesn't execute if its not alive)



                apply_surface(explosion.x, explosion.y, man, screen, &enemy1[1 + explosion.currentframe]);

        }

}

void spawn_explosion(int x, int y)
{

        for (int index = 0; index < MAX_ENEMIES; index++)

        {

                // grab a reference to the explosion array element for this index

                EnemyExplosion& explosion = savedexplosion[index];



                // if this explosion is "alive"

                if (explosion.alive)

                {

                        // then we skip it

                        continue;

                }



                // we spawn our explosion using the first "dead" explosion slot



                explosion.alive = true;

                explosion.x = x;

                explosion.y = y;

                explosion.currentframe = 0;

                explosion.enemyexplosioncounter = 0;

                explosion.enemyexplosiondelay = 6;



                // we simply exit the function because we don't need to continue processing anything here

                return;

        }

}

void checkscore()
{
        int i,mynum,cnt=16*10;
        for (i = 0; i < 6; i++)
        {
          mynum = digitAtPosition(Score,i);
          apply_surface( cnt, 0, Numb, screen, &num[mynum]);
          cnt = cnt - 16;


 //         printf("mynum %d ", mynum);

        }


}


int digitAtPosition(int number,int position)
{

    if(position == 0) return number % 10;
    else return (number / (int)pow(10,position)) % 10;
}

void checkmainshipcollision()
{

        int leftA	= player->x;
		int topA	= player->y;
        int rightA	= player->x + 98;
		int bottomA = player->y + 98;

    for (int i = 0; i < MAX_ENEMIES; i++)
	{


			// get the point of the bullet that we will collide with
			int bx = savedenemy[i].x;
			int by = savedenemy[i].y;
			int bx1 = savedenemy[i].x + savedenemy[i].w;
			int by1 = savedenemy[i].y + savedenemy[i].h;


           // bool checkship = (sx < bx1 && sx1 > bx && sy < by1 && sy1 > by);

			bool checkship = (leftA < bx1 && rightA > bx && topA < by1 && bottomA > by);

            if (checkship)
            {
                // the ships health goes down
                if (rect.w < 1)
                {
                    rect.w = 300;
                }

                rect.w = rect.w - .2;
            }
	}
}


void shootingenemy()
{


/*    //inline void LineTo(SDL_Surface *scr , int x1 , int y1 , int x2 , int y2 ) {
	//SDL_Rect dotRect; // For drawing a dot
	int vtx , vty; // The vector from (x1,y1) to (x2,y2)
	int x = x1 , y = y1; // The coordinate of current interpolate point
	vtx = x2 - x1 ;
	vty = y2 - y1 ;
	if(vtx == 0 && vty == 0 ) {
		//dotRect.x = x;
		//dotRect.x = x;
		//dotRect.w = dotRect.h = 2;
		//SDL_FillRect(scr , &dotRect , 0xFFFF22);
		return;
		}
	if(vtx == 0) {
		dotRect.x = x;
		if(y1 < y2) dotRect.y = y1;
		if(y2 < y1) dotRect.y = y2;
		//dotRect.w = 2 ;
		//dotRect.h = abs(vty) ;
		//SDL_FillRect(scr , &dotRect , 0xFFFF22);
		return;
		}
	if(vty == 0) {
		dotRect.y = y;
		if(x1 < x2) dotRect.x = x1;
		if(x2 < x1) dotRect.x = x2;
		//dotRect.w = abs(vtx) ;
		//dotRect.h = 2 ;
		//SDL_FillRect(scr , &dotRect , 0xFFFF22);
		return;
		}
	// Case vtx >= vty
	if( abs(vtx) >= abs(vty) ) {
		while( abs(x-x1) <= abs(vtx) ) {
			y = y1 + vty * (x - x1) / vtx ;
			//dotRect.x = x;
			//dotRect.y = y;
			//dotRect.w = dotRect.h = 2 ;
			//SDL_FillRect(scr , &dotRect , 0xFFFF22);
			if(vtx>0) x++;
			if(vtx<0) x--;
			} // while( y - y1 < vty ) { END
		} // if( abs(vtx) >= abs(vty) ) {END
	// Case vtx < vty
	if( abs(vtx) < abs(vty) ) {
		while( abs(y - y1) <= abs(vty) ) {
			x = x1 + vtx * (y - y1) / vty ;
			//dotRect.x = x;
			//dotRect.y = y;
			//dotRect.w = dotRect.h = 2 ;
			//SDL_FillRect(scr , &dotRect , 0xFFFF22);
			if(vty>0) y++;
			if(vty<0) y--;
			} // while( y - y1 < vty ) { END
		} // if( abs(vtx) < abs(vty) ) { END
	return;
	}
// inline void LineTo(...) { END

*/

}
