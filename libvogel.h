#ifndef LIBVOGEL_H
#define LIBVOGEL_H
#include <SDL2/SDL.h>
struct vogel //Create data structure voor vogel
{
    int speedX;
    int speedY;
    int x; //locatie
    int y; //locatie
};

struct cameraType{
    int x;
    int y;
    bool c_auto;
};

struct collision
{ //Type of collision seperate from object
    char* name;
    int mass; //Mass
    int speed; //Speed
    int radius; //Radius
};

struct object
{
    int x;
    int y;
    int mass;
    int radius;
    int speedX;
    int speedY;
};

int initialize_vogels_SDL(int windowX, int windowY, int n, SDL_Renderer* rend, struct vogel* vogels, struct cameraType camera); 
void birdloop_SDL(int windowX, int windowY, int n, SDL_Renderer* rend, struct vogel* vogels, struct cameraType camera);

struct collision* cfg_init(struct collision* collisions );
struct object* createObject(struct object* objects, struct collision* collisions, int mouseX, int mouseY, int selected, const int windowX, const int windowY, int n, struct vogel* vogels, int allocated_objects);
#endif

