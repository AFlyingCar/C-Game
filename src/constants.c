#include "constants.h"
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

// Do some math with the help of the preprocessor to get how large SURFACES is
#define __SURFACES_START__ __LINE__
const char** SURFACE_NAMES = {
    ""
};
#define __SURFACES_END__ __LINE__

// Number of surfaces that can be used
const int MAX_SURFACES = __SURFACES_END__ - __SURFACES_START__ - 2;
#undef __SURFACES_START__
#undef __SURFACES_END__

