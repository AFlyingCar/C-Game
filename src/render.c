#include "src/render.h"
#include "src/enums.h"
#include "src/constants.h"

SDL_Surface* getSpriteSurfaceForType(int type){
    switch(type){
        
    }
}

int renderAllEnemies(enemy_struct* enemies, int size,window_struct* window){
    SDL_Surface* toplevel = createBlankSurface(window->width,window->height);
    if(toplevel == NULL) return 1;
    size_t i=0;
    for(;i<size;i++){
        SDL_Surface* sprite = getSpriteSurfaceForType(enemies[i].type);
        if(sprite == NULL) return 1;
        if(blit(sprite,toplevel,enemies[i].posx,enemies[i].posy)) return 1;
    }
    SDL_BlitSurface(toplevel,NULL,window->surface,NULL);
}

int renderAllBullets(bullet_struct* bullets, int size, window_struct* window){
    SDL_Surface* toplevel = createBlankSurface(window->width,window->height);
    if(toplevel == NULL) return 1;
    size_t i=0;
    for(;i<size;i++){
        SDL_Surface* sprite = getSpriteSurfaceForType(bullets[i].type);
        if(sprite == NULL) return 1;
        if(blit(sprite,toplevel,bullets[i].posx,bullets[i].posy)) return 1;
    }
    SDL_BlitSurface(toplevel,NULL,window->surface,NULL);
}

int renderPlayer(player_struct* player, window_struct* window){
    SDL_Surface* sprite = getSpriteSurfaceForType(player->character);
    if(sprite == NULL) return 1;
    return blit(sprite,window->surface,player->posx,player->posy);
}

int blit(SDL_Surface* source, SDL_Surface* destination, int x, int y){
    SDL_Rect xy;
    xy.x=x;
    xy.y=y;
    return SDL_BlitSurface(source,NULL,destination,&xy);
}

SDL_Surface* createBlankSurface(int w, int h){
    return SDL_CreateRGBSurface(0,w,h,8,RED_MASK,GREEN_MASK,BLUE_MASK,ALPHA_MASK);
}

int renderMenu(int type){
    switch(type){
        case START_MENU:
            return renderStartMenu();
        case CHARACTER_MENU:
            return renderCharacterMenu();
        case PAUSE_MENU:
            return renderPauseMenu();
        default:
            error("Invalid menu id %d",type);
    }
}

int renderStartMenu(){
    SDL_Surface* menu;
    renderButton(menu,"Begin",0,0);
    return 0;
}

int renderCharacterMenu(){
    return 0;
}

int renderPauseMenu(){
    return 0;
}

int renderButton(SDL_Surface* surface,const char* text,int x,int y){
}

int renderGame(){
    return 0;
}

void clearSurface(SDL_Surface* surface){
    SDL_FillRect(surface,NULL,0x000000);
}

