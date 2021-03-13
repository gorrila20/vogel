
#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_timer.h> 
#include <unistd.h>
#define DEFAULT_BIRD_SPEED_X 1
#define DEFAULT_BIRD_SPEED_Y 1
const unsigned int windowX = 1000; //Default values can be overriden
const unsigned int windowY = 1000;

int s_speedX = 1; //Standard bird x speed
int s_speedY = 1; //Standard bird y speed

struct vogel //Create data structure voor vogel
{
    int speedX;
    int speedY;
    int x; //locatie
    int y; //locatie
    struct vogel *next;
};

struct vogel* vogels; //Declare dynamically allocated array

void initialize_vogels_data(int n, int s_speedX, int s_speedY) //n=number of birds
{
    //TODO: Initialize datastructure for data
    vogels = (struct vogel * ) malloc((n+1) * sizeof(struct vogel));
    if(vogels == NULL)
    {
        fprintf(stderr, "malloc() failed!!!\n");
        exit(EXIT_FAILURE);

    }
    int j = 0;
    int row = 0;
    for(int i=0; i<=n; i++)
    {
        vogels[i].speedX = s_speedX;
        vogels[i].speedY = s_speedY;
        if(j >=windowX)
        {
            j = 0;
            row++;
        }
        
        vogels[i].x = j * 2;
        vogels[i].y = row;
        j++;

    }
}

void usage()
{
    fprintf(stderr, "-n <number of birds to draw> \n-x <bird default x speed> \n-y <bird default y speed> \n-h show this message\nEXAMPLE: vogel -n 30 -x 20 -y 10\n");
    exit(EXIT_FAILURE);
}
int initialize_vogels_SDL()
{

    //TODO: Initialize vogels to draw
    fprintf(stderr, "TODO!");

    return 0;
}

int init_vogels(int n, int s_speedX, int s_speedY)
{
 
 //wrapper function
 initialize_vogels_data(n, s_speedX, s_speedY);
 initialize_vogels_SDL();

}


int d_calculateSpeedVector(int massOne, int massTwo, int v) //Usage voor vogel: d_calculateSpeedVector(mobj, vobjx, mvogel)
{
    return (massOne * v) / massTwo; //Wet behoud van impuls


}


int main(int argc, char** argv) 
{ 
    
    int n = 20; //Default value
   

 
        int opt_index = 0; //Option index for passing arguments

        while (( opt_index = getopt(argc, argv, "n:x:y:h")) != -1)
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

                }

        }
        
        if (optind < argc)
         usage();
    
    init_vogels(n, s_speedX, s_speedY);
    
    //Main setup
    for(int i =0; i<=n; i++)
    {
        printf("X: %d Y: %d SpeedX: %d SpeedY: %d\n", vogels[i].x, vogels[i].y, vogels[i].speedX, vogels[i].speedY);

    }
    //SDL code after here
    // retutns zero on success else non-zero 
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { 
        printf("error initializing SDL: %s\n", SDL_GetError()); 
    } 
   printf("INIT!\n");
   SDL_Window* win = SDL_CreateWindow("Vogel", 
                                       SDL_WINDOWPOS_CENTERED, 
                                       SDL_WINDOWPOS_CENTERED, 
                                       windowX, windowY, 0); 

    uint32_t render_flags = SDL_RENDERER_ACCELERATED;

    //Create renderer
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);

    //Creates surface to load visual data
    int close = 0;
    while (!close)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type)
            {
                case SDL_QUIT:
                    close = 1;
                    break;


            }
         }


    }
         
    free(vogels);  
    return 0; 
}

