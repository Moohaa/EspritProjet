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
    personnage.posX = 100;
    personnage.posY = 485;
    return personnage;
}

Personnage loadSprite(Personnage personnage, int direction)
{
    char filepath[50];
    if (direction == 1)
    {
        sprintf(filepath, "personnagesG/personnage/%d/pl%d.png", direction, personnage.animationFrame);
    }
    else
    {
        sprintf(filepath, "personnagesG/personnage/%d/pr%d.png", direction, personnage.animationFrame);
    }

    personnage.currentFrame = load_image(filepath, 0);
    Uint32 colorkey = SDL_MapRGB(personnage.currentFrame->format, 0, 0xFF, 0);
    SDL_SetColorKey(personnage.currentFrame, SDL_SRCCOLORKEY, colorkey);
    personnage.animationFrame = personnage.animationFrame + 1;
    if (personnage.animationFrame > 8)
    {
        personnage.animationFrame = 1;
    }
    return personnage;
}
