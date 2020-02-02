#include "utils.h"

int main(int argc, char *args[])
{
    bool quit = false;
    if (init() == false || load_files() == false)
    {
        return 1;
    }

    //Apply the background to the screen
    initBg(screen, background);
    color.b = 255;
    //Clip range for the top left
    clip[0].x = 0;
    clip[0].y = 0;
    clip[0].w = 200;
    clip[0].h = 80;

    //Clip range for the top right
    clip[1].x = 200;
    clip[1].y = 0;
    clip[1].w = 200;
    clip[1].h = 80;

    //Clip range for the bottom left
    clip[2].x = 400;
    clip[2].y = 0;
    clip[2].w = 200;
    clip[2].h = 80;

    //Apply the images to the screen
    apply_surface(-30, 0, buttons, screen, &clip[0]);
    apply_surface(-30, 80, buttons, screen, &clip[1]);
    apply_surface(-30, 160, buttons, screen, &clip[2]);

    SDL_Surface *text = generateFontSurface("assets/ttf/ARCADECLASSIC.TTF", 32, "Hello", color);
    apply_surface(0, 0, text, screen, NULL);

    while (quit == false)
    {
        SDL_Delay(15);
        SDL_Flip(screen);

        if (running == true)
        {
            char time[50];
            sprintf(time, "%d", SDL_GetTicks() - start);
            SDL_Surface *seconds = generateFontSurface("", 50, time, color);
            apply_surface((SCREEN_WIDTH - seconds->w) / 2, 50, seconds, screen, NULL);
            SDL_FreeSurface(seconds);
            SDL_FreeSurface(screen);
        }

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                    if (menuSelect != 0)
                    {
                        menuSelect--;
                    }

                    break;
                case SDLK_DOWN:
                    if (menuSelect != 3)
                    {
                        menuSelect++;
                    }
                    break;

                case (SDLK_s):

                    if (running == true)
                    {
                        running = false;
                        start = 0;
                    }
                    else
                    {
                        running = true;
                        start = SDL_GetTicks();
                    }
                }
            }
        }
    }
    clean_up();
    return 0;
}