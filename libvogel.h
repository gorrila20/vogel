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

struct cameraType{
    int x;
    int y;
    bool c_auto;
};

int initialize_vogels_SDL(int windowX, int windowY, int n, SDL_Renderer* rend, struct vogel* vogels, struct cameraType camera); 
void birdloop_SDL(int windowX, int windowY, int n, SDL_Renderer* rend, struct vogel* vogels, struct cameraType camera);
#endif

