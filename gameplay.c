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
Personnage personnage2;

Personnage jump(Personnage personnage)
{
    for (int i = 0; i < 10; i++)
    {
        apply_surface(offsetBG, 0, gameBackground, screen, NULL);
        afficherEntitiesSecondaires();
        offsetBG = offsetBG - 10;
        personnage.posY = personnage.posY - 10;
        affichePersonnage(personnage, screen);
        SDL_Flip(screen);
        SDL_Delay(20);
    }
    for (int i = 0; i < 10; i++)
    {
        apply_surface(offsetBG, 0, gameBackground, screen, NULL);
        afficherEntitiesSecondaires();
        offsetBG = offsetBG - 10;
        personnage.posY = personnage.posY + 10;
        affichePersonnage(personnage, screen);
        SDL_Flip(screen);
        SDL_Delay(20);
    }
}

void loadVars()
{
    SaveFile savefile;
    FILE *file = fopen("save", "rb");
    if (file != NULL)
        if (file != NULL)
        {
            fread(&savefile, sizeof(SaveFile), 1, file);
            fclose(file);
        }
    offsetBG = savefile.posX;
    score = savefile.score;
    personnage = savefile.personnage;
    vies = savefile.vies;
    ennemi1 = savefile.ennemi;
    ennemi2 = savefile.ennemi2;
}
void SaveVars()
{
    SaveFile savefile;
    savefile.posX = offsetBG;
    savefile.score = score;
    savefile.vies = vies;
    savefile.personnage = personnage;
    savefile.ennemi = ennemi1;
    savefile.ennemi2 = ennemi2;
    FILE *file = fopen("save", "wb");
    if (file != NULL)
    {
        fwrite(&savefile, sizeof(SaveFile), 1, file);
        fclose(file);
    }
}

void afficherPersonnage(Personnage personnage, SDL_Surface *screen)
{
    apply_surface(personnage.posX, personnage.posY, personnage.currentFrame, screen, NULL);
}

void initGameplay()
{
    int keyrepeat = SDL_EnableKeyRepeat(20, 64);
    personnage = initPersonnage();
    personnage2 = initPersonnage2();
    initEnnemi();
    offsetBG = 0;
    offsetBG2 = 0;
    gameplayStartTick = SDL_GetTicks();
    minimap = load_image("assets/minimap.png", 0);
    minimapIcon = load_image("assets/minimap icon.png", 0);
    vies = 3;
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
            break;
        case SDLK_SPACE:
            personnage = jump(personnage);
            break;
        case SDLK_q:

            offsetBG2 = offsetBG2 + 15;
            ennemi3.posX = ennemi3.posX + 7;
            ennemi4.posX = ennemi4.posX + 7;
            personnage2.direction = 1;
            break;
        case SDLK_ESCAPE:
            choiceSelect = 6;
            break;
        case SDLK_j:
            vies = vies - 1;
            break;
        case SDLK_u:
            SaveVars();
            printf("saved  ? ");
            break;
        case SDLK_i:
            loadVars();
            printf("Loaded ? ");
            break;
        case SDLK_d:
            offsetBG2 = offsetBG2 - 15;
            ennemi3.posX = ennemi3.posX - 7;
            ennemi4.posX = ennemi4.posX - 7;
            personnage2.direction = 0;
            break;
        default:
            break;
        }
        break;
    case SDL_MOUSEBUTTONDOWN:
        if (mouseX > personnage.posX)
        {
            offsetBG = offsetBG - 15;
            ennemi1.posX = ennemi1.posX - 7;
            ennemi2.posX = ennemi2.posX - 7;
            personnage.direction = 0;
        }
        else if (mouseX < personnage.posX)
        {
            offsetBG = offsetBG + 15;
            ennemi1.posX = ennemi1.posX + 7;
            ennemi2.posX = ennemi2.posX + 7;
            personnage.direction = 1;
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
    afficheEnnemi(ennemi3, screen);
    afficheEnnemi(ennemi4, screen);
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
            ennemi2.posX = ennemi2.posX - 5;
        }
        else
        {
            ennemi2.posX = ennemi2.posX + 5;
        }
    }
    if (ennemyVision(ennemi1) == 1)
    {
        if (ennemi1.direction == 1)
        {
            ennemi1.posX = ennemi1.posX - 5;
        }
        else
        {
            ennemi1.posX = ennemi1.posX + 5;
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

void aiMove()
{
    offsetBG2 = offsetBG2 - 7;
}

void gameplayPipelineMulti()
{
    apply_surface(offsetBG, 0, gameBackground, screen, NULL);
    apply_surface(offsetBG2, -375, gameBackground, screen, NULL);
    personnage.model = modelSelected;
    personnage = loadSprite(personnage, personnage.direction);
    personnage2 = loadSprite(personnage2, personnage2.direction);

    ennemi1 = loadSpriteEnnemi(ennemi1, ennemi1.direction);
    ennemi2 = loadSpriteEnnemi(ennemi2, ennemi2.direction);
    ennemi3 = loadSpriteEnnemi(ennemi3, ennemi3.direction);
    ennemi4 = loadSpriteEnnemi(ennemi4, ennemi4.direction);

    affichePersonnage(personnage, screen);
    affichePersonnage(personnage2, screen);
    if (choiceSelect == 4)
    {
        aiMove();
    }
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

    //apply_surface(SCREEN_WIDTH - minimap->w, 0, minimap, screen, NULL);
    //apply_surface(SCREEN_WIDTH - minimap->w - (offsetBG / 14.5), 30, minimapIcon, screen, NULL);
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

void gameOver()
{
    gameover = load_image("stage complete.png", 0);
    apply_surface(0, 0, gameover, screen, NULL);
    SDL_Flip(screen);
    SDL_Delay(5000);
    exit(0);
}
void gameplayPipeline()
{ /*
    if (vies < 1)
    {
        showGameOverScreen();
        SDL_Delay(3000);
        playState = 0;
        inits = 0;
        return;
    }*/
    personnage.model = modelSelected;
    apply_surface(offsetBG, 0, gameBackground, screen, NULL);
    personnage = loadSprite(personnage, personnage.direction);
    ennemi1 = loadSpriteEnnemi(ennemi1, ennemi1.direction);
    ennemi2 = loadSpriteEnnemi(ennemi2, ennemi2.direction);
    affichePersonnage(personnage, screen);
    personnage = gameplayEventHandler(personnage);
    afficherEntitiesSecondaires();
    moveEnnemies();
    /////////////////
    moveSeenEnnemies();
    ////////////////////
    char uiString[40];

    sprintf(uiString, "Vies: %d || Score : %d", vies, score);
    SDL_Color colorUI;
    colorUI.b = 0;
    colorUI.r = 255;
    colorUI.g = 0;
    printf("%d", offsetBG);
    if (offsetBG < -4800)
    {
        gameOver();
    }

    ///////////////
    char gameplayTimeString[20];
    sprintf(gameplayTimeString, "Temps passe : %d ", (SDL_GetTicks() - gameplayStartTick) / 1000);
    SDL_Surface *gameplayTimeSurface = generateFontSurface(32, gameplayTimeString, colorUI);
    apply_surface(50, 650, gameplayTimeSurface, screen, NULL);
    SDL_FreeSurface(gameplayTimeSurface);

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
