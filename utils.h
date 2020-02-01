#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_timer.h"

#include "defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Surfaces and Ressources as global Variables
extern SDL_Surface *hello;
extern SDL_Surface *screen;
extern SDL_Surface *message;
extern SDL_Surface *background;
extern SDL_Surface *image;
extern SDL_Event event;
extern TTF_Font *font;
extern Menu menu;
extern MenuElement menuElement;
extern SDL_Color color;

void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination);
bool init();
bool load_files();
void clean_up();
SDL_Surface *load_image(char filename[]);
SDL_Surface *generateFontSurface(char file[], int size, char text[], SDL_Color color);