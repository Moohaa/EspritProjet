#include "utils.h"

int main()
{
    if (!initAll())
        return 0;
    color.b = 255;
    while (!quit)
    {
        Uint32 start_time = SDL_GetTicks();
        if (!playState)
        {
            initBg(screen, background);
        }
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
        SDL_PollEvent(&event);
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
                if (menuSelect == 2)
                {
                    quit = 1;
                }
                if (menuSelect == 0)
                {
                    playState = 1;
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

        frameLimiter(start_time);
    }
    clean_up();
    return 0;
}
