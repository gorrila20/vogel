
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

#define CAMERA_SPEED 10

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
    fprintf(stderr, "-n <number of birds to draw> DEFAULT: 2500 \n-x <bird default x speed> \n-y <bird default y speed> \n-d <ideal distance between birds in pixels>\n-h show this message\nEXAMPLE: vogel -n 30 -x 20 -y 10\n");
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


int main(int argc, char** argv) 
{ 
    
    int n = 2500; //Default value
   
        struct collision* collisions = NULL;
        cfg_init(collisions); 
        int opt_index = 0; //Option index for passing arguments

        while (( opt_index = getopt(argc, argv, "n:x:y:hd:")) != -1)
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

                }

        }
        
        if (optind < argc)
         usage();
    
   
    printf("Initialized. Parameters given:\nvx(bird): %d, vy(bird): %d\nIdeal distance: %d\nNumber of birds: %d\n",s_speedX, s_speedY, d, n); 
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
   


    //Creates surface to load visual data
    int close = 0;
    while (!close)
    {
        SDL_Event event;
        birdloop_SDL(windowX, windowY, n, rend, vogels, camera); 
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
					break;
				
				case SDL_QUIT:
                    close = 1;
                    break;


            }
         }


    }
         
    free(vogels);  
    return 0; 
}

