//Boolean for clarity
typedef int bool;
#define false 0
#define true 1

//The attributes of the screen
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP 32

typedef struct menu Menu;
typedef struct menuElement MenuElement;

typedef int Level;
#define MAIN_MENU 0;
#define SETTINGS 1;
#define MAP 2;
#define LEVEL1 3;

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_timer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
