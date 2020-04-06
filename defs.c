#include "defs.h"

SDL_Surface *hello;
SDL_Surface *screen;
SDL_Surface *message;
SDL_Surface *background;
SDL_Surface *image;
SDL_Event event;
TTF_Font *font;
SDL_Color color;
SDL_Surface *buttons;
Uint32 next_time;
int fullscreen = 0;
SDL_Surface *volumeSurface;
SDL_Surface *windowState;

SDL_Surface *volumeBar;
SDL_Surface *volumeSelector;

SDL_Surface *menuBackground;
SDL_Surface *menuButtonNormalState;
SDL_Surface *menuButtonClickedState;
SDL_Surface *infoBar;
SDL_Surface *slider;
SDL_Surface *sliderBar;

int mouseX;
int mouseY;

char windowStateChar[15] = "Windowed";

SDL_Surface *menu1;
SDL_Surface *menu2;
SDL_Surface *menu3;
SDL_Surface *menu1Hover;
SDL_Surface *menu2Hover;
SDL_Surface *menu3Hover;

SDL_Surface *newGameButton;
SDL_Surface *settingsButton;
SDL_Surface *quitButton;

int fxVolume = 100;
SDL_VideoInfo *info;

int playState = 0;

int seconds = 0;

State state = MAIN_MENU;

SDL_Color selected;
SDL_Color n_selected;

SDL_Surface *settingsText;
SDL_Surface *modeText;
SDL_Surface *fullScreenText;
SDL_Surface *windowedText;
SDL_Surface *volumeText;
SDL_Surface *exitText;

Mix_Music *music;
Mix_Chunk *click;
Mix_Chunk *switcher;
Mix_Chunk *fullscreenSound;

SDL_Surface *animation;

int fullscreenWidth = 0;
int fullscreenHeight = 0;

SDL_Surface *text1;
SDL_Surface *text2;
SDL_Surface *text3;

int FPS = 30;
int musicVolume = 50;
int frame = 1;
int quit = 0;
int menuSelect = 0;

int keyPressed = 0;
int settingsState = 0;
int volumeSlider = 0;

int score = 0;