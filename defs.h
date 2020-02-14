#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_timer.h"
#include "SDL/SDL_audio.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 720
#define SCREEN_BPP 32

typedef int State;
#define MAIN_MENU 0
#define SETTINGS 1
#define VOLUMESLIDER 2
#define MAP 3
#define LEVEL1 4

#define MENU_FONT "assets/ttf/BMYEONSUNG_ttf.ttf"

extern SDL_Surface *hello;
extern SDL_Surface *message;
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

extern SDL_Surface *menuBackground;
extern SDL_Surface *menuButtonNormalState;
extern SDL_Surface *menuButtonClickedState;
extern SDL_Surface *infoBar;
extern SDL_Surface *slider;
extern SDL_Surface *sliderBar;
extern SDL_Color selected;
extern SDL_Color n_selected;

#define MENU_POS_W (SCREEN_WIDTH - menuBackground->w) / 2
#define MENU_POS_H (SCREEN_HEIGHT - menuBackground->h) / 2
#define INFO_POS_W ((SCREEN_WIDTH - infoBar->w) / 2)
#define INFO_POS_H ((SCREEN_HEIGHT - menuBackground->h) / 2) - (int)(infoBar->h / 2 * 0.5)

extern State state;

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

extern SDL_Surface *screen;
extern SDL_Surface *background;

extern int settingsState;
extern int volumeSlider;