#include "personnage.h"

void affichePersonnage(Personnage personnage, SDL_Surface *background)
{
    apply_surface(personnage.posX, personnage.posY, personnage.currentFrame, background, NULL);
}

Personnage initPersonnage()
{
    Personnage personnage;
    personnage.posX = 0;
    personnage.posY = 0;
    personnage.hp = 100;
    return personnage;
}

void loadSprite(Personnage *personnage)
{
    if (personnage->direction == 1)
    {
        char filePath[50];
        sprintf(filePath, "assets/m2/%d.png", personnage->animationFrame);
        personnage->currentFrame = load_image(filePath, 0);
    }
    else
    {
    }
}