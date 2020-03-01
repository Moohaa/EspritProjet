#include "ui.h"
#include "utils.h"
UI initUI()
{
    UI ui;
    ui.x = SCREEN_HEIGHT * 0.90;
    ui.y = 0;
    ui.w = SCREEN_WIDTH;
    ui.h = SCREEN_HEIGHT * 0.10;
    ui.level = 1;
    ui.life = 100;
    ui.score = 0;
    return ui;
}

void showUI(UI ui, SDL_Surface *screen)
{
    apply_surface(ui.x, ui.h, generateSurfaces(ui), screen, NULL);
}

UI updateScore(UI ui, int score)
{
    ui.score = score;
    return ui;
}
UI updateLife(UI ui, int life)
{
    ui.life = life;
    return ui;
}

SDL_Surface *generateSurfaces(UI ui)
{
    SDL_Surface *temp;
    return temp;
}