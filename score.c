#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "score.h"

void intialiser_score(score *s)
{
SDL_Color couleurNoire = {0, 0, 0};
  SDL_Color  couleurBlanche = {255, 255, 255};
char  temps[20] = "";
   s->police = NULL;
      s->Now = 0;
 s->Prev = 0;
 s->compteur =2;
  s->police = TTF_OpenFont("images/texte.ttf", 60); 
        s->position.x = 0;
        s->position.y = 0;
            s->texte = TTF_RenderText_Shaded(s->police, temps, couleurNoire,couleurBlanche); 

}
void score_pers( score *s,SDL_Surface *ecran)
{
 SDL_Color couleurNoire = {0, 0, 0};
  SDL_Color  couleurBlanche = {255, 255, 255};



 char  temps[20] = "";

sprintf(temps, "score : %d", s->compteur);

    s->Now = SDL_GetTicks();
        if (s->Now - s->Prev >= 1000) 
        {
            s->compteur += 2; 
            sprintf(temps, "score : %d", s->compteur); 
            SDL_FreeSurface(s->texte);
            s->texte = TTF_RenderText_Shaded(s->police, temps, couleurNoire,couleurBlanche); 
            s->tempsPrecedent = s->tempsActuel;
	}
      


}
void afficher_score(score s,SDL_Surface *screen)
{
	SDL_BlitSurface(s.texte, NULL, screen, &s.position);
}
