
#include "utils.h"
#include "inits.h"
#include "enigme.h"
#include "gameplay.h"

SDL_Surface *load_image(char filename[], int colorKey)
{
    SDL_Surface *loadedImage;
    SDL_Surface *optimizedImage;
    loadedImage = IMG_Load(filename);
    if (loadedImage != NULL)
    {
        optimizedImage = SDL_DisplayFormat(loadedImage);
        SDL_FreeSurface(loadedImage);
        if (colorKey)
        {
            SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB(optimizedImage->format, 0, 0, 0));
        }
    }
    else
    {
        printf("Error loading images %s\n", SDL_GetError());
    }
    return optimizedImage;
}

void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(source, clip, destination, &offset);
}

SDL_Surface *generateFontSurface(int size, char text[50], SDL_Color color)
{
    font = TTF_OpenFont(MENU_FONT, size);
    SDL_Surface *surfaceText = TTF_RenderText_Blended(font, text, color);
    TTF_CloseFont(font);
    return surfaceText;
}

Uint32 time_left(void)
{
    Uint32 now;
    now = SDL_GetTicks();
    if (next_time <= now)
        return 0;
    else
        return next_time - now;
}

void frameLimiter(Uint32 start_time)
{
    unsigned int elapsed;
    unsigned int lasttime = SDL_GetTicks();
    SDL_Flip(screen);
    if ((1000 / FPS) > (SDL_GetTicks() - start_time))
        SDL_Delay((1000 / FPS) - (SDL_GetTicks() - start_time));
    frame++;
    if (frame == 1161)
    {
        frame = 1;
    }
    seconds = seconds + 1;
}

void menuHandler(SDL_Event event, int state)
{
    if (playState == 0)
    {
        if (settingsState == 1)
        {
            if ((mouseX > (SCREEN_WIDTH - newGameButton->w) / 2) &&
                (mouseX < (SCREEN_WIDTH - newGameButton->w) / 2 + newGameButton->w) &&
                (mouseY > ((MENU_POS_H) + 125)) &&
                ((mouseY < (MENU_POS_H) + 125 + newGameButton->h)))
            {
                menuSelect = 0;
            }
            else if ((mouseX > (SCREEN_WIDTH - newGameButton->w) / 2) &&
                     (mouseX < (SCREEN_WIDTH - newGameButton->w) / 2 + newGameButton->w) &&
                     (mouseY > ((MENU_POS_H) + 250)) &&
                     ((mouseY < (MENU_POS_H) + 250 + newGameButton->h)))
            {
                menuSelect = 1;
            }
            else if ((mouseX > (SCREEN_WIDTH - newGameButton->w) / 2) &&
                     (mouseX < (SCREEN_WIDTH - newGameButton->w) / 2 + newGameButton->w) &&
                     (mouseY > ((MENU_POS_H) + 375)) &&
                     ((mouseY < (MENU_POS_H) + 375 + newGameButton->h)))
            {
                menuSelect = 2;
            }
            switch (event.type)
            {
            case SDL_QUIT:
                quit = 1;
                Mix_PlayChannel(-1, click, 0);
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (keyPressed == 0)
                {
                    Mix_PlayChannel(-1, click, 0);
                    if (menuSelect == 0)
                    {
                        if (fullscreen == 0)
                        {
                            screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_FULLSCREEN | SDL_DOUBLEBUF);
                        }
                        else
                        {
                            SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_DOUBLEBUF);
                        }
                        if (fullscreen)
                            strcpy(windowStateChar, "Windowed");
                        else
                            strcpy(windowStateChar, "Fullscreen");
                        fullscreen = !fullscreen;
                    }
                    if (menuSelect == 1)
                    {
                    }
                    if (menuSelect == 2)
                    {
                        settingsState = 0;
                    }
                    keyPressed = 1;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                keyPressed = 0;
            case SDL_KEYUP:
                keyPressed = 0;
                break;
            case SDL_KEYDOWN:
                if (keyPressed == 0)
                {
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_RETURN:
                        Mix_PlayChannel(-1, click, 0);
                        if (menuSelect == 0)
                        {
                            if (fullscreen == 0)
                            {
                                screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_FULLSCREEN | SDL_DOUBLEBUF);
                            }
                            else
                            {
                                SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_DOUBLEBUF);
                            }
                            if (fullscreen)
                                strcpy(windowStateChar, "Windowed");
                            else
                                strcpy(windowStateChar, "Fullscreen");
                            fullscreen = !fullscreen;
                        }
                        else if (menuSelect == 1)
                        {
                        }
                        else if (menuSelect == 2)
                            settingsState = 0;
                        break;
                    case SDLK_ESCAPE:
                        quit = 1;
                        break;
                    case SDLK_UP:
                        Mix_PlayChannel(-1, switcher, 0);
                        if (menuSelect != 0)
                            menuSelect--;
                        break;
                    case SDLK_DOWN:
                        Mix_PlayChannel(-1, switcher, 0);
                        if (menuSelect != 2)
                            menuSelect++;
                        break;
                    case SDLK_RIGHT:
                        if (menuSelect == 1)
                        {
                            Mix_Volume(-1, ++musicVolume);
                            Mix_VolumeMusic(musicVolume);
                            if (musicVolume > 100)
                            {
                                musicVolume = 100;
                            }
                        }
                        break;
                    case SDLK_LEFT:
                        if (menuSelect == 1)
                        {
                            Mix_Volume(-1, --musicVolume);
                            Mix_VolumeMusic(musicVolume);
                            if (musicVolume < 0)
                            {
                                musicVolume = 0;
                            }
                        }
                    }
                }
                keyPressed = 1;
                break;
            default:
                break;
            }
        }
        else if (settingsState == 0)
        {
            if ((mouseX > (SCREEN_WIDTH - newGameButton->w) / 2) &&
                (mouseX < (SCREEN_WIDTH - newGameButton->w) / 2 + newGameButton->w) &&
                (mouseY > ((MENU_POS_H) + 125)) &&
                ((mouseY < (MENU_POS_H) + 125 + newGameButton->h)))
            {
                menuSelect = 0;
            }
            else if ((mouseX > (SCREEN_WIDTH - newGameButton->w) / 2) &&
                     (mouseX < (SCREEN_WIDTH - newGameButton->w) / 2 + newGameButton->w) &&
                     (mouseY > ((MENU_POS_H) + 250)) &&
                     ((mouseY < (MENU_POS_H) + 250 + newGameButton->h)))
            {
                menuSelect = 1;
            }
            else if ((mouseX > (SCREEN_WIDTH - newGameButton->w) / 2) &&
                     (mouseX < (SCREEN_WIDTH - newGameButton->w) / 2 + newGameButton->w) &&
                     (mouseY > ((MENU_POS_H) + 375)) &&
                     ((mouseY < (MENU_POS_H) + 375 + newGameButton->h)))
            {
                menuSelect = 2;
            }
            switch (event.type)
            {
            case SDL_QUIT:
                quit = 1;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (keyPressed == 0)
                {
                    Mix_PlayChannel(-1, click, 0);
                    if (menuSelect == 2)
                    {
                        quit = 1;
                    }
                    if (menuSelect == 0)
                    {
                        playState = 1;
                    }
                    if (menuSelect == 1)
                    {
                        settingsState = 1;
                    }
                }
                keyPressed = 1;
                break;
            case SDL_MOUSEBUTTONUP:
                keyPressed = 0;
                break;
            case SDL_KEYUP:
                keyPressed = 0;
                break;
            case SDL_KEYDOWN:
                if (keyPressed == 0)
                {
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_RETURN:
                        Mix_PlayChannel(-1, click, 0);
                        if (menuSelect == 0)
                            playState = 1;
                        else if (menuSelect == 1)
                        {
                            settingsState = 1;
                            menuSelect = 0;
                        }
                        else if (menuSelect == 2)
                            quit = 1;
                        break;
                    case SDLK_ESCAPE:
                        quit = 1;
                        break;
                    case SDLK_UP:
                        Mix_PlayChannel(-1, switcher, 0);
                        if (menuSelect != 0)
                            menuSelect--;
                        break;
                    case SDLK_DOWN:
                        Mix_PlayChannel(-1, switcher, 0);
                        if (menuSelect != 2)
                            menuSelect++;
                        break;
                    }
                }
                keyPressed = 1;
                break;
            default:
                break;
            }
        }
    }
}

void renderFrame(State state)
{

    color.b = 255;
    if (!playState)
        initBg(screen, background);

    loadAnimationFile(frame);
    if (settingsState == 0)
    {
        initMenu(menuSelect);
    }
    else if (settingsState == 1)
    {
        initSetting(menuSelect);
    }
    if (playState)
    {

        if (inits == 0)
        {
            initGameplay();
            inits = 1;
        }
        else if (choiceSelect == -1)
        {
            gameplayPipeline();
            //gameplayPipelineMulti();
            //EnigmePipeline();
            //selectionMenu();
            //SaveMenu();
        }
        else if (choiceSelect == 1)
        {
            modelSelected = 1;
            gameplayPipeline();
        }
        else if (choiceSelect == 2)
        {
            modelSelected = 0;
            gameplayPipeline();
        }
        else if (choiceSelect == 3)
        { //MULTIPLAYER
            gameplayPipelineMulti();
        }
        else if (choiceSelect == 4)
        { //AI AI
            gameplayPipelineMulti();
        }
        else if (choiceSelect == 5)
        { //LOAD
            loadVars();
            gameplayPipeline();
        }
        else if (choiceSelect == 6)
        {
            SaveMenu();
        }
    }
}

SDL_Color GetPixel(SDL_Surface *pSurface, int x, int y)
{
    SDL_Color color;
    Uint32 col = 0;
    char *pPosition = (char *)pSurface->pixels;
    pPosition += (pSurface->pitch * y);
    pPosition += (pSurface->format->BytesPerPixel * x);
    memcpy(&col, pPosition, pSurface->format->BytesPerPixel);
    SDL_GetRGB(col, pSurface->format, &color.r, &color.g, &color.b);
    return (color);
}

int selectEventHandler()
{
    SDL_WaitEvent(&event);
    switch (event.type)
    {
    case SDL_MOUSEBUTTONUP:
        keyPressed = 0;
        break;
    case SDL_KEYUP:
        keyPressed = 0;
    case SDL_KEYDOWN:
        if (keyPressed == 0)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_UP:
                gameSelector = gameSelector - 1;
                if (gameSelector < 1)
                {
                    gameSelector = 1;
                }
                break;
            case SDLK_DOWN:
                gameSelector = gameSelector + 1;
                if (gameSelector > 5)
                {
                    gameSelector = 5;
                }
                break;
            case SDLK_RETURN:
            case SDL_MOUSEBUTTONDOWN:
                keyPressed = 1;
                return gameSelector;
                break;
            }
            keyPressed = 1;
        }
        break;

    default:
        break;
    }
    if ((mouseX > 250) && (mouseY > 250) && (mouseX < 250 + 112) && (mouseY < 250 + 37))
    {
        gameSelector = 1;
    }
    else if ((mouseX > 550) && (mouseY > 250) && (mouseX < 550 + 112) && (mouseY < 250 + 37))
    {
        gameSelector = 2;
    }
    else if ((mouseX > 250) && (mouseY > 350) && (mouseX < 250 + 112) && (mouseY < 350 + 37))
    {
        gameSelector = 3;
    }
    else if ((mouseX > 550) && (mouseY > 350) && (mouseX < 550 + 112) && (mouseY < 350 + 37))
    {
        gameSelector = 4;
    }
    else if ((mouseX > 400) && (mouseY > 450) && (mouseX < 400 + 112) && (mouseY < 450 + 37))
    {
        gameSelector = 5;
    }
    return -1;
}
void selectionMenu()
{
    SDL_Surface *back = load_image("menu choix.png", 0);
    apply_surface(0, 0, back, screen, NULL);

    SDL_Surface *perso1 = load_image("pr10.png", 0);
    SDL_Surface *perso2 = load_image("perso vert.png", 0);

    Uint32 colorkey = SDL_MapRGB(perso1->format, 0, 0xFF, 0);
    SDL_SetColorKey(perso1, SDL_SRCCOLORKEY, colorkey);
    SDL_SetColorKey(perso2, SDL_SRCCOLORKEY, colorkey);

    apply_surface(300, 150, perso1, screen, NULL);
    apply_surface(600, 150, perso2, screen, NULL);

    //SDL_Surface *bouton3 = load_image("assets/menu/b_ns.png", 0);
    SDL_Surface *bouton1 = load_image("assets/menu/b_ns.png", 0);
    SDL_Surface *bouton2 = load_image("assets/menu/b_ns.png", 0);
    SDL_Surface *bouton4 = load_image("assets/menu/b_ns.png", 0);
    SDL_Surface *bouton5 = load_image("assets/menu/b_ns.png", 0);
    SDL_Surface *bouton6 = load_image("assets/menu/b_ns.png", 0);
    //SDL_Surface *bouton7 = load_image("assets/menu/b_ns.png", 0);
    selectionText1 = generateFontSurface(32, "Perso 1", n_selected);
    selectionText2 = generateFontSurface(32, "Perso 2", n_selected);
    selectionText4 = generateFontSurface(32, "Multiplayer", n_selected);
    selectionText5 = generateFontSurface(32, "VS AI", n_selected);
    selectionText6 = generateFontSurface(32, "Load Game", n_selected);
    switch (gameSelector)
    {
    case 1:
        selectionText1 = generateFontSurface(32, "Perso 1", selected);
        break;
    case 2:
        selectionText2 = generateFontSurface(32, "Perso 2", selected);
        break;
    case 3:
        selectionText4 = generateFontSurface(32, "Multiplayer", selected);
        break;
    case 4:
        selectionText5 = generateFontSurface(32, "VS AI", selected);
        break;
    case 5:
        selectionText6 = generateFontSurface(32, "Load Game", selected);
        break;
    default:
        break;
    }
    //selectionText3 = generateFontSurface(32, "Solo", selected);
    SDL_Surface *separator;
    apply_surface(20, bouton1->h * 0.10, selectionText1, bouton1, NULL);
    apply_surface(20, bouton2->h * 0.10, selectionText2, bouton2, NULL);
    //apply_surface(20, bouton3->h * 0.10, selectionText3, bouton3, NULL);
    apply_surface(20, bouton4->h * 0.10, selectionText4, bouton4, NULL);
    apply_surface(20, bouton5->h * 0.10, selectionText5, bouton5, NULL);
    apply_surface(20, bouton6->h * 0.10, selectionText6, bouton6, NULL);
    //apply_surface(20, bouton7->h * 0.10, selectionText7, bouton7, NULL);
    apply_surface(250, 250, bouton1, screen, NULL);
    apply_surface(550, 250, bouton2, screen, NULL);
    //apply_surface(350, 250, bouton3, screen, NULL);
    apply_surface(250, 350, bouton4, screen, NULL);
    apply_surface(550, 350, bouton5, screen, NULL);
    apply_surface(400, 450, bouton6, screen, NULL);
    int selection = -1;
    selection = selectEventHandler();
    switch (selection)
    {
    case 1:
        choiceSelect = 1;
        break;
    case 2:
        choiceSelect = 2;
        break;

    case 3:
        choiceSelect = 3;
        break;

    case 4:
        choiceSelect = 4;
        break;

    case 5:
        choiceSelect = 5;
        break;

    default:
        break;
    }
    //apply_surface(550, 350, bouton7, screen, NULL);
    SDL_Flip(screen);
}

void SaveMenu()
{
    SDL_Surface *back = load_image("menu choix.png", 0);
    apply_surface(0, 0, back, screen, NULL);

    SDL_Surface *bouton1 = load_image("assets/menu/b_ns.png", 0);
    SDL_Surface *bouton2 = load_image("assets/menu/b_ns.png", 0);
    SDL_Surface *bouton3 = load_image("assets/menu/b_ns.png", 0);
    selectionText1 = generateFontSurface(32, "Save Game", n_selected);
    selectionText2 = generateFontSurface(32, "Resume", n_selected);
    selectionText3 = generateFontSurface(32, "Main Menu", n_selected);
    switch (saveMenuSelector)
    {
    case 1:
        selectionText1 = generateFontSurface(32, "Save Game", selected);
        break;
    case 2:
        selectionText2 = generateFontSurface(32, "Resume", selected);
        break;
    case 3:
        selectionText3 = generateFontSurface(32, "Main Menu", selected);
        break;

    default:
        break;
    }
    SDL_Surface *separator;
    apply_surface(20, bouton1->h * 0.10, selectionText1, bouton1, NULL);
    apply_surface(20, bouton2->h * 0.10, selectionText2, bouton2, NULL);
    apply_surface(20, bouton3->h * 0.10, selectionText3, bouton3, NULL);
    apply_surface(400, 200, bouton1, screen, NULL);
    apply_surface(400, 300, bouton2, screen, NULL);
    apply_surface(400, 400, bouton3, screen, NULL);
    int selection = -1;
    selection = saveMenuHandler();
    switch (selection)
    {
    case 1:
        SaveVars();
        break;
    case 2:
        choiceSelect = 1;
        break;
    case 3:
        choiceSelect = -1;
        playState = !playState;
        break;
    default:
        break;
    }

    SDL_Flip(screen);
}

int saveMenuHandler()
{
    SDL_WaitEvent(&event);
    printf("1");
    switch (event.type)
    {
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_UP:
            saveMenuSelector = saveMenuSelector - 1;
            if (saveMenuSelector < 1)
            {
                saveMenuSelector = 1;
            }
            break;
        case SDLK_DOWN:
            saveMenuSelector = saveMenuSelector + 1;
            if (saveMenuSelector > 3)
            {
                saveMenuSelector = 3;
            }
            break;
        case SDLK_RETURN:
        case SDL_MOUSEBUTTONDOWN:
            selectedSaveMenu = saveMenuSelector;
            return selectedSaveMenu;
            break;
        }
        break;

    default:
        break;
    }
    if ((mouseX > 400) && (mouseY > 200) && (mouseX < 400 + 112) && (mouseY < 200 + 37))
    {
        saveMenuSelector = 1;
    }
    else if ((mouseX > 400) && (mouseY > 300) && (mouseX < 400 + 112) && (mouseY < 300 + 37))
    {
        saveMenuSelector = 2;
    }
    else if ((mouseX > 400) && (mouseY > 400) && (mouseX < 400 + 112) && (mouseY < 400 + 37))
    {
        saveMenuSelector = 3;
    }
}