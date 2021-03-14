#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#define BIRD_RADIUS 4

struct vogel //Create data structure voor vogel
{
    int speedX;
    int speedY;
    int x; //locatie
    int y; //locatie
    struct vogel *next;
};


int initialize_vogels_SDL(int windowX, int windowY, int n, SDL_Window* win, SDL_Renderer* rend, struct vogel* vogels)
{
    
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);

    SDL_RenderClear(rend);  
    
    SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<BIRD_RADIUS; j++)
        {
            for(int k=0; k<BIRD_RADIUS; k++)
            {
            SDL_RenderDrawPoint(rend, vogels[i].x+j, vogels[i].y+k);  
            }
        }
    }
    SDL_RenderPresent(rend);
    return 0;
}
