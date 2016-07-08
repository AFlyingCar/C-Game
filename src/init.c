#include "init.h"
#include <SDL.h>
#include "struct.h"
#include "constants.h"

int init(window_struct* window){
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        error("Failed to initialize!\n\tSDL_GetError()=%s\n",SDL_GetError());

    if((window->window = SDL_CreateWindow("game",POSX,POSY,WIDTH,HEIGHT,SDL_WINDOW_SHOWN)) == NULL)
        error("Failed to create window!\n\tSDL_GetError()=%s\n",SDL_GetError());

    if((window->surface = SDL_GetWindowSurface(window->window)) == NULL)
        error("Failed to get window surface!\n\tSDL_GetError()=%s\n",SDL_GetError());

    window->loaded_surfaces = (SDL_Surface*)malloc(MAX_SURFACES+1 * sizeof(SDL_Surface*));

    if(loadAllSurfaces(window))
        error("Failed to load one or more surfaces.");

    return 0;
}

SDL_Surface* loadSurface(const char* name){
    SDL_Surface* surface = SDL_LoadBMP(name);
    return surface;
}

SDL_Surface* loadSurfaceAndOptimize(const char* name, window_struct* window){
    SDL_Surface* surface = loadSurface(name);
    SDL_Surface* optimized = SDL_ConvertSurface(surface,window->surface->format,NULL);
    SDL_FreeSurface(surface);
    return optimized;
}

int loadAllSurfaces(window_struct* window){
    int i;
    for(i=0; i < MAX_SURFACES; i++){
        window->loaded_surfaces[i] = loadSurfaceAndOptimize(SURFACE_NAMES[i],window);
        if(window->loaded_surfaces[i] == NULL)
            error("Failed to load %s",SURFACE_NAMES[i]);
    }
    return 0;
}

