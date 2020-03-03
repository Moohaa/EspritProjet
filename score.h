#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
 

typedef struct 
{

    TTF_Font *police;
SDL_Rect position ;  



SDL_Surface *texte;

    int Now, Prev, compteur;

 

} score ; 
void intialiser_score(score *s);
void score_pers(score *s,SDL_Surface *screen);
void afficher_score(score s,SDL_Surface *screen);

#endif
