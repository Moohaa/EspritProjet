/**
* @file main.c
* @brief main program file.
* @author Creative Sparks
* @version 2.0
* @date 2020
*
* main program 
*
*/

#include "utils.h"
#include "inits.h"

int FilterEvents(const SDL_Event *event)
{
    if (event->type == SDL_MOUSEMOTION)
    {
        mouseX = event->motion.x;
        mouseY = event->motion.y;
        return (0);
    }
    return (1);
}
int main()

{
    if (!initAll())
        return 0;
    Mix_PlayMusic(music, -1);
    SDL_SetEventFilter(FilterEvents);
    while (!quit)
    {
        Uint32 start_time = SDL_GetTicks();
        renderFrame(1);
        SDL_PollEvent(&event);
        menuHandler(event, settingsState);
        frameLimiter(start_time);
    }
    clean_up();

    return 0;
}
