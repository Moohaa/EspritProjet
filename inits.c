/**
* @file inits.c
* @brief  initialisation functions implementation 
* @author Creative Sparks
* @version 2.0
* @date 2020
*
*
*/

#include "utils.h"
#include "inits.h"

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
    gameBackground = load_image("assets/back.png", 0);
    gameBackgroundMask = load_image("assets/back_m.png", 0);
}

int loadMusic()
{
    SDL_Init(SDL_INIT_AUDIO);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
        printf("%s", Mix_GetError());
    Mix_AllocateChannels(32);

    click = Mix_LoadWAV("assets/wav/click.wav");
    fullscreenSound = Mix_LoadWAV("assets/wav/fullscreenSound.wav");
    switcher = Mix_LoadWAV("assets/wav/switcher.wav");

    Mix_PlayChannel(1, click, 0);
    Mix_PlayChannel(1, fullscreenSound, 0);
    Mix_PlayChannel(1, switcher, 0);
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
    sprintf(filePath, "newanjpg/%d.jpg", frame);
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
    newGameButton = load_image("assets/menu/b_ns.png", 0);
    settingsButton = load_image("assets/menu/b_ns.png", 0);
    quitButton = load_image("assets/menu/b_ns.png", 0);
}

void initMenu(int menuSelect)
{
    if (menuSelect == 0)
    {
        text1 = generateFontSurface(32, "New Game", selected);
        text2 = generateFontSurface(32, "Settings", n_selected);
        text3 = generateFontSurface(32, "Quit", n_selected);
    }
    else if (menuSelect == 1)
    {
        text1 = generateFontSurface(32, "New Game", n_selected);
        text2 = generateFontSurface(32, "Settings", selected);
        text3 = generateFontSurface(32, "Quit", n_selected);
    }
    else if (menuSelect == 2)
    {
        text1 = generateFontSurface(32, "New Game", n_selected);
        text2 = generateFontSurface(32, "Settings", n_selected);
        text3 = generateFontSurface(32, "Quit", selected);
    }
    SDL_Surface *menuText = generateFontSurface(32, "Menu", n_selected);
    apply_surface(20, newGameButton->h * 0.10, text1, newGameButton, NULL);
    apply_surface(35, newGameButton->h * 0.10, text2, settingsButton, NULL);
    apply_surface(55, newGameButton->h * 0.10, text3, quitButton, NULL);

    apply_surface(MENU_POS_W, MENU_POS_H, menuBackground, screen, NULL);
    apply_surface(INFO_POS_W, INFO_POS_H, infoBar, screen, NULL);
    apply_surface(INFO_POS_W + 75, INFO_POS_H + 5, menuText, screen, NULL);

    apply_surface((SCREEN_WIDTH - newGameButton->w) / 2, (MENU_POS_H) + 125, newGameButton, screen, NULL);
    apply_surface((SCREEN_WIDTH - newGameButton->w) / 2, (MENU_POS_H) + 250, settingsButton, screen, NULL);
    apply_surface((SCREEN_WIDTH - newGameButton->w) / 2, (MENU_POS_H) + 375, quitButton, screen, NULL);
}

void initSetting(int menuSelect)
{

    if (menuSelect == 0)
    {
        modeText = generateFontSurface(32, "Mode", selected);
        fullScreenText = generateFontSurface(32, "Fullscreen", selected);
        windowedText = generateFontSurface(32, "Windowed", selected);
        volumeText = generateFontSurface(32, "Volume", n_selected);
        exitText = generateFontSurface(32, "return", n_selected);
    }
    else if (menuSelect == 1)
    {
        modeText = generateFontSurface(32, "Mode", n_selected);
        fullScreenText = generateFontSurface(32, "Fullscreen", n_selected);
        windowedText = generateFontSurface(32, "Windowed", n_selected);
        volumeText = generateFontSurface(32, "Volume", selected);
        exitText = generateFontSurface(32, "return", n_selected);
    }
    else if (menuSelect == 2)
    {
        modeText = generateFontSurface(32, "Mode", n_selected);
        fullScreenText = generateFontSurface(32, "Fullscreen", n_selected);
        windowedText = generateFontSurface(32, "Windowed", n_selected);
        volumeText = generateFontSurface(32, "Volume", n_selected);
        exitText = generateFontSurface(32, "return", selected);
    }

    apply_surface(MENU_POS_W, MENU_POS_H, menuBackground, screen, NULL);
    apply_surface(INFO_POS_W, INFO_POS_H, infoBar, screen, NULL);
    apply_surface(INFO_POS_W + 61, INFO_POS_H + 5, settingsText, screen, NULL);

    apply_surface(MENU_POS_W + 65, MENU_POS_H + 150, modeText, screen, NULL);
    apply_surface(MENU_POS_W + 65, MENU_POS_H + 250, volumeText, screen, NULL);

    if (fullscreen == 0)
    {
        apply_surface(MENU_POS_W + 175, MENU_POS_H + 150, fullScreenText, screen, NULL);
    }
    else
    {
        apply_surface(MENU_POS_W + 175, MENU_POS_H + 150, windowedText, screen, NULL);
    }
    apply_surface(MENU_POS_W + 175, MENU_POS_H + 270, volumeSelector, screen, NULL);
    apply_surface(MENU_POS_W + 150, MENU_POS_H + 375, exitText, screen, NULL);

    char volumeChar[20];
    sprintf(volumeChar, "%d %%", musicVolume);
    volumeSurface = generateFontSurface(20, volumeChar, n_selected);
    int x = MENU_POS_W + 175;
    int y = x + volumeSelector->w;
    float step = (float)(((float)y - (float)x) / 100);
    apply_surface(MENU_POS_W + 175 + (step * musicVolume), MENU_POS_H + 255, volumeBar, screen, NULL);
    apply_surface(MENU_POS_W + 225, MENU_POS_H + 290, volumeSurface, screen, 0);
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
    menuBackground = load_image("assets/menu/bgm.png", 0);
    infoBar = load_image("assets/menu/ttlbar.png", 0);
    volumeSelector = load_image("assets/menu/bar.png", 0);
    volumeBar = load_image("assets/menu/l_bar.png", 0);
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
    selected.r = 255;
    selected.g = 255;
    selected.b = 0;
    n_selected.r = 0;
    n_selected.g = 0;
    n_selected.b = 0;

    return 1;
}
