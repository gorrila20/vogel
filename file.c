#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include "ini.h"
#define PATH_MAX 2000
#define SUFFIX ".ini"

struct collision{
    char* name;
    int mass; //Mass
    int speed; //Soeed
    int radius; //Radius

};

typedef struct
{
    char* name;
    int mass;
    int speed;
    int radius;

} collisionType;

static int handler(void* config, const char* section, const char* name, const char* value)
{ 

    collisionType* cur_collision = (collisionType*)config;
    #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) ==0
    if(MATCH("object", "mass"))
    {
        cur_collision->mass = atoi(value);

    }
    else if(MATCH("object", "radius"))
    {
        cur_collision->radius = atoi(value);
    }
    else if(MATCH("object", "speed"))
    {
        cur_collision->speed = atoi(value);
    }
    else{
        return 0;
    }

    return 1;

}


static void removeSuffix(char** out, const char* in)
{
    *out = strdup(in);
    ( *out )[strlen(in) - strlen(SUFFIX)] = '\0';
}

struct collision* cfg_init(struct collision* collisions)
{
     
   char INI_PATH[PATH_MAX] = "/collisions/"; //Relative path
   char cwd[PATH_MAX];
    if(getcwd(cwd, sizeof(cwd)) != NULL){
        printf("initializing config files...");
    }
    else{
        fprintf(stderr,"getcwd() error\n");
        exit(EXIT_FAILURE);
    } //Get current path
   strcat(cwd, INI_PATH);

   DIR *dp;
   struct dirent *ep;
   dp = opendir(cwd);
   //TODO: volatile code improve error handling
   if (dp != NULL)
   {
        int counter = 0; //First two directory listings are , and .. skip them
        int j = 0;
        collisionType cur_collision;
        //Allocate space for one more declaration
        char* path = NULL;
        char* combined_path = NULL;
        while((ep = readdir(dp)))
            counter++; //Count how many files
        
        dp = NULL; //Reset dp
        dp = opendir(cwd); //Reset complete
        collisions = (struct collision *) malloc(sizeof(struct collision)*(counter-2)); //Malloc enough size to store everything
        counter = 0;
        while((ep = readdir(dp)))
        {
           
            if(counter>=2)
            {
                removeSuffix(&cur_collision.name, ep->d_name);
                path = strdup(ep->d_name);
                if((combined_path = malloc(strlen(cwd))+strlen(path)+1) != NULL)
                {
                    combined_path[0] = '\0';
                    strcat(combined_path, cwd);
                    strcat(combined_path, path);
                }
                else
                {
                    fprintf(stderr, "malloc() failed"); 
                    exit(EXIT_FAILURE);
                }
                if(ini_parse(combined_path, handler, &cur_collision) < 0)
                {
                    fprintf(stderr, "Cant load ini files\n");
                    exit(EXIT_FAILURE);
                }
                collisions[j].name = strdup(cur_collision.name);
                collisions[j].speed = cur_collision.speed;
                collisions[j].mass = cur_collision.mass;
                collisions[j].radius = cur_collision.radius;
                j++;
               
            }
            counter++;
        }
        
        printf("done\n");
        free(&combined_path);            
        (void) closedir(dp);
        return collisions;
   }
   else 
    perror("Directory not found");
}


