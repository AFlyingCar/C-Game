#ifndef _INIT_H_
#define _INIT_H_

#include <SDL.h>
#include "src/struct.h"

int init(window_struct*);

int loadAllSurfaces(window_struct*);

SDL_Surface* loadSurface(const char*);

SDL_Surface* loadSurfaceAndOptimize(const char*,window_struct*);

#endif

