#include "defs.h"
#include "utils.h"

typedef struct personnage
{

    int speed;
    int frameImmuninty;
    int posX;
    int posY;
    int animationFrame;
    int direction; // 0 : right / 1 : left
    SDL_Surface *currentFrame;
} Personnage;

extern Personnage personnage;

void affichePersonnage(Personnage personnage, SDL_Surface *background);
Personnage initPersonnage();
Personnage loadSprite(Personnage personnage, int direction);