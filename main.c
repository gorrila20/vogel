
#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_timer.h> 
#define DEFAULT_BIRD_SPEED_X 1
#define DEFAULT_BIRD_SPEED_Y 1
const int windowX = 1000; //Default values can be overriden
const int windowY = 1000;

struct vogel //Create data structure voor vogel
{
    int speedX;
    int speedY;
    int x; //locatie
    int y; //locatie
    struct vogel *next;
};

struct vogel *prev, *head, *p; //define list variables

int initialize_vogels_data(int n, int s_speedX, int s_speedY) //n=number of birds
{
    //TODO: Initialize datastructure for data
    
   head = NULL;
   for(int i=0; i<=n; i++)
   {
            p = malloc(sizeof(struct vogel)); //allocate memory
            p->speedX = s_speedX;
            p->speedY = s_speedY;
            p->x = i*2;
            p->y = 0;
            p->next = NULL;
            if(head==NULL)
                head=p;
            else
                prev->next=p;
            prev=p;
   }

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


void display()
{ //Display linked list debug function
    struct vogel *tmp;
    tmp = head;
    while(tmp != NULL)
    {
        printf("X: %d Y: %d speedX: %d speedY: %d\n", tmp->x,tmp->y,tmp->speedX,tmp->speedY);
        tmp = tmp->next;

    }

}

int d_calculateSpeedVector(int massOne, int massTwo, int v) //Usage voor vogel: d_calculateSpeedVector(mobj, vobjx, mvogel)
{
    return (massOne * v) / massTwo; //Wet behoud van impuls


}


int main(int argc, char** argv) 
{ 
    //Main setup
   const int n = 20; //Start with 20 birds
   init_vogels(n, DEFAULT_BIRD_SPEED_X, DEFAULT_BIRD_SPEED_Y); 
   display();
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
    SDL_Surface* surface;
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

