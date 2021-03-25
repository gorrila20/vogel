#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
struct cameraType
{
    int x;
    int y;
    bool c_auto;
};

struct object* createObject(struct object* objects, struct collision* collisions, int mouseX, int mouseY, int selected, const int windowX, const int windowY, int allocated_objects, struct cameraType camera)
{
    objects = (struct object*) realloc(objects, sizeof(struct object)*allocated_objects);
   
    if (objects == NULL)
    {
        free(objects);
        objects = NULL;
        fprintf(stderr, "realloc() error");
        exit(EXIT_FAILURE);
    }
    objects[allocated_objects-1].mass = collisions[selected].mass;
    objects[allocated_objects-1].radius = collisions[selected].radius;
    
    if(mouseX <= (windowX/2))
    {
        objects[allocated_objects-1].x=-20+camera.x;
        objects[allocated_objects-1].y = mouseY+camera.y;
        objects[allocated_objects-1].speedX = collisions[selected].speed;
        objects[allocated_objects-1].speedY = 0;
    }
    else if(mouseX > (windowX/2))
    {
        objects[allocated_objects-1].x=windowX+camera.x+100;
        objects[allocated_objects-1].y = mouseY+camera.y;
        objects[allocated_objects-1].speedX = -collisions[selected].speed;
        objects[allocated_objects-1].speedY = 0;
    }

    return objects;
    
}





