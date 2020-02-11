#include "utils.h"

#include <math.h>

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

Level Scene = MAIN_MENU;

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
    if (font == NULL)
    {
        TTF_CloseFont(font);
    }
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
}

int load_files()
{
    background = load_image("assets/jpg/1.jpg", 0);
    hello = load_image("assets/bmp/hello.bmp", 0);
    buttons = load_image("assets/png/restart.png", 0);
    if (background == NULL)
        return 0;
    if (hello == NULL)
        return 0;
    return 1;
}

int init()
{

    SDL_Init(SDL_INIT_VIDEO);
    if (SDL_Init(SDL_INIT_AUDIO || SDL_INIT_VIDEO) == -1)
    {
        printf("SDL init error %s ", SDL_GetError());
        return 0;
    }
    const SDL_VideoInfo *videoInformation = SDL_GetVideoInfo();
    fullscreenHeight = videoInformation->current_h;
    fullscreenWidth = videoInformation->current_w;
    printf("%d %d ", fullscreenHeight, fullscreenWidth);

    if ((screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_RESIZABLE | SDL_DOUBLEBUF)) == NULL)
    {
        printf("SDL video mode error %s", SDL_GetError());
        return 0;
    }
    SDL_WM_SetCaption("Esprit Projet Jeu Video", "Esprit Projet Jeu Video");
    if (TTF_Init() == -1)
    {
        printf("TTF Init Failed");
        return 0;
    }
    return 1;
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
    menu1 = load_image("assets/png/buttons/ng_ns.png", 0);
    menu2 = load_image("assets/png/buttons/s_ns.png", 0);
    menu3 = load_image("assets/png/buttons/q_ns.png", 0);
    menu1Hover = load_image("assets/png/buttons/ng_h.png", 0);
    menu2Hover = load_image("assets/png/buttons/s_h.png", 0);
    menu3Hover = load_image("assets/png/buttons/q_h.png", 0);
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

int loadMusic()
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
    music = Mix_LoadMUS("assets/mp3/song.mp3");

    if (Mix_PlayingMusic() == 0)
    {
        if (Mix_PlayMusic(music, -1) == -1)
        {
            return 1;
        }
    }
    return 1;
}

void loadAnimationFile(int frame)
{
    char filePath[50];
    sprintf(filePath, "assets/animation/%d.png", frame);
    SDL_FreeSurface(background);
    background = load_image(filePath, 0);
}

int initAll()
{
    if (init() == 0 || load_files() == 0 || loadMusic() == 0)
    {
        printf("Initialization Failed \n %s ", SDL_GetError());
        return -1;
    }
    loadMenuFiles();
    Mix_Volume(-1, musicVolume);
    Mix_VolumeMusic(musicVolume);
}

void frameLimiter(Uint32 start_time)
{
    SDL_Flip(screen);
    if ((1000 / FPS) > (SDL_GetTicks() - start_time))
        SDL_Delay((1000 / FPS) - (SDL_GetTicks() - start_time));
    frame++;
    if (frame == 581)
    {
        frame = 1;
    }
}