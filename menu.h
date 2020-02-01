#include "SDL/SDL.h"
#include "utils.h"

struct menuElement
{
    SDL_Surface *menuElementNormal;
    SDL_Surface *menuElementHover;
    SDL_Surface *menuElementClick;
    int posX;
    int posY;
    int fontSize;
    char fontPath[50];
    bool selected;
    SDL_Color colorNormal;
    SDL_Color colorHover;
    SDL_Color colorClick;
};

struct menu
{
    MenuElement elements[10];
    int posX;
    int posY;
    int nElements;
};

void initMenu(Menu *menu);
void createMenuElement(MenuElement *menuElement);
void addMenuElements(MenuElement menuElement[10], int n, Menu menu);
