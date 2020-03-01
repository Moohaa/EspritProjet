#include "personnage.h"

void loadSprites(Personnage personnage, SDL_Surface *frames[10]);
void affichePersonnage(Personnage personnage, SDL_Surface *background)
{
    apply_surface(personnage.posX, personnage.posY, personnage.sprites[personnage.animationFrame], background, NULL);
}

Personnage initPersonnage()
{
    Personnage personnage;
    personnage.posX = 0;
    personnage.posY = 0;
    personnage.hp = 100;
    return personnage;
}