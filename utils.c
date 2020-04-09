#include "utils.h"
#include "inits.h"
#include "enigme.h"

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
        EnigmePipeline();
    }
}

void renderGameFrame()
{
}

void gameHandler(SDL_Event event, int state)
{
}
