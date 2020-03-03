#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_rotozoom.h>
 #include "joueur.h"
 #include "rotation.h"
#define TEMPS       30 
 void rooto(SDL_Surface *screen,joueur *j)
{
 SDL_Surface *rotation = NULL;
   
    SDL_Event event;
    double angle = 0;
    double zoom = 1;
    int sens = 1;
 
    int stop = 1;
    int Prev = 0, Now = 0;
 
  
 
    while(stop)
    {
        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
               stop = 0;
                break;

        
  case SDL_KEYDOWN:


		switch(event.key.keysym.sym)
		{               
		case SDLK_ESCAPE:

                 stop = 0;
		}
}	
        
        Prev = SDL_GetTicks();
        if (Now - Prev > TEMPS)
        {
            angle += 2; 
 
            Prev = Now;
        }
        else
        {
            SDL_Delay(TEMPS - (Now - Prev));
        }
 

 
        rotation = rotozoomSurface(j->imgA, angle, zoom, 0); 
         SDL_BlitSurface(rotation , NULL, screen, &j->position); 
        SDL_Flip(ecran);


       
        if(zoom >= 2)
         {sens = 0;}
        else if(zoom <= 0.5)
        {sens = 1;}
 
        if(sens == 0)
         {zoom -= 0.02;}
        else{zoom += 0.02;}

  
        SDL_Flip(screen);
    } 





        SDL_FreeSurface(rotation); 

 
 

