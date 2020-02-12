#include "defs.h"

//Surfaces and Ressources as global Variables

void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip);
void frameLimiter(Uint32 start_time);
SDL_Surface *load_image(char filename[], int colorKey);
SDL_Surface *generateFontSurface(int size, char text[], SDL_Color color);
Uint32 time_left();
void renderFrame(State state);