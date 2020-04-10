#include "gameplay.h"

Personnage personnage;

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

Personnage gameplayEventHandler(Personnage personnage)
{
    SDL_WaitEvent(&event);
    switch (event.type)
    {
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_RIGHT:
            personnage.direction = 0;
            personnage.posX = personnage.posX + 15;
            break;
        case SDLK_LEFT:
            personnage.direction = 1;
            personnage.posX = personnage.posX - 15;
        default:
            break;
        }
        break;
    case SDL_MOUSEBUTTONDOWN:
        if (mouseX > personnage.posX)
        {

            personnage.direction = 0;
            personnage.posX = personnage.posX + 15;
        }
        else if (mouseX < personnage.posX)
        {
            personnage.direction = 1;
            personnage.posX = personnage.posX - 15;
        }
        break;
    default:
        break;
    }
    return personnage;
}

void gameplayPipeline()
{
    SDL_Surface *background;
    background = load_image("assets/bgGameplay.png", 0);
    apply_surface(0, 0, background, screen, NULL);
    personnage = loadSprite(personnage, personnage.direction);
    affichePersonnage(personnage, screen);
    personnage = gameplayEventHandler(personnage);
}
