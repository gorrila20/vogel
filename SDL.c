#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <stdbool.h>
#define FPS 33 //Cap to 30FPS 1/Actual FPS * 1000
#define BIRD_RADIUS 4


struct vogel //Create data structure voor vogel
{
    double speedX;
    double speedY;
    double x; //locatie
    double y; //locatie
    bool disruption;
};

struct cameraType{
	int x;
	int y;	
	bool c_auto; //Boolean whether the camera automoves to the middle bird
};

struct object
{
    int x;
    int y;
    int mass;
    int radius;
    int speedX;
    int speedY;

};
/*

int initialize_vogels_SDL(int windowX, int windowY, int n,  SDL_Renderer* rend, struct vogel* vogels)
{
	
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);

    SDL_RenderClear(rend);  
    
    SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<BIRD_RADIUS; j++)
        {
            for(int k=0; k<BIRD_RADIUS; k++)
            {GG
            SDL_RenderDrawPoint(rend, vogels[i].x+j, vogels[i].y+k);  
            }
        }
    }
    SDL_RenderPresent(rend);
    return 0;
}

void updateBirds(int windowX, int windowY, int n, SDL_Renderer* rend, struct vogel* vogels, struct cameraType camera)
{
	SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
	SDL_RenderClear(rend);
	SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<BIRD_RADIUS; j++)
		{
			for(int k=0; k<BIRD_RADIUS; k++)
			{
				SDL_RenderDrawPoint(rend, vogels[i].x+j-camera.x, vogels[i].y+k-camera.y);
				
			}
			
		}
		
	}
	
}

void updateObjects(int windowX, int windowY, int allocated_objects, SDL_Renderer* rend, struct object* objects, struct cameraType camera)
{
    SDL_SetRenderDrawColor(rend, 0, 0, 255, 255);
    for (int i=0; i<=allocated_objects-1; i++)
    {
        for(int j=0; j<objects[i].radius; j++)
        {
            for(int k=0; k<objects[i].radius; k++)
            {
                SDL_RenderDrawPoint(rend, objects[i].x+j-camera.x, objects[i].y+k-camera.y);

            }

        }

    }
}
void birdloop_SDL(int windowX, int windowY, int n, SDL_Renderer* rend, struct vogel* vogels, struct cameraType camera, int allocated_objects, struct object* objects)
{
	//Cameraman is vogels[n/2]. 
	for(int i=0; i<n; i++)
	{
		vogels[i].x+=vogels[i].speedX;
		vogels[i].y+=vogels[i].speedY;
        if(camera.c_auto == true)
        {
		    camera.x=vogels[0].x;
		    camera.y=vogels[0].y;
        }
	}

    //Update objects
    for(int i=0; i<=allocated_objects-1; i++)
    {
        objects[i].x+=objects[i].speedX;
        objects[i].y+=objects[i].speedY;
    }

	updateBirds(windowX, windowY,n, rend, vogels, camera);
    updateObjects(windowX, windowY, allocated_objects, rend, objects, camera);
    SDL_Delay(FPS);
    SDL_RenderPresent(rend);
	
}
*/
int initialize_vogels2_SDL(int windowX, int windowY, int n,  SDL_Renderer* rend, struct vogel vogels2[n][n])
{
	
    SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
    
    for(int i=0; i<n; i++)
      for (int j=0; j<n; j++)
        for(int k=0; k<BIRD_RADIUS; k++)
            for(int l=0; l<BIRD_RADIUS; l++)
            {
            SDL_RenderDrawPoint(rend, round(vogels2[i][j].x)+k, round(vogels2[i][j].y)+l);  
            }
        
    
    SDL_RenderPresent(rend);
    return 0;
}

void updateBirds2(int windowX, int windowY, int n, SDL_Renderer* rend, struct vogel vogels2[n][n], struct cameraType camera)
{
    SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
	    {
		
            for(int k=0; k<BIRD_RADIUS; k++)
		    {
			    for(int l=0; l<BIRD_RADIUS; l++)
			    {
				    SDL_RenderDrawPoint(rend, vogels2[i][j].x+k-camera.x, vogels2[i][j].y+l-camera.y);
				
			    }
			
		    }
		
	    }
    }
}

void updateObjects(int windowX, int windowY, int allocated_objects, SDL_Renderer* rend, struct object* objects, struct cameraType camera)
{
    SDL_SetRenderDrawColor(rend, 0, 0, 255, 255);
    
    for (int i=0; i<=allocated_objects-1; i++)
    {
        for(int j=0; j<objects[i].radius; j++)
        {
            for(int k=0; k<objects[i].radius; k++)
            {
                SDL_RenderDrawPoint(rend, objects[i].x+j-camera.x, objects[i].y+k-camera.y);

            }

        }

    }
   
}


void birdloop_SDL2(int windowX, int windowY, int n, SDL_Renderer* rend, struct vogel vogels2[n][n], struct cameraType camera, int allocated_objects, struct object* objects)
{
	
    //Cameraman is vogels[n/2]. 
    if(camera.c_auto == true)
    {   
	    camera.x=round(vogels2[0][0].x);
		camera.y=round(vogels2[0][0].y);
    }
	

    //Update objects
    for(int i=0; i<=allocated_objects-1; i++)
    {
        objects[i].x+=objects[i].speedX;
        objects[i].y+=objects[i].speedY;
    }

	updateBirds2(windowX, windowY,n, rend, vogels2, camera);
    updateObjects(windowX, windowY, allocated_objects, rend, objects, camera);
    
    SDL_Delay(FPS);	
    SDL_RenderPresent(rend);

}

