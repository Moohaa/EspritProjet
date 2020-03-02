#include "enigme.h"

void afficherEnigme(Enigme enigme, SDL_Surface *screen)
{
    SDL_Surface *enigmeBackground;
    SDL_Surface *question;
    SDL_Surface *reponse;
    SDL_Surface *question2;
    SDL_Surface *question3;

    char enigmeQuestion[30];
    char enigmeQuestion1[30];
    char enigmeQuestion2[30];
    sprintf(enigmeQuestion, "Combien font %d + %d ?", enigme.a, enigme.b);
    question = generateFontSurface(32, enigmeQuestion, selected);
    int a = rand() % 10 + rand() % 10;
    int b = rand() % 10 + rand() % 10;
    int c = rand() % 10 + rand() % 10;
    sprintf(enigmeQuestion1, "1 : %d  | 2 : %d", a, b);
    sprintf(enigmeQuestion2, "3 : %d  | 4 : %d", c, enigme.reponse);
    generateFontSurface(32, enigmeQuestion1, selected);
    generateFontSurface(32, enigmeQuestion2, selected);
    question2 = generateFontSurface(32, enigmeQuestion1, selected);
    question3 = generateFontSurface(32, enigmeQuestion2, selected);
}

Enigme generateEnigme(int type)
{
    Enigme enigme;
    if (type = 0)
    {
        int a = rand() % 10;
        int b = rand() % 10;
        enigme.a = a;
        enigme.b = b;
        enigme.reponseInt = a + b;
        return enigme;
    }
    else
    {
        return loadRandomEnigmeFile();
    }
}
Enigme loadRandomEnigmeFile()
{
}

int randomEnigmeType()
{
    return rand() % 2;
}