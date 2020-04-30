/**
* @file personnage.h
* @brief charcacter struct and function prototypes
* @author Creative Sparks
* @version 2.0
* @date 2020
*
*
*/

#include "defs.h"
#include "utils.h"

typedef struct personnage
{

    int speed;
    int posX;
    int posY;
    int animationFrame;
    int direction; // 0 : right / 1 : left
    SDL_Surface *currentFrame;
    int model;
    int acceleration;
    int maxSpeed;
    int currentSpeed;
    int resetSpeed;
} Personnage;

extern Personnage personnage;

void affichePersonnage(Personnage personnage, SDL_Surface *background);
Personnage initPersonnage();
Personnage loadSprite(Personnage personnage, int direction);
Personnage setModel(Personnage personngage, int model);