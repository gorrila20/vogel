#ifndef SDL_H
#define SDL_H
#include <SDL2/SDL.h>
struct vogel //Create data structure voor vogel
{
    int speedX;
    int speedY;
    int x; //locatie
    int y; //locatie
    struct vogel *next;
};


int initialize_vogels_SDL(int windowX, int windowY, int n, SDL_Renderer* rend, struct vogel* vogels); 
void birdloop_SDL(int windowX, int windowY, int n, SDL_Renderer* rend, struct vogel* vogels);
#endif

