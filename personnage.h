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
    int posX;
    int posY;
    int animationFrame;
    int animationFramesTotal;
    int direction;
    SDL_Surface *currentFrame;
} Personnage;

void affichePersonnage(Personnage personnage, SDL_Surface *background);
Personnage initPersonnage();
void loadSprite(Personnage *personnage);