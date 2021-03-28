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
        objects[allocated_objects-1].x=mouseX+camera.x;
        objects[allocated_objects-1].y = mouseY+camera.y;
        
        objects[allocated_objects-1].speedX = collisions[selected].speed;
        objects[allocated_objects-1].speedY = 0;
    }
    else if(mouseX > (windowX/2))
    {
        objects[allocated_objects-1].x=mouseX+camera.x;
        objects[allocated_objects-1].y = mouseY+camera.y;
        objects[allocated_objects-1].speedX = -collisions[selected].speed;
        objects[allocated_objects-1].speedY = 0;
    }
    

    return objects;
    
}
struct object* deleteObject(struct object* objects, int allocated_objects)
{

     
    for(int i=0; i<allocated_objects; i++)
    {
       if(i!=0)
       {
        objects[i-1].mass = objects[i].mass;
        objects[i-1].x = objects[i].x;
        objects[i-1].y = objects[i].y;
        objects[i-1].radius = objects[i].radius;
        objects[i-1].speedX = objects[i].speedX;
        objects[i-1].speedY = objects[i].speedY;
       }
    }
    if(objects == NULL)
    {
        free(objects);
        objects = NULL;
        fprintf(stderr, "realloc() failed! \n");
        exit(EXIT_FAILURE);

    }
    return objects;

}




