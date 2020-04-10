#include "personnage.h"

void affichePersonnage(Personnage personnage, SDL_Surface *screen)
{
    apply_surface(personnage.posX, personnage.posY, personnage.currentFrame, screen, NULL);
}

Personnage initPersonnage()
{
    Personnage personnage;
    personnage.animationFrame = 1;
    personnage.direction = 0;
    personnage.posX = 20;
    personnage.posY = 600;
    return personnage;
}

Personnage loadSprite(Personnage personnage, int direction)
{
    char filepath[50];
    if (direction == 1)
    {
        sprintf(filepath, "personnages/personnage/%d/pl%d.png", direction, personnage.animationFrame);
    }
    else
    {
        sprintf(filepath, "personnages/personnage/%d/pr%d.png", direction, personnage.animationFrame);
    }

    personnage.currentFrame = load_image(filepath, 0);
    personnage.animationFrame = personnage.animationFrame + 1;
    if (personnage.animationFrame > 8)
    {
        personnage.animationFrame = 1;
    }
    return personnage;
}
