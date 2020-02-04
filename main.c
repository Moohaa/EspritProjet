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

        while (SDL_PollEvent(&event))
        {
            initBg(screen, background);
            SDL_Delay(33);

            loadMenuFiles();
            initMenu(menuSelect);
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_RETURN:
                    if (menuSelect == 2)
                        quit = true;
                    break;
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
                    break;
                case (SDLK_s):
                    running == false;
                }
                break;
            default:
                break;
            }
            SDL_Flip(screen);
        }
    }
    clean_up();
    return 0;
}
