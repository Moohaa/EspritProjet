/**
* @file gameplay.h
* @brief in-game function prototypes
* @author Creative Sparks
* @version 2.0
* @date 2020
*
*
*/

#include "defs.h"
#include "personnage.h"
#include "ennemies.h"

void afficherPersonnage(Personnage personnage, SDL_Surface *screen);
void afficherEntitiesSecondaires();
int collisionDetection(Personnage personnage);
int boundingBoxCollision(SDL_Rect a, SDL_Rect b);
int perfectPixelCollision(Personnage personnage, int x, int y);
void initGameplay();
void moveEnnemies();
void gameplayPipeline();
void gameplayPipelineMulti();
int ennemyVision(Ennemi ennemi);
