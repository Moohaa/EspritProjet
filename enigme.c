#include "enigme.h"

void afficherEnigme(Enigme enigme, SDL_Surface *screen)
{
    int a = rand() % 10 + rand() % 10;
    int b = rand() % 10 + rand() % 10;
    int c = rand() % 10 + rand() % 10;

    SDL_Surface *enigmeBackground;
    SDL_Surface *question;
    SDL_Surface *reponse;
    SDL_Surface *question2;
    SDL_Surface *question3;
    SDL_Surface *questionReponses;

    char enigmeQuestion[30];
    char enigmeQuestion1[30];
    char enigmeQuestion2[30];
    char enigmeReponses[10] = "1  2  3  4";

    SDL_FillRect(enigmeBackground, NULL, SDL_MapRGB(screen->format, 255, 0, 0));

    sprintf(enigmeQuestion, "Combien font %d + %d ?", enigme.a, enigme.b);
    question = generateFontSurface(32, enigmeQuestion, selected);
    sprintf(enigmeQuestion1, "1 : %d  | 2 : %d", a, b);
    sprintf(enigmeQuestion2, "3 : %d  | 4 : %d", c, enigme.reponse);

    question2 = generateFontSurface(32, enigmeQuestion1, selected);
    question3 = generateFontSurface(32, enigmeQuestion2, selected);
    questionReponses = generateFontSurface(32, enigmeReponses, selected);
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

int enigmeEventHandler(Enigme enigme, int type)
{
    int reponse = -1;
    int continueEnigme = 1;
    while (continueEnigme)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case (SDLK_1):
                reponse = 1;
                break;
            case (SDLK_2):
                reponse = 2;
                break;
            case (SDLK_3):
                reponse = 3;
                break;
            case (SDLK_4):
                reponse = 4;
                break;
            case (SDLK_RETURN):
                continueEnigme = 0;
                return reponse;
                break;
            }
            break;
        default:
            break;
        }
    }
}

void EnigmePipeline()
{
    Enigme enigme;
    enigme = generateEnigme(1);
    afficherEnigme(enigme, screen);
    int reponse = enigmeEventHandler(enigme, 1);
    switch (enigme.type)
    {
    case 1: // GENERATE

        break;
    case 0: ///  FICHIER

    default:
        break;
    }
}