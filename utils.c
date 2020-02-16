#include "utils.h"
#include "inits.h"

SDL_Surface *hello;
SDL_Surface *screen;
SDL_Surface *message;
SDL_Surface *background;
SDL_Surface *image;
SDL_Event event;
TTF_Font *font;
SDL_Color color;
SDL_Surface *buttons;
Uint32 next_time;
int fullscreen = 0;
SDL_Surface *volumeSurface;
SDL_Surface *windowState;

SDL_Surface *volumeBar;
SDL_Surface *volumeSelector;

SDL_Surface *menuBackground;
SDL_Surface *menuButtonNormalState;
SDL_Surface *menuButtonClickedState;
SDL_Surface *infoBar;
SDL_Surface *slider;
SDL_Surface *sliderBar;

int mouseX;
int mouseY;

char windowStateChar[15] = "Windowed";

SDL_Surface *menu1;
SDL_Surface *menu2;
SDL_Surface *menu3;
SDL_Surface *menu1Hover;
SDL_Surface *menu2Hover;
SDL_Surface *menu3Hover;

SDL_Surface *newGameButton;
SDL_Surface *settingsButton;
SDL_Surface *quitButton;

int fxVolume = 100;
SDL_VideoInfo *info;

int playState = 0;

State state = MAIN_MENU;

SDL_Color selected;
SDL_Color n_selected;

SDL_Surface *settingsText;
SDL_Surface *modeText;
SDL_Surface *fullScreenText;
SDL_Surface *windowedText;
SDL_Surface *volumeText;
SDL_Surface *exitText;

Mix_Music *music;
Mix_Chunk *click;
Mix_Chunk *switcher;
Mix_Chunk *fullscreenSound;

SDL_Surface *animation;

int fullscreenWidth = 0;
int fullscreenHeight = 0;

SDL_Surface *text1;
SDL_Surface *text2;
SDL_Surface *text3;

int FPS = 30;
int musicVolume = 50;
int frame = 1;
int quit = 0;
int menuSelect = 0;

int keyPressed = 0;
int settingsState = 0;
int volumeSlider = 0;

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
                    playState = 1;
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
                        playState = 1;
                    }
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
        background = load_image("assets/jpg/3.jpg", 0);
        initBg(screen, background);
    }
}

void UpdateEvents(input_t *in)
{
    SDL_Event event;
    in->mousebuttons[SDL_BUTTON_WHEELUP] = 0;
    in->mousebuttons[SDL_BUTTON_WHEELDOWN] = 0;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            in->key[event.key.keysym.sym] = 1;
            break;
        case SDL_KEYUP:
            in->key[event.key.keysym.sym] = 0;
            break;
        case SDL_MOUSEBUTTONDOWN:
            in->mousebuttons[event.button.button] = 1;
            break;
        case SDL_MOUSEBUTTONUP:
            if (event.button.button != SDL_BUTTON_WHEELUP && event.button.button != SDL_BUTTON_WHEELDOWN)
                in->mousebuttons[event.button.button] = 0;
            break;
        case SDL_QUIT:
            in->quit = 1;
            break;
        default:
            break;
        }
    }
}