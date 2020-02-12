#include "utils.h"
#include "inits.h"

int main()
{
    if (!initAll())
        return 0;
    while (!quit)
    {
        Uint32 start_time = SDL_GetTicks();
        renderFrame(1);
        SDL_PollEvent(&event);
        menuHandler(event);
        frameLimiter(start_time);
    }
    clean_up();
    return 0;
}
