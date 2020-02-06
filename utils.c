#include "utils.h"

SDL_Surface *hello = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *message = NULL;
SDL_Surface *background = NULL;
SDL_Surface *image = NULL;
SDL_Event event;
TTF_Font *font = NULL;
SDL_Color color;
SDL_Surface *buttons = NULL;
Uint32 next_time;

SDL_Surface *menu1 = NULL;
SDL_Surface *menu2 = NULL;
SDL_Surface *menu3 = NULL;
SDL_Surface *menu1Hover = NULL;
SDL_Surface *menu2Hover = NULL;
SDL_Surface *menu3Hover = NULL;

int fxVolume = 100;
int musicVolume = 100;

Level Scene = MAIN_MENU;

Mix_Music *music = NULL;
Mix_Chunk *scratch = NULL;
Mix_Chunk *high = NULL;
Mix_Chunk *med = NULL;
Mix_Chunk *low = NULL;

SDL_Surface *load_image(char filename[], int colorKey)
{
    SDL_Surface *loadedImage = NULL;
    SDL_Surface *optimizedImage = NULL;
    loadedImage = IMG_Load(filename);
    if (loadedImage != NULL)
    {
        optimizedImage = SDL_DisplayFormat(loadedImage);
        SDL_FreeSurface(loadedImage);
        if (colorKey)
        {
            Uint32 colorkey = SDL_MapRGB(optimizedImage->format, 0, 0, 0);
            SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey);
        }
    }
    else
    {
        printf("Error loading images %s\n", SDL_GetError());
    }
    return optimizedImage;
}

void clean_up()
{
    SDL_FreeSurface(image);
    SDL_FreeSurface(hello);
    SDL_FreeSurface(screen);
    SDL_FreeSurface(menu1);
    SDL_FreeSurface(menu2);
    SDL_FreeSurface(menu3);
    SDL_FreeSurface(menu1Hover);
    SDL_FreeSurface(menu2Hover);
    SDL_FreeSurface(menu3Hover);
    SDL_FreeSurface(background);
    Mix_FreeChunk(scratch);
    Mix_FreeChunk(high);
    Mix_FreeChunk(med);
    Mix_FreeChunk(low);
    Mix_FreeMusic(music);
    TTF_CloseFont(font);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
}

bool load_files()
{
    background = load_image("assets/jpg/1.jpg", 0);
    hello = load_image("assets/bmp/hello.bmp", 0);
    buttons = load_image("assets/png/restart.png", 0);
    if (background == NULL)
        return false;
    if (hello == NULL)
        return false;
    return true;
}

bool init()
{
    if (SDL_Init(SDL_INIT_AUDIO || SDL_INIT_VIDEO) == -1)
    {
        printf("SDL init error %s ", SDL_GetError());
        return false;
    }
    if ((screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
    {
        printf("SDL video mode error %s", SDL_GetError());
        return false;
    }
    SDL_WM_SetCaption("Esprit Projet Jeu Video", "Esprit Projet Jeu Video");
    if (TTF_Init() == -1)
    {
        return false;
    }
    return true;
}

void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(source, clip, destination, &offset);
}

SDL_Surface *generateFontSurface(char file[50], int size, char text[50], SDL_Color color)
{
    font = TTF_OpenFont("assets/ttf/ARCADECLASSIC.TTF", size);
    SDL_Surface *surfaceText = TTF_RenderText_Blended(font, text, color);
    TTF_CloseFont(font);
    return surfaceText;
}

void initBg(SDL_Surface *screen, SDL_Surface *background)
{
    apply_surface(0, 0, background, screen, NULL);
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

void loadMenuFiles()
{
    menu1 = load_image("assets/png/new.png", 1);
    menu2 = load_image("assets/png/settings.png", 1);
    menu3 = load_image("assets/png/exit.png", 1);
    menu1Hover = load_image("assets/png/new_hover.png", 1);
    menu2Hover = load_image("assets/png/settings_hover.png", 1);
    menu3Hover = load_image("assets/png/exit_hover.png", 1);
}

void initMenu(int menuSelect)
{
    if (menuSelect == 0)
    {
        apply_surface((SCREEN_WIDTH - menu1Hover->w) / 2, 100, menu1Hover, screen, NULL);
        apply_surface((SCREEN_WIDTH - menu2->w) / 2, 200, menu2, screen, NULL);
        apply_surface((SCREEN_WIDTH - menu3->w) / 2, 300, menu3, screen, NULL);
    }
    if (menuSelect == 1)
    {
        apply_surface((SCREEN_WIDTH - menu1->w) / 2, 100, menu1, screen, NULL);
        apply_surface((SCREEN_WIDTH - menu2Hover->w) / 2, 200, menu2Hover, screen, NULL);
        apply_surface((SCREEN_WIDTH - menu3->w) / 2, 300, menu3, screen, NULL);
    }
    if (menuSelect == 2)
    {
        apply_surface((SCREEN_WIDTH - menu1->w) / 2, 100, menu1, screen, NULL);
        apply_surface((SCREEN_WIDTH - menu2->w) / 2, 200, menu2, screen, NULL);
        apply_surface((SCREEN_WIDTH - menu3Hover->w) / 2, 300, menu3Hover, screen, NULL);
    }
}

bool loadMusic()
{
    SDL_Init(SDL_INIT_AUDIO);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    {
        printf("%s", Mix_GetError());
    }
    Mix_AllocateChannels(32);
    scratch = Mix_LoadWAV("beat.wav");
    high = Mix_LoadWAV("assets/wav/high.wav");
    med = Mix_LoadWAV("assets/wav/medium.wav");
    low = Mix_LoadWAV("assets/wav/low.wav");
    Mix_PlayChannel(1, scratch, 0);
    Mix_PlayChannel(1, high, 0);
    Mix_PlayChannel(1, med, 0);
    Mix_PlayChannel(1, low, 0);
    music = Mix_LoadMUS("assets/mp3/beep.mp3");
    return true;
}