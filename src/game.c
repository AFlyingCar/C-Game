#include <SDL.h>
#include "src/struct.h"
#include "src/enums.h"
#include "src/render.h"
#include "src/constants.h"
#include "src/init.h"

int quit(game_struct* game){
    SDL_DestroyWindow(game->window.window);
    SDL_Quit();

    if(game->enemies != NULL){
        size_t i;
        for(i=0;i<MAX_ENEMIES;i++)
            // Sanity check
            if(game->enemies[i].ready){
                // TODO: Find out why this damn function call keeps throwing a fucking SEGFAULT
                //SDL_FreeSurface(game->enemies[i].sprite);
            }
        free(game->enemies);
    }
    if(game->sprite.bullet_sprites != NULL){
        size_t i;
        for(i=0;i<BULLET_TYPES;i++){
            SDL_FreeSurface(game->sprite.bullet_sprites[i]);
        }
        free(game->bullets);
    }
    if(game->sprite.player_sprites != NULL){
        size_t i;
        for(i=0;i<PLAYER_TYPES;i++)
            if(game->sprite.player_sprites[i] != NULL)
                SDL_FreeSurface(game->sprite.player_sprites[i]);
        free(game->sprite.player_sprites);
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

// Menu system (start menu, character menu, etc...)
int preGameStart(game_struct* game){
    keypress_struct keypresses[1024];
    if(checkForInput(keypresses,1025,game)) return 1;

    size_t i;
    for(i=0;i<1025;i++){
        keypress_struct key = keypresses[i];
        switch(key.key){
            case ARROWL:
                // Try to fill the surface. This is for debugging purposes only
                /*
                if(fillSurface(game->window.surface,0xFF0000))
                    error("Error when filling surface on ARROWL!");
                    */
                SDL_FillRect(game->window.surface,NULL,SDL_MapRGB(game->window.surface->format,0xFF,0x00,0x00));
                break;
            case ARROWR:
                SDL_FillRect(game->window.surface,NULL,SDL_MapRGB(game->window.surface->format,0x00,0xFF,0x00));
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
    SDL_Delay(fps/1000);
    return 0;
}


int main(int argc, char** argv){
    game_struct game;

    game.menu = START_MENU;
    game.game_started = 0;
    game.quit = 0;
    game.bullets = malloc(MAX_BULLETS+1 * sizeof(bullet_struct*)); // Just as big as we can fucking make it
    game.enemies = malloc(MAX_ENEMIES+1 * sizeof(enemy_struct*)); // Doesn't need to be as big, but you never know

    game.sprite.enemy_sprites = malloc(ENEMY_TYPES+1 * sizeof(SDL_Surface*));
    game.sprite.enemy_sprites = malloc(BULLET_TYPES+1 * sizeof(SDL_Surface*));
    game.sprite.enemy_sprites = malloc(PLAYER_TYPES+1 * sizeof(SDL_Surface*));

    if(init(&game.window))
        error("Initialization failed!\n");

    while(!game.quit){
        if(!game.game_started){
            if(preGameStart(&game)) error("An error occurred in preGameStart(game_struct*)!");
        }else{
            if(postGameStart(&game)) error("An error occurred in postGameStart(game_struct*)!");
        }

        //if(updateScreen(&(game.window))) error("An error occurred in updateScreen(window_struct*)!");
        SDL_UpdateWindowSurface(game.window.window);
        clearSurface(game.window.surface);
        tick(60);
    }

    if(quit(&game)) error("An error occurred in quit!");

    return 0;
}

