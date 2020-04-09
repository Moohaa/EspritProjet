#include "enigme.h"

void afficherEnigme(Enigme enigme, SDL_Surface *screen)
{
    int a = rand() % 10 + rand() % 10;
    int b = rand() % 10 + rand() % 10;
    int c = rand() % 10 + rand() % 10;

    SDL_Surface *enigmeBackground;
    SDL_Surface *question;
    SDL_Surface *question2;
    SDL_Surface *question3;
    SDL_Surface *reponse;

    char enigmeQuestion[30];
    char enigmeQuestion1[30];
    char enigmeQuestion2[30];
    char enigmeReponses[10] = "1  2  3  4";

    SDL_FillRect(enigmeBackground, NULL, SDL_MapRGB(screen->format, 255, 0, 0));

    sprintf(enigmeQuestion, "Combien font %d + %d ?", enigme.a, enigme.b);
    sprintf(enigmeQuestion1, "1 : %d  | 2 : %d", a, b);
    sprintf(enigmeQuestion2, "3 : %d  | 4 : %d", c, enigme.reponse);

    question = generateFontSurface(32, enigmeQuestion, selected);
    question2 = generateFontSurface(32, enigmeQuestion1, selected);
    question3 = generateFontSurface(32, enigmeQuestion2, selected);
    apply_surface(100, 200, question, enigmeBackground, NULL);
    apply_surface(100, 200, question2, enigmeBackground, NULL);
    apply_surface(100, 200, question3, enigmeBackground, NULL);
    apply_surface(0, 0, enigmeBackground, screen, NULL);
    SDL_Flip(screen);
}

Enigme generateEnigme(int type)
{
    Enigme enigme;
    if (type == 0)
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
    Enigme enigme;
    enigme.type = 1;
    int a = rand() % 5;
    char filePath[50];
    sprintf(filePath, "assets/enigmes/%d.png", a);
    enigme.enigme = load_image(filePath, NULL);
    return enigme;
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
                printf(" //reponse : %d / continueEnigme %d ", reponse, continueEnigme);
                reponse = 1;
                break;
            case (SDLK_2):
                printf(" //reponse : %d / continueEnigme %d ", reponse, continueEnigme);
                reponse = 2;
                break;
            case (SDLK_3):
                printf(" //reponse : %d / continueEnigme %d ", reponse, continueEnigme);
                reponse = 3;
                break;
            case (SDLK_4):
                printf(" //reponse : %d / continueEnigme %d ", reponse, continueEnigme);
                reponse = 4;
                break;
            case (SDLK_RETURN):
                printf(" //reponse : %d / continueEnigme %d ", reponse, continueEnigme);
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

void enigmeFalse()
{
    SDL_Surface *loseString = generateFontSurface(32, "La reponse est fausse", selected);
}

void enigmeTrue()
{

    SDL_Surface *winString = generateFontSurface(32, "La reponse est correcte", selected);
}

void EnigmePipeline()
{
    Enigme enigme;
    enigme = generateEnigme(0);
    afficherEnigme(enigme, screen);
    int reponse = enigmeEventHandler(enigme, 0);
    switch (enigme.type)
    {
    case 0: // GENERATE
        if (reponse == 4)
        {
            enigmeTrue();
        }
        else
        {
            enigmeFalse();
        }
        break;
    case 1: ///  FICHIER
        if (reponse == 4)
        {
            enigmeTrue();
        }
        else
        {
            enigmeFalse();
        }

    default:
        break;
    }
}