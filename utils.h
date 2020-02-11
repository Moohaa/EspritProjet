#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_timer.h"
#include "SDL/SDL_audio.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP 32

typedef int Level;
#define MAIN_MENU 0;
#define SETTINGS 1
#define MAP 2
#define LEVEL1 3

#define MENU_FONT "assets/ttf/ARCADECLASSIC.TTF"

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
extern int fullscreen;

extern SDL_Surface *buttons;
extern Mix_Music *music;
extern Mix_Chunk *scratch;
extern Mix_Chunk *high;
extern Mix_Chunk *med;
extern Mix_Chunk *low;
extern int mouseX;
extern int mouseY;

extern int playState;

extern SDL_Surface *volumeSurface;
extern SDL_Surface *windowState;
extern char windowStateChar[15];

extern int fullscreenWidth;
extern int fullscreenHeight;

extern SDL_Surface *animation;

extern int FPS;
extern int frame;
extern int quit;
extern int menuSelect;

void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip);
int init();
int load_files();
void clean_up();
SDL_Surface *load_image(char filename[], int colorKey);
SDL_Surface *generateFontSurface(int size, char text[], SDL_Color color);
void initBg(SDL_Surface *screen, SDL_Surface *background);
Uint32 time_left();
void initMenu(int menuSelect);
void loadMenuFiles();
int loadMusic();
void loadAnimationFile(int frame);
int initAll();
void frameLimiter(Uint32 start_time);
