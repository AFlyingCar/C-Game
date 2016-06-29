#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_
#include <SDL.h>

extern const Uint32 RED_MASK;
extern const Uint32 GREEN_MASK;
extern const Uint32 BLUE_MASK;
extern const Uint32 ALPHA_MASK;

extern const char** SURFACE_NAMES;

// Number of surfaces that can be used
extern const int MAX_SURFACES;

#define POSX 0
#define POSY 0
#define WIDTH 640
#define HEIGHT 480

#define MAX_ENEMIES 1024
#define MAX_BULLETS 16384

// TODO: Change these when we've actually got sprites
#define ENEMY_TYPES 1
#define BULLET_TYPES 1
#define PLAYER_TYPES 1

#define error(MSG,...) \
    { \
        printf(MSG,##__VA_ARGS__); \
        return 1; \
    }

#endif

