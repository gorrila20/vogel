#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "ini.h"
#define PATH_MAX 2000

int counter = -1; //Has to be global otherwise out of scope reset
struct collision{
    char* name;
    int mass; //Mass
    int speed; //Soeed
    int radius; //Radius

};


static int handler(void* config, const char* section, const char* name, const char* value)
{ 
    counter++;
    struct collision* collisions = (struct collision*)config;
    collisions = (struct collision*) malloc(sizeof(struct collision)); //Allocate space for one more
    strcpy(collisions[counter].name, section);


    #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) ==0
    if(strcmp(name, "mass") == 0)
    {
       collisions[counter].mass = atoi(value); 
    }
    else if(strcmp(name, "radius") == 0)
    {
        collisions[counter].radius = atoi(value);
    }
    else if(strcmp(name, "speed") == 0)
    {
        collisions[counter].speed = atoi(value);
    }
    else{
        return 0;
    }
    return 1;

}
void cfg_init(struct collision* collisions)
{
  
   char INI_PATH[PATH_MAX] = "/collisions/config.ini"; //Relative path
   char cwd[PATH_MAX];
    if(getcwd(cwd, sizeof(cwd)) != NULL){
        printf("initializing config files...\n");
    }
    else{
        fprintf(stderr,"getcwd() error\n");
        exit(EXIT_FAILURE);
    } //Get current path
   strcat(cwd, INI_PATH);
   if (ini_parse(cwd, handler, collisions) < 0)
   {
        fprintf(stderr,"INI config error!\n");
        exit(EXIT_FAILURE);
   }

   for(int i=0; i<counter; i++)
   {
        printf("collision[%d].name = %s \n collision[%d].mass = %d\n", i, collisions[i].name, i, collisions[i].mass);

   }

}

