
#include "gameplay.h"

int boundingBoxCollision(SDL_Rect a, SDL_Rect b)
{
    return (abs(a.x - b.x) * 2 < (a.w + b.w)) &&
           (abs(a.y - b.y) * 2 < (a.h + b.h));
}

void afficherPersonnage(Personnage personnage, SDL_Surface *screen)
{
    apply_surface(personnage.posX, personnage.posY, personnage.currentFrame, screen, NULL);
}
void afficherEntitiesSecondaires();

int collisionDetection(Personnage personnage);

int perfectPixelCollision(SDL_Rect a, int x, int y);

void initGameplay()
{
    personnage = initPersonnage();
}

void gameplayPipeline()
{
    affichePersonnage(personnage, screen);
    afficherEntitiesSecondaires();
    if (collisionDetection(personnage) == 1)
    {
        if (EnigmePipeline() == 4)
        {
        }
        else
        {
        }
    }
}