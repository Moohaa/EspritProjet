#include "ennemies.h"

Ennemi ennemi1;
Ennemi ennemi2;
Ennemi ennemis[2];

void initEnnemi()
{
    ennemi1.posX = 700;
    ennemi2.posX = 400;
    ennemi1.posY = 600;
    ennemi2.posY = 600;
    ennemi1.posXDeb = 700;
    ennemi1.posXFin = 900;
    ennemi2.posXDeb = 350;
    ennemi2.posXDeb = 500;
    ennemi1.animationFrame = 0;
    ennemi2.animationFrame = 0;
}

void afficheEnnemi(Ennemi ennemi, SDL_Surface *background)
{
    apply_surface(ennemi.posX, ennemi.posY, ennemi.currentFrame, screen, NULL);
}

Ennemi loadSpriteEnnemi(Ennemi ennemi, int direction)
{
    char filepath[50];
    if (direction == 1)
    {
        sprintf(filepath, "personnages/ennemi/%d/el%d.png", direction, ennemi.animationFrame);
    }
    else
    {
        sprintf(filepath, "personnages/ennemi/%d/er%d.png", direction, ennemi.animationFrame);
    }

    ennemi.currentFrame = load_image(filepath, 0);
    ennemi.animationFrame = ennemi.animationFrame + 1;
    if (ennemi.animationFrame > 7)
    {
        ennemi.animationFrame = 0;
    }
    return ennemi;
}
void remplirTableauEnnemi()
{
    ennemis[0] = ennemi1;
    ennemis[1] = ennemi2;
}