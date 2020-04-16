#include "defs.h"
#include "utils.h"

typedef struct ennemi
{
    int posX;
    int posY;
    int animationFrame;
    int direction; // 0 : right / 1 : left
    SDL_Surface *currentFrame;
    int posXDeb;
    int posXFin;
} Ennemi;

extern Ennemi ennemi1;
extern Ennemi ennemi2;
extern Ennemi ennemis[2];

void afficheEnnemi(Ennemi ennemi, SDL_Surface *background);
void initEnnemi();
Ennemi loadSpriteEnnemi(Ennemi ennemi, int direction);
void remplirTableauEnnemi();
Ennemi killEnnemy(Ennemi ennemi);