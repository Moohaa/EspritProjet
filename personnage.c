#include "personnage.h"

void affichePersonnage(Personnage personnage, SDL_Surface *screen)
{
    apply_surface(personnage.posX, personnage.posY, personnage.currentFrame, screen, NULL);
}

Personnage initPersonnage()
{
    Personnage personnage;
    personnage.posX = 860;
    personnage.posY = 20;
    return personnage;
}

Personnage loadSprite(Personnage personnage, int direction)
{
    char filepath[50];
    sprintf(filepath, "/personnages/personnage/%d/pl%d.png", direction, personnage.animationFrame);
    personnage.currentFrame++;
    if (personnage.animationFrame > 8)
    {
        personnage.animationFrame = 1;
    }
    return personnage;
}
