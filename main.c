
#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_timer.h> 
#define DEFAULT_BIRD_SPEED_X 1
#define DEFAULT_BIRD_SPEED_Y 1
const unsigned int windowX = 1000; //Default values can be overriden
const unsigned int windowY = 1000;

struct vogel //Create data structure voor vogel
{
    int speedX;
    int speedY;
    int x; //locatie
    int y; //locatie
    struct vogel *next;
};

struct vogel* vogels; //Declare dynamically allocated array

int initialize_vogels_data(int n, int s_speedX, int s_speedY) //n=number of birds
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
    return 0; 

}

int initialize_vogels_SDL()
{

    //TODO: Initialize vogels to draw
    fprintf(stderr, "TODO!");
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
    //Main setup
   const int n = 20000; //Start with 20 birds
   init_vogels(n, DEFAULT_BIRD_SPEED_X, DEFAULT_BIRD_SPEED_Y); 
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
         
  
    return 0; 
}

