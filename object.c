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
struct object* createObject(struct object* objects, struct collision* collisions, int mouseX, int mouseY, int selected, const int windowX, const int windowY, int n, struct vogel* vogels, int allocated_objects)
{
    objects = (struct object*) realloc(objects, sizeof(struct object)*allocated_objects);
    if (objects == NULL)
    {
        free(objects);
        objects = NULL;
        fprintf(stderr, "realloc() error");
        exit(EXIT_FAILURE);
    }
    printf("allocated_objects: %d\n", allocated_objects);    
    objects[allocated_objects-1].mass = collisions[selected].mass;
    objects[allocated_objects-1].radius = collisions[selected].radius;
    
    if(mouseX > (windowX/2))
    {
        objects[allocated_objects-1].x=vogels[n].x+5;
        objects[allocated_objects-1].y = mouseY;
        objects[allocated_objects-1].speedX = -collisions[selected].speed;
        objects[allocated_objects-1].speedY = 0;
    }
    else if(mouseX < (windowX/2))
    {
        objects[allocated_objects-1].x=vogels[0].x-5;
        objects[allocated_objects-1].y = mouseY;
        objects[allocated_objects-1].speedX = collisions[selected].speed;
        objects[allocated_objects-1].speedY = 0;
    }

    return objects;
    
}





