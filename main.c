#include "utils.h"

int main(int argc, char *args[])
{
    int FPS = 60;
    SDL_Init(SDL_INIT_VIDEO);
    musicVolume = 100;
    bool quit = false;
    int menuSelect = 0;
    if (init() == false || load_files() == false || loadMusic() == false)
    {
        printf("Initialization Failed \n %s ", SDL_GetError());
        return -1;
    }
    color.b = 255;
    loadMenuFiles();
    while (!quit)
    {
        Uint32 start_time = SDL_GetTicks();
        if (SDL_WaitEvent(&event) != 0)
        {
            initBg(screen, background);
            initMenu(menuSelect);
            char volumeChar[4];
            sprintf(volumeChar, "%d", musicVolume);
            volumeSurface = generateFontSurface("", 100, volumeChar, color);
            //windowState = generateFontSurface("", 100, fullscreen, color);
            apply_surface(100, 50, volumeSurface, screen, NULL);
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                Mix_PlayChannel(-1, low, 0);
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_RETURN:
                    Mix_PlayChannel(-1, med, 0);
                    if (menuSelect == 2)
                        quit = true;
                    break;
                case SDLK_BACKSPACE:
                    break;
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                case SDLK_d:
                    if (fullscreen == false)
                    {
                        screen = SDL_SetVideoMode(fullscreenWidth, fullscreenHeight, SCREEN_BPP, SDL_HWSURFACE | SDL_FULLSCREEN | SDL_DOUBLEBUF);
                    }
                    else
                    {
                        SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_DOUBLEBUF);
                    }
                    fullscreen = !fullscreen;
                    strcmp(windowStateChar, "Windowed") ? strcpy(windowStateChar, "Fullscreen") : "Windowed";
                    printf(windowStateChar);
                    break;
                case SDLK_UP:
                    Mix_PlayChannel(-1, high, 0);
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
            SDL_Flip(screen);
            if ((1000 / FPS) > (SDL_GetTicks() - start_time))
                SDL_Delay((1000 / FPS) - (SDL_GetTicks() - start_time));
        }
    }
    clean_up();
    return 0;
}
