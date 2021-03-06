/**
* @file inits.h
* @brief initialization functions for the game
* @author Creative Sparks
* @version 2.0
* @date 2020
*
* initialization functions for the game
* loading game files (images , sound)
*
*/

#include "defs.h"

void initBg(SDL_Surface *screen, SDL_Surface *background);
void initMenu(int menuSelect);
void loadMenuFiles();
void loadAnimationFile(int frame);
void clean_up();
int loadMusic();
int initAll();
int init();
int load_files();
void initSetting(int menuSelect);