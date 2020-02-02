#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_timer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"

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
extern SDL_Surface rect;
extern SDL_Rect clip[3];
extern int menuSelect;

//The frames per second
extern const int FRAMES_PER_SECOND;
extern int frame;
extern bool cap;
extern bool quit;
extern Uint32 start;
extern bool running;
#define TICK_INTERVAL 30;
extern Uint32 next_time;

extern SDL_Surface *buttons;

void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip);
bool init();
bool load_files();
void clean_up();
SDL_Surface *load_image(char filename[]);
SDL_Surface *generateFontSurface(char file[], int size, char text[], SDL_Color color);
void initBg(SDL_Surface *screen, SDL_Surface *background);
Uint32 time_left();