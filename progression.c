/*#include "progression.h"

void updateTimer(Values values)
{
    char time[50];
    sprintf(time, "%d", SDL_GetTicks());
    SDL_Surface *seconds = generateFontSurface("", 50, time, color);
    apply_surface((SCREEN_WIDTH - seconds->w) / 2, 100, seconds, screen, NULL);
}*/