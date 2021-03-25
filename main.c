
#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_timer.h> 
#include <unistd.h>
#include <stdbool.h>
#include "libvogel.h"
#define DEFAULT_BIRD_SPEED_X 1
#define DEFAULT_BIRD_SPEED_Y 1
#define BIRD_RADIUS 4
#define MAXDISRUPTIONS 15
#define CAMERAFACTOR 5 //Be 5 times as fast as birds

const unsigned int windowX = 1000; //Default values can be overriden
const unsigned int windowY = 1000;

int s_speedX = 1; //Standard bird x speed
int s_speedY = 1; //Standard bird y speed
unsigned int d = 6; //Ideal distance
struct vogel* vogels; //Declare dynamically allocated array

void initialize_vogels_data(int n, int s_speedX, int s_speedY) //n=number of birds
{
    //TODO: Initialize datastructure for data
    vogels = (struct vogel * ) malloc(n * sizeof(struct vogel));
    if(vogels == NULL)
    {
        fprintf(stderr, "malloc() failed!!!\n");
        exit(EXIT_FAILURE);

    }
    int j = 0;
    int row = 0;
    for(int i=0; i<n; i++)
    {
        vogels[i].speedX = s_speedX;
        vogels[i].speedY = s_speedY;
        if(j * (d+BIRD_RADIUS) >=windowX)
        {
            j = 0;
            row++;
        }
        vogels[i].x = j * (d+BIRD_RADIUS);
        vogels[i].y = row * (d+BIRD_RADIUS);
        j++;

    }
}

void usage()
{
    fprintf(stderr, "-n <number of birds to draw> DEFAULT: 2500 \n-x <bird default x speed> \n-y <bird default y speed> \n-d <ideal distance between birds in pixels>\n-m define mass of bird -h show this message\nEXAMPLE: vogel -n 30 -x 20 -y 10\n");
    exit(EXIT_FAILURE);
}

int init_vogels(int n, int s_speedX, int s_speedY, SDL_Renderer* rend, struct cameraType camera)
{
 
 //wrapper function
 initialize_vogels_data(n, s_speedX, s_speedY);
 initialize_vogels_SDL(windowX, windowY, n, rend, vogels, camera);
 return 0;
}


int d_calculateSpeedVector(int massOne, int massTwo, int v) //Usage voor vogel: d_calculateSpeedVector(mobj, vobjx, mvogel)
{
    return (massOne * v) / massTwo; //Wet behoud van impuls


}

void displayInfo(struct collision* collisions, int selected)
{
    printf("Name: %s \n Mass: %d \n Radius: %d \n Speed; %d \n", collisions[selected].name, collisions[selected].mass, collisions[selected].radius,collisions[selected].speed);

}
int main(int argc, char** argv) 
{ 
    
        int n = 2500; //Default value
        int bird_mass = 5; //Default value
        struct collision* collisions = NULL;
        collisions = cfg_init(collisions);
        int l_collisions = 0;
        for(int i=0; collisions[i].name !=NULL; i++)
            l_collisions++; //Count how many collision types there are
            

        
        int opt_index = 0; //Option index for passing arguments
        
        while (( opt_index = getopt(argc, argv, "n:x:y:hd:m:")) != -1)
        {
                 switch(opt_index)
                {
                 case 'n':
                    n = atoi(optarg);
                    break;
                 case 'h':
                    usage();
                    break;
                 case 'x':
                    s_speedX = atoi(optarg);
                    break;
                 case 'y':
                   s_speedY = atoi(optarg);
                   break;
                 case 'd':
                   d = atoi(optarg);
                   break;
                 case 'm':
                   bird_mass = atoi(optarg);
                   break;

                }

        }
        
        if (optind < argc)
         usage();
    
   
    printf("Initialized. Parameters given:\nvx(bird): %d, vy(bird): %d\nIdeal distance: %d\nNumber of birds: %d\nBird Mass: %d\n",s_speedX, s_speedY, d, n, bird_mass); 
    //Main setup
    
    //SDL code after here
    // retutns zero on success else non-zero 
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { 
        printf("error initializing SDL: %s\n", SDL_GetError()); 
    } 
   SDL_Window* win = SDL_CreateWindow("Vogel", 
                                       SDL_WINDOWPOS_CENTERED, 
                                       SDL_WINDOWPOS_CENTERED, 
                                       windowX, windowY, 0); 

    uint32_t render_flags = SDL_RENDERER_ACCELERATED;

    //Create renderer
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
    struct cameraType camera;
    camera.x = 0;
    camera.y = 0;
    camera.c_auto = true;
    init_vogels(n, s_speedX, s_speedY, rend, camera);
   

    const signed int CAMERA_SPEED = sqrt((s_speedX*s_speedX) + (s_speedY * s_speedY))*CAMERAFACTOR;
    int close = 0;
    int selected = 0;
    struct object* objects;
    int allocated_objects = 0; //How many disruptions are allocated


    objects = (struct object*) malloc(sizeof(struct object)); //Ensure there is space for at least one object
    displayInfo(collisions, selected);
    while (!close)
    {
        SDL_Event event;
        
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<=allocated_objects-1; j++)
            {
                if(abs(vogels[i].x - objects[j].x) < objects[j].radius && abs(vogels[i].y - objects[j].y) < objects[j].radius ){ //Check for collision
                    vogels[i].speedX = d_calculateSpeedVector(objects[j].mass, bird_mass, objects[j].speedX);
                    vogels[i].speedY = d_calculateSpeedVector(objects[j].mass, bird_mass, objects[j].speedY);
                    deleteObject(objects, allocated_objects);
                    allocated_objects--;
                    }
            }

        }

        birdloop_SDL(windowX, windowY, n, rend, vogels, camera, allocated_objects, objects); 
		while (SDL_PollEvent(&event)) {
                       
            switch (event.type)
            {
                case SDL_KEYDOWN:
                    if(camera.c_auto == true)
                    {
                        if(event.key.keysym.sym == SDLK_SPACE)
                        {
                            camera.c_auto = false;
                            
                        }    
                    }
                    else if(camera.c_auto == false)
                    {
                        switch(event.key.keysym.sym)
					    {
					    	  case SDLK_LEFT:  camera.x-=CAMERA_SPEED; break;
					          case SDLK_RIGHT: camera.x+=CAMERA_SPEED; break;
					          case SDLK_UP:    camera.y-=CAMERA_SPEED; break;
					          case SDLK_DOWN:  camera.y+=CAMERA_SPEED; break;
					          case SDLK_SPACE: camera.c_auto = true; break;	
                       }
                    }
                    switch(event.key.keysym.sym)
                    {
                              case SDLK_j: 
                              if(selected<l_collisions-1)
                                selected++;
                              else
                                selected = 0;

                              displayInfo(collisions, selected);
                              break;
                              case SDLK_k: 
                              if(selected<=0)
                                selected = l_collisions -1;
                              else
                                selected--;
                              
                              displayInfo(collisions, selected);
                              break;
                              case SDLK_q:
                                close = 1;
                                break;
                    }
					break;
				
                case SDL_MOUSEBUTTONDOWN:
                    switch(event.button.button)
                    {
                        case SDL_BUTTON_LEFT:
                        allocated_objects++;
                        objects = createObject(objects, collisions, event.motion.x, event.motion.y, selected, windowX, windowY, allocated_objects, camera);
                        break;

                        case SDL_BUTTON_RIGHT:
                        break;

                    }
                break;
			 case SDL_QUIT:
                    close = 1;
                    break;


            }
         }


    }
         
    free(vogels); 
    free(objects);
    free(collisions);
    return 0; 
}

