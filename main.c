#include "utils.h"

int main(int argc, char *args[])
{
    int FPS = 50;
    bool quit = false;
    int menuSelect = 0;
    if (init() == false || load_files() == false || loadMusic() == false)
    {
        printf("Initialization Failed \n %s ", SDL_GetError());
        return -1;
    }
    loadMenuFiles();
    while (!quit)
    {
        Uint32 start_time = SDL_GetTicks();
        if (SDL_WaitEvent(&event) != 0)
        {
            initBg(screen, background);
            initMenu(menuSelect);
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
                        screen = SDL_SetVideoMode(1920, 1080, SCREEN_BPP, SDL_HWSURFACE | SDL_FULLSCREEN | SDL_DOUBLEBUF);
                    else
                        SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_DOUBLEBUF);
                    fullscreen = !fullscreen;
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
