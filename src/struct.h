#ifndef _STRUCTS_H_
#define _STRUCTS_H_
#include <SDL.h>

typedef struct player_struct {
    int posx;
    int posy;
    int character;
    int focus; // 1=yes,0=no
} player_struct;

typedef struct window_struct {
    int posx;
    int posy;
    int width;
    int height;
    SDL_Window* window;
    SDL_Surface* surface;
} window_struct;

typedef struct bullet_struct {
    int posx;
    int posy;
    int type; // What sprite should we use?
    int owner;
} bullet_struct;

typedef struct enemy_struct {
    int posx;
    int posy;
    int ready; // 0=NO,1=OH HELL YES
    int type; // What sprite should we use?
} enemy_struct;

typedef struct keypress_struct {
    int key;
    int state; // 0=press,1=release
} keypress_struct;

typedef struct sprite_struct {
    SDL_Surface** enemy_sprites;
    SDL_Surface** bullet_sprites;
    SDL_Surface** player_sprites;
} sprite_struct;

// One struct to rule them all
// One struct to bind them
//      - Tolkiens: Lord of the Struct
typedef struct game_struct{
    enemy_struct* enemies;
    bullet_struct* bullets;
    window_struct window;
    player_struct player;
    sprite_struct sprite;
    int menu;
    int game_started;
    int quit;
} game_struct;

#endif

