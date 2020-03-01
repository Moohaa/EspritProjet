#include "defs.h"
#include "utils.h"

typedef struct enigme
{
    int type;
    char question[60];
    char reponses[4][60];
    char reponse;
    int reponseInt;
    int a;
    int b;
    SDL_Surface *background;
    SDL_Surface *enigme;

} Enigme;

void afficherEnigme(Enigme enigme, SDL_Surface *screen);
Enigme generateEnigme(int type);
Enigme loadRandomEnigmeFile();
int randomEnigmeType();

int randomEnigmeType();
void afficherReponseEnigme(Enigme enigme, SDL_Surface *screen);