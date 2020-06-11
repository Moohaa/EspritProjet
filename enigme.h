/**
* @file enigme.h
* @brief riddle struct and function prototypes
* @author Creative Sparks
* @version 2.0
* @date 2020
*
*
*/

#include "defs.h"
#include "utils.h"

/**
* @struct enigme
* @brief struct for riddles
*/

typedef struct enigme
{
    int type; // 0 dynamique ; 1 Statique
    char question[60];
    char reponses[4][60];
    char reponse;
    int reponseInt;
    int a;
    int b;
    SDL_Surface *enigme;
    int startTicks;
} Enigme;

void afficherEnigme(Enigme enigme, SDL_Surface *screen);
Enigme generateEnigme(int type);
Enigme loadRandomEnigmeFile();

int randomEnigmeType();
void afficherReponseEnigme(Enigme enigme, SDL_Surface *screen);
int EnigmePipeline();