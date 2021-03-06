#ifndef LIBVOGEL_H
#define LIBVOGEL_H
#include <SDL2/SDL.h>
struct vogel //Create data structure voor vogel
{
    double speedX;
    double speedY;
    double x; //locatie
    double y; //locatie
    //bool disruption;
    bool disruption;
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
void birdloop_SDL(int windowX, int windowY, int n, SDL_Renderer* rend, struct vogel* vogels, struct cameraType camera, int allocated_objects, struct object* objects);

struct collision* cfg_init(struct collision* collisions );
struct object* createObject(struct object* objects, struct collision* collisions, int mouseX, int mouseY, int selected, const int windowX, const int windowY, int allocated_objects, struct cameraType camera);
struct object* deleteObject(struct object* objects, int allocated_objects);
#endif

