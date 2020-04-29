/**
* @file utils.h
* @brief many utilities and helper functions
* @author Creative Sparks
* @version 2.0
* @date 2020
*
* Functions that simplify SDL default functions and other function used by the game 
*
*/

#include "defs.h"

void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip);
void frameLimiter(Uint32 start_time);
SDL_Surface *load_image(char filename[], int colorKey);
SDL_Surface *generateFontSurface(int size, char text[], SDL_Color color);
Uint32 time_left();
void renderFrame(State state);
void menuHandler(SDL_Event event, int state);

void renderGameFrame();
void gameHandler(SDL_Event event, int state);
SDL_Color GetPixel(SDL_Surface *pSurface, int x, int y);