#include "utils.h"

int main(int argc, char *args[])
{
    bool quit = false;
    if (init() == false || load_files() == false)
    {
        printf("Initialization Failed \n");
        return -1;
    }
    menuSelect = 0;

    while (quit == false)
    {
        initBg(screen, background);
        SDL_Delay(33);

        SDL_Surface *text = generateFontSurface("assets/ttf/ARCADECLASSIC.TTF", 32, "Hello", color);
        apply_surface(0, 0, text, screen, NULL);

        if (running == true)
        {
            char time[50];
            sprintf(time, "%d", SDL_GetTicks());
            SDL_Surface *seconds = generateFontSurface("", 50, time, color);
            apply_surface((SCREEN_WIDTH - seconds->w) / 2, 100, seconds, screen, NULL);
        }

        char menuselectchar[10];
        sprintf(menuselectchar, "%d", menuSelect);
        SDL_Surface *menuSelection = generateFontSurface("", 40, menuselectchar, color);
        apply_surface((SCREEN_WIDTH - menuSelection->w) / 2, 50, menuSelection, screen, NULL);
        /*
        loadMenuFiles();
        initMenu(menuSelect);
        */
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                quit = true;
                break;
            case SDLK_UP:
                if (menuSelect != 0)
                    menuSelect--;
                break;
            case SDLK_DOWN:
                if (menuSelect != 2)
                    menuSelect++;
                break; /*
            case (SDLK_s):
                running == false;
            }
            break;*/
            default:
                break;
            }
            SDL_Flip(screen);
        }
        clean_up();
        return 0;
    }
}