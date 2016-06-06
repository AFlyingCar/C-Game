#include <SDL.h>

#define error(MSG,...) \
    { \
        printf(MSG,##__VA_ARGS__); \
        return 1; \
    }

#define POSX 0
#define POSY 0
#define WIDTH 640
#define HEIGHT 480

#define MAX_ENEMIES 1024
#define MAX_BULLETS 16384

enum KeyPresses{
    KEYFAIL=-1,
    ARROWU,
    ARROWD,
    ARROWL,
    ARROWR,
    PRIMARY,
    SECONDARY,
    SHIFT,
    PAUSE,
};

typedef struct player_struct {
    int posx;
    int posy;
    int character;
    int focus; // 0=yes,1=no
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
    SDL_Surface* sprite;
    int owner;
} bullet_struct;

typedef struct enemy_struct {
    int posx;
    int posy;
    int ready; // 0=NO,1=OH HELL YES
    SDL_Surface* sprite;
} enemy_struct;

typedef struct keypress_struct {
    int key;
    int state; // 0=press,1=release
} keypress_struct;

// One struct to rule them all
// One struct to bind them
//      - Tolkiens: Lord of the Struct
typedef struct game_struct {
    enemy_struct* enemies;
    bullet_struct* bullets;
    window_struct window;
    player_struct player;
    int game_started;
    int quit;
} game_struct;

int init(window_struct* window){
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        error("Failed to initialize!\n\tSDL_GetError()=%s\n",SDL_GetError());

    if((window->window = SDL_CreateWindow("game",POSX,POSY,WIDTH,HEIGHT,SDL_WINDOW_SHOWN)) == NULL)
        error("Failed to create window!\n\tSDL_GetError()=%s\n",SDL_GetError());

    if((window->surface = SDL_GetWindowSurface(window->window)) == NULL)
        error("Failed to get window surface!\n\tSDL_GetError()=%s\n",SDL_GetError());

    return 0;
}

int quit(game_struct* game){
    SDL_DestroyWindow(game->window.window);
    SDL_Quit();

    if(game->enemies != NULL){
        size_t i;
        for(i=0;i<MAX_ENEMIES;i++)
            // Sanity check
            if(game->enemies[i].ready)
                // TODO: Find out why this damn function call keeps throwing a fucking SEGFAULT
                SDL_FreeSurface(game->enemies[i].sprite);
        free(game->enemies);
    }
    if(game->bullets != NULL){
        size_t i;
        for(i=0;i<MAX_BULLETS;i++)
            SDL_FreeSurface(game->bullets[i].sprite);
        free(game->bullets);
    }
    //if(game->window.window != NULL) free(game->window.window);
    //if(game->window.surface != NULL) free(game->window.surface);

    return 0;
}

int getNewKeyNum(SDL_Keycode sym){
    switch(sym){
        case SDLK_UP:
            return ARROWU;
        case SDLK_DOWN:
            return ARROWD;
        case SDLK_LEFT:
            return ARROWL;
        case SDLK_RIGHT:
            return ARROWR;
        case SDLK_z:
            return PRIMARY;
        case SDLK_x:
            return SECONDARY;
        case SDLK_LSHIFT:
            return SHIFT;
        case SDLK_ESCAPE:
            return PAUSE;
        default:
            return -1;
    }
}

// Only need game so we can check for a QUIT call.
int checkForInput(keypress_struct* array, int size,game_struct* game){
    // TODO: make this method more efficient
    SDL_Event e;
    int i=0;
    while(SDL_PollEvent(&e) && i < size){
        if(e.type == SDL_QUIT){
            game->quit = 1;
            return 0;
        }else if(e.type == SDL_KEYDOWN){
            array[i].key = getNewKeyNum(e.key.keysym.sym);
            array[i].state = 0;
            i++;
        }else if(e.type == SDL_KEYUP){
            array[i].key = getNewKeyNum(e.key.keysym.sym);
            array[i].state = 1;
            i++;
        }
        // Who cares if it isn't any of these three. Seriously, who gives a fuck
    }
    return 0;
}

SDL_Surface* loadBMPSurface(const char* path){
    return SDL_LoadBMP(path);
}

int fillSurface(SDL_Surface* surface,int color){
    int r = color&0xFF0000;
    int g = color&0x00FF00;
    int b = color&0x0000FF;
    return SDL_FillRect(surface,NULL,SDL_MapRGB(surface->format,r,g,b));
}

int preGameStart(game_struct* game){
    //game->quit = 1;

    keypress_struct keypresses[1024];
    if(checkForInput(keypresses,1025,game)) return 1;

    size_t i;
    for(i=0;i<1025;i++){
        keypress_struct key = keypresses[i];
        switch(key.key){
            case ARROWL:
                if(fillSurface(game->window.surface,0xFF0000)) error("Error when filling surface on ARROWL!");
                break;
        }
    }

    return 0;
}

int postGameStart(game_struct* game){
    return 0;
}

int updateScreen(window_struct* window){
    SDL_UpdateWindowSurface(window->window);
    return 0;
}

int tick(int fps){
    SDL_Delay(1000*fps);
    return 0;
}

int main(int argc, char** argv){
    game_struct game;

    game.game_started = 0;
    game.quit = 0;
    game.bullets = malloc(MAX_BULLETS+1 * sizeof(bullet_struct*)); // Just as big as we can fucking make it
    game.enemies = malloc(MAX_ENEMIES+1 * sizeof(enemy_struct*)); // Doesn't need to be as big, but you never know

    if(init(&game.window))
        error("Initialization failed!\n");

    while(!game.quit){
        SDL_FillRect(game.window.surface,NULL,SDL_MapRGB(game.window.surface->format,0x00,0x00,0x00));
        if(!game.game_started){
            if(preGameStart(&game)) error("An error occurred in preGameStart(game_struct*)!");
        }else{
            if(postGameStart(&game)) error("An error occurred in postGameStart(game_struct*)!");
        }

        if(updateScreen(&(game.window))) error("An error occurred in updateScreen(window_struct*)!");
    }

    if(quit(&game)) error("An error occurred in quit!");

    return 0;
}

