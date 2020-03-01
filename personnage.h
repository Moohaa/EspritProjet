#include "defs.h"
#include "utils.h"
#include "inits.h"

typedef struct personnage
{
    int hp;
    int velocity;
    int acceleration;
    int speed;
    int frameImmuninty;
    SDL_Surface *sprites[10];
    int posX;
    int posY;
    int animationFrame;
} Personnage;

void loadSprites(Personnage personnage, SDL_Surface *frames[10]);
void affichePersonnage(Personnage personnage, SDL_Surface *background);
Personnage initPersonnage();