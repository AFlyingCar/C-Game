#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_
#include <SDL.h>

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    const Uint32 RED_MASK =   0xff000000;
    const Uint32 GREEN_MASK = 0x00ff0000;
    const Uint32 BLUE_MASK =  0x0000ff00;
    const Uint32 ALPHA_MASK = 0x000000ff;
#else
    const Uint32 RED_MASK =   0x000000ff;
    const Uint32 GREEN_MASK = 0x0000ff00;
    const Uint32 BLUE_MASK =  0x00ff0000;
    const Uint32 ALPHA_MASK = 0xff000000;
#endif

#endif

