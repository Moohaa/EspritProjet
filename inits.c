#include "utils.h"

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

int loadMusic()
{
    SDL_Init(SDL_INIT_AUDIO);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
        printf("%s", Mix_GetError());
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
        return 1;
    }
    if (Mix_PlayMusic(music, -1) == -1)
    {
        return 1;
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

void initBg(SDL_Surface *screen, SDL_Surface *background)
{
    apply_surface(0, 0, background, screen, NULL);
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
