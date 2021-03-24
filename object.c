#include <stdio.h>
#include <stdlib.h>
struct collision
{
    char* name;
    int mass;
    int speed; 
    int radius;

};

struct object
{
    int x,y;
    int mass,radius;
    int speedX;
    int speedY;
};

struct vogel
{
    int speedX, speedY;
    int x;
    int y;
};
struct object* createObject(struct object* objects, struct collision* collisions, int mouseX, int mouseY, int selected, const int windowX, const int windowY, int n, struct vogel* vogels )
{
    if((objects = realloc(objects, sizeof(struct object)) == NULL))
    {
        fprintf(stderr, "realloc() error\n");
        exit(EXIT_FAILURE);
    }
    int len_objects = 0;
    for(int i=0; objects[i].x!=NULL; i++)
    {
        len_objects++;
    }
    
    objects[len_objects-1].mass = collisions[selected].mass;
    objects[len_objects].radius = collisions[selected].radius;
    
    if(mouseX > (windowX/2))
    {
        objects[len_objects].x=vogels[n].x+5;
        objects[len_objects].y = mouseY;
        objects[len_objects].speedX = -collisions[selected].speed;
        objects[len_objects].speedY = 0;
    }
    else if(mouseX < (windowX/2))
    {
        objects[len_objects].x=vogels[0].x-5;
        objects[len_objects].y = mouseY;
        objects[len_objects].speedX = collisions[selected].speed;
        objects[len_objects].speedY = 0;
    }

    return objects;
    
}





