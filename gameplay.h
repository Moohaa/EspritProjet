#include "defs.h"
#include "personnage.h"

void afficherPersonnage(Personnage personnage, SDL_Surface *screen);
void afficherEntitiesSecondaires();
int collisionDetection(Personnage personnage);
int boundingBoxCollision(SDL_Rect a, SDL_Rect b);
int perfectPixelCollision(SDL_Rect a, int x, int y);
void collisionHandler();
void initGameplay();
void gameplayPipeline();