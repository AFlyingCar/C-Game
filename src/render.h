#ifndef _RENDER_H_
#define _RENDER_H_
#include <SDL.h>
#include "src/struct.h"

SDL_Surface* getSpriteSurfaceForType(int);

SDL_Surface* createBlankSurface(int,int);

int renderAllEnemies(enemy_struct*,int,window_struct*);

int renderAllBullets(bullet_struct*,int,window_struct*);

int renderPlayer(player_struct*,window_struct*);

int blit(SDL_Surface*,SDL_Surface*,int,int);

#endif
