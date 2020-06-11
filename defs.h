/**
* @file defs.h
* @brief global variables definitions
* @author Creative Sparks
* @version 2.0
* @date 2020
*
*
*/

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_timer.h"
#include "SDL/SDL_audio.h"
#include "SDL/SDL_rotozoom.h"

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
#define MAP 2
#define LEVEL1 3
#define LEVEL2 4
#define LEVEL3 5
#define LEVEL4 6
#define ENIGMEDYN 7
#define ENIGMESTATIQUE 8

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
extern SDL_Surface *volumeBar;
extern SDL_Surface *volumeSelector;

extern int seconds;

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
extern int mouseX;
extern int mouseY;

extern int playState;

extern SDL_Surface *volumeSurface;
extern SDL_Surface *windowState;
extern char windowStateChar[15];

extern int fullscreenWidth;
extern int fullscreenHeight;

extern SDL_Surface *newGameButton;
extern SDL_Surface *settingsButton;
extern SDL_Surface *quitButton;

extern SDL_Surface *animation;

extern int FPS;
extern int frame;
extern int quit;
extern int menuSelect;

extern SDL_Surface *screen;
extern SDL_Surface *background;

extern Mix_Chunk *click;
extern Mix_Chunk *switcher;
extern Mix_Chunk *fullscreenSound;

extern int settingsState;
extern int volumeSlider;

extern SDL_Surface *text1;
extern SDL_Surface *text2;
extern SDL_Surface *text3;

extern SDL_Surface *settingsText;
extern SDL_Surface *modeText;
extern SDL_Surface *fullScreenText;
extern SDL_Surface *windowedText;
extern SDL_Surface *volumeText;
extern SDL_Surface *exitText;

extern int keyPressed;

extern Uint32 next_time;
extern int inits;

extern SDL_Surface *gameBackground;
extern SDL_Surface *gameBackgroundMask;

extern int offsetBG;
extern int score;
extern int vies;

extern int offsetBG2;
extern int score2;
extern int vies2;

extern SDL_Surface *enigmeTempImage;
extern int gameplayStartTick;

extern SDL_Surface *minimap;
extern SDL_Surface *minimapIcon;
extern int posXminimapIcon;
extern int posYminimapIcon;

extern SDL_Surface *selectionText1;
extern SDL_Surface *selectionText2;
extern SDL_Surface *selectionText3;
extern SDL_Surface *selectionText4;
extern SDL_Surface *selectionText5;
extern SDL_Surface *selectionText6;
extern SDL_Surface *selectionText7;

extern int gameSelector;

extern int modelSelected;
extern int chosenMode;
extern int inSaveMenu;
extern int saveMenuSelector;
extern int selectedSaveMenu;
