#include "defs.h"
#include "personnage.h"
#include "enigme.h"

extern Personnage personnage;

void afficherPersonnage(Personnage personnage, SDL_Surface *screen);
void afficherEntitiesSecondaires();
void gameplayPipeline();
int collisionDetection(Personnage personnage);
int boundingBoxCollision(SDL_Rect a, SDL_Rect b);
int perfectPixelCollision(SDL_Rect a, int x, int y);
void collisionHandler();
void initGameplay();