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

int fxVolume = 100;
SDL_VideoInfo *info;

int playState = 0;

State state = MAIN_MENU;

SDL_Color selected;
SDL_Color n_selected;

Mix_Music *music;
Mix_Chunk *scratch;
Mix_Chunk *high;
Mix_Chunk *med;
Mix_Chunk *low;

SDL_Surface *animation;

int fullscreenWidth = 0;
int fullscreenHeight = 0;

int FPS = 60;
int musicVolume = 10;
int frame = 1;
int quit = 0;
int menuSelect = 0;

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
    SDL_Flip(screen);
    if ((1000 / FPS) > (SDL_GetTicks() - start_time))
        SDL_Delay((1000 / FPS) - (SDL_GetTicks() - start_time));
    frame++;
    if (frame == 1161)
    {
        frame = 1;
    }
}

void menuHandler(SDL_Event event)
{
    switch (event.type)
    {
    case SDL_MOUSEMOTION:
        if ((event.motion.x > (SCREEN_WIDTH - menu1->w) / 2) && (event.motion.x < ((SCREEN_WIDTH - menu1->w) / 2) + menu1->w) && (event.motion.y > ((100)) && (event.motion.y > (100)) + menu1->h))
        {
            menuSelect = 0;
        }
        if ((event.motion.x > (SCREEN_WIDTH - menu2->w) / 2) && (event.motion.x < ((SCREEN_WIDTH - menu2->w) / 2) + menu2->w) && (event.motion.y > ((200)) && (event.motion.y > (200)) + menu2->h))
        {
            menuSelect = 1;
        }
        if ((event.motion.x > (SCREEN_WIDTH - menu3->w) / 2) && (event.motion.x < ((SCREEN_WIDTH - menu3->w) / 2) + menu3->w) && (event.motion.y > ((300)) && (event.motion.y > (300)) + menu3->h))
        {
            menuSelect = 2;
        }
        printf("x%d y%d\n", event.motion.x, event.motion.y);
        break;
    case SDL_QUIT:
        quit = 1;
        Mix_PlayChannel(-1, low, 0);
        break;
    case SDL_MOUSEBUTTONDOWN:
        Mix_PlayChannel(-1, med, 0);
        if (menuSelect == 2)
        {
            quit = 1;
        }
        if (menuSelect == 0)
        {
            playState = 1;
        }
        break;
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_RETURN:
            Mix_PlayChannel(-1, med, 0);
            if (settingsState == 0)
            {
                if (menuSelect == 0)
                    playState = 1;
                else if (menuSelect == 1)
                {
                    settingsState = 1;
                    menuSelect = 0;
                }
                else if (menuSelect == 2)
                    quit = 1;
            }
            else if (settingsState == 1)
            {
                if (menuSelect == 0)
                {
                }
                else if (menuSelect == 1)
                {
                }
                else if (menuSelect == 2)
                {
                    menuSelect = 0;
                    settingsState = 0;
                }
            }

            break;
        case SDLK_ESCAPE:
            quit = 1;
            break;
        case SDLK_d:
            if (fullscreen == 0)
            {
                screen = SDL_SetVideoMode(fullscreenWidth, fullscreenHeight, SCREEN_BPP, SDL_HWSURFACE | SDL_FULLSCREEN | SDL_DOUBLEBUF);
            }
            else
            {
                SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_DOUBLEBUF);
            }
            if (fullscreen)
                strcpy(windowStateChar, "Windowed");
            else
                strcpy(windowStateChar, "Fullscreen");
            printf("%s", windowStateChar);
            fullscreen = !fullscreen;
            break;
        case SDLK_UP:
            Mix_PlayChannel(-1, med, 0);
            if (menuSelect != 0)
                menuSelect--;
            break;
        case SDLK_DOWN:
            Mix_PlayChannel(-1, low, 0);
            if (menuSelect != 2)
                menuSelect++;
            break;
        case SDLK_RIGHT:
            Mix_Volume(-1, ++musicVolume);
            Mix_VolumeMusic(musicVolume);
            break;
        case SDLK_LEFT:
            Mix_Volume(-1, --musicVolume);
            Mix_VolumeMusic(musicVolume);
            break;
        }
        break;
    default:
        break;
    }
}

void renderFrame(State state)
{
    color.b = 255;
    if (!playState)
        initBg(screen, background);
    else
    {
        background = load_image("assets/jpg/2.jpg", 0);
        initBg(screen, background);
    }
    initMenu(menuSelect);
    loadAnimationFile(frame);
    char volumeChar[20];
    sprintf(volumeChar, "Volume %d", musicVolume);
    volumeSurface = generateFontSurface(20, volumeChar, color);
    windowState = generateFontSurface(100, windowStateChar, color);
    apply_surface(SCREEN_WIDTH - volumeSurface->w, SCREEN_HEIGHT - volumeSurface->h, volumeSurface, screen, 0);
    apply_surface(SCREEN_WIDTH - windowState->w, SCREEN_HEIGHT - windowState->h, windowState, screen, 0);
}