#include "gameplay.h"

Personnage personnage;

void afficherPersonnage(Personnage personnage, SDL_Surface *screen)
{
    apply_surface(personnage.posX, personnage.posY, personnage.currentFrame, screen, NULL);
}

void initGameplay()
{
    personnage = initPersonnage();
    initEnnemi();
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
void moveEnnemies()
{
    int a = rand() % 2;
    if (a == 0)
    {
        ennemi1.posX = ennemi1.posX - 10;
    }
    else
    {
        ennemi1.posX = ennemi1.posX + 10;
    }
    a = rand() % 2;
    if (a == 0)
    {
        ennemi2.posX = ennemi2.posX - 10;
    }
    else
    {
        ennemi2.posX = ennemi2.posX + 10;
    }
}
void afficherEntitiesSecondaires()
{
    afficheEnnemi(ennemi1, screen);
    afficheEnnemi(ennemi2, screen);
    SDL_Flip(screen);
}

int boundingBoxCollision(SDL_Rect A, SDL_Rect B)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;
    /*  if (bottomA <= topB)
    {
        return 0;
    }
    if (topA >= bottomB)
    {
        return 0;
    }*/
    if (rightA <= leftB)
    {
        return 0;
    }
    if (leftA >= rightB)
    {
        return 0;
    }
    //If none of the sides from A are outside B
    return 1;
}

int collisionDetection(Personnage personnage)
{
    SDL_Rect a;
    SDL_Rect b;
    SDL_Rect c;
    a.x = personnage.posX;
    a.y = personnage.posY;
    a.h = personnage.currentFrame->h;
    a.w = personnage.currentFrame->w;
    b.x = ennemi2.posX;
    b.y = ennemi2.posY;
    b.h = ennemi2.currentFrame->h;
    b.w = ennemi2.currentFrame->w;
    c.x = ennemi1.posX;
    c.y = ennemi1.posY;
    c.h = ennemi1.currentFrame->h;
    c.w = ennemi1.currentFrame->w;

    if (boundingBoxCollision(a, b) == 1)
    {
        printf("Collision !\n");
    }
    if (boundingBoxCollision(a, c) == 1)
    {
        printf("Collision !\n");
    }
    return 1;
}

int perfectPixelCollision(SDL_Rect a, int x, int y)
{
    return;
}

void gameplayPipeline()
{
    SDL_Surface *background;
    background = load_image("assets/bgGameplay.png", 0);
    apply_surface(0, 0, background, screen, NULL);
    personnage = loadSprite(personnage, personnage.direction);
    ennemi1 = loadSpriteEnnemi(ennemi1, 1);
    ennemi2 = loadSpriteEnnemi(ennemi2, 1);
    affichePersonnage(personnage, screen);
    personnage = gameplayEventHandler(personnage);
    afficherEntitiesSecondaires();
    moveEnnemies();
    collisionDetection(personnage);
}
