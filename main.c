
#include <stdio.h>
#include <unistd.h> //for sleep function
#include <math.h>
#include <limits.h>
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_timer.h> 
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include "libvogel.h"
#define DEFAULT_BIRD_SPEED_X 1
#define DEFAULT_BIRD_SPEED_Y 1
#define BIRD_RADIUS 4
#define MAXDISRUPTIONS 15
#define CAMERAFACTOR 5 //Be 5 times as fast as birds

const unsigned int windowX = 1000; //Default values can be overriden
const unsigned int windowY = 1000;
double s_speedX = 1; //Standard bird x speed
double s_speedY = 1; //Standard bird y speed
int d = 6; //Ideal distance
int bird_mass = 5; //default value
int n = 50; //nr of birds flying around
//struct vogel* vogels; //Declare dynamically allocated array

unsigned int vdecel = 2;
unsigned int nprow = 0; //Birds per row
unsigned int t_row = 1; //Total number of rows with bridz
  
bool collision = false;
int max_hulpvogels=0;


void usage()
{
    fprintf(stderr, "-n <number of birds to draw> DEFAULT: 2500 \n-x <bird default x speed> \n-y <bird default y speed> \n-d <ideal distance between birds in pixels>\n-m define mass of bird -h show this message\n -v define deccelaration speed\nEXAMPLE: vogel -n 30 -x 20 -y 10\n");
    exit(EXIT_FAILURE);
}


int d_calculateSpeedVector(int massOne, int massTwo, int v) //Usage voor vogel: d_calculateSpeedVector(mobj, vobjx, mvogel)
{
    return (massOne * v) / massTwo; //Wet behoud van impuls
}


bool isIntersect(int ax, int ay, int aw, int ah, int bx, int by, int bw, int bh)
{
    return bx + bw > ax && by + bh > ay && ax +aw > bx && ay + ah > by;
}


void displayInfo(struct collision* collisions, int selected)
{
    printf("Name: %s \n Mass: %d \n Radius: %d \n Speed; %d \n", collisions[selected].name, collisions[selected].mass, collisions[selected].radius,collisions[selected].speed);

}


int square(int number) //Helper function for readabillity
{
    return number*number;
}


int **fill_hulpvogels(int i, int j, struct vogel vogels2[n][n]) 
{
  int **h =(int **)malloc(sizeof(int *)*n);
  int hulpvogels_gevonden = 1;
  int huidige_hulpvogel = 2;
  int teller1 = 0;
  int teller2 = 0;

  for (teller1=0; teller1<n; teller1++)
      h[teller1] = (int *)malloc(sizeof(int)*n); 

  for (teller1=0; teller1<n; teller1++)
      for (teller2=0; teller2<n; teller2++)
          h[teller1][teller2]=0;
 

   huidige_hulpvogel = 2;
     //maak hulpvogel matrix 
     //matrix heeft zelfde grootte als aantal vogels
     //positie in matrix met cijfer 1: dit is de geraakte vogel
     //daaromheen krijgen ze cijfer 2
     //dus elk cijfer geeft aan naar welke buurman gekeken moet worden om juiste snelheid te berekenen
     //dus vakje met cijfer 3->kijkt naar al zijn buren. diegene die een 2 hebben als buurman zijn nodig om zijn nieuwe snelheid te bepalen
   h[i][j]=1;
   while (hulpvogels_gevonden<(n*n))
       {
       for(teller1=0; teller1<n;teller1++)
          for (teller2=0; teller2<n;teller2++)
             {
                //printf("check:(%d,%d)\n", teller1, teller2);
                if (h[teller1][teller2]==huidige_hulpvogel-1)
                {//vul buren
                 //printf("positie: %d,%d, misschien gevonden:%d|n", teller1, teller2, huidige_hulpvogel);
                 if (teller2-1>=0) if (h[teller1][teller2-1]==0) {h[teller1][teller2-1]=huidige_hulpvogel; hulpvogels_gevonden++;}//noord 
                 if (teller1+1<n) if (h[teller1+1][teller2]==0) {h[teller1+1][teller2]=huidige_hulpvogel; hulpvogels_gevonden++;} //oost   
                 if (teller2+1<n) if (h[teller1][teller2+1]==0) {h[teller1][teller2+1]=huidige_hulpvogel; hulpvogels_gevonden++;} //zuid
                 if (teller1-1>=0) if (h[teller1-1][teller2]==0) {h[teller1-1][teller2]=huidige_hulpvogel; hulpvogels_gevonden++;} //west      
                 }
             }    
             huidige_hulpvogel++;        
             //printf("huidige hulpvogel onderzoeken: %d, hulpvogelsgevonden: %d, \n", huidige_hulpvogel, hulpvogels_gevonden);
          
        }
    max_hulpvogels = huidige_hulpvogel;    
    return h;
}

void set_position(int i, int j, int n, struct vogel vogels2[n][n], int** hulpvogels, double t, double c)
{
 
 if(i-1>0) //indien linker vogel bestaat
    {  
               
    if(round(fabs(vogels2[i][j].x - vogels2[i-1][j].x)) != d + BIRD_RADIUS) 
       { 
          vogels2[i][j].speedX += (c/bird_mass * ((d + BIRD_RADIUS) - (fabs(vogels2[i][j].x - vogels2[i-1][j].x)))*t);
       }
    }    
 if (i+1<n)
    {
   if(round(fabs(vogels2[i][j].x - vogels2[i+1][j].x)) != d + BIRD_RADIUS)
       {
         vogels2[i][j].speedX += - (c/bird_mass * ((d + BIRD_RADIUS) - (fabs(vogels2[i][j].x - vogels2[i+1][j].x)))*t);
       }
    } 
 if (j-1>0) //bekijk afstand tot noorderbuur
    {  
    if(round(fabs(vogels2[i][j].y - vogels2[i][j-1].y)) != d + BIRD_RADIUS)
       {
            vogels2[i][j].speedY += (c/bird_mass * ((d + BIRD_RADIUS) - (fabs(vogels2[i][j].y - vogels2[i][j-1].y)))*t);
       }
    } 
 if (j+1<n)
    { 
    if(round(fabs(vogels2[i][j].y - vogels2[i][j+1].y) != d + BIRD_RADIUS))
       {
           vogels2[i][j].speedY += - (c/bird_mass * ((d + BIRD_RADIUS) - (fabs(vogels2[i][j].y - vogels2[i][j+1].y)))*t);
       } 
     }
         
//         printf("vogels[%d][%d].speedX: %f, vogels[%d][%d].speedY: %f, xpos: %f  ", i, j, vogels2[i][j].speedX, i, j, vogels2[i][j].speedY, vogels2[i][j].x);
//        printf("vogels[%d][%d[).x,y  %f, %f\n", i,j, vogels2[i][j].x, vogels2[i][j].y);

}



// mbv hulpvogel
 void change_position(int windowX, int windowY, int n, SDL_Renderer* rend, struct vogel vogels2[n][n], int** hulpvogels, struct cameraType camera, double t, double c)
{  
 
   if (collision)
     for (int hulpvogel = 1; hulpvogel<max_hulpvogels; hulpvogel ++) 
       for(int i=0; i<n; i++)
       {
          for(int j=0; j<n; j++)
          {
           if (hulpvogels[i][j] == hulpvogel)
              { 
              //printf("SET HULPVOGEL !!!!!!!!!![%d][%d]: HUIDIGE HULPVOGEL: %d\n", i,j, hulpvogel);
              set_position(i,j,n, vogels2, hulpvogels, t, c);
              }
          }
      }
   else      

     for(int i=0; i<n; i++)
     {
        for(int j=0; j<n; j++)
        {
 
 
          set_position(i,j,n, vogels2, hulpvogels, t, c);
      
        } 
    } 
}

               


int main(int argc, char** argv) 
{ 
    
        int n = 25; //Default value
        int bird_mass = 5; //Default value
        struct collision* collisions = NULL;
        collisions = cfg_init(collisions);
        int l_collisions = 0;
        double c = 6; //Was 600 
        double t = 0;
        #define DT 0.01
        //struct vogel vogels2[n][n];
       int **hulpvogels;
     

        for(int i=0; collisions[i].name !=NULL; i++)
            l_collisions++; //Count how many collision types there are
            

        
        int opt_index = 0; //Option index for passing arguments
        
        while (( opt_index = getopt(argc, argv, "n:x:y:hd:m:v:c:")) != -1)
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
                 case 'v':
                   vdecel = atoi(optarg);
                   break;
                 case 'c':
                   c = atof(optarg);
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
    struct vogel vogels2[n][n];
    int i,j;
    for (i=0; i<n; i++)
        for (j=0; j<n; j++)
         {
            vogels2[i][j].speedX = s_speedX;
            vogels2[i][j].speedY = s_speedY;
            vogels2[i][j].x = i*(BIRD_RADIUS + d);
            vogels2[i][j].y = j*(BIRD_RADIUS + d);
            vogels2[i][j].disruption=false;
        }
   

    //init_vogels(n, s_speedX, s_speedY, rend, camera);
   // printf("Total number of rows: %d, birds per row: %d\n", t_row, nprow);
    
    initialize_vogels2_SDL(windowX, windowY, n, rend, vogels2, camera);
  

    const unsigned int CAMERA_SPEED = sqrt((s_speedX*s_speedX) + (s_speedY * s_speedY))*CAMERAFACTOR;
    int close = 0;
    int selected = 0;
    struct object* objects;
    int allocated_objects = 0; //How many disruptions are allocated
    
    
    

    objects = (struct object*) malloc(sizeof(struct object)); //Ensure there is space for at least one object
    
    displayInfo(collisions, selected);

    while (!close)
    {
        SDL_Event event;
        if (t>50*DT) 
        {  //t mag niet te groot worden
           if (collision) free(hulpvogels);
           collision = false;           
           t=0;
           for(int i=0; i<n; i++)
           {
               for(int j=0; j<n; j++)
               {
                
                //  halveer telkens snelheid, totdat je op oude snelheid zit
                vogels2[i][j].speedX = vogels2[i][j].speedX / 2;
                vogels2[i][j].speedY = vogels2[i][j].speedY / 2;
                if (fabs(vogels2[i][j].speedX) < s_speedX) 
                   vogels2[i][j].speedX = s_speedX; 
                if (fabs(vogels2[i][j].speedY) < s_speedY) 
                   vogels2[i][j].speedY = s_speedY; 


               }
           }
           
        } 
        
        for(int i=0; i<n; i++)
          {
          for (int j=0; j<n; j++)
              for(int k=0; k<=allocated_objects-1; k++)
              {
                 if(isIntersect(vogels2[i][j].x, vogels2[i][j].y, BIRD_RADIUS, BIRD_RADIUS, objects[k].x, objects[k].y, objects[k].radius, objects[k].radius))
                 {       
                   vogels2[i][j].speedX = d_calculateSpeedVector(objects[k].mass, bird_mass, objects[k].speedX);
                   vogels2[i][j].speedY = d_calculateSpeedVector(objects[k].mass, bird_mass, objects[k].speedY);
                   vogels2[i][j].disruption = true;
                   deleteObject(objects, allocated_objects);
                   allocated_objects--;
                        
                    collision = true;     
                    //printf("COLLISION: %d, %d\n", i, j);
                    
              
                    hulpvogels = fill_hulpvogels(i, j, vogels2);
                     
                  

                    printf("Klaar met intersect\n");
                      
                  } //if is intersect 
              
              }
        }
      
        for(int i=0; i<n; i++)
        {
              for(int j=0; j<n; j++)
              {
                // vogels2[i][j].x = vogels2[i][j].x + (vogels2[i][j].speedX*t);
                //zorgt ervoor dat vogels niet kunnen worden ingehaald
                if (i != n-1)
                   if (vogels2[i][j].x + (vogels2[i][j].speedX*t) > vogels2[i+1][j].x)
                    //  vogels2[i][j].x = vogels2[i+1][j].x - 1 - vogels2[i][j].speedX*t;  //zet op afstand van 1 
                       vogels2[i][j].x = vogels2[i+1][j].x - (d + BIRD_RADIUS) - vogels2[i][j].speedX*t;  //zet vogel op ideale afstand
                    // vogels2[i][j].x -= vogels2[i][j].speedX*t ;

                     
                if (i != 0)
                  if (vogels2[i][j].x + (vogels2[i][j].speedX*t) < vogels2[i-1][j].x)
                   //vogels2[i][j].x = vogels2[i-1][j].x + (1) - vogels2[i][j].speedX*t;
                     vogels2[i][j].x = vogels2[i-1][j].x + (d + BIRD_RADIUS) - vogels2[i][j].speedX*t;
                  //  vogels2[i][j].x -= vogels2[i][j].speedX*t;
                
                vogels2[i][j].x += vogels2[i][j].speedX*t;
               
               

               // zorgt ervoor dat vogels niet ingehaald kunnen worden
               if (j != n-1)
                 if (vogels2[i][j].y + (vogels2[i][j].speedY*t) > vogels2[i][j+1].y)
                 //   vogels2[i][j].y = vogels2[i][j+1].y - (1) - vogels2[i][j].speedY*t;
                    vogels2[i][j].y = vogels2[i][j+1].y - (d + BIRD_RADIUS) - vogels2[i][j].speedY*t;
                //   vogels2[i][j].y -= vogels2[i][j].speedY*t;
               if (j != 0)
                 if (vogels2[i][j].y + (vogels2[i][j].speedY*t) < vogels2[i][j-1].y)
                   //vogels2[i][j].y = vogels2[i][j-1].y + (1) - vogels2[i][j].speedY*t;
                    vogels2[i][j].y = vogels2[i][j-1].y + (d + BIRD_RADIUS) - vogels2[i][j].speedY*t;
                  // vogels2[i][j].y -=vogels2[i][j].speedY*t;


               
               vogels2[i][j].y += (vogels2[i][j].speedY*t);
            }
         }
       
       change_position(windowX, windowY, n, rend, vogels2, hulpvogels, camera, t, c);
          
       SDL_SetRenderDrawColor(rend,0,0,0,255);
       SDL_RenderClear(rend);
        
 
        birdloop_SDL2(windowX, windowY, n, rend, vogels2, camera, allocated_objects, objects); 
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
    t += DT;
 
   }
         

    free(objects);
    free(collisions);
    return 0; 
}

