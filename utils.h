#include "defs.h"

//Surfaces and Ressources as global Variables
extern SDL_Surface *hello;
extern SDL_Surface *screen;
extern SDL_Surface *message;
extern SDL_Surface *background;
extern SDL_Surface *image;
extern SDL_Event event;
extern TTF_Font *font;
extern SDL_Color color;
extern SDL_Surface rect;

extern SDL_Surface *menu1;
extern SDL_Surface *menu2;
extern SDL_Surface *menu3;
extern SDL_Surface *menu1Hover;
extern SDL_Surface *menu2Hover;
extern SDL_Surface *menu3Hover;

extern Level scene;

extern int fxVolume;
extern int musicVolume;
extern SDL_Surface *volume;

extern bool fullscreen;

extern SDL_Surface *buttons;
extern Mix_Music *music;
extern Mix_Chunk *scratch;
extern Mix_Chunk *high;
extern Mix_Chunk *med;
extern Mix_Chunk *low;

extern int fullscreenWidth;
extern int fullscreenHeight;

void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip);
bool init();
bool load_files();
void clean_up();
SDL_Surface *load_image(char filename[], int colorKey);
SDL_Surface *generateFontSurface(char file[], int size, char text[], SDL_Color color);
void initBg(SDL_Surface *screen, SDL_Surface *background);
Uint32 time_left();
void initMenu(int menuSelect);
void loadMenuFiles();
bool loadMusic();