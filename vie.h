#ifndef VIE_H_INCLUDED
#define VIE_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
 

typedef struct vie 
{
SDL_Rect position ;  
int val ;
SDL_Surface *image[5]; 
} vie ; 


void init_vie(vie *v) ; 
void updatevie(vie *v,int test,joueur *j); 
void displayvie(vie v ,SDL_Surface *ecran) ;  
void vie_freevie(vie *v ) ;  

#endif
