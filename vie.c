#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "joueur.h"
#include"vie.h"

void init_vie(vie *v) 
{
 (v->position.x)=300;
 (v->position.y)=0;
 (v->val)=0 ;
 (v->image[0])=IMG_Load("vies/vie0.png") ;
 (v->image[1])=IMG_Load("vies/vie1.png") ;
 (v->image[2])=IMG_Load("vies/vie2.png") ;
 (v->image[3])=IMG_Load("vies/vie3.png") ;
 (v->image[4])=IMG_Load("vies/vie4.jpg") ;

}
void updatevie(vie *v,int test,joueur *j) 
{

if(test && v->val <4) 
 (v->val)++;


}
void displayvie(vie v ,SDL_Surface *ecran) 
{

SDL_BlitSurface(v.image[v.val],NULL,ecran,&(v.position));

					

}
void vie_freevie(vie *v ) 
{
SDL_FreeSurface(v->image[0]);
SDL_FreeSurface(v->image[1]);
SDL_FreeSurface(v->image[2]);
SDL_FreeSurface(v->image[3]);
SDL_FreeSurface(v->image[4]);
}

 
   
              



 
 






			
			
