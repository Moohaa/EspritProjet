#include "utils.h"

int main(int argc, char *args[])
{
    int FPS = 30;
    musicVolume = 10;
    int frame = 1;
    bool quit = false;
    int menuSelect = 0;
    if (init() == false || load_files() == false || loadMusic() == false)
    {
        printf("Initialization Failed \n %s ", SDL_GetError());
        return -1;
    }
    color.b = 255;
    loadMenuFiles();
    Mix_Volume(-1, musicVolume);
    Mix_VolumeMusic(musicVolume);
    while (!quit)
    {
        Uint32 start_time = SDL_GetTicks();

        SDL_PollEvent(&event);
        if (!playState)
        {
            initBg(screen, background);
        }
        else
        {
            background = load_image("assets/jpg/2.jpg", NULL);
            initBg(screen, background);
        }
        initMenu(menuSelect);
        loadAnimationFile(frame);
        char volumeChar[20];
        sprintf(volumeChar, "Volume %d", musicVolume);
        volumeSurface = generateFontSurface("", 20, volumeChar, color);
        //windowState = generateFontSurface("", 100, fullscreen, color);
        apply_surface(SCREEN_WIDTH - volumeSurface->w, SCREEN_HEIGHT - volumeSurface->h, volumeSurface, screen, NULL);
        //            printf("W %d WE %d H %d HE %d\n", (SCREEN_WIDTH - menu1->w) / 2,
        //  ((SCREEN_WIDTH - menu1->w) / 2) + menu1->w,
        //(100),
        //((100) + menu1->h));

        switch (event.type)
        {
        case SDL_MOUSEMOTION:
            mouseX = event.motion.x;
            mouseY = event.motion.y;
            if ((mouseX > (SCREEN_WIDTH - menu1->w) / 2) && (mouseX < ((SCREEN_WIDTH - menu1->w) / 2) + menu1->w) && (mouseY > ((100)) && (mouseY > (100)) + menu1->h))
            {
                menuSelect = 0;
            }
            if ((mouseX > (SCREEN_WIDTH - menu2->w) / 2) && (mouseX < ((SCREEN_WIDTH - menu2->w) / 2) + menu2->w) && (mouseY > ((200)) && (mouseY > (200)) + menu2->h))
            {
                menuSelect = 1;
            }
            if ((mouseX > (SCREEN_WIDTH - menu3->w) / 2) && (mouseX < ((SCREEN_WIDTH - menu3->w) / 2) + menu3->w) && (mouseY > ((300)) && (mouseY > (300)) + menu3->h))
            {
                menuSelect = 2;
            }
            printf("x%d y%d\n", mouseX, mouseY);
            break;
        case SDL_QUIT:
            quit = true;
            Mix_PlayChannel(-1, low, 0);
            break;
        case SDL_MOUSEBUTTONDOWN:
            Mix_PlayChannel(-1, med, 0);
            if (menuSelect == 2)
            {
                quit = true;
            }
            if (menuSelect == 0)
            {
                playState = true;
            }
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_RETURN:
                Mix_PlayChannel(-1, med, 0);
                if (menuSelect == 2)
                {
                    quit = true;
                }
                if (menuSelect == 0)
                {
                    playState = true;
                }
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
                //strcmp(windowStateChar, "Windowed") ? strcpy(windowStateChar, "Fullscreen") : "Windowed";
                printf(windowStateChar);
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
        SDL_Flip(screen);
        if ((1000 / FPS) > (SDL_GetTicks() - start_time))
            SDL_Delay((1000 / FPS) - (SDL_GetTicks() - start_time));
        frame++;
        if (frame == 581)
        {
            frame = 1;
        }
    }
    clean_up();
    return 0;
}
