/**
* @file gameplay.c
* @brief in-game gameplay source code 
* @author Creative Sparks
* @version 2.0
* @date 2020
*
* 
*
*/

#include "gameplay.h"

Personnage personnage;

void afficherPersonnage(Personnage personnage, SDL_Surface *screen)
{
    apply_surface(personnage.posX, personnage.posY, personnage.currentFrame, screen, NULL);
}

void initGameplay()
{
    int keyrepeat = SDL_EnableKeyRepeat(20, 64);
    personnage = initPersonnage();
    initEnnemi();
    offsetBG = 0;
    gameplayStartTick = SDL_GetTicks();
    minimap = load_image("assets/minimap.png", 0);
    minimapIcon = load_image("assets/minimap icon.png", 0);
}

Personnage gameplayEventHandler(Personnage personnage)
{
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_RIGHT:
            offsetBG = offsetBG - 15;
            ennemi1.posX = ennemi1.posX - 7;
            ennemi2.posX = ennemi2.posX - 7;
            personnage.direction = 0;
            break;
        case SDLK_LEFT:
            offsetBG = offsetBG + 15;
            ennemi1.posX = ennemi1.posX + 7;
            ennemi2.posX = ennemi2.posX + 7;
            personnage.direction = 1;
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
        ennemi1.direction = 1;
    }
    else
    {
        ennemi1.direction = 0;
        ennemi1.posX = ennemi1.posX + 10;
    }
    a = rand() % 2;
    if (a == 0)
    {
        ennemi2.direction = 1;
        ennemi2.posX = ennemi2.posX - 10;
    }
    else
    {

        ennemi2.direction = 0;
        ennemi2.posX = ennemi2.posX + 10;
    }
}
void afficherEntitiesSecondaires()
{
    afficheEnnemi(ennemi1, screen);
    afficheEnnemi(ennemi2, screen);
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
    if (bottomA <= topB)
    {
        return 0;
    }
    if (topA >= bottomB)
    {
        return 0;
    }
    if (rightA <= leftB)
    {
        return 0;
    }
    if (leftA >= rightB)
    {
        return 0;
    }
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
        return 1;
    }
    if (boundingBoxCollision(a, c) == 1)
    {
        printf("Collision !\n");
        return 1;
    }
    return 0;
}

int perfectPixelCollision(Personnage personnage, int x, int y)
{
    SDL_Color collisionColor;
    collisionColor.b = 0;
    collisionColor.r = 0;
    collisionColor.g = 255;
    int X5 = personnage.posX;
    int Y5 = personnage.posY + personnage.currentFrame->h;
    int X6 = (personnage.posX + personnage.currentFrame->w) / 2;
    int X7 = personnage.posX + personnage.currentFrame->w;
    SDL_Color color1 = GetPixel(gameBackgroundMask, X5, Y5);
    SDL_Color color2 = GetPixel(gameBackgroundMask, X6, Y5);
    SDL_Color color3 = GetPixel(gameBackgroundMask, X7, Y5);
    if ((collisionColor.b == color1.b && collisionColor.r == color1.r && collisionColor.g == color1.g))
    {
        return 1;
    }
    if ((collisionColor.b == color2.b && collisionColor.r == color2.r && collisionColor.g == color2.g))
    {
        return 1;
    }
    if ((collisionColor.b == color3.b && collisionColor.r == color3.r && collisionColor.g == color3.g))
    {
        return 1;
    }
    return 0;
}

int ennemyVision(Ennemi ennemi)
{
    if (ennemi.posX - personnage.posX < 200 && ennemi.posX - personnage.posX > 0)
    {
        ennemi.posX = ennemi.posX - 10;
        return 1;
    }
    else if (ennemi.posX - personnage.posX > -200 && ennemi.posX - personnage.posX < 0)
    {
        ennemi.posX = ennemi.posX + 10;
        return 1;
    }
    return 0;
}

void moveSeenEnnemies()
{
    if (ennemyVision(ennemi2) == 1)
    {
        if (ennemi2.direction == 1)
        {
            ennemi2.posX = ennemi2.posX - 50;
        }
        else
        {
            ennemi2.posX = ennemi2.posX + 50;
        }
    }
    if (ennemyVision(ennemi1) == 1)
    {
        if (ennemi1.direction == 1)
        {
            ennemi1.posX = ennemi1.posX - 50;
        }
        else
        {
            ennemi1.posX = ennemi1.posX + 50;
        }
    }
}

void showGameOverScreen()
{
    SDL_Surface *endScreen;
    endScreen = load_image("assets/enigmes/enigme1F.png", 0);
    apply_surface(0, 0, endScreen, screen, NULL);
    SDL_Surface *gameOverText;
    char gameOver[50];
    sprintf(gameOver, "Game Over, Score: %d , Time : %d", score, 1);
    gameOverText = generateFontSurface(32, gameOver, n_selected);
    apply_surface(200, 200, gameOverText, screen, NULL);
    SDL_FreeSurface(gameOverText);
    SDL_Flip(screen);
}

void showMinimap()
{
}

void gameplayPipeline()
{
    apply_surface(offsetBG, 0, gameBackground, screen, NULL);
    personnage = loadSprite(personnage, personnage.direction);
    ennemi1 = loadSpriteEnnemi(ennemi1, ennemi1.direction);
    ennemi2 = loadSpriteEnnemi(ennemi2, ennemi1.direction);
    affichePersonnage(personnage, screen);
    personnage = gameplayEventHandler(personnage);
    afficherEntitiesSecondaires();
    //moveEnnemies();
    /////////////////
    moveSeenEnnemies();
    ////////////////////
    char uiString[40];

    sprintf(uiString, "Vies: %d || Score : %d", vies, score);
    SDL_Color colorUI;
    colorUI.b = 0;
    colorUI.r = 255;
    colorUI.g = 0;

    ///////////////
    char gameplayTimeString[20];
    sprintf(gameplayTimeString, "Temps passe : %d ", (SDL_GetTicks() - gameplayStartTick) / 1000);
    SDL_Surface *gameplayTimeSurface = generateFontSurface(32, gameplayTimeString, colorUI);
    apply_surface(50, 650, gameplayTimeSurface, screen, NULL);
    SDL_FreeSurface(gameplayTimeSurface);
    ////////////////
    ///////////////////////
    //showGameOverScreen();
    ////////////////////////

    ////////ROTOZOOM

    apply_surface(SCREEN_WIDTH - minimap->w, 0, minimap, screen, NULL);
    apply_surface(SCREEN_WIDTH - minimap->w - (offsetBG / 14.5), 30, minimapIcon, screen, NULL);
    SDL_Flip(screen);
    SDL_Surface *uiStringSurface = generateFontSurface(32, uiString, colorUI);
    apply_surface(SCREEN_WIDTH / 2, 650, uiStringSurface, screen, NULL);
    if (collisionDetection(personnage) == 1)
    {
        int enigmeReponse = EnigmePipeline();
        if (enigmeReponse == 4)
        {
            personnage.posX = personnage.posX + 200;
            ennemi1 = killEnnemy(ennemi1);
            score = score + 100;
        }
        else if (enigmeReponse == 1 || enigmeReponse == 2 || enigmeReponse == 3)
        {
            vies = vies - 1;
            score = score - 100;
        }
        printf("vies %d score %d", vies, score);
    }
}
