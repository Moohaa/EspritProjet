#include "utils.h"

int main(int argc, char *args[])
{
    bool quit = false;
    if (init() == false || load_files() == false)
    {
        return 1;
    }

    //Apply the background to the screen
    apply_surface(0, 0, background, screen);
    apply_surface(320, 0, background, screen);
    apply_surface(0, 240, background, screen);
    apply_surface(320, 240, background, screen);
    apply_surface(180, 140, hello, screen);
    color.b = 255;

    SDL_Surface *text = generateFontSurface("assets/ttf/ARCADECLASSIC.TTF", 32, "Hello", color);
    apply_surface(0, 0, text, screen);

    SDL_Flip(SDL_GetVideoSurface());
    //While the user hasn't quit
    while (quit == false)
    {
        //While there's an event to handle
        while (SDL_PollEvent(&event))
        { //If the user has Xed out the window
            if (event.type == SDL_QUIT)
            {
                //Quit the program
                quit = true;
            }
        }
    }
    clean_up();
    return 0;
}