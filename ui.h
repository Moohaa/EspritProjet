#include "defs.h"

typedef struct ui
{
    int life;
    int timer;
    int score;
    int level;
    int x;
    int y;
    int w;
    int h;
    SDL_Color color;
} UI;

void showUI(UI ui, SDL_Surface *screen);
UI initTimer(SDL_Surface timer);
UI updateScore(UI ui, int score);
UI updateLife(UI ui, int life);
UI initUI();
SDL_Surface *generateSurfaces(UI ui);